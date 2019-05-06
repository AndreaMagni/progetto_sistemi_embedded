/*
 *  Nome file: Motor.h
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
