/*
 *  Nome file: semaforo.ino
 *
 *  Questo programma permette al semaforo di valutare la presenza di una macchina all'interno di un determinato range 
 *  stabilito dalla presenza di due sensori ad ultrasuoni. Quando la macchina supera il primo sensore viene attivato 
 *  il canale radio e lo stato del semaforo viene comunicato alla macchina. Il programma è stato creato per permettere 
 *  una distinzione del semaforo giallo tramite la variabile loopTime, la quale permette di valutare se il giallo è 
 *  appena iniziato e quindi la macchina può proseguire oppure è quasi finito e la macchina deve fermarsi.
 *
 *  Informazioni dettagliate sul progetto al seguente link: https://github.com/AndreaMagni/SistemiEmbedded/
 *
 *  Copyright © 2018, Magni Andrea & Mercanti Davide, 23 Febbraio 2018
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
 
/* Inclusione librerie */

#include <NewPing.h>
#include <SPI.h>
#include <RF24.h>

/* Definizione etichette per i LED */

#define RED_LED 4
#define YELLOW_RED 5
#define GREEN_LED 6

/* Creazione oggetti */

RF24 radio(7, 8);
NewPing sonarA(46, 47, 500);
NewPing sonarB(49, 48, 500);

/* Dichiarazione e assegnazione variabili */
/* 50 corrisponde più o meno a 10 secondi */

bool debug = 1;
bool car_presence = false;
int loop_time; 
int loop_time_multiplier = 50;
int max_distance = 25;
const uint64_t pipe = 0xABCDEF;
const uint8_t channel = 0x1;

/* Setup */

void setup() {
  
  Serial.begin(9600);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_RED, OUTPUT);
  pinMode(RED_LED, OUTPUT);  
  radio.begin();
  radio.setChannel(channel);
  radio.openWritingPipe(pipe);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  
}

/* Loop */

void loop() {  
  
  loop_time = 0;
  
  for (loop_time; loop_time <= loop_time_multiplier*1; loop_time++) {
    green_light();
    if (debug) {Serial.print("Loop time = "); Serial.println(loop_time);}
    if (car_presence) light_status();
  }
  
  for (loop_time; loop_time <= loop_time_multiplier*2; loop_time++) {
    yellow_light();
    if (debug) {Serial.print("Loop time = "); Serial.println(loop_time);}
    if (car_presence) light_status();
  }
      
  for (loop_time; loop_time <= loop_time_multiplier*3; loop_time++) { 
    red_light();
    if (debug) {Serial.print("Loop time = "); Serial.println(loop_time);}    
    if (car_presence) light_status();
  }

}

/* Funzione obstacle_detection_A */

bool obstacle_detection_A() {  
  
  int ping_time = sonarA.ping_median(3);
  int distance = sonarA.convert_cm(ping_time);  
  if (debug) {Serial.print("Distanza ostacolo A - "); Serial.println(distance);}  
  if (distance <= max_distance) return true;  
  else return false;
  
}

/* Funzione detected_A */

void detected_A() {
  
  if (debug) Serial.println("Trovato ostacolo A - Settaggio car a true");
  car_presence = true;
    
}

/* Funzione obstacle_detection_B */

bool obstacle_detection_B() {    
  
  int ping_time = sonarB.ping_median(3);
  int distance = sonarB.convert_cm(ping_time);  
  if (debug) {Serial.print("Distanza ostacolo B - "); Serial.println(distance);}  
  if (distance <= max_distance) return true;  
  else return false;
  
}

/* Funzione detected_B */

void detected_B() {
  
  if (debug) Serial.println("Trovato ostacolo B - Settaggio car a false");
  car_presence = false;
    
}

/* Funzione light_status */

void light_status() {
  
  int green_status = digitalRead(GREEN_LED);
  int yellow_status = digitalRead(YELLOW_RED);
  int red_status = digitalRead(RED_LED);
  char actual_status[7];  
  sprintf(actual_status, "%d%d%d,%c", green_status, yellow_status, red_status, (char)loop_time);
  radio.write(&actual_status, sizeof(actual_status)); 
  if (debug) {Serial.print("Dati inviati: "); Serial.println(actual_status); Serial.println("-------------------------------");}
  
}

/* Funzione green_light */

void green_light() {  
  
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(YELLOW_RED, LOW);
  digitalWrite(RED_LED, LOW); 
  if (obstacle_detection_A()) detected_A(); 
  if (obstacle_detection_B()) detected_B();
  if (debug) {Serial.println("Stato semaforo attuale: VERDE"); Serial.print("Trasmissione: "); Serial.println(car_presence);} 
   
}

/* Funzione yellow_light */

void yellow_light() {
  
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_RED, HIGH);
  digitalWrite(RED_LED, LOW); 
  if (obstacle_detection_A()) detected_A();
  if (obstacle_detection_B()) detected_B();
  if (debug) {Serial.println("Stato semaforo attuale: GIALLO"); Serial.print("Trasmissione: "); Serial.println(car_presence);} 
  
}

/* Funzione red_light */

void red_light() { 
  
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_RED, LOW);
  digitalWrite(RED_LED, HIGH);
  if (obstacle_detection_A()) detected_A();
  if (obstacle_detection_B()) detected_B();
  if (debug) {Serial.println("Stato semaforo attuale: ROSSO"); Serial.print("Trasmissione: "); Serial.println(car_presence);}
   
}
