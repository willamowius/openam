/*
 * main.cxx
 *
 * Main source for for OpenAM
 *
 * A H.323 answering machine application.
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
 * Portions are Copyright (C) 1993 Free Software Foundation, Inc.
 * All Rights Reserved.
 *
 * Contributor(s): ______________________________________.
 *
 * $Log$
 * Revision 1.38  2010/12/08 08:49:20  willamowius
 * avoid link error if G7231_File_Capability is not available
 *
 * Revision 1.37  2010/11/02 11:15:21  willamowius
 * use same trace format as GnuGk
 *
 * Revision 1.36  2010/05/25 20:28:46  willamowius
 * fix compile without video
 *
 * Revision 1.35  2010/01/07 21:54:32  willamowius
 * better type checking when setting maxBitRate
 *
 * Revision 1.34  2010/01/07 21:30:21  willamowius
 * fix initialization of videobitrate, use G7231File_Codec only if supplied by PTLib
 *
 * Revision 1.33  2010/01/07 15:37:57  willamowius
 * remove unused code
 *
 * Revision 1.32  2010/01/01 00:58:36  willamowius
 * allow setting of video maxBitRate with --videobitrate <rate>
 *
 * Revision 1.31  2009/12/20 21:07:21  willamowius
 * print error code of executed command
 *
 * Revision 1.30  2009/08/29 01:53:31  shorne
 * Fix compiling on Windows
 *
 * Revision 1.29  2009/05/14 11:05:09  willamowius
 * make sure compilation without video works
 *
 * Revision 1.28  2009/05/14 10:31:56  willamowius
 * disable video codecs when no video ogm is set
 *
 * Revision 1.27  2009/05/06 18:33:07  willamowius
 * generic --no-record switch replaces --no-recordg7231
 *
 * Revision 1.26  2009/05/06 17:42:07  willamowius
 * destructing global objects on shutdown causes an infinite recursion with current PTLibs (eg. 2.4.5), so we don't do that for now
 *
 * Revision 1.25  2009/05/06 15:22:45  willamowius
 * ignore errors on SetFrameRate, fix OGM selection, make error messages seen
 *
 * Revision 1.24  2009/05/06 13:13:49  willamowius
 * fix warnings + cleanup
 *
 * Revision 1.23  2008/05/23 11:18:10  willamowius
 * switch BOOL to PBoolean to be able to compile with Ptlib 2.2.x
 *
 * Revision 1.22  2008/05/05 15:08:16  willamowius
 * add option --displayname <name>
 *
 * Revision 1.21  2008/04/16 07:55:18  willamowius
 * set default message limit to 0 (unlimited)
 *
 * Revision 1.20  2008/04/14 08:36:02  willamowius
 * add switches to set port ranges for H.245, RAS and RTP
 *
 * Revision 1.19  2008/02/07 08:38:04  shorne
 * fix warning on VS 2008
 *
 * Revision 1.18  2008/01/02 19:12:30  willamowius
 * better enforce limit on call duration for video channels
 *
 * Revision 1.17  2008/01/02 17:12:53  willamowius
 * assign different name to each recorded video (same as with audio files)
 *
 * Revision 1.16  2007/11/22 22:31:13  willamowius
 * remove uneccessary restriction to exactly one frame size
 *
 * Revision 1.15  2007/11/19 23:23:11  willamowius
 * trace codec and frame size
 *
 * Revision 1.14  2007/11/19 00:28:17  willamowius
 * limit the video size to size of the provided video OGM
 *
 * Revision 1.13  2007/11/17 13:52:25  willamowius
 * cleanup
 *
 * Revision 1.12  2007/11/14 15:23:59  willamowius
 * declare overloaded methods as virtual
 *
 * Revision 1.11  2007/11/14 14:16:43  willamowius
 * always print message about call start/end to stdout
 *
 * Revision 1.10  2007/11/14 14:09:32  willamowius
 * avoid using NULLOutput device since it doesn't work with 'make optnoshared'
 *
 * Revision 1.9  2007/11/14 13:12:44  willamowius
 * trace message which output device is being created
 *
 * Revision 1.8  2007/11/14 11:53:47  willamowius
 * delete endpoint object on shutdown
 *
 * Revision 1.7  2007/11/13 14:58:54  willamowius
 * reduce read size for very short frame so G7231 OGMs work again
 *
 * Revision 1.6  2007/11/13 14:37:05  willamowius
 * allow operation without audio OGM, only with video OGM
 *
 * Revision 1.5  2007/11/13 14:03:45  willamowius
 * fix message about recording limit
 *
 * Revision 1.4  2007/11/13 13:51:04  willamowius
 * more cleanup
 *
 * Revision 1.3  2007/11/13 13:18:24  willamowius
 * cleanup
 *
 * Revision 1.2  2007/11/07 05:58:37  shorne
 * Fixed Windows compile
 *
 * Revision 1.1  2007/11/07 03:42:13  willamowius
 * port OpenAM to H323Plus
 *
 * Revision 1.102  2006/04/19 04:11:53  csoutheren
 * Fix problem when outputting CIF stream using QCIF source
 *
 * Revision 1.101  2006/03/12 06:37:53  rjongbloed
 * Fixed DevStudio warning
 *
 * Revision 1.100  2006/03/06 07:05:19  csoutheren
 * Preliminary support for capturing video input
 *
 * Revision 1.99  2006/02/28 12:46:31  csoutheren
 * Removed warning on Windows
 *
 * Revision 1.98  2006/02/28 12:36:31  csoutheren
 * Fixed video capabilities
 *
 * Revision 1.97  2006/02/28 10:12:50  csoutheren
 * Added support for NULL receive video
 *
 * Revision 1.96  2006/02/24 10:16:07  csoutheren
 * Fixed for CIF
 *
 * Revision 1.95  2006/02/21 07:52:18  csoutheren
 * Added outgoing video message functions
 *
 * Revision 1.94  2005/11/25 00:52:49  csoutheren
 * Applied patch #1292653
 * OpenAM patch to log calling number
 *
 * Revision 1.93  2005/02/03 01:21:42  csoutheren
 * Added called party to call log and command parameters
 *
 * Revision 1.92  2004/05/26 04:01:57  csoutheren
 * Changed to work completely with new plugin codecs
 *
 * Revision 1.91  2004/05/10 13:07:19  rjongbloed
 * Changed G.726 and MS-ADPCM to plug in codecs.
 *
 * Revision 1.90  2004/05/04 12:21:16  rjongbloed
 * Converted LPC-10 codec to plug in.
 *
 * Revision 1.89  2004/05/03 13:25:46  rjongbloed
 * Converted everything to be codec plug in freindly
 * Removed GSM and G.729 as now plug ins are "the way"!
 *
 * Revision 1.88  2004/04/06 11:27:49  rjongbloed
 * Changes to support native C++ Run Time Type Information
 * Changes for codec plug ins
 *
 * Revision 1.87  2004/01/31 07:38:21  rjongbloed
 * Changed HAS_IXJ usage to if defined not if non-zero
 *
 * Revision 1.86  2004/01/02 02:52:10  csoutheren
 * Thanks to Michal Zygmuntowicz for these changes
 *   Added support for iLBC codec
 *   Added ability to specify a gatekeeper password,
 *   Fixed small bug with Speex capabilities being accidentally included.
 *
 * Revision 1.85  2003/12/02 09:46:59  csoutheren
 * Added --loop option thanks to Jan Willamowius
 *
 * Revision 1.84  2002/11/13 10:23:12  rogerh
 * Enable Speex support by default.
 *
 * Revision 1.83  2002/11/10 08:12:42  robertj
 * Moved constants for "well known" ports to better place (OPAL change).
 *
 * Revision 1.82  2002/08/21 08:48:09  rogerh
 * Fix some problems caused by the user specif OGM changes
 *
 * Revision 1.81  2002/08/21 06:55:09  rogerh
 * Support all 5 Speex bitrates.
 *
 * Revision 1.80  2002/08/16 02:04:30  craigs
 * Ensure compilation without Speex installed
 *
 * Revision 1.79  2002/08/15 18:52:49  rogerh
 * Add support for one of the Speex codecs
 *
 * Revision 1.78  2002/08/05 10:06:06  robertj
 * Changed to use the version of G.7231. file capability/codec as used in
 *   opalvxml module. Prevents duplicate symbol link errors.
 *
 * Revision 1.77  2002/06/28 00:30:41  robertj
 * Fixed Clone() for G.723 file capability, must clone contents!
 *
 * Revision 1.76  2002/05/08 03:15:35  robertj
 * Removed unecessary initialisation of frameBuffer PBYTEArray
 *
 * Revision 1.75  2002/04/01 14:45:43  craigs
 * Fixed flag to end call after OGM
 *
 * Revision 1.74  2002/04/01 13:16:09  craigs
 * Added ability to kill calls at end of playing OGM
 * Added ability to play different OGMs depending on target DN
 *
 * Revision 1.73  2002/02/21 07:21:52  rogerh
 * Change the outgoing audio's FrameDelay() code to use the PAdaptiveDelay
 * class which should give clearer audio for the OGMs.
 *
 * Revision 1.72  2002/02/04 13:23:24  rogerh
 * Change the silence frame back to a 4 byte SID. It caused Quicnet cards
 * to play a loud noise instead of silence.
 *
 * Revision 1.71  2002/01/31 16:12:26  rogerh
 * Clear the end of the frame buffer if we cannot read a full frame.
 *
 * Revision 1.70  2002/01/26 09:40:03  rogerh
 * Make OpenAM send out G.723.1 OGM audio files correctly.
 *
 * Revision 1.69  2002/01/25 11:50:10  rogerh
 * dd --port option to play and record commands so you can use a
 * telephone on the POTS port or use speakers and microphone.
 *
 * Revision 1.68  2002/01/25 08:58:46  rogerh
 * Send out silence using a standard 24 byte frame instead of a 4 byte SID.
 * This is a workaround to support an end point which does not understand SID.
 *
 * Revision 1.67  2002/01/22 04:15:04  craigs
 * Updated for move of PWavFile to PTCLib
 * Replaced AudioDelay with PAdaptiveDelay
 *
 * Revision 1.66  2002/01/11 16:07:15  rogerh
 * Make PCMExt non static as it is used externally in cmds.cxx
 *
 * Revision 1.65  2001/11/18 23:07:36  craigs
 * Fixed problem whereby recording could start when queue of OGMs was not empty
 * Thanks to Frank Derks
 *
 * Revision 1.64  2001/10/24 10:45:33  rogerh
 * replace 4 byte SID frames with 24 byte frames of silence. Windows Media
 * Player's codec cannot handle SID frames.
 *
 * Revision 1.63  2001/10/24 10:28:59  rogerh
 * Make -m option find g7231 wav files.
 * Fix bug where record file format was set by the outgoing codec type.
 * (fixes bug when NetMeeting decides to receive G.723.1 and send MS-GSM)
 *
 * Revision 1.62  2001/10/24 09:01:07  rogerh
 * Fix a mistake in the 24 byte frames used for silence.
 *
 * Revision 1.61  2001/10/16 12:28:43  rogerh
 * Add support for saving g.723.1 audio data into a g.723.1 WAV File
 *
 * Revision 1.60  2001/10/15 14:55:03  rogerh
 * Add error message
 *
 * Revision 1.59  2001/10/15 14:20:10  rogerh
 * Add support for reading G.723.1 WAV files for the G.723.1 codec.
 * Recorded messages are still saved out in raw .g723 files.
 *
 * Revision 1.58  2001/10/15 07:09:38  rogerh
 * New sox homepage
 *
 * Revision 1.57  2001/10/14 08:22:54  rogerh
 * Record the silence in G.723.1 connections to the record file.
 * This also gives a proper fix for the 100% CPU utilisation bug.
 *
 * Revision 1.56  2001/10/13 07:13:18  rogerh
 * Add a 5ms sleep if the length of the G.723.1 audio data is zero.
 * This hack stops the 100% CPU usage seen when recording G.723.1 files.
 * Submitted by Maurizio Beni <m.beni@deimositalia.com>
 *
 * Revision 1.55  2001/10/04 23:55:00  craigs
 * Added deletion of file in PCM_RecordFile destructor thanks to Patrick Koorevaar
 *
 * Revision 1.54  2001/10/02 11:02:31  rogerh
 * Use the audio delay class when writing G723.1 audio files.
 * Add a quick hack.Set the frameBuffer to 1024 so OpenAM tworks on Unix boxes
 *
 * Revision 1.53  2001/09/29 07:11:48  rogerh
 * Delete ogmChanel in destructor - Patrick Koorevaar <pkoorevaar@hotmail.com>
 * Only call conn.ClearCall() once after we pass the record time limit.
 * Reported by Patrick.
 *
 * Revision 1.52  2001/09/28 00:14:30  robertj
 * Changed BYTE* to PBYTEArray so get automatic memory management.
 * Fixed redundant entries in argument parsing, thanks Patrick Koorevaar
 *
 * Revision 1.51  2001/09/24 22:39:42  craigs
 * Added commands to play and record data files, esp G.723.1
 *
 * Revision 1.50  2001/08/24 14:04:29  rogerh
 * Delete the listener if StartListener() fails.
 *
 * Revision 1.49  2001/08/13 00:01:15  robertj
 * Fixed #ifdef for memory check code to use PMEMORY_CHECK and not _DEBUG
 *
 * Revision 1.48  2001/07/23 09:17:36  rogerh
 * Add the LPC10 codec, a low quality and low bitrate codec.
 *
 * Revision 1.47  2001/07/23 04:01:10  rogerh
 * remove debugging info
 *
 * Revision 1.46  2001/07/20 03:36:58  robertj
 * Minor cosmetic changes to new PWAVFile class.
 *
 * Revision 1.45  2001/07/19 10:05:27  rogerh
 * PWAVFile is now part of the standard PWLib.
 *
 * Revision 1.44  2001/07/17 14:33:01  rogerh
 * Support writing of .wav audio files from PCM codecs (eg G711 and GSM).
 * .wav files are written out by default now. If you still want to record
 * to raw audio files with a .sw extension, use the --recordraw option.
 *
 * Revision 1.43  2001/07/17 12:02:37  rogerh
 * Change title, OpenAm -> OpenAM
 *
 * Revision 1.42  2001/07/14 07:44:29  rogerh
 * Add .wav file support to the OGM.
 * The -m option now looks for .wav and then .sw file extensions.
 * .wav file must be 16 bit mono at 8000 Hz
 *
 * Revision 1.41  2001/07/11 15:47:55  rogerh
 * Add G711 A-Law codec, reported by Niels Svennekjær <linux@post.tele.dk>
 *
 * Revision 1.40  2001/07/01 07:38:57  rogerh
 * Add Microsoft GSM codec. Also allocate memory for frameBuffer dynamically
 * as different codecs can have different frame sizes.
 *
 * Revision 1.39  2001/06/29 11:13:15  rogerh
 * Add AudioDelay class which removes the jitter in recorded files.
 *
 * Revision 1.38  2001/06/29 09:01:17  rogerh
 * Put back a line accidentally deleted in the last commit
 *
 * Revision 1.37  2001/06/29 06:34:57  rogerh
 * Add mutex locks in PCM_Recordfile. This solves the race condition where
 * Close() was called while Write() was still running.
 *
 * Revision 1.36  2001/04/27 07:08:46  robertj
 * Fixed 100% Cip problem, thanks APinaev@microtest.ru
 *
 * Revision 1.35  2001/03/20 23:42:55  robertj
 * Used the new PTrace::Initialise function for starting trace code.
 *
 * Revision 1.34  2001/01/25 07:27:14  robertj
 * Major changes to add more flexible OpalMediaFormat class to normalise
 *   all information about media types, especially codecs.
 *
 * Revision 1.33  2000/10/20 23:11:29  robertj
 * Fixed incorrect parameter parsing string that stopped -l from working, thanks Bruno BOSQUED
 *
 * Revision 1.32  2000/10/19 06:55:41  robertj
 * Fixed compiler crash by rearranging loop.
 *
 * Revision 1.31  2000/08/29 23:11:41  robertj
 * Fixed MSVC warnings.
 *
 * Revision 1.30  2000/08/29 12:32:07  craigs
 * Fixed problems with recording messages
 *
 * Revision 1.29  2000/08/28 16:42:59  craigs
 * Finally fixed problems with G.723.1. All codecs now working
 *
 * Revision 1.28  2000/08/28 09:13:54  robertj
 * Fixed MSVC compiler warnings.
 *
 * Revision 1.27  2000/08/28 07:49:26  craigs
 * New code to maybe get G.723.1 replaying working
 *
 * Revision 1.26  2000/08/28 00:38:37  craigs
 * Added support for setting listening port number
 *
 * Revision 1.25  2000/08/27 23:42:24  craigs
 * Fixed problem with playback of messages
 * Fixed problem with recording messages
 *
 * Revision 1.24  2000/06/20 02:38:27  robertj
 * Changed H323TransportAddress to default to IP.
 *
 * Revision 1.23  2000/06/17 09:14:52  robertj
 * Added setting of closed flag when closing OGM.
 *
 * Revision 1.22  2000/05/25 13:25:47  robertj
 * Fixed incorrect "save" parameter specification.
 *
 * Revision 1.21  2000/05/25 12:06:17  robertj
 * Added PConfigArgs class so can save program arguments to config files.
 *
 * Revision 1.20  2000/05/11 11:47:11  robertj
 * Fixed alpha linux GNU compiler problems.
 *
 * Revision 1.19  2000/05/10 05:14:25  robertj
 * Changed capabilities so has a function to get name of codec, instead of relying on PrintOn.
 *
 * Revision 1.18  2000/05/09 11:22:15  craigs
 * Fixed problems caused by new jitter buffer code
 * and fixed OGM problems
 *
 * Revision 1.17  2000/05/09 02:41:32  craigs
 * Added extra debugging, and fixed problems with OGM in non-IVR mode
 *
 * Revision 1.16  2000/04/26 03:18:38  craigs
 * Fixed problem when GSM specified as preferred codec
 *
 * Revision 1.15  2000/04/25 23:34:22  craigs
 * Added lots of new code, including outgoing and incoming
 * multiplexors, and the start of an IVR system
 *
 * Revision 1.14  2000/01/13 04:03:45  robertj
 * Added video transmission
 *
 * Revision 1.13  2000/01/07 08:28:09  robertj
 * Additions and changes to line interface device base class.
 *
 * Revision 1.12  1999/12/10 01:44:46  craigs
 * Added ability to set interface
 *
 * Revision 1.11  1999/12/01 04:38:25  robertj
 * Added gatekeeper support to OpenAM
 *
 * Revision 1.10  1999/11/11 00:27:49  robertj
 * Changed OnAnswerCall() call back function  to allow for asyncronous response.
 *
 * Revision 1.9  1999/11/06 13:27:48  craigs
 * Added extra output and changed for new library changes
 *
 * Revision 1.8  1999/10/29 10:57:04  robertj
 * Added answering machine project.
 *
 * Revision 1.7  1999/10/24 12:50:37  craigs
 * Fixed G723.1 capability, and added ability for discrete OGMs
 *
 * Revision 1.6  1999/10/24 08:24:56  craigs
 * Added GSM capability back in
 *
 * Revision 1.5  1999/10/24 08:19:58  craigs
 * Fixed problem that caused crash when unknown codecs used
 *
 * Revision 1.4  1999/10/24 03:29:07  craigs
 * Fixed problem with -h parsing
 *
 * Revision 1.3  1999/10/24 03:08:49  craigs
 * Fixed problem with recording zero length messages, and added autodelete of files
 *
 * Revision 1.2  1999/10/22 09:56:24  craigs
 * Fixed various compile warnings
 *
 * Revision 1.1  1999/10/11 00:15:18  craigs
 * Initial version
 *
 */

#include <ptlib.h>
#include <ptlib/pipechan.h>
#include <signal.h>

#include "version.h"

#include "opalvxml.h"	// for G7231_File_Codec
#include "main.h"

PCREATE_PROCESS(OpenAm);

#define	DEFAULT_MSG_LIMIT	0		// unlimited
#define DEFAULT_CALL_LOG	"call_log.txt"

#define	G7231_SAMPLES_PER_BLOCK	240

#define CHECK_PCM   1
#define CHECK_G7231 2

#define	MENU_PREFIX		"UserMenu-"

#define DISABLE_COUT  1

static PMutex logMutex;
static PTextFile logFile;
static PFilePath logFilename = DEFAULT_CALL_LOG;

PString G7231Ext(".g723");
PString WAVExt(".wav");
PString PCMExt(".sw");


#if OPENAM_VIDEO
#include <ptclib/pvfiledev.h>

PString VideoGrabberDriverName("YUVFile");

#define DEFAULT_VIDEO_FRAME_RATE  10
#define DEFAULT_VIDEO_SIZE        "qcif"
#define DEFAULT_VIDEO_FORMAT      "pal"
#define DEFAULT_VIDEO_MODE        PVideoInputDevice_YUVFile::Channel_PlayAndClose

// these must be in the same order as the enum in PVideoInputDevice_YUVFile
static const char * VideoModes[PVideoInputDevice_YUVFile::ChannelCount] = {
  "Close",
  "Repeat",
  "KeepLast",
  "Black",
};

#endif // OPENAM_VIDEO


///////////////////////////////////////////////////////////////////////////////////////////

static void LogMessage(const PString & str)
{
  PTime now;
  PString msg = now.AsString("hh:mm:ss dd/MM/yyyy") & str;
  logMutex.Wait();

  if (!logFile.IsOpen()) {
    logFile.Open(logFilename, PFile::ReadWrite);
    logFile.SetPosition(0, PFile::End);
  }

  logFile.WriteLine(msg);

  logFile.Close();
  
  logMutex.Signal();
}

static void LogCall(const PFilePath & fn,
                    const PString & from,
                    const PString & user,
                    unsigned len,
                    const PString & codec,
                    const PString & product,
                    const PString & to)
{
  PString addr = from;
  LogMessage(addr + " \"" + user + "\" " + PString(PString::Unsigned, len) + " " + codec + " \"" + product + "\" \"" + fn + "\" \"" + to + "\"");
}


#ifdef _WIN32

BOOL WINAPI WinCtrlHandlerProc(DWORD dwCtrlType)
{
	PString eventName = "CTRL_UNKNOWN_EVENT";
	
	if( dwCtrlType == CTRL_LOGOFF_EVENT ) {
		eventName = "CTRL_LOGOFF_EVENT";
        LogMessage("OpenAM received " + eventName);
		// prevent shut down
		return FALSE;
	}
	
	if( dwCtrlType == CTRL_C_EVENT )
		eventName = "CTRL_C_EVENT";
	else if( dwCtrlType == CTRL_BREAK_EVENT )
		eventName = "CTRL_BREAK_EVENT";
	else if( dwCtrlType == CTRL_CLOSE_EVENT )
		eventName = "CTRL_CLOSE_EVENT";
	else if( dwCtrlType == CTRL_SHUTDOWN_EVENT )
		eventName = "CTRL_SHUTDOWN_EVENT";
	LogMessage("OpenAM shutdown due to " + eventName);

	OpenAm::Shutdown();	
	exit(1);
}

#else

void UnixShutdownHandler(int sig)
{
	LogMessage(PString("OpenAM received signal ") + PString(sig));

	OpenAm::Shutdown();	
	exit(1);
}

#endif

///////////////////////////////////////////////////////////////

MyH323EndPoint * OpenAm::endpoint = NULL;

OpenAm::OpenAm()
  : PProcess("OpenH323 Project", "OpenAM",
             MAJOR_VERSION, MINOR_VERSION, BUILD_TYPE, BUILD_NUMBER)
{
}


OpenAm::~OpenAm()
{
}


void OpenAm::Main()
{
  cout << GetName()
       << " Version " << GetVersion(TRUE)
       << " by " << GetManufacturer()
       << " on " << GetOSClass() << ' ' << GetOSName()
       << " (" << GetOSVersion() << '-' << GetOSHardware() << ")\n\n";

#ifdef _WIN32
	SetConsoleCtrlHandler(WinCtrlHandlerProc, TRUE);
#else
	signal(SIGTERM, UnixShutdownHandler);
	signal(SIGINT, UnixShutdownHandler);
	signal(SIGQUIT, UnixShutdownHandler);
#endif

  PConfigArgs args(GetArguments());

  args.Parse(
             "D-disable:"
             "d-directory:"
             "g-gatekeeper:"         "n-no-gatekeeper."
             "-g711-ulaw."           "-no-g711-ulaw."
             "-g711-alaw."           "-no-g711-alaw."
             "-g711message:"         "-no-g711message."
#if OPENAM_G723
             "-g7231."               "-no-g7231."
             "-g7231message:"        "-no-g7231message."
#endif
             "-ilbc."                "-no-ilbc."
             "-ilbcmessage:"         "-no-ilbcmessage."
             "-gsm."                 "-no-gsm."
             "-gsmmessage:"          "-no-gsmmessage."
             "h-help."
             "H-hangup."             "-no-hangup."
             "i-interface:"          "-no-interface."
             "k-kill."               "-no-kill."
             "l-limit:"              "-no-limit."
             "-listenport:"          "-no-listenport."
             "-lpc10message:"        "-no-lpc10message."
             "-speexmessage:"        "-no-speexmessage."
             "m-message:"            "-no-message."
             "-no-record."
             "-loop."
#if PTRACING
             "o-output:"
#endif
             "P-prefer:"
             "-pcm."                 "-no-pcm."
             "-pcmmessage:"          "-no-pcmmessage."
             "-port:"
             "r-run:"                "-no-run."
	           "-recordraw."
             "-require-gatekeeper."  "-no-require-gatekeeper."
             "-save."
#if PMEMORY_CHECK
             "-setallocationbreakpoint:"
#endif
#if PTRACING
             "t-trace."
#endif
			 "u-username:"           "-no-username."
             "p-password:"
             "-displayname:"
#if OPENAM_VIDEO
             "-videomessage:"
             "-videorate:"
             "-videosize:"
             "-videobitrate:"
             "-videoformat:"
             "-videomode:"
#endif
			"-tcp-minport:"
			"-tcp-maxport:"
			"-udp-minport:"
			"-udp-maxport:"
			"-rtp-minport:"
			"-rtp-maxport:"
          , FALSE);

#if PMEMORY_CHECK
  if (args.HasOption("setallocationbreakpoint"))
    PMemoryHeap::SetAllocationBreakpoint(args.GetOptionString("setallocationbreakpoint").AsInteger());
#endif

#if PTRACING
  PTrace::Initialise(args.GetOptionCount('t'),
                     args.HasOption('o') ? (const char *)args.GetOptionString('o') : NULL,
                     PTrace::DateAndTime | PTrace::TraceLevel | PTrace::FileAndLine);
#endif

  if (args.HasOption('h')) {
    cout << "Usage : " << GetName() << " [options]\n"
            "Options:\n"
            "  -d --directory dir  : Put recorded mesages into dir\n"
            "  -l --limit secs     : Limit recorded messages to secs duration (default " << DEFAULT_MSG_LIMIT << ")\n"
            "  --no-record         : Don't record a message\n"
            "  -m --pcmmessage fn  : Set outgoing message for PCM derived codecs (G.711/GSM) to fn\n"
#if OPENAM_G723
            "  --g7231message fn   : Set outgoing message for G723.1 codec to fn\n"
            "  --g711message fn    : Set outgoing message for G711 codec to fn\n"
#endif
            "  --gsmmessage fn     : Set outgoing message for GSM codec to fn\n"
            "  --lpc10message fn   : Set outgoing message for LPC10 codec to fn\n"
            "  --speexmessage fn   : Set outgoing message for Speex codec to fn\n"
            "  --ilbcmessage fn    : Set outgoing message for iLBC codec to fn\n"
#if OPENAM_VIDEO
            "  --videomessage fn   : Set outgoing message for video to fn\n"
            "  --videorate num     : Set video frame rate (default is " << DEFAULT_VIDEO_FRAME_RATE << ")\n"
            "  --videobitrate rate : Set video max bit rate for video (default is unlimited)\n"
            "  --videosize size    : Set video frame size (default is " << DEFAULT_VIDEO_SIZE << ")\n"
            "                      : Must be one of qcif or cif\n"
            "  --videoformat fmt   : Set video frame format (default is " << DEFAULT_VIDEO_FORMAT << ")\n"
            "                      : Must be one of pal or ntsc\n"
            "  --videomode mode:   : Set video play mode. Default is " << VideoModes[DEFAULT_VIDEO_MODE] << "\n"
            "                      : Must be one of Close, Repeat, KeepLast or Black\n"
#endif
            "  --loop              : loop message, no recording\n"

            "  --recordraw         : Record PCM audo in raw files (.sw) instead of .wav\n"
            "  -r --run cmd        : Run this command after each recorded message\n"
            "  -k --kill           : Kill recorded files after user command\n"
            "  -H --hangup         : hangup after playing message\n"
            "  -u --username str   : Set the local endpoint name to str\n"
            "  -p --password str   : Set the gatekeeper password to str\n"
            "  --displayname str   : Set the display name to str\n"
            "  -i --interface ip   : Bind to a specific interface\n"
            "  --listenport port   : Listen on a specific port\n"
			"  --tcp-minport port  : Set min TCP port to use for H.245\n"
			"  --tcp-maxport port  : Set max TCP port to use for H.245\n"
			"  --udp-minport port  : Set min UDP port to use for RAS\n"
			"  --udp-maxport port  : Set max UDP port to use for RAS\n"
			"  --rtp-minport port  : Set min UDP port to use for RTP\n"
			"  --rtp-maxport port  : Set max UDP port to use for RTP\n"
            "  -g --gatekeeper host: Specify gatekeeper host.\n"
            "  -n --no-gatekeeper  : Disable gatekeeper discovery.\n"
            "  --require-gatekeeper: Exit if gatekeeper discovery fails.\n"
            "  -D --disable codec  : Disable the specified codec (may be used multiple times)\n"
            "  -P --prefer codec   : Prefer the specified codec (may be used multiple times)\n"
#if PTRACING
            "  -t --trace          : Enable trace, use multiple times for more detail\n"
            "  -o --output         : File for trace output, default is stderr\n"
#endif
            "     --save           : Save arguments in configuration file\n"
            "  -h --help           : Display this help message\n";
    return;
  }

  args.Save("save");

  unsigned callLimit = DEFAULT_MSG_LIMIT;
  if (args.HasOption('l')) {
    callLimit = args.GetOptionString('l').AsInteger();
    if (callLimit > 3600) {
      cout << "warning: maximum call length " << callLimit << " is out of range. Using " << DEFAULT_MSG_LIMIT << " instead\n";
      callLimit = DEFAULT_MSG_LIMIT;
    } else if (callLimit == 0)
      cout << "warning: recorded message call limit disabled\n";
  }
  if (!args.HasOption("no-record") && !args.HasOption("loop"))
	  cout << "Recorded messages limited to " << callLimit << " seconds\n";
  else
	  cout << "Recording disabled\n";

  PString runCmd;
  if (args.HasOption('r')) {
    runCmd = args.GetOptionString('r');
    cout << "Executing \"" << runCmd << "\" after each message" << endl;
  }

  PDirectory dir;
  if (args.HasOption('d'))
    dir = args.GetOptionString('d');

  int flags = 0;

  if (args.HasOption('k')) {
    cout << "Deleting recorded files after processing" << endl;
    if (runCmd.IsEmpty()) 
      cout << "WARNING: recorded files will be deleted even though no run command is present" << endl;
    flags |= MyH323EndPoint::DeleteAfterRecord;
  }

  if (args.HasOption('H'))
    flags |= MyH323EndPoint::HangupAfterPlay;

  endpoint = new MyH323EndPoint(callLimit, runCmd, dir, flags);

  PString userName = "OpenH323 Answering Machine v" + GetVersion();
  if (args.HasOption('u'))
    userName = args.GetOptionString('u');
  endpoint->SetLocalUserName(userName);
  if (args.HasOption("displayname"))
	  endpoint->SetDisplayName(args.GetOptionString("displayname"));

  if (args.HasOption('p')) {
    const PString password = args.GetOptionString('p');
    endpoint->SetGatekeeperPassword(password);
  }
  
  // set port ranges
  if (args.HasOption("tcp-minport")) {
	  unsigned tcpMinPort = args.GetOptionString("tcp-minport").AsInteger();
	  if (tcpMinPort > 65536)
		  tcpMinPort = 65536;
	  unsigned tcpMaxPort = 65536;
	  if (args.HasOption("tcp-maxport")) {
		  tcpMaxPort = args.GetOptionString("tcp-maxport").AsInteger();
		  if (tcpMaxPort > 65536)
			  tcpMaxPort = 65536;
	  }
	  endpoint->SetTCPPorts(tcpMinPort, tcpMaxPort);
  }
  if (args.HasOption("udp-minport")) {
	  unsigned udpMinPort = args.GetOptionString("udp-minport").AsInteger();
	  if (udpMinPort > 65536)
		  udpMinPort = 65536;
	  unsigned udpMaxPort = 65536;
	  if (args.HasOption("udp-maxport")) {
		  udpMaxPort = args.GetOptionString("udp-maxport").AsInteger();
		  if (udpMaxPort > 65536)
			  udpMaxPort = 65536;
	  }
	  endpoint->SetUDPPorts(udpMinPort, udpMaxPort);
  }
  if (args.HasOption("rtp-minport")) {
	  unsigned rtpMinPort = args.GetOptionString("rtp-minport").AsInteger();
	  if (rtpMinPort > 65536)
		  rtpMinPort = 65536;
	  unsigned rtpMaxPort = 65536;
	  if (args.HasOption("rtp-maxport")) {
		  rtpMaxPort = args.GetOptionString("rtp-maxport").AsInteger();
		  if (rtpMaxPort > 65536)
			  rtpMaxPort = 65536;
	  }
	  endpoint->SetRtpIpPorts(rtpMinPort, rtpMaxPort);
  }
  
  if (!endpoint->Initialise(args))
    return;

  // start the H.323 listener
  H323ListenerTCP * listener;
  PIPSocket::Address interfaceAddress(INADDR_ANY);
  WORD listenPort = H323EndPoint::DefaultTcpPort;

  if (args.HasOption("listenport"))
    listenPort = (WORD)args.GetOptionString("listenport").AsInteger();

  if (args.HasOption('i'))
    interfaceAddress = PIPSocket::Address(args.GetOptionString('i'));

  listener  = new H323ListenerTCP(*endpoint, interfaceAddress, listenPort);

  if (!endpoint->StartListener(listener)) {
    cout <<  "Could not open H.323 listener port on "
         << listener->GetListenerPort() << endl;
    delete listener;
    return;
  }

  if (args.HasOption('g')) {
    PString gkName = args.GetOptionString('g');
    if (endpoint->SetGatekeeper(gkName, new H323TransportUDP(*endpoint)))
      cout << "Gatekeeper set: " << *endpoint->GetGatekeeper() << endl;
    else {
      cout << "Error registering with gatekeeper at \"" << gkName << '"' << endl;
      return;
    }
  }
  else if (!args.HasOption('n')) {
    cout << "Searching for gatekeeper..." << flush;
    if (endpoint->DiscoverGatekeeper(new H323TransportUDP(*endpoint)))
      cout << "\nGatekeeper found: " << *endpoint->GetGatekeeper() << endl;
    else {
      cout << "\nNo gatekeeper found." << endl;
      if (args.HasOption("require-gatekeeper"))
        return;
    }
  }

  cout << "Waiting for incoming calls for \"" << endpoint->GetLocalUserName() << '"' << endl;

  for (;;) 
    PThread::Current()->Sleep(5000);
}

void OpenAm::Shutdown()
{
	if (endpoint) {
		if (endpoint->IsRegisteredWithGatekeeper())
			endpoint->RemoveGatekeeper();
		delete endpoint;
	}
	_exit(0);	// HACK: avoid destruction of global objects
}


///////////////////////////////////////////////////////////////

MyH323EndPoint::MyH323EndPoint(unsigned _callLimit,
                               const PString & _runCmd,
                               const PDirectory & _dir,
                               int   _flags)
  : callLimit(_callLimit), runCmd(_runCmd), dir(_dir), flags(_flags)
{
#if OPENAM_VIDEO
  videoSize    = 0;
  videoIsPal   = TRUE;
  frameRate    = DEFAULT_VIDEO_FRAME_RATE;
  videoChannel = DEFAULT_VIDEO_MODE;
#endif
}

MyH323EndPoint::~MyH323EndPoint()
{
}

PBoolean MyH323EndPoint::OnIncomingCall(H323Connection & _conn,
                                    const H323SignalPDU & setupPDU,
                                    H323SignalPDU &)
{
  MyH323Connection & conn = (MyH323Connection &)_conn;

  // see if incoming call is to an E.164 number
  PString number;
  if (setupPDU.GetDestinationE164(number)) 
    conn.SetE164Number(number);

  return TRUE;
}

H323Connection * MyH323EndPoint::CreateConnection(unsigned callReference)
{
  unsigned options = 0;
  options |= H323Connection::H245TunnelingOptionDisable;
//  options |= H323Connection::FastStartOptionDisable;
//  options |= H323Connection::H245inSetupOptionDisable;
  return new MyH323Connection(*this, callReference, options);
}

PBoolean MyH323EndPoint::Initialise(PConfigArgs & args)
{
  // format for record files, raw or wav
  if (args.HasOption("recordraw")) 
    SetRecordWav(FALSE);
  else
    SetRecordWav(TRUE);

#if OPENAM_G723
  // get G.723.1 OGM
  if (args.HasOption("g7231message"))
    g7231Ogm = args.GetOptionString("g7231message");
  else if (args.HasOption('m'))  {
    if (PFile::Exists(args.GetOptionString('m') + "_g7231" + WAVExt)) {
      g7231Ogm = args.GetOptionString('m') + "_g7231" + WAVExt;
    }
    else if (PFile::Exists(args.GetOptionString('m') + PCMExt)) {
      g7231Ogm = args.GetOptionString('m') + G7231Ext;
    }
  }

  if (!g7231Ogm.IsEmpty()) {
    // check if the file exists. (do not check if filename contains %s)
    if ((g7231Ogm.Find("%s") == P_MAX_INDEX) && !PFile::Exists(g7231Ogm)) {
      cout << "warning: cannot open G723.1 OGM file \"" << g7231Ogm << "\"" << endl;
      g7231Ogm = "";
    } 
  }

  if (g7231Ogm.IsEmpty()) 
    cout << "No G.723.1 outgoing message set\n";
  else {
    cout << "Using \"" << g7231Ogm << "\" as G.723.1 outgoing message\n";
  }
#endif

  // Get the OGM message for the 'PCM' codecs
  // Check if the file specified exists. If it does, use it.
  // If it does not exist, try with .wav and .sw extensions.
  if (args.HasOption("pcmmessage")) {
    pcmOgm = args.GetOptionString("pcmmessage");
  }
  else if (args.HasOption('m')) {
      if (PFile::Exists(args.GetOptionString('m'))) {
        pcmOgm = args.GetOptionString('m');
      }
      else if (PFile::Exists(args.GetOptionString('m') + WAVExt)) {
        pcmOgm = args.GetOptionString('m') + WAVExt;
      }
      else if (PFile::Exists(args.GetOptionString('m') + PCMExt)) {
        pcmOgm = args.GetOptionString('m') + PCMExt;
      }
  }

  if (args.HasOption("no-record"))
    SetNoRecord(TRUE);
  else
	SetNoRecord(FALSE);

  if (args.HasOption("loop")) {
    SetLoopMessage(TRUE);
    SetNoRecord(TRUE);
  } else
	SetLoopMessage(FALSE);


  // By default, use the pcmOgm for all the PCM codecs, but allow the user
  // to override them.
  gsmOgm   = pcmOgm;
  g711Ogm  = pcmOgm;
  lpc10Ogm = pcmOgm;
  speexOgm = pcmOgm;
  ilbcOgm  = pcmOgm;

  // We can set the filename for specific codecs.
  if (args.HasOption("gsmmessage")) 
    gsmOgm = args.GetOptionString("gsmmessage");

  if (args.HasOption("g711message")) 
    g711Ogm = args.GetOptionString("g711message");

  if (args.HasOption("lpc10message")) 
    lpc10Ogm = args.GetOptionString("lpc10message");

  if (args.HasOption("speexmessage")) 
    speexOgm = args.GetOptionString("speexmessage");

  if (args.HasOption("ilbcmessage")) 
    ilbcOgm = args.GetOptionString("ilbcmessage");
    
  if (args.HasOption("ilbcmessage")) 
    ilbcOgm = args.GetOptionString("ilbcmessage");

  // Check GSM OGM message
  if (!gsmOgm.IsEmpty()) {
    if ((gsmOgm.Find("%s") == P_MAX_INDEX) && !PFile::Exists(gsmOgm)) {
      cout << "warning: cannot open GSM OGM file \"" << gsmOgm << "\"" << endl;
      gsmOgm = "";
    }
  } 
  if (gsmOgm.IsEmpty()) 
    cout << "No GSM outgoing message set\n";
  else {
    cout << "Using \"" << gsmOgm << "\" as GSM outgoing message\n";
  }

  // Check G.711 OGM message 
  if (!g711Ogm.IsEmpty()) {
    if ((g711Ogm.Find("%s") == P_MAX_INDEX) && !PFile::Exists(g711Ogm)) {
      cout << "warning: cannot open G711 OGM file \"" << g711Ogm << "\"" << endl;
      g711Ogm = "";
    }
  } 
  if (g711Ogm.IsEmpty()) 
    cout << "No G711 outgoing message set\n";
  else {
    cout << "Using \"" << g711Ogm << "\" as G.711 outgoing message\n";
  }

  // Check LPC10 OGM message 
  if (!lpc10Ogm.IsEmpty()) {
    if ((lpc10Ogm.Find("%s") == P_MAX_INDEX) && !PFile::Exists(lpc10Ogm)) {
      cout << "warning: cannot open LPC10 OGM file \"" << lpc10Ogm << "\"" << endl;
      lpc10Ogm = "";
    }
  } 
  if (lpc10Ogm.IsEmpty()) 
    cout << "No LPC10 outgoing message set\n";
  else {
    cout << "Using \"" << lpc10Ogm << "\" as LPC10 outgoing message\n";
  }

  // Check Speex OGM message 
  if (!speexOgm.IsEmpty()) {
    // check if the file exists. (do not check if filename contains %s)
    if ((speexOgm.Find("%s") == P_MAX_INDEX) && !PFile::Exists(speexOgm)) {
      cout << "warning: cannot open Speex OGM file \"" << speexOgm << "\"" << endl;
      speexOgm = "";
    }
  } 
  if (speexOgm.IsEmpty()) 
    cout << "No Speex outgoing message set\n";
  else {
    cout << "Using \"" << speexOgm << "\" as Speex outgoing message\n";
  }

  // Check iLBC OGM message 
  if (!ilbcOgm.IsEmpty()) {
    // check if the file exists. (do not check if filename contains %s)
    if ((ilbcOgm.Find("%s") == P_MAX_INDEX) && !PFile::Exists(ilbcOgm)) {
      cout << "warning: cannot open iLBC OGM file \"" << ilbcOgm << "\"" << endl;
      ilbcOgm = "";
    }
  } 
  if (ilbcOgm.IsEmpty()) 
    cout << "No iLBC outgoing message set\n";
  else {
    cout << "Using \"" << ilbcOgm << "\" as iLBC outgoing message\n";
  }

#if OPENAM_VIDEO
  // Check for video message
  videoOgm = args.GetOptionString("videomessage");
#endif

  if (g7231Ogm.IsEmpty() && gsmOgm.IsEmpty() && g711Ogm.IsEmpty()
                         && lpc10Ogm.IsEmpty() && speexOgm.IsEmpty()
#if OPENAM_VIDEO
                         && videoOgm.IsEmpty()
#endif
			 ) {
    cerr << "Must specify at least one outgoing message" << endl;
    return FALSE;
  }

  AddAllCapabilities(0, P_MAX_INDEX, "*");

#if OPENAM_VIDEO
  if (!videoOgm.IsEmpty()) {

    autoStartTransmitVideo = TRUE;

    cout << "Using \"" << videoOgm << "\" as video outgoing message\n";

    OpalMediaFormat::List mediaFormats = H323PluginCodecManager::GetMediaFormats();

	videoBitRate = 0; // disable setting videoBitRate.
	if (args.HasOption("videobitrate")) {
		videoBitRate = args.GetOptionString("videobitrate").AsInteger();
		videoBitRate = 1024 * PMAX(16, PMIN(2048, videoBitRate));
	}

    videoSize = (PString(DEFAULT_VIDEO_SIZE) *= "qcif") ? 0 : 1;
    if (args.GetOptionString("videosize") *= "cif")
      videoSize = 1;

    videoIsPal = PString(DEFAULT_VIDEO_FORMAT) *= "pal";
    if (args.HasOption("videoformat"))
      videoIsPal = args.GetOptionString("videoformat") *= "pal";

    cout << "Video size is " << (videoIsPal ? "pal" : "ntsc") << " " << (videoSize == 0 ? "qcif" : "cif") << endl;

    frameRate = DEFAULT_VIDEO_FRAME_RATE;
    if (args.HasOption("videorate"))
      frameRate = args.GetOptionString("videorate").AsInteger();
    cout << "Video frame rate is " << frameRate << endl;

    videoChannel = DEFAULT_VIDEO_MODE;
    {
      PString str = args.GetOptionString("videomode");
      if (!str.IsEmpty()) {
        PINDEX i;
        for (i = 0; VideoModes[i] != NULL; ++i) 
          if (str *= VideoModes[i])
            break;
        if (VideoModes[i] == NULL) {
          PError << "error: cannot set video mode " << str << endl;
          return FALSE;
        }
        videoChannel = i;
      }
    }
    cout << "Video play mode is " << VideoModes[videoChannel] << endl;
  }

#endif  // OPENAM_VIDEO

  PString removeString;
  if (gsmOgm.IsEmpty())
    removeString = removeString & OpalGSM0610 & "MS-GSM";

  if (speexOgm.IsEmpty())
    removeString = removeString & "Speex";
 
  if (g711Ogm.IsEmpty())
    removeString = removeString & "G.711";

  if (lpc10Ogm.IsEmpty())
    removeString = removeString & "LPC-10";

  if (ilbcOgm.IsEmpty())
    removeString = removeString & "iLBC";

#if OPENAM_VIDEO
  if (videoOgm.IsEmpty())
    removeString = removeString & "H.261 H.263 H.264";	// TODO: disable all possible video codecs
#endif

  // also remove other codecs we do don't have an OGM for
  removeString = removeString & "G.726";

#ifdef OPENAM_G723
  if (!g7231Ogm.IsEmpty())
    SetCapability(0, 0, new G7231_File_Capability);
#endif

  capabilities.Remove(args.GetOptionString('D').Lines());
  if (!removeString.IsEmpty())
    capabilities.Remove(removeString.Tokenise(' '));
  capabilities.Reorder(args.GetOptionString('P').Lines());

  cout << "Codecs (in preference order):\n" << setprecision(2) << capabilities << endl;

  return TRUE;
}

///////////////////////////////////////////////////////////////

PCM_RecordFile::PCM_RecordFile(MyH323Connection & _conn, const PFilePath & _fn, unsigned _callLimit)
  : conn(_conn), fn(_fn), callLimit(_callLimit)
{
  recordStarted = FALSE;
  timeLimitExceeded = FALSE;
  closed        = FALSE;
  dataWritten   = FALSE;

  // If the file name ends in .wav then open the output as a WAV file.
  // Otherwise open it as a raw file.
  if ((_fn.Right(4)).ToLower() == ".wav")
    fileclass = new PWAVFile(_fn, PFile::WriteOnly,
			     PFile::ModeDefault,PWAVFile::PCM_WavFile);
  else
    fileclass = new PFile(_fn, PFile::WriteOnly);
}

void PCM_RecordFile::StartRecording()
{
  PWaitAndSignal mutex(pcmrecordMutex);

  if (recordStarted)
    return;

  PTRACE(1, "Starting recording to " << fn);

  PTime now;
  recordStarted = TRUE;
  finishTime = now + (callLimit * 1000);
}

PBoolean PCM_RecordFile::Close()
{
  PWaitAndSignal mutex(pcmrecordMutex);

  closed = TRUE;
  return fileclass->Close();
}

PBoolean PCM_RecordFile::Write(const void * buf, PINDEX len)
{
  // Wait for the mutex, and Signal it at the end of this function
  PWaitAndSignal mutex(pcmrecordMutex);

  // If the record file has been closed, or if the time limit has
  // been exceeded, then return immediatly.
  if (closed || timeLimitExceeded)
    return FALSE;

  if (!recordStarted) {
    DelayFrame(len);
    return TRUE;
  }

  PTime now;
  if ((callLimit != 0) && (now >= finishTime)) {
    PTRACE(1, "Terminating call due to timeout");
    conn.ClearCall();
    timeLimitExceeded = TRUE;
    return TRUE;
  }

  DelayFrame(len);

  dataWritten = TRUE;

  return WriteFrame(buf, len);
}

PBoolean PCM_RecordFile::WriteFrame(const void * buf, PINDEX len)
{
  //cerr << "Writing PCM " << len << endl;
  return  fileclass->Write(buf, len);
}

void PCM_RecordFile::DelayFrame(PINDEX len)
{
  delay.Delay(len/16);
}

PCM_RecordFile::~PCM_RecordFile()
{
  PWaitAndSignal mutex(pcmrecordMutex);

  if (!dataWritten) {
    PTRACE(1, "Deleting " << fn << " as no data recorded");
    fileclass->Remove(fn);
  }

  delete fileclass;
}

///////////////////////////////////////////////////////////////
// Override some of the PCM_RecordFile functions to write
// G723.1 data instead of PCM data.

G7231_RecordFile::G7231_RecordFile(MyH323Connection & _conn, const PFilePath & _fn, unsigned _callLimit)
  : PCM_RecordFile(_conn, _fn, _callLimit)
{
  // If the record file is a .wav file, we need to close the file
  // that PCM_RecordFile will have opened, and reopen it as a G.723.1 Wav file.
  if ((_fn.Right(4)).ToLower() == ".wav") {
    fileclass->Remove(_fn);
    delete fileclass;
    fileclass = new PWAVFile(_fn, PFile::WriteOnly,
			     PFile::ModeDefault,PWAVFile::G7231_WavFile);
  }
}

PBoolean G7231_RecordFile::WriteFrame(const void * buf, PINDEX /*len*/)
{
#ifdef OPENAM_G723
  int frameLen = G7231_File_Codec::GetFrameLen(*(BYTE *)buf);
//  cerr << "Writing G7231 " << frameLen << endl;
  return fileclass->Write(buf, frameLen);
#else
  return FALSE;
#endif
}

void G7231_RecordFile::DelayFrame(PINDEX /*len*/)
{
  // Ignore the len parameter as that is the compressed size.
  // We must delay by the actual sample time.
  delay.Delay((G7231_SAMPLES_PER_BLOCK*2)/16);
}

///////////////////////////////////////////////////////////////

static PBoolean MatchString(const PString & str1, const PString str2)
{
  if (str1.GetLength() != str2.GetLength())
    return FALSE;

  PINDEX len = str1.GetLength();

  PINDEX i;
  for (i = 0; i < len; i++) 
    if ((str1[i] != '?') && (str2[i] != '?') && (str1[i] != str2[i]))
      return FALSE;

  return TRUE;
}

static PINDEX FindMatch(const PStringList & list, const PString & key)
{
  PINDEX maxKeyLen = 0;
  PINDEX i;

  PINDEX keyLen = key.GetLength();
  PINDEX listLen = list.GetSize();

  for (i = 0; i < listLen; i++)
    maxKeyLen = PMAX(maxKeyLen, list[i].GetLength());

  if (keyLen == 0 || maxKeyLen == 0)
    return P_MAX_INDEX;

  if (keyLen > maxKeyLen)
    return P_MAX_INDEX;

  PINDEX len = 1;
  while (len <= keyLen) {
    PString subStr = key.Left(len);

    PINDEX matches = 0;
    PINDEX lastMatch = P_MAX_INDEX;
    PINDEX i;

    // look for a match to the substring
    for (i = 0; i < list.GetSize(); i++) {
      if ((list[i].GetLength() >= keyLen) && MatchString(list[i].Left(len), subStr)) {
        matches++;
        lastMatch = i;
      }
    }

    // if we got ONE match, we have a winner
    if (matches == 1)
      return lastMatch+1;

    // if we have no matches, then there is no point continuing
    if (matches == 0)
      return P_MAX_INDEX;

    // if we have more than one match, try the next char
    len++;
  }

  // too many matches
  return 0;
}


MyH323Connection::MyH323Connection(MyH323EndPoint & _ep, unsigned callReference, unsigned _options)
  : H323Connection(_ep, callReference, _options), ep(_ep)
{
  basename = psprintf("%04i%02i%02i_%02i%02i%02i", callStartTime.GetYear(), callStartTime.GetMonth(),  callStartTime.GetDay(),
                                                   callStartTime.GetHour(), callStartTime.GetMinute(), callStartTime.GetSecond());
  recordFile = NULL;
  ogmChannel = NULL;

  receiveAudioCodecName = transmitAudioCodecName = "none";

#if OPENAM_VIDEO
  receiveVideoCodecName = transmitVideoCodecName = "none";
#endif

#ifndef DISABLE_COUT
  cout << "Opening connection" << endl;
#endif

  currentMenu = 0;
  digits = "";

  PConfig config;
  PStringList sections = config.GetSections();
  PINDEX i;
  for (i = 0; i < sections.GetSize(); i++) {
    if (sections[i].Find(MENU_PREFIX) == 0) 
      menuNames.AppendString(sections[i]);
  }

  if (!_ep.GetDisplayName().IsEmpty())
	SetDisplayName(_ep.GetDisplayName());
}

PBoolean MyH323Connection::OnReceivedSignalSetup(const H323SignalPDU & setupPDU)
{
  if (!H323Connection::OnReceivedSignalSetup(setupPDU))
    return FALSE;

  // extract the called number
  const H225_Setup_UUIE & setup = setupPDU.m_h323_uu_pdu.m_h323_message_body;
  if (setup.HasOptionalField(H225_Setup_UUIE::e_destinationAddress) && setup.m_destinationAddress.GetSize() > 0) {
    calledParty = H323GetAliasAddressString(setup.m_destinationAddress[0]);
  }

  return TRUE;
}

MyH323Connection::~MyH323Connection()
{
  cout << "Call ended" << endl;

  PTime now;
  PTimeInterval interval = now - recordStartTime;
  PString addr = GetControlChannel().GetRemoteAddress();

  PString codecStr = receiveAudioCodecName + "/" + transmitAudioCodecName;
#if OPENAM_VIDEO
  codecStr += "/" + transmitVideoCodecName;
#endif

  unsigned duration = (unsigned)((interval.GetMilliSeconds()+999)/1000);

  LogCall(recordFn, addr, GetRemotePartyName(), duration, codecStr, product, calledParty);

  if ((recordFile!= NULL) && (recordFile->WasRecordStarted()) && !ep.GetRunCmd().IsEmpty()) {
    PString cmdStr = ep.GetRunCmd() +
                     recordFn +
                     "'" + addr + "' " +
                     "\"" + GetRemotePartyName() + "\" " +
                     PString(PString::Unsigned, duration) +
                     "\"" + codecStr + "\" " +
                     "\"" + product + "\" " +
                     "\"" + calledParty + "\"";
    PTRACE(1, "Executing : " << cmdStr);
    int status = system((const char *)cmdStr);
    if (status != 0) {
    PTRACE(1, "Execution failed with code " << status);
    }
  } else {
    PTRACE(1, "No action to perform at end of record");
  }

  if (ogmChannel != NULL)
    delete ogmChannel;

  if (recordFile != NULL)
    delete recordFile;

  if (ep.GetDeleteAfterRecord()) {
    PTRACE(1, "Removing " << recordFn << " as requested by option");
    PFile::Remove(recordFn);
  }
}

H323Connection::AnswerCallResponse
     MyH323Connection::OnAnswerCall(const PString & caller,
                                    const H323SignalPDU & setupPDU,
                                    H323SignalPDU & /*connectPDU*/)
{
  product = "Unknown";

  const H225_Setup_UUIE & setup = setupPDU.m_h323_uu_pdu.m_h323_message_body;
  const H225_EndpointType & epInfo = setup.m_sourceInfo;

  if (epInfo.HasOptionalField(H225_EndpointType::e_vendor)) {
    const H225_VendorIdentifier & vendorInfo = epInfo.m_vendor;
    if (vendorInfo.HasOptionalField(H225_VendorIdentifier::e_productId))
      product = vendorInfo.m_productId.AsString();
    if (vendorInfo.HasOptionalField(H225_VendorIdentifier::e_versionId))
      product = product + "/" + vendorInfo.m_versionId.AsString();
  }
  
  cout << "Accepting call from " << caller << " using " << product << endl;

  return AnswerCallNow;
}

void MyH323Connection::OnSendCapabilitySet(H245_TerminalCapabilitySet & pdu)
{
	H323Connection::OnSendCapabilitySet(pdu);

#ifdef OPENAM_VIDEO
	// reduce maxBitRate for H.261 and H.263
	unsigned newMaxBitRate = ep.GetVideoBitRate();
	if (newMaxBitRate > 0) {
		for (PINDEX i=0; i < pdu.m_capabilityTable.GetSize(); i++) {
			H245_Capability & cap = pdu.m_capabilityTable[i].m_capability;
			if (cap.GetTag() == H245_Capability::e_receiveVideoCapability) {
				H245_VideoCapability & videocap = cap;
				if (videocap.GetTag() == H245_VideoCapability::e_h261VideoCapability) {
					H245_H261VideoCapability & h261cap = videocap;
					h261cap.m_maxBitRate = newMaxBitRate;
				} else if (videocap.GetTag() == H245_VideoCapability::e_h263VideoCapability) {
					H245_H263VideoCapability & h263cap = videocap;
					h263cap.m_maxBitRate = newMaxBitRate;
				}
			}
		}
	}
#endif
}

PBoolean MyH323Connection::OpenAudioChannel(PBoolean isEncoding, 
                                        unsigned /* bufferSize */, 
                                        H323AudioCodec & codec)
{
  codec.SetSilenceDetectionMode(H323AudioCodec::NoSilenceDetection);
  PString codecName = codec.GetMediaFormat();

  PString ogm;
  PBoolean isPCM = FALSE;

  if (codecName == OPAL_G7231_6k3) {
    ogm   = ep.GetG7231OGM();
    isPCM = FALSE;
  } else {
    isPCM = TRUE;
    if (codecName == OPAL_G711_ULAW_64K || codecName == OPAL_G711_ALAW_64K)
      ogm = ep.GetG711OGM();
    else if (codecName == OPAL_GSM0610)
      ogm = ep.GetGSMOGM();
    else if (codecName.Find("iLBC") != P_MAX_INDEX)
      ogm = ep.GetiLBCOGM();
    else if (codecName.Find("Speex") != P_MAX_INDEX)
      ogm = ep.GetSPEEXOGM();
    else {
      cerr << "Unsupported codec \"" << codecName << endl;
      return FALSE;
    }
  }

  PWaitAndSignal mutex(connMutex);

  if ((recordFile == NULL) && (isEncoding == FALSE)) {
    if (isPCM) {
      if (ep.GetRecordWav() == TRUE)
	      recordFn = ep.GetDirectory() + (basename + ".wav");
      else
	      recordFn = ep.GetDirectory() + (basename + ".sw");
      recordFile = new PCM_RecordFile  (*this, recordFn, ep.GetCallLimit());
    } else {
      if (ep.GetRecordWav() == TRUE)
	      recordFn = ep.GetDirectory() + (basename + ".wav");
      else
	      recordFn = ep.GetDirectory() + (basename + ".g723");
      recordFile = new G7231_RecordFile(*this, recordFn, ep.GetCallLimit());
    }
  }

  if ((ogmChannel == NULL) && (isEncoding == TRUE)) {
    if (isPCM)
      ogmChannel = new PCM_OGMChannel(*this);
    else
      ogmChannel = new G7231_OGMChannel(*this);
  }

  if (isEncoding) {

    if (ep.GetHangupAfterPlay())
      ogmChannel->SetPlayOnce();

	if (ep.GetLoopMessage())
	  ogmChannel->SetLoopMessage();

    if (ogm.Find("%s"))
      ogm.Replace("%s", e164Number);

    transmitAudioCodecName = codecName;
    if (!StartMenu(0)) {
      if (!PFile::Exists(ogm)) {
        cerr << "error: cannot find OGM \"" << ogm << "\"" << endl;
        return FALSE;
      }
      else
        ogmChannel->QueueFile(ogm);
      if (!ep.GetNoRecord())
        ogmChannel->SetRecordTrigger();
    }
    codec.AttachChannel(ogmChannel, FALSE);
  } else {
    receiveAudioCodecName = codecName;
    codec.AttachChannel(recordFile, FALSE);
  }

  return TRUE;
}

#if OPENAM_VIDEO

PBoolean MyH323Connection::OpenVideoChannel(PBoolean isEncoding, H323VideoCodec & codec)
{
  PString capture_filename(ep.GetDirectory() + (basename + ".yuv"));
  if (!isEncoding) {	// incoming connection
    receiveVideoCodecName = codec.GetMediaFormat(); 
    PVideoOutputDevice * display = NULL;
	if (ep.GetNoRecord()) {
		// TODO: this would be better, but fails when building with 'make optnoshared'
		// PTRACE(3, "Try to create NULLOutput device");
		// display = PVideoOutputDevice::CreateDevice("NULLOutput");
		display = new PVideoOutputDevice_YUVFile();
		PTRACE(3, "Try to create YUVFile device on NULL device");
#ifdef _WIN32
		capture_filename = "NUL:";
#else
		capture_filename = "/dev/null";
#endif
	} else {
		PTRACE(3, "Try to create YUVFile device");
		display = new PVideoOutputDevice_YUVFile();
	}   
    if (display == NULL) {
      PTRACE(1, "Cannot create video output device");
      return FALSE;
    }

    if (!display->Open(capture_filename)) {
      PTRACE(1, "Cannot open capture file " << capture_filename);
      delete display;
      return FALSE;
    }
     
    display->SetFrameSize(codec.GetWidth(), codec.GetHeight()); // needed to enable resize
    display->SetColourFormatConverter("YUV420P");

	PTRACE(1,"Video device opened IN: " << codec.GetMediaFormat() << " : " << codec.GetWidth() << "x" << codec.GetHeight());
    PVideoChannel * channel = new TimeLimitedVideoChannel(*this, ep.GetCallLimit()); 
    channel->AttachVideoPlayer(display); 
    return codec.AttachChannel(channel,TRUE);
  }

  PString nameStr = isEncoding ? PString("Local") : GetRemotePartyName();
  transmitVideoCodecName = codec.GetMediaFormat();

  //if (0 != videoTxMinQuality) // set MinQuality first so TxQuality cannot be set lower
  //  codec.SetTxMinQuality(videoTxMinQuality);

  //if (0 != videoTxQuality)
  //  codec.SetTxQualityLevel(videoTxQuality);

  //codec.SetBackgroundFill(videoFill);

  //if (0 != videoBitRate) {
//    codec.SetMaxBitRate(videoBitRate);
//    codec.SetVideoMode(
//    H323VideoCodec::DynamicVideoQuality | 
//    H323VideoCodec::AdaptivePacketDelay |
//    codec.GetVideoMode());
  //}

  //if (0 != frameTimeMs) {
  //  codec.SetTargetFrameTimeMs(frameTimeMs);
  //  codec.SetVideoMode(
  //    H323VideoCodec::DynamicVideoQuality | 
  //    H323VideoCodec::AdaptivePacketDelay |
  //    codec.GetVideoMode());
  //}

  // create the device using the file driver name
  PVideoChannel      * channel = new TimeLimitedVideoChannel(*this, ep.GetCallLimit());
  PVideoInputDevice  * grabber = PVideoInputDevice::CreateDevice(VideoGrabberDriverName);
  if (grabber == NULL) {
    PTRACE(3, "Cannot create video input device for driver " << VideoGrabberDriverName);
    return FALSE;
  }

  if (!InitGrabber(grabber, codec.GetWidth(), codec.GetHeight())) {
	PTRACE(1, "Cannot initialize grabber " << VideoGrabberDriverName);
    delete grabber;
    return FALSE;
  }

  PTRACE(1,"Video device opened OUT: " << codec.GetMediaFormat() << " : " << codec.GetWidth() << "x" << codec.GetHeight());
  grabber->Start();
  channel->AttachVideoReader(grabber);

  return codec.AttachChannel(channel,TRUE);
}

PBoolean MyH323Connection::InitGrabber(PVideoInputDevice * grabber, unsigned codecFrameWidth, unsigned codecFrameHeight)
{
  unsigned int grabberFrameWidth  =  352 >> (1 - ep.GetVideoSize());                
  unsigned int grabberFrameHeight = (ep.GetVideoIsPal() ? 288 : 240) >> (1 - ep.GetVideoSize());                

  //if (!(pfdColourFormat.IsEmpty()))
  //  grabber->SetPreferredColourFormat(pfdColourFormat);

  PTRACE(3, "Attempt to open file " << ep.GetVideoOGM() << " for reading."); 
  if (!grabber->Open(ep.GetVideoOGM(), FALSE)) {
    PTRACE(1, "Failed to open the video input device " << ep.GetVideoOGM());
    return FALSE;
  }

  if (!grabber->SetChannel(ep.GetVideoPlayMode())) {
    PTRACE(1, "Failed to set channel to " << ep.GetVideoPlayMode());
    return FALSE;
  }

  if (!grabber->SetVideoFormat(
      ep.GetVideoIsPal() ? PVideoDevice::PAL : PVideoDevice::NTSC)) {
    PTRACE(1, "Failed to set format to " << (ep.GetVideoIsPal() ? "PAL" : "NTSC"));
    return FALSE;
  }

  if (!grabber->SetColourFormatConverter("YUV420P") ) {
    PTRACE(1,"Failed to set format to YUV420P");
    return FALSE;
  }

  if (ep.GetVideoFrameRate() != 0) {
    grabber->SetFrameRate(ep.GetVideoFrameRate());
  }

  // set the grabber to grab the size specified by the command line
  grabber->SetFrameSizeConverter(grabberFrameWidth, grabberFrameHeight, FALSE);

  // if the codec wants a different size, then change to that size
  if (grabberFrameWidth != codecFrameWidth || grabberFrameHeight != codecFrameHeight) {
    if (!grabber->SetFrameSizeConverter(codecFrameWidth, codecFrameHeight,FALSE)) {
      PTRACE(1, "Failed to set frame size to " << codecFrameWidth << "x" << codecFrameHeight);
      return FALSE;
    }
  }

  return TRUE;
}

#endif // OPENAM_VIDEO


PBoolean MyH323Connection::OnStartLogicalChannel(H323Channel & channel)
{
  if (!H323Connection::OnStartLogicalChannel(channel))
    return FALSE;

#ifndef DISABLE_COUT
  cout << "Started logical channel: ";

  switch (channel.GetDirection()) {
    case H323Channel::IsTransmitter :
      cout << "sending ";
      break;

    case H323Channel::IsReceiver :
      cout << "receiving ";
      break;

    default :
      break;
  }

  cout << channel.GetCapability() << endl;
#endif

  return TRUE;
}

void MyH323Connection::StartRecording()
{
  recordFile->StartRecording();
}

void MyH323Connection::OnUserInputString(const PString & value)
{
  PINDEX i;
  for (i = 0; i < value.GetLength(); i++) {
    OnUserInputChar(value[i]);
  }
}

PBoolean MyH323Connection::StartMenu(int menuNumber)
{
  digits = "";
  currentMenu = menuNumber;
  PString menuName = psprintf("%s%i", MENU_PREFIX, menuNumber);
  if (menuNames.GetStringsIndex(menuName) == P_MAX_INDEX) 
    return FALSE;

  PTRACE(1, "Starting menu " << menuNumber);

  PConfig menu(menuName);
  PString startCmd = menu.GetString("start");

  if (!startCmd.IsEmpty())
    ProcessMenuCmd(startCmd);

  return TRUE;
}

PBoolean MyH323Connection::ProcessMenuCmd(const PString & cmdStr)
{
  PTRACE(1, "Processing menu cmd " << cmdStr);
  PStringArray tokens = cmdStr.Tokenise(" ", FALSE);
  int len = tokens.GetSize();
  if (len == 0)
    return TRUE;

  PString cmd = tokens[0];

  if ((len >= 2) && (cmd *= "play")) {
    ogmChannel->QueueFile(tokens[1]);
    if (len > 2) {
      cmd = "menu";
      tokens[1] = tokens[2];
    }
  }

  if ((len >= 2) && (cmd *= "menu")) {
    int newMenu = tokens[1].AsInteger();
    if (newMenu != currentMenu)
      StartMenu(newMenu);
  }

  else if (cmd *= "hangup")
    ogmChannel->SetHangupTrigger();

  else if (cmd *= "record")
    ogmChannel->SetRecordTrigger();

  return TRUE;
}

void MyH323Connection::OnUserInputChar(char ch)
{
  if (ch == '#') 
    digits += '$';
  else 
    digits += ch;

  PTRACE(1, "Processing digit string " << digits);

  ogmChannel->FlushQueue();

  PString menuName = psprintf("%s%i", MENU_PREFIX, currentMenu);
  if (menuNames.GetStringsIndex(menuName) == P_MAX_INDEX) {
    PTRACE(1, "Cannot find menu " << menuName);
    StartMenu(0);
    return;
  }

  PConfig menu(menuName);
  PStringList keys = menu.GetKeys();
  PINDEX keyMatch = FindMatch(keys, digits);

  // if key is still ambiguous, then keep collecting
  if (keyMatch == 0)
    return;

  PString cmd;
  if (keyMatch != P_MAX_INDEX) {
    PString key = keys[keyMatch-1];
    PTRACE(1, "Executing cmd for key " << key);
    cmd = menu.GetString(key);
  } else {
    PTRACE(1, "Cannot match cmd " << digits << " in menu " << menuName);
    cmd = menu.GetString("error", "menu 0");
  } 

  if (!cmd.IsEmpty()) {
    ProcessMenuCmd(cmd);
    digits = "";
  }
}

///////////////////////////////////////////////////////////////

PBoolean CheckWAVFileValid(PWAVFile *chan, int type) {
  // Check the wave file header
  if (!chan->IsValid()) {
    PTRACE(1, chan->GetName() << " wav file header invalid");
    return FALSE;
  }

  // Check the wave file format
  if ( (type == CHECK_PCM) && (chan->GetFormat() != 0x01) ){
    PTRACE(1, chan->GetName() << " is not a PCM format wav file");
    PTRACE(1, "It is format " << chan->GetFormat() );
    return FALSE;
  }

  if ( (type == CHECK_G7231) && 
       ((chan->GetFormat() != 0x42) && (chan->GetFormat() != 0x111)) ){
    PTRACE(1, chan->GetName() << " is not a G.723.1 format wav file");
    PTRACE(1, "It is format " << chan->GetFormat() );
    return FALSE;
  }

  // Check the sample rate for PCM wave files
  if ( (type == CHECK_PCM) &&
       ( (chan->GetSampleRate() != 8000)
       ||(chan->GetChannels() != 1)
       ||(chan->GetSampleSize() != 16) )
     ) {
    PTRACE(1, chan->GetName() << " is not a 16 Bit, Mono, 8000 Hz (8Khz) PCM wav file");
    PTRACE(1, "It is " << chan->GetSampleSize() << " bits, "
                       << (chan->GetChannels()==1 ? "mono " : "stereo ")
                       << chan->GetSampleRate() << " Hz");
    return FALSE;
  }

  return TRUE;
}

///////////////////////////////////////////////////////////////

PCM_OGMChannel::PCM_OGMChannel(MyH323Connection & _conn)
  : conn(_conn)
{
  silentCount = 20;         // wait 20 frames before playing the OGM
  recordTrigger = FALSE;
  hangupTrigger = FALSE;
  closed        = FALSE;
  playOnce      = FALSE;
  loopMessage   = FALSE;

  frameLen = frameOffs = 0;
}


void PCM_OGMChannel::PlayFile(PFile * chan)
{ 
  PWaitAndSignal mutex(chanMutex);

  if (!chan->Open(PFile::ReadOnly)) {
    PTRACE(1, "Cannot open file \"" << chan->GetName() << "\"");
    return;
  }

  PTRACE(1, "Playing file \"" << chan->GetName() << "\"");
  totalData = 0;
  SetReadChannel(chan, TRUE);
}


PBoolean PCM_OGMChannel::IsWAVFileValid(PWAVFile *chan) {
  // Check that this is a PCM wave file
  return CheckWAVFileValid(chan, CHECK_PCM);
}


PBoolean PCM_OGMChannel::Read(void * buffer, PINDEX amount)
{
	PWaitAndSignal mutex(chanMutex);

	// if the channel is closed, then return error
	if (closed)
		return FALSE;

	// Create the frame buffer using the amount of bytes the codec wants to
	// read. Different codecs use different read sizes.
	frameBuffer.SetMinSize(1024);//amount);

	// assume we are returning silence
	PBoolean doSilence = TRUE;
	PBoolean frameBoundary = FALSE;

	// if still outputting a frame from last time, then keep doing it
	if (frameOffs < frameLen) {
		frameBoundary = AdjustFrame(buffer, amount);
		doSilence = FALSE;
	} else {
		// if we are returning silence frames, then 
		if (silentCount > 0) 
			silentCount--;
		// if a channel is already open, don't do silence
		else if (GetBaseReadChannel() != NULL)
			doSilence = FALSE;

		// If not in silence and no existing channel, open a new file.
		else {
			PString * str = playQueue.Dequeue();
			if (str != NULL) {

				// check the file extension and open a .wav or a raw (.sw or .g723) file
				if (((*str).Right(4)).ToLower() == ".wav") {
				PWAVFile *chan = new PWAVFile(*str, PFile::ReadOnly);
				if (!chan->IsOpen()) {
					PTRACE(1, "Cannot open file \"" << chan->GetName() << "\"");
					delete chan;
				} else {
					if (!IsWAVFileValid(chan) ) {
						PTRACE(1, chan->GetName() << " is not a valid wav file");
						delete chan;
						cerr << "wave file is invalid" << endl;
					} else {
						PTRACE(1, "Playing file \"" << chan->GetName() << "\"");
						totalData = 0;
						SetReadChannel(chan, TRUE);
						doSilence = FALSE;
					}

					if (loopMessage) {
						PTRACE(1, "Looping file \"" << *str << "\"");
						playQueue.Enqueue(new PString(*str));
					}
				}
			} else { // raw file (eg .sw)
				PFile *chan = new PFile(*str);
				if (!chan->Open(PFile::ReadOnly)) {
					PTRACE(1, "Cannot open file \"" << chan->GetName() << "\"");
					delete chan;
				} else {
					PTRACE(1, "Playing file \"" << chan->GetName() << "\"");
					totalData = 0;
					SetReadChannel(chan, TRUE);
					doSilence = FALSE;
				}
			}
			delete str;
		}
	}

    // if not doing silence, try and read from the file
    if (!doSilence) {
  
      if (ReadFrame(amount)) {
        frameBoundary = AdjustFrame(buffer, amount);
        totalData += amount;
  
      } else {

        PTRACE(1, "Finished playing " << totalData << " bytes");
  
        PIndirectChannel::Close();
        silentCount = 5;   // always do 5 frames of silence after every file
  
        // hangup if required
        if (hangupTrigger || playOnce) 
          conn.ClearCall();
  
        // trigger record if required
        else if (recordTrigger) {
          if ((playQueue.GetSize() == 0) && (GetBaseReadChannel() == NULL))
            conn.StartRecording();
	      }
   
        // no silence
        doSilence = TRUE;
      }
    }
  }
  
  // start silence frame if required
  if (doSilence) {
    CreateSilenceFrame(amount);
    frameBoundary = AdjustFrame(buffer, amount);
  }

  // delay to synchronise to frame boundary
  if (frameBoundary)
    Synchronise(amount);

  return TRUE;
}

PBoolean PCM_OGMChannel::Close()
{
  PWaitAndSignal mutex(chanMutex);
  closed = TRUE;
  PIndirectChannel::Close();
  return TRUE;
}

void PCM_OGMChannel::SetRecordTrigger()
{
  PWaitAndSignal mutex(chanMutex);
  recordTrigger = TRUE;
  if ((playQueue.GetSize() == 0) && (GetBaseReadChannel() == NULL))
    conn.StartRecording();
}

void PCM_OGMChannel::SetHangupTrigger()
{
  PWaitAndSignal mutex(chanMutex);
  hangupTrigger = TRUE;
  if (GetBaseReadChannel() == NULL)
    conn.ClearCall();
}

void PCM_OGMChannel::QueueFile(const PString & fn)
{
  PWaitAndSignal mutex(chanMutex);
  PTRACE(1, "Enqueueing file " << fn << " for playing");
  playQueue.Enqueue(new PString(fn));
}

void PCM_OGMChannel::FlushQueue()
{
  PWaitAndSignal mutex(chanMutex);

  if (GetBaseReadChannel() != NULL) {
    PIndirectChannel::Close();
    if (hangupTrigger) 
      conn.ClearCall();
    else if (recordTrigger) 
      conn.StartRecording();
  }

  PString * str;
  while ((str = playQueue.Dequeue()) != NULL)
    delete str;
}

PBoolean PCM_OGMChannel::AdjustFrame(void * buffer, PINDEX amount)
{
  // reduce read size for very short frame
  if ((amount > frameLen) && (frameOffs == 0))
	amount = frameLen;

  if ((frameOffs + amount) > frameLen) {
    cerr << "Reading past end of frame:offs=" << frameOffs << ",amt=" << amount << ",len=" << frameLen << endl;
    return TRUE;
  }
  //PAssert((frameOffs + amount) <= frameLen, "Reading past end of frame");

  memcpy(buffer, frameBuffer.GetPointer()+frameOffs, amount);
  frameOffs += amount;

  lastReadCount = amount;

  return frameOffs == frameLen;
}

void PCM_OGMChannel::Synchronise(PINDEX amount)
{
  ogm_delay.Delay(amount / 16);
}

PBoolean PCM_OGMChannel::ReadFrame(PINDEX amount)
{
  frameOffs = 0;
  frameLen  = amount;

  PBoolean result = PIndirectChannel::Read(frameBuffer.GetPointer(), frameLen);

  // if we did not read a full frame of audio, fill the end of the
  // frame with zeros.
  PINDEX count = GetLastReadCount();
  if (count < frameLen)
    memset(frameBuffer.GetPointer()+count, 0, frameLen-count);

  return result;
}

void PCM_OGMChannel::CreateSilenceFrame(PINDEX amount)
{
  frameOffs = 0;
  frameLen  = amount;
  memset(frameBuffer.GetPointer(), 0, frameLen);
}

///////////////////////////////////////////////////////////////

G7231_OGMChannel::G7231_OGMChannel(MyH323Connection & conn)
  : PCM_OGMChannel(conn)
{
}

void G7231_OGMChannel::Synchronise(PINDEX /*amount*/)
{
  ogm_delay.Delay(30);
}

PBoolean G7231_OGMChannel::ReadFrame(PINDEX /*amount*/)
{
#ifdef OPENAM_G723
  if (!PIndirectChannel::Read(frameBuffer.GetPointer(), 1))
    return FALSE;

  frameOffs = 0;
  frameLen = G7231_File_Codec::GetFrameLen(frameBuffer[0]);

  return PIndirectChannel::Read(frameBuffer.GetPointer()+1, frameLen-1);
#else
  return FALSE;
#endif
}

void G7231_OGMChannel::CreateSilenceFrame(PINDEX /*amount*/)
{
  frameOffs = 0;
  frameLen  = 4;

  frameBuffer[0] = 2;
  memset(frameBuffer.GetPointer()+1, 0, 3);
}

PBoolean G7231_OGMChannel::IsWAVFileValid(PWAVFile *chan) {
  // Check that this is a G.723.1 wave file
  return CheckWAVFileValid(chan, CHECK_G7231);
}

///////////////////////////////////////////////////////////////

#ifdef OPENAM_VIDEO

TimeLimitedVideoChannel::TimeLimitedVideoChannel(MyH323Connection & _conn, unsigned _callLimit)
	: conn(_conn), callLimit(_callLimit)
{
	PTime now;
	finishTime = now + (callLimit * 1000);
}

PBoolean TimeLimitedVideoChannel::Write(const void * buf, PINDEX len)
{
	PTime now;
	if ((callLimit != 0) && (now >= finishTime)) {
		PTRACE(1, "Terminating call due to timeout");
		conn.ClearCall();
		return TRUE;
	}

	return PVideoChannel::Write(buf, len);
}

#endif

///////////////////////////////////////////////////////////////

