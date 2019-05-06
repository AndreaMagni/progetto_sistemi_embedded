/*
 *  Nome file: Motor.cpp
 *
 *  Libreria creata per gestire i motori
 *
 *  Informazioni dettagliate al seguente link: https://github.com/AndreaMagni/SistemiEmbedded/
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

#include "Arduino.h"
#include "Motor.h"

Motor::Motor(int PIN_SPEED_M1, int PIN_SPEED_M2, int PIN_SPEED_M3, int PIN_SPEED_M4, int PIN_DIR_A_M1, int PIN_DIR_A_M2, int PIN_DIR_A_M3, int PIN_DIR_A_M4, int PIN_DIR_B_M1, int PIN_DIR_B_M2, int PIN_DIR_B_M3, int PIN_DIR_B_M4) {
  pinMode(PIN_SPEED_M1, OUTPUT);
  pinMode(PIN_DIR_A_M1, OUTPUT);
  pinMode(PIN_DIR_B_M1, OUTPUT);   
  pinMode(PIN_SPEED_M2, OUTPUT);
  pinMode(PIN_DIR_A_M2, OUTPUT);
  pinMode(PIN_DIR_B_M2, OUTPUT);   
  pinMode(PIN_SPEED_M3, OUTPUT);
  pinMode(PIN_DIR_A_M3, OUTPUT);
  pinMode(PIN_DIR_B_M3, OUTPUT);
  pinMode(PIN_SPEED_M4, OUTPUT);
  pinMode(PIN_DIR_A_M4, OUTPUT);
  pinMode(PIN_DIR_B_M4, OUTPUT); 
  _PIN_SPEED_M1 = PIN_SPEED_M1;
  _PIN_DIR_A_M1 = PIN_DIR_A_M1;
  _PIN_DIR_B_M1 = PIN_DIR_B_M1;
  _PIN_SPEED_M2 = PIN_SPEED_M2;
  _PIN_DIR_A_M2 = PIN_DIR_A_M2;
  _PIN_DIR_B_M2 = PIN_DIR_B_M2;   
  _PIN_SPEED_M3 = PIN_SPEED_M3;
  _PIN_DIR_A_M3 = PIN_DIR_A_M3;
  _PIN_DIR_B_M3 = PIN_DIR_B_M3; 
  _PIN_SPEED_M4 = PIN_SPEED_M4;
  _PIN_DIR_A_M4 = PIN_DIR_A_M4;
  _PIN_DIR_B_M4 = PIN_DIR_B_M4;  
}

void Motor::car_forward(int SPEED) {
  analogWrite(_PIN_SPEED_M1, SPEED);
  analogWrite(_PIN_SPEED_M2, SPEED);
  analogWrite(_PIN_SPEED_M3, SPEED);
  analogWrite(_PIN_SPEED_M4, SPEED);    
  digitalWrite(_PIN_DIR_A_M1, LOW);
  digitalWrite(_PIN_DIR_B_M1, HIGH);  
  digitalWrite(_PIN_DIR_A_M2, LOW);
  digitalWrite(_PIN_DIR_B_M2, HIGH);
  digitalWrite(_PIN_DIR_A_M3, LOW);
  digitalWrite(_PIN_DIR_B_M3, HIGH);
  digitalWrite(_PIN_DIR_A_M4, LOW);
  digitalWrite(_PIN_DIR_B_M4, HIGH);
}

void Motor::car_forward(int SPEED_1, int SPEED_2, int SPEED_3, int SPEED_4) {
  analogWrite(_PIN_SPEED_M1, SPEED_1);
  analogWrite(_PIN_SPEED_M2, SPEED_2);
  analogWrite(_PIN_SPEED_M3, SPEED_3);
  analogWrite(_PIN_SPEED_M4, SPEED_4);    
  digitalWrite(_PIN_DIR_A_M1, LOW);
  digitalWrite(_PIN_DIR_B_M1, HIGH);  
  digitalWrite(_PIN_DIR_A_M2, LOW);
  digitalWrite(_PIN_DIR_B_M2, HIGH);
  digitalWrite(_PIN_DIR_A_M3, LOW);
  digitalWrite(_PIN_DIR_B_M3, HIGH);
  digitalWrite(_PIN_DIR_A_M4, LOW);
  digitalWrite(_PIN_DIR_B_M4, HIGH);
}

void Motor::car_backward(int SPEED) {
  analogWrite(_PIN_SPEED_M1, SPEED);
  analogWrite(_PIN_SPEED_M2, SPEED);
  analogWrite(_PIN_SPEED_M3, SPEED);
  analogWrite(_PIN_SPEED_M4, SPEED);    
  digitalWrite(_PIN_DIR_A_M1, HIGH);
  digitalWrite(_PIN_DIR_B_M1, LOW);  
  digitalWrite(_PIN_DIR_A_M2, HIGH);
  digitalWrite(_PIN_DIR_B_M2, LOW);
  digitalWrite(_PIN_DIR_A_M3, HIGH);
  digitalWrite(_PIN_DIR_B_M3, LOW);
  digitalWrite(_PIN_DIR_A_M4, HIGH);
  digitalWrite(_PIN_DIR_B_M4, LOW);
}

void Motor::car_backward(int SPEED_1, int SPEED_2, int SPEED_3, int SPEED_4) {
  analogWrite(_PIN_SPEED_M1, SPEED_1);
  analogWrite(_PIN_SPEED_M2, SPEED_2);
  analogWrite(_PIN_SPEED_M3, SPEED_3);
  analogWrite(_PIN_SPEED_M4, SPEED_4);    
  digitalWrite(_PIN_DIR_A_M1, HIGH);
  digitalWrite(_PIN_DIR_B_M1, LOW);  
  digitalWrite(_PIN_DIR_A_M2, HIGH);
  digitalWrite(_PIN_DIR_B_M2, LOW);
  digitalWrite(_PIN_DIR_A_M3, HIGH);
  digitalWrite(_PIN_DIR_B_M3, LOW);
  digitalWrite(_PIN_DIR_A_M4, HIGH);
  digitalWrite(_PIN_DIR_B_M4, LOW);
}

void Motor::car_left(int SPEED) {
  analogWrite(_PIN_SPEED_M1, SPEED);
  analogWrite(_PIN_SPEED_M2, SPEED);
  analogWrite(_PIN_SPEED_M3, SPEED);
  analogWrite(_PIN_SPEED_M4, SPEED);    
  digitalWrite(_PIN_DIR_A_M1, HIGH);
  digitalWrite(_PIN_DIR_B_M1, LOW);  
  digitalWrite(_PIN_DIR_A_M2, HIGH);
  digitalWrite(_PIN_DIR_B_M2, LOW);
  digitalWrite(_PIN_DIR_A_M3, LOW);
  digitalWrite(_PIN_DIR_B_M3, HIGH);
  digitalWrite(_PIN_DIR_A_M4, LOW);
  digitalWrite(_PIN_DIR_B_M4, HIGH);
}

void Motor::car_left(int SPEED_1, int SPEED_2, int SPEED_3, int SPEED_4) {
  analogWrite(_PIN_SPEED_M1, SPEED_1);
  analogWrite(_PIN_SPEED_M2, SPEED_2);
  analogWrite(_PIN_SPEED_M3, SPEED_3);
  analogWrite(_PIN_SPEED_M4, SPEED_4);    
  digitalWrite(_PIN_DIR_A_M1, HIGH);
  digitalWrite(_PIN_DIR_B_M1, LOW);  
  digitalWrite(_PIN_DIR_A_M2, HIGH);
  digitalWrite(_PIN_DIR_B_M2, LOW);
  digitalWrite(_PIN_DIR_A_M3, LOW);
  digitalWrite(_PIN_DIR_B_M3, HIGH);
  digitalWrite(_PIN_DIR_A_M4, LOW);
  digitalWrite(_PIN_DIR_B_M4, HIGH);
}

void Motor::car_right(int SPEED) {
  analogWrite(_PIN_SPEED_M1, SPEED);
  analogWrite(_PIN_SPEED_M2, SPEED);
  analogWrite(_PIN_SPEED_M3, SPEED);
  analogWrite(_PIN_SPEED_M4, SPEED);    
  digitalWrite(_PIN_DIR_A_M1, LOW);
  digitalWrite(_PIN_DIR_B_M1, HIGH);  
  digitalWrite(_PIN_DIR_A_M2, LOW);
  digitalWrite(_PIN_DIR_B_M2, HIGH);
  digitalWrite(_PIN_DIR_A_M3, HIGH);
  digitalWrite(_PIN_DIR_B_M3, LOW);
  digitalWrite(_PIN_DIR_A_M4, HIGH);
  digitalWrite(_PIN_DIR_B_M4, LOW);
}

void Motor::car_right(int SPEED_1, int SPEED_2, int SPEED_3, int SPEED_4) {
  analogWrite(_PIN_SPEED_M1, SPEED_1);
  analogWrite(_PIN_SPEED_M2, SPEED_2);
  analogWrite(_PIN_SPEED_M3, SPEED_3);
  analogWrite(_PIN_SPEED_M4, SPEED_4);    
  digitalWrite(_PIN_DIR_A_M1, LOW);
  digitalWrite(_PIN_DIR_B_M1, HIGH);  
  digitalWrite(_PIN_DIR_A_M2, LOW);
  digitalWrite(_PIN_DIR_B_M2, HIGH);
  digitalWrite(_PIN_DIR_A_M3, HIGH);
  digitalWrite(_PIN_DIR_B_M3, LOW);
  digitalWrite(_PIN_DIR_A_M4, HIGH);
  digitalWrite(_PIN_DIR_B_M4, LOW);
}

void Motor::car_stop() {
  analogWrite(_PIN_SPEED_M1, 0);
  analogWrite(_PIN_SPEED_M2, 0);
  analogWrite(_PIN_SPEED_M3, 0);
  analogWrite(_PIN_SPEED_M4, 0);    
  digitalWrite(_PIN_DIR_A_M1, LOW);
  digitalWrite(_PIN_DIR_B_M1, LOW);  
  digitalWrite(_PIN_DIR_A_M2, LOW);
  digitalWrite(_PIN_DIR_B_M2, LOW);
  digitalWrite(_PIN_DIR_A_M3, LOW);
  digitalWrite(_PIN_DIR_B_M3, LOW);
  digitalWrite(_PIN_DIR_A_M4, LOW);
  digitalWrite(_PIN_DIR_B_M4, LOW);
}
