/*
 * cmds.cxx
 *
 * Auxiliary commands for OpenAM
 *
 * Copyright (c) 1993-2001 Equivalence Pty. Ltd.
 *
 * The contents of this file are subject to the Mozilla Public License
 * Version 1.0 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See
 * the License for the specific language governing rights and limitations
 * under the License.
 *
 * The Original Code is Portable Windows Library.
 *
 * The Initial Developer of the Original Code is Equivalence Pty. Ltd.
 *
 * Contributor(s): ______________________________________.
 *
 * $Log$
 * Revision 1.9  2004/01/31 07:38:21  rjongbloed
 * Changed HAS_IXJ usage to if defined not if non-zero
 *
 * Revision 1.8  2002/02/03 22:57:22  rogerh
 * Add support for playback and recording on the PSTN line using --port 2
 *
 * Revision 1.7  2002/01/26 00:18:19  robertj
 * Fixed MSVC warnings.
 * Removed unix specific symbol PORT_POTS
 *
 * Revision 1.6  2002/01/25 14:48:34  rogerh
 * Add a console thread which lets us terminate recording or playback
 * when the Enter key is pressed
 *
 * Revision 1.5  2002/01/25 11:50:10  rogerh
 * dd --port option to play and record commands so you can use a
 * telephone on the POTS port or use speakers and microphone.
 *
 * Revision 1.4  2002/01/13 20:55:59  rogerh
 * Update to allow proper recording and playback of both PCM and G.723.1 .WAV
 * files as well as .sw and .g7231 files
 *
 * Revision 1.3  2002/01/11 14:34:20  rogerh
 * Fix play command so it plays G.723.1 files correctly
 *
 * Revision 1.2  2001/09/25 01:10:30  robertj
 * Fixed compile problerm. Still incomplete code.
 *
 * Revision 1.1  2001/09/24 22:39:42  craigs
 * Added commands to play and record data files, esp G.723.1
 *
 */

#include <ptlib.h>
//#include <ixjlid.h>

#include "version.h"
#include "main.h"

class ConsoleThread : public PThread {
  PCLASSINFO(ConsoleThread, PThread);
  public:
    ConsoleThread(PMutex *_enter, BOOL *_enter_pressed) : PThread(1000,AutoDeleteThread)
    {
      enter = _enter;
      enter_pressed = _enter_pressed;
      
      Resume(); // start running this thread as soon as the thread is created.
    }

    void Main() {
      PConsoleChannel console(PConsoleChannel::StandardInput);

      // wait for Enter to be pressed
      console.peek();

      enter->Wait();
      *enter_pressed = TRUE;
      enter->Signal();
    }
  private:
    PMutex *enter;
    BOOL   *enter_pressed;
};

#define new PNEW

#ifdef HAS_IXJ

#define	G7231_BUFFER_SIZE	24
#define	PCM_BUFFER_SIZE		480

extern PString G7231Ext;
extern PString WAVExt;
extern PString PCMExt;

extern BOOL CheckWAVFileValid(PWAVFile *chan, int type);

#define CHECK_PCM   1
#define CHECK_G7231 2





static BOOL DetermineType(PArgList & args, const PFilePath & fn, BOOL & isPCM, BOOL & isWAV, BOOL openExisting)
{
  BOOL knowType = FALSE;

  // Handle .WAV file types
  if ((fn.GetType() *= WAVExt) && (openExisting)) {

    // determine the file type by peeking into the existing file

    PWAVFile *wavfile = new PWAVFile(fn, PFile::ReadOnly);
    if (!wavfile->IsOpen()) {
      PError << "error: cannot open file \"" << fn << "\"" << endl;
      delete wavfile;
      return FALSE;
    }
    if (CheckWAVFileValid(wavfile,CHECK_G7231))    isPCM = FALSE;
    else if (CheckWAVFileValid(wavfile,CHECK_PCM)) isPCM = TRUE;
    else {
      PError << "error: invalid wav file format for file \"" << fn << "\"" << endl;
      delete wavfile;
      return FALSE;
    }
    wavfile->Close();
    delete wavfile;

    isWAV    = TRUE;
    knowType = TRUE;
  }

  if ((fn.GetType() *= WAVExt) && (!openExisting)) {
    // determine the file type from the command line options
    if (args.HasOption("pcm")) {
      isPCM    = TRUE;
      isWAV    = TRUE;
      knowType = TRUE;
    } else if (args.HasOption("g7231")) {
      isPCM    = FALSE;
      isWAV    = TRUE;
      knowType = TRUE;
    } else {
      PError << "usage: recording a .wav file requires either --g7231 or --pcm,"
             << endl;
      return FALSE;
    }
  }

  // For non .WAV files determine file type from filename extension
  if (fn.GetType() *= G7231Ext) {
    isPCM    = FALSE;
    isWAV    = FALSE;
    knowType = TRUE;
  }

  if (fn.GetType() *= PCMExt) {
    isPCM    = TRUE;
    isWAV    = FALSE;
    knowType = TRUE;
  }

  // if we still do not know the file type, use the command line options
  if (!knowType) {
    if (args.HasOption("pcm")) {
      isPCM    = TRUE;
      isWAV    = FALSE;
      knowType = TRUE;
    } else if (args.HasOption("g7231")) {
      isPCM    = FALSE;
      isWAV    = FALSE;
      knowType = TRUE;
    }
  }

  // error if we could not determine the file type
  if (!knowType) {
    PError << "usage: command requires either --g7231 or --pcm,"
           << "       or filename with " << WAVExt << " or " << G7231Ext
           << " or " << PCMExt << " extension" << endl;
    return FALSE;
  }

  return TRUE;
}

static BOOL OpenDevice(OpalIxJDevice & xJack, const PString & ixjDevice, int port)
{
  if (!xJack.Open(ixjDevice)) {
    PError << "error: cannot open device \"" << ixjDevice << "\"" << endl;
    return FALSE;
  }

  xJack.SetLineToLineDirect(0, 1, FALSE);

  if (port == 3) xJack.EnableAudio(0, FALSE);
  if (port == 2) xJack.EnableAudio(OpalIxJDevice::PSTNLine, TRUE);
  if (port == 1) xJack.EnableAudio(OpalIxJDevice::POTSLine, TRUE);

  return TRUE;
}

void OpenAm::RecordFile(PArgList & args)
{
  if (args.GetCount() < 2) {
    PError << "usage: openam record [--port n] [--pcm|--g7231] -q N  fn" << endl;
    PError << "usage: port 1=POTS 3=MIC+SPEAKER" << endl;
    PError << "usage: -q N   quicknet device. Eg -q 0" << endl;
    PError << "usage: -fn    filename" << endl;
    return;
  }

  PFilePath fn  = args[1];
  BOOL isPCM = FALSE;
  BOOL isWAV = FALSE;
  int port;

  // Determine the type of file
  if (!DetermineType(args, fn, isPCM, isWAV, FALSE)) return;

  PFile *recordFile;
  if (isWAV) {
    if (isPCM) recordFile = new PWAVFile(PWAVFile::PCM_WavFile);
    else       recordFile = new PWAVFile(PWAVFile::G7231_WavFile);
  }
  else       recordFile = new PFile();

  if (recordFile == NULL)
    return;

  // open the file
  if (!recordFile->Open(fn, PFile::WriteOnly)) {
    PError << "error: cannot open file \"" << fn << "\"" << endl;
    return;
  }

  // open the device
  if (!args.HasOption('q')) {
    PError << "error: record command requires -q option for Quicknet device" << endl;
    return;
  }

  cout << "ok" << endl
       << "Recording " << (isPCM ? "PCM" : "G.723.1")
       << (isWAV ? " wav message" : " message") << endl;

  if (args.HasOption("port")) {
    port = args.GetOptionString("port").AsInteger();
  } else {
    port = OpalIxJDevice::POTSLine; // default to a real telephone
  }

  OpalIxJDevice xJack;
  if (!OpenDevice(xJack, args.GetOptionString('q'),port)) 
    return;

  // ring handset
  if (port == OpalIxJDevice::POTSLine) {
    xJack.RingLine(OpalIxJDevice::POTSLine, 0x33);

    // wait for answer
    cout << "Waiting for phone to go offhook...";
    cout.flush();

    while (!xJack.IsLineOffHook(OpalIxJDevice::POTSLine))
      Sleep(100);

    cout << endl;
  }

  // start codecs
  if (!xJack.SetReadCodec (OpalIxJDevice::POTSLine,
                           isPCM ? RTP_DataFrame::L16_Mono : RTP_DataFrame::G7231)) {
    PError << "error: error during SetReadCodec" << endl;
    return;
  }
  if (!xJack.SetWriteCodec(OpalIxJDevice::POTSLine,
                           isPCM ? RTP_DataFrame::L16_Mono : RTP_DataFrame::G7231)) {
    PError << "error: error during SetWriteCodec" << endl;
    return;
  }

  // determine the read buffer size
  PINDEX bufferSize;
  if (isPCM)
    bufferSize = xJack.GetReadFrameSize(OpalIxJDevice::POTSLine);
  else
    bufferSize = G7231_BUFFER_SIZE;

  // allocate a buffer
  PBYTEArray buffer;
  buffer.SetSize(bufferSize);

  // Create the console thread.
  PMutex enter;
  BOOL enter_pressed = FALSE;
  PThread * consolethread;
  consolethread = new ConsoleThread( &enter, &enter_pressed);

  cout << "Recording Started." << endl << "To stop recording " ;
  if (port == OpalIxJDevice::POTSLine)
    cout << "put the phone back onhook or ";
  cout << "press Enter" << endl;

  // start recording
  for (;;) {

    // stop if we are using POTS and the telephone handset it put down
    if ((port == OpalIxJDevice::POTSLine) && (!xJack.IsLineOffHook(OpalIxJDevice::POTSLine)))
      break;

    // stop if the user pressed Enter on the console
    enter.Wait();
    if (enter_pressed == TRUE) {
      enter.Signal();
      break;
    }
    enter.Signal();

    PINDEX count;
    if (!xJack.ReadFrame(OpalIxJDevice::POTSLine, buffer.GetPointer(), count)) {
      PError << "error: error during ReadFrame" << endl;
      return;
    }
    recordFile->Write(buffer, count);
  }

  cout << "Recording Finished" << endl;

  // stop recording;
  xJack.StopReadCodec (OpalIxJDevice::POTSLine);
  xJack.StopWriteCodec(OpalIxJDevice::POTSLine);

  // close the file
  recordFile->Close();
  delete recordFile;
}


void OpenAm::PlayFile(PArgList & args)
{
  if (args.GetCount() < 2) {
    PError << "usage: openam play [--port n] [--pcm|--g7231] -q N  fn" << endl;
    PError << "usage: port 1=POTS 2=PSTN 3=MIC+SPEAKER" << endl;
    PError << "usage: -q N   quicknet device. Eg -q 0" << endl;
    PError << "usage: -fn    filename" << endl;
    return;
  }

  PFilePath fn  = args[1];
  BOOL isPCM = FALSE;
  BOOL isWAV = FALSE;
  int port;

  // Determine the type of file
  if (!DetermineType(args, fn, isPCM, isWAV, TRUE)) return;

  PFile *playFile;
  if (isWAV) playFile = new PWAVFile();
  else       playFile = new PFile();

  if (playFile == NULL)
    return;

  // open the file
  if (!playFile->Open(fn, PFile::ReadOnly)) {
    PError << "error: cannot open file \"" << fn << "\"" << endl;
    return;
  }

  // open the device
  if (!args.HasOption('q')) {
    PError << "error: play command requires -q option for Quicknet device" << endl;
    return;
  }

  cout << "Playing " << (isPCM ? "PCM" : "G.723.1")
       << (isWAV ? " wav message" : " message") << endl;

  if (args.HasOption("port")) {
    port = args.GetOptionString("port").AsInteger();
  } else {
    port = 1; // default to a real telephone
  }

  OpalIxJDevice xJack;
  if (!OpenDevice(xJack, args.GetOptionString('q'),port))
    return;

  // ring handset
  if (port == 1) {
    xJack.RingLine(OpalIxJDevice::POTSLine, 0x33);

    // wait for answer
    cout << "Waiting for phone to go offhook...";
    cout.flush();

    while (!xJack.IsLineOffHook(OpalIxJDevice::POTSLine))
      Sleep(100);

    cout << endl;
  }


  // start codecs
  if (!xJack.SetReadCodec (OpalIxJDevice::POTSLine,
                           isPCM ? RTP_DataFrame::L16_Mono : RTP_DataFrame::G7231)) {
    PError << "error: error during SetReadCodec" << endl;
    return;
  }
  if (!xJack.SetWriteCodec(OpalIxJDevice::POTSLine,
                           isPCM ? RTP_DataFrame::L16_Mono : RTP_DataFrame::G7231)) {
    PError << "error: error during SetWriteCodec" << endl;
    return;
  }

  // determine the write buffer size
  PINDEX bufferSize;
  if (isPCM)
    bufferSize = xJack.GetReadFrameSize(OpalIxJDevice::POTSLine);
  else
    bufferSize = G7231_BUFFER_SIZE;

  // allocate a buffer
  PBYTEArray buffer;
  buffer.SetSize(bufferSize);


  // Create the console thread.
  PMutex enter;
  BOOL enter_pressed = FALSE;
  PThread * consolethread;
  consolethread = new ConsoleThread( &enter, &enter_pressed);

  cout << "Playback Started." << endl << "To stop playback " ;
  if (port == 1)
    cout << "put the phone back onhook or ";
  cout << "press Enter" << endl;

  // start playing
  for (;;) {

    // stop if we are using POTS and the telephone handset it put down
    if ((port == 1) && (!xJack.IsLineOffHook(OpalIxJDevice::POTSLine))) {
      break;
    }

    // stop if the user pressed Enter on the console
    enter.Wait();
    if (enter_pressed == TRUE) {
      enter.Signal();
      break;
    }
    enter.Signal();

    PINDEX count = 0;
    if (isPCM) {
      if (!playFile->Read(buffer.GetPointer(), bufferSize))
        break;
    } else {
      if (!playFile->Read(buffer.GetPointer(), 1)) 
        break;
      count++;
      static const int frameLen[] = { 24, 20, 4, 1 };
      if (!playFile->Read(buffer.GetPointer()+1, frameLen[buffer[0]&3] - 1))
        break;
    }
    count += playFile->GetLastReadCount();

    PINDEX written;
    if (!xJack.WriteFrame(OpalIxJDevice::POTSLine, buffer.GetPointer(), count, written)) {
      PError << "error: error during WriteFrame" << endl;
      return;
    }
  }

  // stop recording;
  xJack.StopReadCodec (OpalIxJDevice::POTSLine);
  xJack.StopWriteCodec(OpalIxJDevice::POTSLine);

  // close the file
  playFile->Close();
  delete playFile;
}


#endif
