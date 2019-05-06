/*
 *  Motor.h - Libreria per motori......
 *  Creata da Andrea Magni e Davide Mercanti, 14 Gennaio 2018
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

// M1 RUOTA ANTERIORE SINISTRA
// M2 RUOTA POSTERIORE SINISTRA
// M3 RUOTA ANTERIORE DESTRA
// M4 RUOTA POSTERIORE DESTRA

void Motor::car_forward(int SPEED) {
  analogWrite(_PIN_SPEED_M1, SPEED);
  analogWrite(_PIN_SPEED_M2, SPEED);
  analogWrite(_PIN_SPEED_M3, SPEED);
  analogWrite(_PIN_SPEED_M4, SPEED);    
  digitalWrite(_PIN_DIR_A_M1, LOW);
  digitalWrite(_PIN_DIR_B_M1, HIGH);  
  digitalWrite(_PIN_DIR_A_M2, HIGH);
  digitalWrite(_PIN_DIR_B_M2, LOW);
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
  digitalWrite(_PIN_DIR_A_M2, HIGH);
  digitalWrite(_PIN_DIR_B_M2, LOW);
  digitalWrite(_PIN_DIR_A_M3, HIGH);
  digitalWrite(_PIN_DIR_B_M3, LOW);
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
  digitalWrite(_PIN_DIR_A_M2, LOW);
  digitalWrite(_PIN_DIR_B_M2, HIGH);
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
  digitalWrite(_PIN_DIR_A_M2, LOW);
  digitalWrite(_PIN_DIR_B_M2, HIGH);
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
  digitalWrite(_PIN_DIR_A_M2, LOW);
  digitalWrite(_PIN_DIR_B_M2, HIGH);
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
  digitalWrite(_PIN_DIR_A_M2, LOW);
  digitalWrite(_PIN_DIR_B_M2, HIGH);
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
  digitalWrite(_PIN_DIR_A_M2, HIGH);
  digitalWrite(_PIN_DIR_B_M2, LOW);
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
  digitalWrite(_PIN_DIR_A_M2, HIGH);
  digitalWrite(_PIN_DIR_B_M2, LOW);
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
