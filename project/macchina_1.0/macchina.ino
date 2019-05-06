/*
 *  Nome file: macchina.ino
 *
 *  Questo programma permette alla macchina, attraverso diverse funzioni, sensori e moduli di poter valutare
 *  ed interagire con l’esterno. Nello specifico la macchina dovrà riuscire a muoversi all’interno di una strada 
 *  appositamente creata e comunicare attraverso segnali Bluetooth e Radio con altri oggetti.
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

/*
 *  Inclusione librerie necessarie per il funzionamento del programma
 *  
 *  NewPing.h utilizzata per la gestione del sensore ad ultrasuoni
 *  SPI.h utilizzata per la comunicazione con dispositivi SPI (Serial Peripheral Interface)
 *  RF24.h utilizzata per la gestione del modulo radio
 *  Motor.h creata per semplificare l’utilizzo dei motori
 */
 
#include <NewPing.h>
#include <SPI.h>
#include <RF24.h>
#include "Motor.h"

/*
 *  Definizione etichette per i sensori ad infrarossi 
 *  nessun ostacolo rilevato [1] - ostacolo rilevato [0]
 * 
 *  DETECT_ED - Sensore esterno destro
 *  DETECT_CD - Sensore centrale destro
 *  DETECT_CS - Sensore centrale sinistro
 *  DETECT_ES - Sensore esterno sinistro
 */
 
#define DETECT_ED 10
#define DETECT_CD 11
#define DETECT_CS 12
#define DETECT_ES 13


/*
 *  Dichiarazione e assegnazione di diverse variabili
 * 
 *  turn_left: stato della macchina "cambio corsia verso sinistra"
 *  turn_right: stato della macchina "cambio corsia verso destra"
 *  debug: stato debug della macchina (attivo / disattivo)
 *  standby: stato standby della macchina (attivo / disattivo)
 *  manual: stato comandi manuali della macchina (attivo / disattivo)
 *  command: determina il comando da eseguire tramite Bluetooth
 *  received_loop: determina l'ultimo loop ricevuto dal semaforo
 *  max_acceptable_loop: determina il massimo loop accettabile oltre il quale la 
 *                       macchina valuta il semaforo giallo come se fosse rosso
 *  motor_power_plus: determina la quantità di potenza aggiunta via Bluetooth ai motori 
 *  motor_power_minus: determina la quantità di potenza tolta via Bluetooth ai motori
 *  motor_power_difference: differenza tra motor_power_plus e motor_power_minus
 *  set_delay: imposta il delay dopo l'invio di un messaggio del menù Bluetooth
 *  obstacle_distance: imposta la distanza sotto la quale viene rilevato un ostacolo 
 *  pipe: definisce l’indirizzo di comunicazione radio 
 *  channel: definisce il channel nell’indirizzo di comunicazione radio
 */
 
bool turn_left = false;
bool turn_right = false;
bool debug = false;                 //
bool standby = false;               //
bool manual = false;                //
int command = 0;
int received_loop;                  //
int max_acceptable_loop = 75;       //
int motor_power_plus = 0;           //
int motor_power_minus = 0;          //
int motor_power_difference = 0;     //
int set_delay = 1000;               // delay tra comandi informazioni bluetooth
int obstacle_distance = 15;         // distanza di valutazione ostacolo
const uint64_t pipe = 0xABCDEF;     // unsigned long long
const uint8_t channel = 0x1;        // unsigned char


/*
 *  Creazione oggetti
 * 
 *  sonar(trigger_pin, echo_pin, max_cm_distance)
 *  Sensore ad ultrasuoni utilizzato per le rilevazioni delle distanza 
 *  
 *  mt(speed_[m1, m2, m3, m4], dir_a_[m1, m2, m3, m4], dir_b_[m1, m2, m3, m4])
 *  Gestione dei quattro motori, velocità e verso, in un singolo oggetto
 *  
 *  radio(ce, csn)
 *  Modulo radio per la comunicazione con il semaforo
 */
 
NewPing sonar(7, 8, 200);
Motor mt(5, 3, 9, 6, 22, 26, 30, 34, 24, 28, 32, 36);
RF24 radio(49, 53);

/*
 *  Funzione secureDigitalRead(int pin)
 * 
 *  Questa funzione è stata creata per avere più sicurezza sui dati letti
 *  da parte dei sensori ad infrarossi. Essi a volte risultano imprecisi e 
 *  quindi è stato inserito un controllo.
 */
 
bool secureDigitalRead(int pin) {
  bool register tmp1, tmp2, tmp3;
  tmp1 = digitalRead(pin);
  delay(1);
  tmp2 = digitalRead(pin);
  delay(1);
  tmp3 = digitalRead(pin);
  return (tmp1&&tmp2) || (tmp2&&tmp3) || (tmp1&&tmp3);
}

/*
 *  Funzione obstacleDetection()
 * 
 *  La funzione permette alla macchina di determinare se è presente un 
 *  ostacolo entro una quantità di centimetri specificata in precedenza 
 *  nella variabile obstacle_distance
 */
 
bool obstacleDetection() {
  int pingTime = sonar.ping_median(3);
  int distance = sonar.convert_cm(pingTime);
  if (distance <= obstacle_distance) {
    if (debug) {
      Serial.print(" Ostacolo rilevato entro ");
      Serial.print(distance);
      Serial.println(" cm");
    }  
    return true;
  }
  else return false;
}

/*  Funzione light_status()
 *   
 *  La funzione permette alla macchina di determinare lo stato del semaforo 
 *  tramite la ricezione di dati via segnale radio. Una volta ricevuti i  
 *  dati vengono elaborati, nel caso in cui il semaforo sia rosso oppure
 *  sia giallo verso la fine la macchina si ferma. Nel resto dei casi
 *  la macchina continua il tragitto
 */

bool light_status() {

  if (radio.available()) {
    char received_status[7] = "";  
    radio.read(&received_status, sizeof(received_status));
    if (strncmp(received_status, "001",3) == 0) {
      if (debug) Serial.println(" Semaforo rosso - Macchina ferma");
      return false;
    } else if (strncmp(received_status, "010",3) == 0) {
      received_loop = received_status[4];
      if (received_loop >= max_acceptable_loop) {
        if (debug) {Serial.println(" Semaforo giallo - Macchina ferma loop "); Serial.println(received_loop);}
        return false;
      } else {
        return true;
      }
    } else {
      return true;      
    }
  }
  
}

/* Setup */

void setup() {   
  
  Serial.begin(9600);  
  pinMode(DETECT_ED,INPUT);
  pinMode(DETECT_CD,INPUT);
  pinMode(DETECT_CS,INPUT);
  pinMode(DETECT_ES,INPUT);
  radio.begin();
  radio.setChannel(channel);
  radio.openReadingPipe(0, pipe);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  
}

/* Loop */

void loop() {

  if (!manual) {
    
    while (Serial.available() > 0){
      
      command = Serial.read();
      
      switch (command) { 
            
        case '1':
          Serial.println(" Elenco comandi disponibili:");
          Serial.println("");
          Serial.println(" 1 - Visualizzazione comandi");
          Serial.println(" 2 - Attivazione debug");
          Serial.println(" 3 - Disattivazione debug");
          Serial.println(" 4 - Aumento potenza motori");
          Serial.println(" 5 - Riduzione potenza motori");
          Serial.println(" 6 - Attivazione controllo manuale");
          Serial.println(" 7 - Disattivazione controllo manuale");
          Serial.println(" 8 - Attivazione modalità standby");
          Serial.println(" 9 - Disattivazione modalità standby");
          Serial.println("");
          for (int i = 30; i >= 1; i--) {
            if (i%10 == 0) {
              Serial.print(" Disconnessione menù in ");
              Serial.print(i);
              Serial.println(" secondi");
              delay(1000);
            } else if (i == 1) {
              Serial.println(" Disconnessione riuscita");
              delay(1000);
            }
          } 
          break;
                
        case '2':
          Serial.println(" 2 | Attivazione debug");
          debug = true;
          delay(set_delay); 
          break;
  
        case '3':
          Serial.println(" 3 | Disattivazione debug");
          debug = false;
          delay(set_delay);
          break;
          
        case '4':
          Serial.println(" 4 | Aumento potenza motori");
          Serial.println("");
          Serial.println(" Attualmente la potenza dei motori");
          Serial.print(" differisce dai valori originali per ");
          motor_power_plus += 5;
          motor_power_difference = motor_power_plus - motor_power_minus;
          Serial.println(motor_power_difference);
          delay(set_delay);
          break;
  
        case '5':
          Serial.println(" 5 | Riduzione potenza motori");
          Serial.println("");
          Serial.println(" Attualmente la potenza dei motori");
          Serial.print(" differisce dai valori originali per ");
          motor_power_minus += 5;
          motor_power_difference = motor_power_plus - motor_power_minus;
          Serial.println(motor_power_difference);
          delay(set_delay); 
          break;
          
        case '6':
          Serial.println(" 6 | Attivazione controllo manuale");
          manual = true;
          delay(set_delay);
          break;
  
        case '7':
          Serial.println(" 7 | Disattivazione controllo manuale");
          manual = false;
          delay(set_delay);
          break;
          
        case '8':
          Serial.println(" 8 | Attivazione modalità standby");
          standby = true;
          delay(set_delay);
          break;
  
        case '9':
          Serial.println(" 9 | Disattivazione modalità standby");
          standby = false;
          delay(set_delay);
          break;
                                          
        default:
          Serial.println(" Comando non riconosciuto");
          Serial.println("");
          Serial.println(" Premere 1 per visualizzare i comandi");
          delay(set_delay); 
          break;
          
      }
      
    }   
     
  }
   
  if (standby) {
    
    mt.car_stop();
    Serial.println(" STANDBY ATTIVO");
    Serial.println("");
    Serial.println(" Premere 9 per disattivare");
    Serial.println(""); 
    delay(3000);
    
  } else {

    if (manual) {
      
      while (Serial.available() > 0){
          
        command = Serial.read();
                 
        switch (command) {  

          case 'W':
            mt.car_forward(80 + motor_power_difference); 
            //delay(300);
            break;
            
          case 'A':
            mt.car_left(125 + motor_power_difference);
            //delay(300);
            break; 
            
          case 'S':
            mt.car_backward(80 + motor_power_difference);
            //delay(300);            
            break;  
            
          case 'D':
            mt.car_right(125 + motor_power_difference);
            //delay(300);
            break; 

          case 'Q':
            manual = false;
            standby = true;
            command = 0;
            break; 
                                                                            
          default:
            mt.car_stop();  
            break;
                            
        }

      }
          
    } else {
      
      if (!light_status()) {
        
        mt.car_stop();
        if (debug) {Serial.println(" ATTENZIONE: stop per il semaforo");}
        
      } else {   
        
        if (obstacleDetection() && !turn_left && secureDigitalRead(DETECT_ED) && secureDigitalRead(DETECT_CD) && secureDigitalRead(DETECT_CS)) { 
          mt.car_stop();
          if (debug) {Serial.println(" Valutazione ostacolo in corso. Attendere 5 secondi");}
          delay(5000);
          if (obstacleDetection()) {
            if (debug) {Serial.println(" Ostacolo fisso. Manovra di cambio corsia in corso"); delay(1000);}
            turn_left = true;
            if (debug) {Serial.println(" Manovra: c.c. retro D -> S");}
            mt.car_backward(80);
            delay(500);
            if (debug) {Serial.println(" Manovra: c.c. sinistra D -> S");}
            mt.car_left(220);
            delay(800);
          } else {
            if (debug) {Serial.println(" Ostacolo mobile. Rimanere nella stessa corsia"); delay(1000);}
          }
          
        } else if (obstacleDetection() && !turn_right && secureDigitalRead(DETECT_ES) && secureDigitalRead(DETECT_CD) && secureDigitalRead(DETECT_CS)) {  
              
          mt.car_stop();
          if (debug) {Serial.println(" Valutazione ostacolo in corso. Attendere 5 secondi");}
          delay(5000);
          if (obstacleDetection()) {
            if (debug) {Serial.println(" Ostacolo fisso. Manovra di cambio corsia in corso"); delay(1000);}
            turn_right = true;
            if (debug) {Serial.println(" Manovra: c.c. retro S -> D");}
            mt.car_backward(80);      
            delay(500);
            if (debug) {Serial.println(" Manovra: c.c. destra S -> D");} 
            mt.car_right(220);       
            delay(800);   
          } else {
            if (debug) {Serial.println(" Ostacolo mobile. Rimanere nella stessa corsia"); delay(1000);}
          } 
                   
        }
      
        if (turn_left) {           
          if (secureDigitalRead(DETECT_CD)) {
            turn_left = false;      
            while (secureDigitalRead(DETECT_CD) && !(secureDigitalRead(DETECT_CS))) {
              mt.car_right(140);
              if (debug) {Serial.println(" Manovra: c.c. allineamento");}
            }      
          } else {   
            mt.car_forward(75);
            if (debug) {Serial.println(" Manovra: c.c. avanti D -> S");}      
          }              
        } else if (turn_right) {    
          if (secureDigitalRead(DETECT_CS)) {
            turn_right = false;
            while (secureDigitalRead(DETECT_CS) && !(secureDigitalRead(DETECT_CD))) {
              mt.car_left(140);
              if (debug) {Serial.println(" Manovra: c.c. allineamento");}
            }           
          } else {      
            mt.car_forward(75);
            if (debug) {Serial.println(" Manovra: c.c. avanti S -> D");}
          }      
        } else {        
          if (digitalRead(DETECT_CD) && digitalRead(DETECT_CS)) { 
            if (debug) {Serial.println(" Manovra: avanti");}
            mt.car_forward(70 + motor_power_difference);     
          } else if (!(digitalRead(DETECT_CD)) && digitalRead(DETECT_CS)) { 
            if (debug) {Serial.println(" Manovra: sinistra");}
            mt.car_left(110 + motor_power_difference);
          } else if (digitalRead(DETECT_CD) && !(digitalRead(DETECT_CS))) {
            if (debug) {Serial.println(" Manovra: destra");}
            mt.car_right(110 + motor_power_difference);          
          } else if (!(digitalRead(DETECT_CD)) && !(digitalRead(DETECT_CS))) {       
            if (debug) {Serial.println(" Manovra: stop");}
            mt.car_stop();
          }        
        }  
      }
    
      if (debug) {Serial.println("-----------------------------------------------------------");}
      
    }
    
  }

}
