#include "DFRobotDFPlayerMini.h"

/*
 * Copyright: DFRobot
 * name:  DFPlayer_Mini_Mp3 sample code
 * Author:  lisper 
 * Date:  2014-05-30
 * Description: sample code for DFPlayer Mini, this code is test on Uno
 *   note: mp3 file must put into mp3 folder in your tf card
 */

#include "SoftwareSerial.h"
 
void setup () {
 Serial.begin (9600);
 delay (500);
 mp3_set_serial (Serial); //set Serial for DFPlayer-mini mp3 module 
 mp3_set_volume (15);
 mp3_play (1); //play 0001.mp3
}
 
void loop () {        
 //delay (63000); //63 sec, time delay to allow 0001.mp3 to finish playing
}
