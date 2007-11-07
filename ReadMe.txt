Notes for OpenAM
----------------

Craig Southeren, 14 July 2006
Updated by Roger Hardiman, October 2001, January 2002, August 2002

1. Introduction
---------------

OpenAM is a simple answering machine using the H.323 protocol. It requires the
OpenH323 library - see http://www.voxgratia.org for more information. It is
known to run on Linux, FreeBSD, Solaris and MacOS X. If you run the program
successfully on another platform, then please send an email to the mailing
list at openh323@openh323.org, or to craigs@postincrement.com


2. Features
-----------

The code contains the following features:

- requires no codec hardware to operate

- requires no audio hardware to operate

- currently supports G.723.1, G.711 muLaw and ALaw, GSM, Microsoft MS-GSM,
  Speex and LPC-10 codecs

- can accept multiple connections simultaneously

- generates a call log containing full information about each call

- runs a user defined program after each call, which can be used to
  automatically send the recorded message as a MIME encoded email
  attachment to a known email address

- can limit the the length of recorded messages

- automatically cleans up recorded voice files

- uses .wav files for the Outgoing Message (OGM). Can also use
  raw audio files

- records messages as .wav files. Can also record as raw audio files

- plays different OGMs depending on the person called


3. Operation
------------

OpenAM works by setting up a H.323 listener process, and then waiting for
incoming connections.  Whenever an incoming connection is established, it
plays the outgoing message (OGM) and then starts recording any incoming audio
from the remote end into a record file.

As a simple demonstration, use:

  openam -m sample_message

This plays the "sample_message.wav" audio file for the outgoing message
of calls using the GSM, MS-GSM, G.711, Speex and LPC-10 codecs,
and "sample_message_g7231.wav" for calls using the G.723.1 codec.


Recorded messages are placed in the current directory and have a filename
made up of the time and date of the recording. Eg:
  20010628_140234.wav (14:02 on 28th June 2001)

Windows users can easily replay messages recorded from a G.723.1 codec
call in the Windows Media Player.

Owners of Quicknet cards (eg LineJack and PhoneJack) can also play messages
recored from a G.723.1 codec call using their Quicknet cards and the
OpenAM play command. This is handy for Linux and FreeBSD users.

Unix users (without Quicknet cards) cannot play G.723.1 files so they may
prefer to use this command, which does not enable G.723.1 in OpenAM.

  openam --pcmmessage sample_message.wav


When the client hangs up, or the maximum record time is reached, the connection
is broken, and the record file is closed. The optional user program is called
with the following parameters:

  name of file containing recorded voice data
  string describing the address of the client that initiated the call
  the username of the remote party
  the duration of the call, in seconds
  a string describing the codecs used during the call
  the vendor description of the remote endpoint software

A record is then written to the call log file, and the record deleted if
necessary.

If the client hangs up before the OGM is finished, then no record file is
created and the user program is not called. A call log record is still
generated.


4. Command line options
-----------------------

OpenAM has the following command line options:

-d dir
--directory dir       Set the directory that record files are created in

-l secs
--limit secs          Limit recorded messages to secs duration (default 30)

-m fn
--message fn          Set outgoing message to fn
                      This sets both the --pcmmessage and the --g7231message
                      parameters.
                      The filename 'fn' must not have an extension.
                      --pcmmessage is set to 'fn'.wav (or 'fn'.sw if there is
		      no .wav file)
		      --g7231message is set to 'fn'_g7231.wav (or 'fn'.g7231 if
		      there is no .wav file)

--g7231message fn     Set the outgoing message for G.723.1 codec connections.
                      This must be a G.723.1 format .wav file or a .g723 file

--pcmmessage fn       Set the outgoing message for the G.711, GSM, MS-GSM
                      Speex and LPC-10 codec connections. This must be a PCM
                      format .wav file or a .sw file

--recordraw           Use raw audio files (.sw and .g723 files) for recorded
                      messages  (the default is to record .wav files)

-n
--nodelete            Do not delete record files after processing

-r cmd
--run cmd             Run this command after each recorded message

-u str
--username str        Set the local endpoint name to str.
                      Default is "OpenH323 Answering Machine vxxx"

-t
--trace               Enable debug trace, use multiple times for more detail

-o fn
--output fn           File for trace output, default is stderr

-h
--help                Display this help message

People with Quicknet PhoneJack/LineJack cards can also use the following
two commands

play -qN [--pcm|--g7231] [--port n] filename
                     Plays the file back via the Quicknet card 'N'
                     (ie /dev/phoneN). This can play .wav files
                     (both PCM and G.723.1 wav files) and also .sw and .g723
                     files. The --pcm and --g7231 options are used if OpenAM
                     cannot determine the file type.
                     The --port option is used to select the output which is
                     1 for a POTS telephone
                     2 for the PSTN line on a LineJack card and
                     3 for the speaker socket.
                                    
record -qN [--pcm|--g7231] [--port n] filename
                     Records a file via the Quicknet card 'N'
                     (ie /dev/phoneN). This can record .wav files
                     (both PCM and G.723.1 wav files) and also .sw and .g723
                     files. The --pcm or --g7231 option must be used when
                     recording a .wav file to specify the file type.
                     These options are also used if OpenAM cannot determine
                     the file type from the file extension.
                     The --port option is used to select the source which is
                     1 for a POTS telephone
                     2 for the PSTN line on a LineJack card and
                     3 for the speaker socket.
                                    

6. OGM and record file formats
------------------------------
OpenAM supports both .wav files and raw audio files.

WAV Files
---------
There are two types of .wav file which OpenAM uses.
i)  8,000 Hz (8KHz), 16-bit, mono PCM wav files. These are standard wav files
    and are used whenever the G.711, GSM, MS-GSM, Speex or LPC-10 codecs are
    used in a call.
    These wav files can be played on all systems which support the .wav format
    including Windows, Linux and FreeBSD.

ii) G.723.1 encoded wav files. These are a special format of .wav file which
    are used whenever the G.723.1 codec is used in a call.
    These wav files can be played on Windows systems using Windows Media Player
    (after it has automatically downloaded the right codec) or the
    Windows Sound Recorder (after Media Player has installed the right codec)..
    They can also be played via a Quicknet card (eg on Linux and FreeBSD)


Raw Files
---------
Some users may prefer to use raw files instead of .wav files as they can
easily be chopped up or joined together.
OpenAM also supports
i)  .sw files containing signed 16-bit mono pcm audio sampled at 8,000 Hz
    These are used with the G.711, GSM, MS-GSM, Speex and LPC-10 codecs.

ii) .g723 files containing G.723.1 data which is used with the G.723.1 codec.


The OGM
-------
The OGM can be either a .wav file or a raw file.
OpenAM will automatically determine the file type from the extension.
Wav files which are not in the correct format (8000 hz, 16-bit, mono PCM
format) or G.723.1 format will be rejected.


User Specific OGMs
------------------
OpenAM can play a different OGM for each person called.
For example, when calling
  roger@h323machine, craig@h323machine and 541153@h323machine,
then OpenAM can be made to play
  message_roger.wav, message_craig.wav and message_541153.wav

To do this, use --pcmmessage message_%s.wav
The %s in the filename is substituted with the e164 name/number called.
This feature does not work with the -m or --message option.
You must use the --pcmmessage and --g7231message options.


The Recorded Messages
---------------------
The recorded messages are written as a .wav files unless the --recordraw
option is used in which case a raw files with .sw and .g723 extensions
are written.


Conversion information
----------------------
The sox package can use used to manipulate both raw files and wav files.
Sox uses the extension .sw to identify 8000 Hz signed 16 bit mono audio
files, which is why OpenAM uses this extension.

To convert a 8000 hz .WAV file to .sw format, just use:

	sox sample.wav sample.sw

the reverse works to convert .sw files to .WAV

The same technique applies for .au files

Sox can be downloaded from http://sox.sourceforge.net

Sox does not support G.723.1 Wav files.
However these can be converted to standard PCM format in the
Windows Sound Recorder, with the File->Properties->Convert option.

There are also some perl scripts for manipulating G.723.1 files
written by M.Stoychev <M.Stoychev@cnsys.bg>. These can be found at
http://kgb.cnsys.bg/voice/


Unix tricks
-----------
On some Unix systems, /dev/dspW0 can be used to record an OGM in the
raw .sw format. For example, you can record your OGM with:

	cat /dev/dspW0 > my_message.sw
	(use Control-C to finish recording)

And you can play back .sw files with:

	cat 20010628_140234.sw > /dev/dspW0

And because raw files do not have any headers, they can be easily joined
together into a larger audio file just by concatenating them.



6. User programs
----------------

OpenAM can be configured to call a user program after finishing the recording of
any message. The most common usage of this feature is to send the voice data as
an email attachment to a known email address. A sample shell script called
"new_msg" is provided that will do this. See this script for more
information. This script expects raw audio files, so use the --recordraw
option with OpenAM.

In order to run this script you will need the following packages:

mimencode      part of the metamail package - ftp://thumper.bellcore.com/pub/nsb
sox            see http://sox.sourceforge.net

These are normally available on most Linux systems, and are in the FreeBSD
Ports tree and FreeBSD Packages collection, but I had to find them and install
them on my Solaris system


There is also additional information on G.723.1 tools for WAV files at:

      http://cds.cnsys.bg/voice/



                              ------------------------
