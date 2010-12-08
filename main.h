/*
 * main.h
 *
 * PWLib application header file for Voxilla
 *
 * A H.323 "net telephone" application.
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
 * Portions of this code were written with the assisance of funding from
 * Vovida Networks, Inc. http://www.vovida.com.
 *
 * Portions are Copyright (C) 1993 Free Software Foundation, Inc.
 * All Rights Reserved.
 *
 * Contributor(s): ______________________________________.
 *
 * $Log$
 * Revision 1.13  2010/11/02 11:15:21  willamowius
 * use same trace format as GnuGk
 *
 * Revision 1.12  2010/01/07 21:30:21  willamowius
 * fix initialization of videobitrate, use G7231File_Codec only if supplied by PTLib
 *
 * Revision 1.11  2010/01/07 15:37:59  willamowius
 * remove unused code
 *
 * Revision 1.10  2010/01/01 00:58:37  willamowius
 * allow setting of video maxBitRate with --videobitrate <rate>
 *
 * Revision 1.9  2009/05/06 18:33:09  willamowius
 * generic --no-record switch replaces --no-recordg7231
 *
 * Revision 1.8  2009/05/06 15:22:48  willamowius
 * ignore errors on SetFrameRate, fix OGM selection, make error messages seen
 *
 * Revision 1.7  2009/05/06 13:13:50  willamowius
 * fix warnings + cleanup
 *
 * Revision 1.6  2009/02/24 10:58:16  willamowius
 * add backwards compatibility to H323Plus versions before the PBoolean change
 *
 * Revision 1.5  2008/05/23 11:18:11  willamowius
 * switch BOOL to PBoolean to be able to compile with Ptlib 2.2.x
 *
 * Revision 1.4  2008/05/05 15:08:16  willamowius
 * add option --displayname <name>
 *
 * Revision 1.3  2008/01/02 19:12:30  willamowius
 * better enforce limit on call duration for video channels
 *
 * Revision 1.2  2007/11/14 15:23:59  willamowius
 * declare overloaded methods as virtual
 *
 * Revision 1.1  2007/11/07 03:42:15  willamowius
 * port OpenAM to H323Plus
 *
 * Revision 1.43  2006/06/26 14:29:40  csoutheren
 * Fixed for new PWLib
 *
 * Revision 1.42  2006/04/19 04:11:53  csoutheren
 * Fix problem when outputting CIF stream using QCIF source
 *
 * Revision 1.41  2006/02/28 10:12:50  csoutheren
 * Added support for NULL receive video
 *
 * Revision 1.40  2006/02/24 10:16:07  csoutheren
 * Fixed for CIF
 *
 * Revision 1.39  2006/02/21 07:52:18  csoutheren
 * Added outgoing video message functions
 *
 * Revision 1.38  2005/11/25 00:52:49  csoutheren
 * Applied patch #1292653
 * OpenAM patch to log calling number
 *
 * Revision 1.37  2005/02/03 01:21:42  csoutheren
 * Added called party to call log and command parameters
 *
 * Revision 1.36  2004/05/03 13:25:46  rjongbloed
 * Converted everything to be codec plug in freindly
 * Removed GSM and G.729 as now plug ins are "the way"!
 *
 * Revision 1.35  2004/01/02 02:52:10  csoutheren
 * Thanks to Michal Zygmuntowicz for these changes
 *   Added support for iLBC codec
 *   Added ability to specify a gatekeeper password,
 *   Fixed small bug with Speex capabilities being accidentally included.
 *
 * Revision 1.34  2003/12/02 09:46:59  csoutheren
 * Added --loop option thanks to Jan Willamowius
 *
 * Revision 1.33  2002/11/13 10:23:12  rogerh
 * Enable Speex support by default.
 *
 * Revision 1.32  2002/08/16 02:04:30  craigs
 * Ensure compilation without Speex installed
 *
 * Revision 1.31  2002/08/15 18:52:49  rogerh
 * Add support for one of the Speex codecs
 *
 * Revision 1.30  2002/08/05 10:06:06  robertj
 * Changed to use the version of G.7231. file capability/codec as used in
 *   opalvxml module. Prevents duplicate symbol link errors.
 *
 * Revision 1.29  2002/04/01 14:45:43  craigs
 * Fixed flag to end call after OGM
 *
 * Revision 1.28  2002/04/01 13:16:09  craigs
 * Added ability to kill calls at end of playing OGM
 * Added ability to play different OGMs depending on target DN
 *
 * Revision 1.27  2002/02/21 07:21:52  rogerh
 * Change the outgoing audio's FrameDelay() code to use the PAdaptiveDelay
 * class which should give clearer audio for the OGMs.
 *
 * Revision 1.26  2002/01/22 04:15:04  craigs
 * Updated for move of PWavFile to PTCLib
 * Replaced AudioDelay with PAdaptiveDelay
 *
 * Revision 1.25  2001/10/15 14:10:01  rogerh
 * Add new definitions
 *
 * Revision 1.24  2001/09/29 07:11:48  rogerh
 * Delete ogmChanel in destructor - Patrick Koorevaar <pkoorevaar@hotmail.com>
 * Only call conn.ClearCall() once after we pass the record time limit.
 * Reported by Patrick.
 *
 * Revision 1.23  2001/09/28 00:13:48  robertj
 * Changed BYTE* to PBYTEArray so get automatic memory management.
 *
 * Revision 1.22  2001/09/24 22:39:42  craigs
 * Added commands to play and record data files, esp G.723.1
 *
 * Revision 1.21  2001/07/23 09:17:36  rogerh
 * Add the LPC10 codec, a low quality and low bitrate codec.
 *
 * Revision 1.20  2001/07/17 14:33:01  rogerh
 * Support writing of .wav audio files from PCM codecs (eg G711 and GSM).
 * .wav files are written out by default now. If you still want to record
 * to raw audio files with a .sw extension, use the --recordraw option.
 *
 * Revision 1.19  2001/07/01 07:38:58  rogerh
 * Add Microsoft GSM codec. Also allocate memory for frameBuffer dynamically
 * as different codecs can have different frame sizes.
 *
 * Revision 1.18  2001/06/29 11:13:15  rogerh
 * Add AudioDelay class which removes the jitter in recorded files.
 *
 * Revision 1.17  2001/06/29 06:34:57  rogerh
 * Add mutex locks in PCM_Recordfile. This solves the race condition where
 * Close() was called while Write() was still running.
 *
 * Revision 1.16  2000/08/29 12:32:08  craigs
 * Fixed problems with recording messages
 *
 * Revision 1.15  2000/08/28 16:42:59  craigs
 * Finally fixed problems with G.723.1. All codecs now working
 *
 * Revision 1.14  2000/08/28 07:49:51  craigs
 * Added extra stuff
 *
 * Revision 1.13  2000/08/28 00:38:37  craigs
 * Added support for setting listening port number
 *
 * Revision 1.12  2000/08/27 23:42:24  craigs
 * Fixed problem with playback of messages
 * Fixed problem with recording messages
 *
 * Revision 1.11  2000/05/25 12:06:17  robertj
 * Added PConfigArgs class so can save program arguments to config files.
 *
 * Revision 1.10  2000/05/10 05:14:25  robertj
 * Changed capabilities so has a function to get name of codec, instead of relying on PrintOn.
 *
 * Revision 1.9  2000/05/09 11:22:15  craigs
 * Fixed problems caused by new jitter buffer code
 * and fixed OGM problems
 *
 * Revision 1.8  2000/04/25 23:34:22  craigs
 * Added lots of new code, including outgoing and incoming
 * multiplexors, and the start of an IVR system
 *
 * Revision 1.7  2000/01/13 04:03:45  robertj
 * Added video transmission
 *
 * Revision 1.6  1999/11/11 00:27:49  robertj
 * Changed OnAnswerCall() call back function  to allow for asyncronous response.
 *
 * Revision 1.5  1999/11/06 13:27:49  craigs
 * Added extra output and changed for new library changes
 *
 * Revision 1.4  1999/10/24 12:50:37  craigs
 * Fixed G723.1 capability, and added ability for discrete OGMs
 *
 * Revision 1.3  1999/10/24 03:08:49  craigs
 * Fixed problem with recording zero length messages, and added autodelete of files
 *
 * Revision 1.2  1999/10/22 09:56:41  craigs
 * Fixed compile warning
 *
 * Revision 1.1  1999/10/11 00:15:18  craigs
 * Initial version
 *
 *
 */

#ifndef _OPENAM_MAIN_H
#define _OPENAM_MAIN_H

#include <h323.h>
#include <h323pdu.h>
#include <h245.h>

#include <ptclib/pwavfile.h>
#include <ptclib/delaychan.h>

#ifndef NO_H323_VIDEO
#if P_VIDFILE
#define OPENAM_VIDEO  1
#endif
#endif

#if OPENAM_VIDEO
#include <ptlib/video.h>
#endif

#ifdef P_VXML
#define OPENAM_G723	1	// G7231_File_Codec is only avalable if VXML is enabled
#endif

#if !defined(P_USE_STANDARD_CXX_BOOL) && !defined(P_USE_INTEGER_BOOL)
	typedef int PBoolean;
#endif

class MyH323EndPoint : public H323EndPoint
{
  PCLASSINFO(MyH323EndPoint, H323EndPoint);

  public:
    MyH323EndPoint(unsigned callLimit,
                   const PString & runCmd,
                   const PDirectory & dir,
                   int flags);
	virtual ~MyH323EndPoint();

    // overrides from H323EndPoint
    virtual H323Connection * CreateConnection(unsigned callReference);
    virtual PBoolean OnIncomingCall(H323Connection &, const H323SignalPDU &, H323SignalPDU &);

    // new functions
    virtual PBoolean Initialise(PConfigArgs & args);
    
    PString    GetDisplayName() const            { return displayName; }
    void       SetDisplayName(const PString & n) { displayName = n; }

    PString    GetGSMOGM() const            { return gsmOgm; }
    void       SetGSMOGM(const PString & s) { gsmOgm = s; }

    PString    GetG711OGM() const            { return g711Ogm; }
    void       SetG711OGM(const PString & s) { g711Ogm = s; }

    PString    GetLPC10OGM() const            { return lpc10Ogm; }
    void       SetLPC10OGM(const PString & s) { lpc10Ogm = s; }

    PString    GetSPEEXOGM() const            { return speexOgm; }
    void       SetSPEEXOGM(const PString & s) { speexOgm = s; }

    PString    GetG7231OGM() const            { return g7231Ogm; }
    void       SetG7231OGM(const PString & s) { g7231Ogm = s; }

    PString    GetiLBCOGM() const            { return ilbcOgm; }
    void       SetiLBCOGM(const PString & s) { ilbcOgm = s; }

    unsigned   GetCallLimit() const { return callLimit; }
    PString    GetRunCmd() const    { return runCmd; }
    PDirectory GetDirectory() const { return dir; }

    void       SetRecordWav(const PBoolean rec){ recordWav = rec; }
    PBoolean       GetRecordWav() const        { return recordWav; }

    void       SetNoRecord(PBoolean flag) { recordMessage = flag; }
    PBoolean       GetNoRecord() const    { return recordMessage; }

    void       SetLoopMessage(PBoolean flag) { loopMessage = flag; }
    PBoolean       GetLoopMessage() const    { return loopMessage; }

#if OPENAM_VIDEO
    PString GetVideoOGM() const       { return videoOgm; }
    int     GetVideoSize() const      { return videoSize; }
    int     GetVideoBitRate() const   { return videoBitRate; }
    PBoolean    GetVideoIsPal() const { return videoIsPal; }
    int     GetVideoFrameRate() const { return frameRate; }
    int     GetVideoPlayMode() const  { return videoChannel; }
#endif
    
    enum {
      DeleteAfterRecord = 0x01,
      HangupAfterPlay   = 0x04
    };

    PBoolean GetDeleteAfterRecord() const   { return flags & DeleteAfterRecord; }
    PBoolean GetHangupAfterPlay() const     { return flags & HangupAfterPlay; }

  protected:
	PString displayName;
    unsigned callLimit;
    PString pcmOgm, g711Ogm, gsmOgm, lpc10Ogm, g7231Ogm, runCmd;
    PString speexOgm, ilbcOgm;
    PDirectory dir;
    int flags;
    PBoolean recordWav;
    PBoolean recordMessage;
    PBoolean loopMessage;
#if OPENAM_VIDEO
    PString videoOgm;
    int videoSize;
    int videoBitRate;
    int frameRate;
    int videoChannel;
    PBoolean videoIsPal;
#endif
};

class OpenAm : public PProcess
{
  PCLASSINFO(OpenAm, PProcess)

  public:
    OpenAm();
    ~OpenAm();

    void Main();
    static void Shutdown();

  protected:
    static MyH323EndPoint * endpoint;
};

class PCM_RecordFile;
class MyH323Connection;
PQUEUE(PStringQueue, PString);

class PCM_OGMChannel : public PIndirectChannel
{
  PCLASSINFO(PCM_OGMChannel, PIndirectChannel);

  public:
    PCM_OGMChannel(MyH323Connection & conn);

    virtual PBoolean Read(void * buffer, PINDEX amount);
    virtual void PlayFile(PFile * chan);

    virtual PBoolean Close();

    void QueueFile(const PString & cmd);
    void FlushQueue();

    void SetRecordTrigger();
    void SetHangupTrigger();

    void SetPlayOnce() { playOnce = TRUE; }
    void SetLoopMessage() { loopMessage = TRUE; }

  protected:
    virtual PBoolean ReadFrame(PINDEX amount);
    virtual void CreateSilenceFrame(PINDEX amount);
    virtual void Synchronise(PINDEX amount);
    virtual PBoolean IsWAVFileValid(PWAVFile *chan);

    PBoolean AdjustFrame(void * buffer, PINDEX amount);

    PStringQueue playQueue;

    MyH323Connection & conn;
    PMutex chanMutex;
    int silentCount;
    int totalData;
    PBoolean recordTrigger, hangupTrigger;
    PBoolean closed;
    PBoolean playOnce;
	  PBoolean loopMessage;

    PAdaptiveDelay ogm_delay;

    PBYTEArray frameBuffer;
    PINDEX frameLen, frameOffs;
};

class G7231_OGMChannel : public PCM_OGMChannel
{
  PCLASSINFO(G7231_OGMChannel, PCM_OGMChannel);
  public:
    G7231_OGMChannel(MyH323Connection & conn);

  protected:
    virtual PBoolean ReadFrame(PINDEX amount);
    virtual void CreateSilenceFrame(PINDEX amount);
    virtual void Synchronise(PINDEX amount);
    virtual PBoolean IsWAVFileValid(PWAVFile *chan);
};

#ifdef OPENAM_VIDEO

class TimeLimitedVideoChannel : public PVideoChannel
{
	PCLASSINFO(TimeLimitedVideoChannel, PVideoChannel);
	public:
		TimeLimitedVideoChannel(MyH323Connection & _conn, unsigned _callLimit);

		virtual PBoolean Write(const void * buf, PINDEX len);

	protected:
		MyH323Connection & conn;
		unsigned callLimit;
		PTime finishTime;
};

#endif

class MyH323Connection : public H323Connection
{
  PCLASSINFO(MyH323Connection, H323Connection);

  public:
    MyH323Connection(MyH323EndPoint &, unsigned, unsigned);
    virtual ~MyH323Connection();

    // overrides from H323Connection
    virtual PBoolean OpenAudioChannel(PBoolean, unsigned, H323AudioCodec & codec);
#if OPENAM_VIDEO
    virtual PBoolean OpenVideoChannel(PBoolean, H323VideoCodec & codec);
#endif
    virtual AnswerCallResponse OnAnswerCall(const PString &, const H323SignalPDU &, H323SignalPDU &);
    virtual void OnSendCapabilitySet(H245_TerminalCapabilitySet & pdu);
    virtual PBoolean OnStartLogicalChannel(H323Channel & channel);
    virtual void OnUserInputString(const PString & value);
    virtual PBoolean OnReceivedSignalSetup(const H323SignalPDU & setupPDU);

    // new functions
    void StartRecording();
    void Hangup();

	void SetE164Number(const PString & _num) { e164Number = _num; }

  protected:
#if OPENAM_VIDEO
    PBoolean InitGrabber(PVideoInputDevice  * grabber, unsigned newWidth, unsigned newHeight);
#endif

    void OnUserInputChar(char ch);
    PBoolean StartMenu(int menuNumber);
    PBoolean ProcessMenuCmd(const PString & cmdStr);

    const MyH323EndPoint & ep;
    PString product;
    PTime   callStartTime;
    PTime   recordStartTime;
    PString basename;
    PFilePath recordFn;
    PString transmitAudioCodecName, receiveAudioCodecName;
#if OPENAM_VIDEO
    PString transmitVideoCodecName, receiveVideoCodecName;
#endif
    PBoolean    recordTrigger;
    PString calledParty;
    PMutex  connMutex;

    PCM_RecordFile * recordFile;
    PCM_OGMChannel * ogmChannel;

    PString digits, lastDigits;
    int currentMenu;
    PStringList menuNames;

    PString securityToken, e164Number;
};

class PCM_RecordFile : public PIndirectChannel
{
  PCLASSINFO(PCM_RecordFile, PIndirectChannel)

  public:
    PCM_RecordFile(MyH323Connection & conn, const PFilePath & fn, unsigned callLimit);
    virtual ~PCM_RecordFile();

    virtual PBoolean Write(const void * buf, PINDEX len);
    virtual PBoolean Close();
    virtual void StartRecording();

    virtual void DelayFrame(PINDEX len);
    virtual PBoolean WriteFrame(const void * buf, PINDEX len);

    virtual PBoolean WasRecordStarted() const { return recordStarted; }

  protected:
    MyH323Connection & conn;
    PTime finishTime;
    PFilePath fn;
    unsigned callLimit;
    PBoolean recordStarted;
    PBoolean timeLimitExceeded;
    PBoolean closed;
    PBoolean isPCM;
    PBoolean dataWritten;
    PAdaptiveDelay delay;
    PMutex pcmrecordMutex;
    PFile *fileclass; // will point to a PWAVFile or PFile class
};

class G7231_RecordFile : public PCM_RecordFile
{
  PCLASSINFO(G7231_RecordFile, PCM_RecordFile);

  public:
    G7231_RecordFile(MyH323Connection & conn, const PFilePath & fn, unsigned callLimit);
    virtual void DelayFrame(PINDEX len);
    virtual PBoolean WriteFrame(const void * buf, PINDEX len);
};


#endif  // _OPENAM_MAIN_H


// End of File ///////////////////////////////////////////////////////////////
