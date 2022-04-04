/* 
 *  DFPlayer Mini MP3/WAV Player
 *  for the Arduino
 *
 * Connections:  
 * - DFPlayer RX (pin 2) to Arduino TX pin 5 through a 1K resistor
 * - DFPlayer TX (pin 3) to Arduino RX pin 4
 * - DFPlayer Busy (pin 16) to Arduino pin 2 (optional used only in the playing() function
 * - DFPlayer speaker output (pins 6,8) to a speaker  
 * - DFPlayer VCC (pin 1) to 5V
 * - DFPlayer GND (pin 7 or 10) to GND of the power supply and to Arduino GND
 * 
 * 
 * If the DFPlayer produces noise try one of the following (usually needed for the 5V Arduino):
 * - Lower the volume. Volume too high will cause noise and may crash the player
 * - Connect the RX pin in series with 1K resistors to the Arduino TX pin 
 * - Connect VCC (pin 1) in series with a 1N4001 diode to 5V (positive end of diode to 5V) to reduce the input voltage
 *   
 *   
 * SD card content:
 * - three folders: 01, mp3 and advert
 * - three files in the respective folders:
 *   - 01/001.mp3        for the playTrack(1, 1) call
 *   - mp3/0001.mp3      for the playMP3Folder(1) call
 *   - advert/0001.mp3   for the playAdvertFolder(1) call
 * - can have more folders from 01 to 99
 * - each folder can have more tracks from 001 to 255
 *   track names can be long filenames after the three digits in the mp3 and advert folders,
 *   or four digits in the 01 to 99 folders.
 *
 * Copyright 2019 Enoch Hwang
 */

//////////////////////////////////////////////////////////////
// DFPlayer Stuff
#define DFPserial_RX 5  // DFP RX pin 2 connect to Arduino TX pin 5
#define DFPserial_TX 4  // DFP TX pin 3 connect to Arduino RX pin 4
#define BUSYPIN 2
#include "DFPlayer.h"
DFPlayer mp3;
bool playing = false;

void setup() {
  Serial.begin(115200);
  pinMode(BUSYPIN, INPUT);
  Serial.print("Initializing DFPlayer...");
  mp3.begin();
  Serial.println("Ready");
  
  mp3.getPlayerStatus();

  int f = mp3.getNumberOfFolders(); // get total number of folders
  Serial.print("Total number of folders on SD card: ");
  Serial.println(f);
  
  int t = mp3.getNumberOfTracks();  // get total number of tracks on SD card
  Serial.print("Total number of tracks on SD card: ");
  Serial.println(t);

  int tf = mp3.getNumberOfTracks(1); // get number of tracks in folder 1
  Serial.print("Number of tracks in folder 1: ");
  Serial.println(tf);

  mp3.setVolume(15);
  int v = mp3.getVolume();
  Serial.print("Volume: ");
  Serial.println(v);


  mp3.playMP3Folder(1);       // play track 1 in the mp3 folder
  int c = mp3.getCurrentTrack(); // returns the current global track number
  Serial.print("Playing MP3 folder track: ");
  Serial.println(c);
  delay(8000);

  mp3.playTrack(1, 1);        // (folder, track) play track 1 in folder 1
  c = mp3.getCurrentTrack();     // returns the current global track number
  Serial.print("Playing folder 1 track: ");
  Serial.println(c);
  delay(8000);

  mp3.playAdvertFolder(1); // play track 1 in the advert folder
                           // after playing this, it will resume playing the previous song
  c = mp3.getCurrentTrack();     // returns the current global track number
  Serial.print("Playing Advert folder track: ");
  Serial.println(c);

////  mp3.playAll();        // play all tracks in global order
////  mp3.playTrack(14);    // play global track 14
////  mp3.repeatTrack(30);  // play and repeat global track 30
//    
//  delay(6000);
//  if (mp3.getPlayerStatus() == 1) {
//    Serial.println("Player status is playing");
//  }
//  delay(6000);
////  mp3.stopPlay();
////  mp3.stopAll();
////  mp3.playFolder(2);    // play all tracks in folder 2
}

void loop() {
  if (mp3.playing(BUSYPIN)) {  // use hardward to detect if playing using the DFPlayer Busy pin connected to pin 2 on the ESP8266
//  if (mp3.playing()) {  // use software to detect if playing. will cause popping noises when playing
    if (!playing) {
      Serial.println("Playing");
      playing = true;
    }
  } else {
    if (playing) {
      Serial.println("Stopped");
      playing = false;
//    mp3.nextTrack();  // play the next track
    }
  }
  delay(10);
}
