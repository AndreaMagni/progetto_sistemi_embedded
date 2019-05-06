# Progetto Sistemi Embedded
Corso di Sistemi Embedded - Università degli Studi di Milano - Anno accademico 2017/2018

### Autori:
Magni Andrea - Mercanti Davide

### Descrizione progetto:
Il progetto che abbiamo deciso di realizzare prevede la costruzione di una "macchina intelligente".

La macchina andrà a svolgere diverse funzioni, principalmente di comunicazione o di valutazione e risoluzione di problematiche, tra le quali:

- riuscire a muoversi all'interno di una strada composta da due corsie, rimanendo all'interno di una corsia
- riuscire ad effettuare una manovra di cambio corsia
- valutare la presenza di un semaforo
  - nel caso in cui venga rilevato un semaforo valuti la sua condizione e regoli la velocità di conseguenza
- valutare la presenza di possibili ostacoli durante il percorso
  - nel caso in cui venga rilevato un ostacolo valuti il tipo di ostacolo (mobile o fisso) e decida se continuare il 
  percorso o effettuare una manovra di cambio corsia
- comunicare con un telefono per permettere lo scambio di informazioni tra la macchina e l'utente in diretta

### Componenti necessari:
- x1 | Arduino MEGA | https://www.amazon.it/gp/product/B06XRJNB27/ (necessario per la macchina, la quale richiede molti GPIO)
- x1 | Board generica per gestire il semaforo, il quale non necessità di molti GPIO
- x1 | 4 Motori - 4 Ruote - Scocca | https://www.amazon.it/gp/product/B073169GBF/ (si possono utilizzare solo due ruote/motori con una terza ruota girevole https://www.amazon.it/dp/B072ZWRM2B/)
- x2 | Modulo gestione motori - L298N | https://www.amazon.it/gp/product/B013QTC18K/ (si può utilizzare un solo modulo gestendo i motori a coppie)
- x2 | Modulo radio - NRF24L01 | https://www.amazon.it/gp/product/B016BAPC0K/ (si possono utilizzare eventualmente dei moduli Wi-Fi o Bluetooth)
- x1 | Modulo bluetooth - HC-05 | https://www.amazon.it/dp/B01G9KSAF6/
- x4 | Sensore ad infrarossi - TE174 o FC-35 | https://www.amazon.it/gp/product/B00XXEJD58/ 
- x3 | Sensore ad ultrasuoni - HC-SR04 | https://www.amazon.it/gp/product/B00R2U8HK6/
- x1 | Resistenza da 8.2 ohm (in alternativa 10)
- x3 | Resistenza da 220 ohm
- x1 | Resistenza da 1 Kohm
- x1 | Resistenza da 2.2 Kohm
- x1 | Resistenza da 10 Kohm
- Componenti vari come breadboard e cavetteria

### Sviluppo del progetto:
- Realizzazione di una macchina, la quale deve:
  - potersi muovere attraverso il controllo, in modo indipendente, della velocità e verso dei _**quattro motori DC**_. Questa funzionalità è permessa dalla presenza di due _**moduli gestione motori**_. Nello specifico per questo progetto viene utilizzato il _**modulo gestione motori L298N**_, il quale permette la gestione del verso e della potenza di due motori in modo indipendente.
  - valutare la corsia da seguire all'interno del tratto stradale. Per questa funzionalità abbiamo deciso di creare un inseguitore di linea, tramite dei _**sensori ad infrarossi**. 
  - valutare la presenza di ostacoli nel suo percorso tramite dei _**sensori ad ultrasuoni**_
  - valutare lo stato dei semafori tramite un _**modulo radio**_
- Realizzazione di una strada:
  - le opzioni per questo punto erano due, da un lato la semplice creazione di delle strisce nere da posizionare sul pavimento per permettere ai sensori ad infrarossi di valutare la strada da seguire oppure realizzare una strada vera e propria. Abbiamo deciso di realizzare una strada tramite del polistirolo cartonato, disegnando le linee tramite degli indelibili neri. La strada è composta da un totale di quattro linee, ogni corsia da due. La linea meno spessa serve alla macchina per stabilire da quale lato della strada si trova in modo da effettuare la giusta manovra nel caso in cui debba effettuare un cambio corsia. 
- Realizzazione di un semaforo, il quale deve:
  - effettuare un cambiamento di stato tra "verde giallo rosso".
  - comunicare con la macchina lo stato del semaforo
  
### Schema collegamenti macchina:
<img src="../master/images/schema_macchina.png" width="100%" height="auto">

### Schema collegamenti semaforo:
<img src="../master/images/schema_semaforo.png" width="100%" height="auto">

### Foto:
<img src="../master/images/macchina_1.jpg" width="100%" height="auto">
<img src="../master/images/macchina_2.jpg" width="100%" height="auto">

### Video: 

Test sistema di gestione delle curve tramite servo:  
https://www.dropbox.com/s/mpuvc6oca1bey50/1_vecchio_sistema_curva.mp4?dl=0

Test sistema di gestione delle curve tramite velocità differenti sulle ruote:  
https://www.dropbox.com/s/kdcqv2tspdruida/2_nuovo_sistema_curva.mp4?dl=0

Test inseguitore di linea tramite infrarossi:  
https://www.dropbox.com/s/6vckf1oelf2ck3c/3_infrarossi_curva.mp4?dl=0

Test gestione velocità tramite ultrasuoni:  
https://www.dropbox.com/s/164yps8jlzu4az5/4_sonar_stop.mp4?dl=0

Prototipo finale con tracciato, gestione ostacolo fisso:  
https://www.dropbox.com/s/opallh4xtinxfd5/5_ostacolo_singolo.mp4?dl=0

Prototipo finale con tracciato, gestione doppio ostacolo fisso:  
https://www.dropbox.com/s/qxkiae7qwjshndc/6_doppio_ostacolo.mp4?dl=0

### Librerie aggiuntive:
- RF24.h (modulo radio): https://github.com/nRF24/RF24
- NewPing.h (sensore ultrasuoni): https://playground.arduino.cc/Code/NewPing
- Motor.h (gestione motori): https://github.com/AndreaMagni/SistemiEmbedded/tree/master/Car

### Possibili upgrade:
- Realizzazione di un sistema di semafori, ad esempio un incrocio, il quale valuti la presenza di cose di macchine nelle varie strade e decida come impostare i semafori in modo intelligente.
- Realizzazione di un sistema GPS per tenere traccia degli spostamenti della macchina, probabilmente sulla piccola scala dei movimenti della macchina potrebbe essere difficile o inutile da sviluppare ma potrebbe portare ad idee alternative collegate.
- Realizzazione di un collegamento tra la macchina e Processing scrivendo del codice per ricreare il tracciato percorso dalla macchina durante ogni sessione di utilizzo.
- Realizzazione di un sistema di sterzo per permettere alla macchina di curvare.
- Realizzazione di un sonar mobile, creato unendo un sensore ad ultrasuoni ad un servomotore. In questo modo sarebbe possibile analizzare le distanze degli oggetti non solo se frontali rispetto al modulo ad ultrasuoni ma anche attorno ad esso.
- Realizzazione di un passaggio a livello tramite un servomotore
