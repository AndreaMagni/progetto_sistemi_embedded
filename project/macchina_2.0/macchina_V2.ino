/*
 *  Nome file: macchina_V2.ino
 *
 *  Questo programma permette alla macchina, attraverso diverse funzioni, sensori e moduli di poter valutare
 *  ed interagire con l’esterno. Nello specifico la macchina dovrà riuscire a muoversi all’interno di una strada 
 *  appositamente creata e comunicare attraverso segnali Bluetooth e Radio con altri oggetti.
 *
 *  Informazioni dettagliate sul progetto al seguente link: https://github.com/AndreaMagni/SistemiEmbedded/
 *
 *  Copyright © 2018, Magni Andrea & Mercanti Davide, 14 Marzo 2018
 *
 *  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General
 *  Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the
 *  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
 *  License for more details. 
 *
 *  You should have received a copy of the GNU General Public License with this program. 
 *  If not, see <http://www.gnu.org/licenses/>.
 */

#include <NewPing.h>
#include "Motor.h"
#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

// Ricordare che i sensori ad infrarossi ritornaro - [1] se vedo nero (libero) - [0] se vedo bianco (ostacolo)

#define INFRARED_EXTERNAL_RIGHT 10
#define INFRARED_CENTRAL_RIGHT 11
#define INFRARED_CENTRAL_LEFT 12
#define INFRARED_EXTERNAL_LEFT 13

#define TRIGGER_PIN 7
#define ECHO_PIN 8
#define MAX_DISTANCE 500

#define OBSTACLE_DELAY 5000
#define OBSTACLE_DETECTION_DISTANCE 20 // va considerato il tempo di frenata, prossimo upgrade
#define PING_NUMBER 10 // 20 iterazioni richiedono circa mezzo secondo

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
Motor motor(5, 3, 9, 6, 22, 26, 30, 34, 24, 28, 32, 36);
RF24 radio(45, 44);

short obstacle_actual_distance;
bool debug = 0;
bool change_lane = 0;
bool to_right = 0;
bool to_left = 0;
int max_acceptable_loop = 75;
int received_loop;
const byte address[6] = "00001";

void setup () {  
  Serial.begin(9600);
  pinMode(INFRARED_EXTERNAL_RIGHT,INPUT);
  pinMode(INFRARED_CENTRAL_RIGHT,INPUT);
  pinMode(INFRARED_CENTRAL_LEFT,INPUT);
  pinMode(INFRARED_EXTERNAL_LEFT,INPUT);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();    
}

void loop () {
  if (light_status()) {
    if (!change_lane) {
      movement();
      lane_change_process();
    } else lane_reach();
  } else {
    motor.car_stop();
  }
}

//////////////////////////
//                      //
//  Funzioni generiche  //
//                      //
//////////////////////////

bool secure_digital_read(int pin) {
  bool tmp1, tmp2, tmp3;
  tmp1 = digitalRead(pin);
  delay(2);
  tmp2 = digitalRead(pin);
  delay(2);
  tmp3 = digitalRead(pin);
  return ((tmp1 && tmp2) || (tmp2 && tmp3));
}

//////////////////////////////////
//                              //
//  Funzioni gestione semaforo  //
//                              //
//////////////////////////////////

bool light_status() {
  if (radio.available()) {
    unsigned char received_status[7] = "";  
    radio.read(&received_status, sizeof(received_status));
    received_loop = received_status[4];
    if (received_loop >= max_acceptable_loop) {
      if (debug) {Serial.print(" Macchina ferma - Loop "); Serial.println(received_loop);}
      return false;     
    } else return true;
  } 
}

///////////////////////////////////////
//                                   //
//  Funzioni movimento sulla corsia  //
//                                   //
///////////////////////////////////////

bool lane_central_left() {
  if (secure_digital_read(INFRARED_CENTRAL_LEFT)) return true;
  else return false;
}

bool lane_central_right() {
  if (secure_digital_read(INFRARED_CENTRAL_RIGHT)) return true;
  else return false;
}

void movement() {
  if (lane_central_left() && lane_central_right()) motor.car_forward(60);
  else if (!lane_central_left() && lane_central_right()) motor.car_right(85);
  else if (lane_central_left() && !lane_central_right()) motor.car_left(85);
  else motor.car_stop();
}

/////////////////////////////////////
//                                 //
//  Funzioni rilevamento ostacoli  //
//                                 //
/////////////////////////////////////

bool obstacle_presence() {
  unsigned int millisec = sonar.ping_median(PING_NUMBER);
  obstacle_actual_distance = sonar.convert_cm(millisec);
  if (obstacle_actual_distance <= OBSTACLE_DETECTION_DISTANCE) return true;
  else return false;
}

bool obstacle_evaluation() {
  if (obstacle_presence()) {
    motor.car_stop(); 
    delay(OBSTACLE_DELAY);       
    if (obstacle_presence()) return true;
    else return false;
  } else return false;
}

//////////////////////////////
//                          //
//  Funzioni cambio corsia  //
//                          //
//////////////////////////////

void lane_change_to_left() {
  to_left = 1;
  motor.car_backward(65);
  delay(400);
  motor.car_left(140);
  delay(400);
}

void lane_change_to_right() {
  to_right = 1;  
  motor.car_backward(65);
  delay(400);
  motor.car_right(140);
  delay(400);  
}

int lane_detection() {
  if (secure_digital_read(INFRARED_EXTERNAL_LEFT)) return 1;
  else if (secure_digital_read(INFRARED_EXTERNAL_RIGHT)) return 2;
  else return 0; // Upgrade se restituisce zero effettuare manovra
}

void lane_change_process() {
  if (obstacle_evaluation()) {
    change_lane = 1;
    if (lane_detection() == 1) lane_change_to_right();
    else if (lane_detection() == 2) lane_change_to_left();
    else motor.car_stop();
  }
}

void lane_reach() {
  if (to_right) {
    if (secure_digital_read(INFRARED_CENTRAL_LEFT)) {
      to_right = 0;
      motor.car_left(100);
      delay(500);
      motor.car_forward(60);
      delay(1000); 
      change_lane = 0;              
    } else motor.car_forward(60);       
  }
  if (to_left) {
    if (secure_digital_read(INFRARED_CENTRAL_RIGHT)) {
      to_left = 0;      
      motor.car_right(100);
      delay(500); 
      motor.car_forward(60);
      delay(1000); 
      change_lane = 0;           
    } else motor.car_forward(60);           
  } 
}
