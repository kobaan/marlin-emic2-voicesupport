/*
  MarlinVoice.cpp - Voice support for Marlin firmware

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

#include "Marlin.h"
#include "MarlinVoice.h"

#ifdef VOICE_EMIC2 // Parallax EMIC 2 Text-to-Speech module support
	#include <SoftwareSerial.h>

	void emicInit() // setup EMIC communication
	{
		SoftwareSerial emicSerial = SoftwareSerial(EMIC2SOUT, EMIC2SIN); // setup serial port

		pinMode(EMIC2SOUT, INPUT); // read from EMIC
		pinMode(EMIC2SIN, OUTPUT); // write  to EMIC
	
		emicSerial.begin(9600); // set data rate for EMIC to 9600 baud
		emicOK() // check if EMIC is ready	
		delay(10); // delay before flush
		emicSerial.flush(); // flush receive buffer, EMIC ready
	}

	void emicOK() // check if EMIC is ready to take next command FIXME NON BLOCKING REQUIRED HERE
	{
		emicSerial.print('\n'); // check if system is up
		while (emicSerial.read() != ':'); // wait for EMIC init ok prompt ':'
	}
	
	void emicTalk(const char* message) // Send message to EMIC and talk
	{
		emicSerial.print('S'); // EMIC command: SAY
		emicSerial.print(message); // message to say FIXME chop string size < 1023 bytes
		emicOK(); // send command to EMIC
	}
	
	void emicVersion()
	{
		emicSerial.print('I\n'); // EMIC command: version Info
		version = emicSerial.read(); // read version info from EMIC
		for line in version.splitlines() SERIAL_ECHOLNPGM(line); // write version info to Marlin serial
		emicOK(); // send command to EMIC
	}
	
	void emicSettings()
	{
		emicSerial.print('C\n'); // EMIC command: Current settings
		settings = emicSerial.read(); // read settings from EMIC
		for line in settings.splitlines() SERIAL_ECHOLNPGM(line); // write settings to Marlin serial
		emicOK(); // send command to EMIC
	}

	void emicSetVoice(int voice)
	{
		emicSerial.print('N'); // EMIC command: Set Voice
		emicSerial.print(voice); // 0=Paul,1=Harry,2=Betty,3=Ursula,4=Dennis,5=Kit,6=Frank,7=Rita,8=Wendy
		emicOK(); // send command to EMIC
	}

	void emicSetLanguage(int language)
	{
		emicSerial.print('L'); // EMIC command: Set language
		emicSerial.print(language); // 0=english, 1=castilian spanish, 2=latin spanish
		emicOK(); // send command to EMIC
	}

	void emicSetParser(int parser)
	{
		emicSerial.print('P'); // EMIC command: Set parser
		emicSerial.print(parser); // 0=DECtalk, 1=Epson
		emicOK(); // send command to EMIC
	}

	void emicSetRate(int rate)
	{
		emicSerial.print('W'); // EMIC command: Set speaking rate
		emicSerial.print(rate); // 75-600 words/minute
		emicOK(); // send command to EMIC
	}

	void emicSetVolume(int volume)
	{
		emicSerial.print('V'); // EMIC command: Set volume
		emicSerial.print(volume); // volume in dB -48 to 18
		emicOK(); // send command to EMIC
	}

	void emicStop()
	{
		emicSerial.print('X'); // EMIC command: Stop playback
		emicOK(); // send command to EMIC
	}
	
	void emicDefaults()
	{
		emicSerial.print('R'); // EMIC command: Load EMIC factory settings
		emicOK(); // send command to EMIC
	}

	emicInit(); // initialice EMIC2 tts chip	

	// speak from AVR program memory instead of SRAM
	void emicTalkPGM(const char *str)
	{
	  char ch=pgm_read_byte(str);
	  emicSerial.print('S');
	  while(ch)
	  {
	    emicSerial.print(ch);
	    ch=pgm_read_byte(++str);
	  }
	    emicOK();
	}

        // only enable voice if language is english or custom, since EMIC only has english/spanish
        #if (LANGUAGE_CHOICE =< 2)
                #define VOICE_MESSAGE(x)  emicTalk(x)
                #define VOICE_MESSAGEPGM(x)  emicTalkPGM(MYPGM(x))
        	#define VOICE_ENABLED

	//emicVersion(); // get EMIC2 version
	//emicSettings(); // get EMIC2 settings	

        #else // no voice output
                #define VOICE_MESSAGE(x)
                #define VOICE_MESSAGEPGM(x)
        #endif
#else // no voice output
        #define VOICE_MESSAGE(x)
        #define VOICE_MESSAGEPGM(x)
#endif


