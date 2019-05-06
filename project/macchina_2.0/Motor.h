/*
 *  Motor.h - Libreria per motori......
 *  Creata da Andrea Magni e Davide Mercanti, 14 Gennaio 2018
*/

#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

class Motor {
  public:
    Motor(int PIN_SPEED_M1, int PIN_SPEED_M2, int PIN_SPEED_M3, int PIN_SPEED_M4, int PIN_DIR_A_M1, int PIN_DIR_A_M2, int PIN_DIR_A_M3, int PIN_DIR_A_M4, int PIN_DIR_B_M1, int PIN_DIR_B_M2, int PIN_DIR_B_M3, int PIN_DIR_B_M4);
    void car_forward(int SPEED);
    void car_backward(int SPEED);
	void car_left(int SPEED);
	void car_right(int SPEED);
	void car_forward(int SPEED_1, int SPEED_2, int SPEED_3, int SPEED_4);
 	void car_backward(int SPEED_1, int SPEED_2, int SPEED_3, int SPEED_4);
 	void car_left(int SPEED_1, int SPEED_2, int SPEED_3, int SPEED_4);
	void car_right(int SPEED_1, int SPEED_2, int SPEED_3, int SPEED_4);
    void car_stop();
  private:
    int _PIN_SPEED_M1;
    int _PIN_SPEED_M2;
    int _PIN_SPEED_M3;
    int _PIN_SPEED_M4;
    int _PIN_DIR_A_M1;
    int _PIN_DIR_A_M2;
    int _PIN_DIR_A_M3;
    int _PIN_DIR_A_M4;
    int _PIN_DIR_B_M1;
    int _PIN_DIR_B_M2;
    int _PIN_DIR_B_M3;
    int _PIN_DIR_B_M4;
};

#endif
