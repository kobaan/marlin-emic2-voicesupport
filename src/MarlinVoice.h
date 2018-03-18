/*
  MarlinVoice.h - Voice support for Marlin firmware

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef MarlinVoice_h
#define MarlinVoice_h
#include "Marlin.h"
#include "language.h"

#ifdef VOICE_EMIC2 // Parallax EMIC 2 Text-to-Speech module support
	#include <SoftwareSerial.h>

	#define EMIC2SOUT 2 // EMIC2 serial out / get those from pins.h
	#define EMIC2SIN  3 // EMIC2 serial out / get those from pins.h

	void emicOK(); // forward declaration of emicOK()
	void emicInit(); // setup EMIC communication
	void emicTalk(const char* message); // Send message to EMIC and talk
	void emicVersion(); // EMIC command: version Info
	void emicSettings(); // EMIC command: Current settings
	void emicSetVoice(int voice); // EMIC command: Set Voice
	void emicSetLanguage(int language); // EMIC command: Set language
	void emicSetParser(int parser); // EMIC command: Set parser
	void emicSetRate(int rate); // EMIC command: Set speaking rate
	void emicSetVolume(int volume)); // EMIC command: Set volume
	void emicStop(); // EMIC command: Stop playback
	void emicDefaults(); // EMIC command: Load EMIC factory settings
	// void emicPause(); // not implemented, not needed
	void emicTalkPGM(const char *str); // speak from progmem
#endif

