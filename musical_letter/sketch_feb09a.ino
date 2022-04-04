#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

// Use pins 2 and 3 to communicate with DFPlayer Mini

// Create the Player object
DFRobotDFPlayerMini player;

void setup() {
  //pinMode(LED_BUILTIN, OUTPUT);
  // Init USB serial port for debugging
  Serial.begin(9600);

  player.volume(10);
  
}

void loop() {
  player.volume(10);
    
  player.playMp3Folder(1);

  delay (10000); //10 sec, time delay to allow 0001.mp3 to finish playing
}
