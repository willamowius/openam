#
# Makefile
#
# Make file for ptlib library
#
# Portable Windows Library
#
# Copyright (c) 1993-1998 Equivalence Pty. Ltd.
#
# The contents of this file are subject to the Mozilla Public License
# Version 1.0 (the "License"); you may not use this file except in
# compliance with the License. You may obtain a copy of the License at
# http://www.mozilla.org/MPL/
#
# Software distributed under the License is distributed on an "AS IS"
# basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See
# the License for the specific language governing rights and limitations
# under the License.
#
# The Original Code is Portable Windows Library.
#
# The Initial Developer of the Original Code is Equivalence Pty. Ltd.
#
# Portions are Copyright (C) 1993 Free Software Foundation, Inc.
# All Rights Reserved.
# 
# Contributor(s): ______________________________________.
#
# $Log$
# Revision 1.2  2007/11/13 13:18:24  willamowius
# cleanup
#
# Revision 1.1  2007/11/07 03:42:12  willamowius
# port OpenAM to H323Plus
#
# Revision 1.9  2002/08/05 10:10:29  robertj
# Normalised Makefile usage of openh323u.mak include file, fixing odd messages.
#
# Revision 1.8  2001/09/24 22:39:42  craigs
# Added commands to play and record data files, esp G.723.1
#
# Revision 1.7  2001/07/19 10:05:27  rogerh
# PWAVFile is now part of the standard PWLib.
#
# Revision 1.6  2001/07/14 07:34:02  rogerh
# Include wav.cxx
#
# Revision 1.5  2000/04/25 23:34:22  craigs
# Added lots of new code, including outgoing and incoming
# multiplexors, and the start of an IVR system
#
# Revision 1.4  2000/02/02 04:10:55  craigs
# Changed to use common Makefiles
#
# Revision 1.3  1999/10/28 12:26:18  craigs
# Changed version number
#
# Revision 1.2  1999/10/24 04:19:28  craigs
# Added make dist target
#
# Revision 1.1  1999/10/11 00:15:18  craigs
# Initial version
#
#

PROG		= openam
SOURCES		:= main.cxx

ifndef OPENH323DIR
OPENH323DIR=$(HOME)/openh323
endif

include $(OPENH323DIR)/openh323u.mak

# dependencies
$(OBJDIR)/main.o: main.h

