//void start_io() {
//
//  // Alles met 1 in io_objecten verwijzen in io_knoppen omdat dit de knoppen zijn. Deze verwijzing zorgt er als het goed is voor dat het overerfbaar blijft.
//  io_knoppen = new int[io_knoppen_cnt];
//  io_sensoren = new int[io_sensoren_cnt];
//  io_diepcheck_pins = new int[io_sensoren_cnt];
//
//  beeld_melding("IO opstarten");
//
//  int knop = 0;
//  int sensor = 0;
//  int diepcheck = 0;
//
//  for (int i = 0 ; i < io_cnt ; i++) {
//    if ((io_objecten[i] == 1) || (io_objecten[i] == 3)){
//      io_knoppen[knop] = i;
//      knop++;
//    } else if (io_objecten[i] == 2) {
//      io_sensoren[sensor] = i;
//      sensor++;
//    } else if (io_objecten[i] == 4) {
//      io_diepcheck_pins[diepcheck] = i;
//      diepcheck++;
//    }
//  }
//
//  start_io_hardware();

//}
  
#include "io.h"

#if controller <= 1
  #if io_versie >= 2
    void start_io_hardware() {
      // Functie die de pinnen start voor de io functionaliteiten
      pinMode(hc_pck, OUTPUT);
      pinMode(hc_sck, OUTPUT);
      pinMode(hc_uit, OUTPUT);
      pinMode(hc_in , INPUT);
      
    }
    void io() {

      // Paralelle klokslag geven
      digitalWrite(hc_pck, LOW);
      delay(10);
      digitalWrite(hc_pck, HIGH);

      for (int i = 0; i < io_cnt; i++) {

        // Seriele klok laag
        digitalWrite(hc_sck, LOW);

        // Gewenste object zenden (in omgekeerde volgorde)
        if ((io_output[io_cnt - (i+1)] == 1) || (io_output[io_cnt - (i+1)] == 2) || (io_output[io_cnt - (i+1)] == 5)) { // 1 = aan, 2 = inv. uit, 5 = inv geblokkeerd
          // Serial.print("aan");
          digitalWrite(hc_uit, HIGH);
        } else { // 0 = uit, 3 = inv aan, 4 = geblokkeerd
          // Serial.print("uit");
          digitalWrite(hc_uit, LOW);
        }
        // Invoer lezen
        tmp_status = digitalRead(hc_in);
        // Controleren of de invoer is gewijzigd. Dit wel in de gewone volgorde omdat dit binnen komend signaal is.
        if (tmp_status != io_input[i]) {
          // Bij een wijziging vaststellen dat deze is gewijzigd en ook de aanpassing opslaan
          io_gewijzigd[i] = true;
          io_input[i] = tmp_status;
          io_meeschakelen(i);
        }
        // Seriele klok hoog
        digitalWrite(hc_sck, HIGH);
      }

      // Paralelle klokslag geven
      digitalWrite(hc_pck, LOW);
      delay(10);
      digitalWrite(hc_pck, HIGH);

    }
  #endif
#elif controller == 2
  void start_io_hardware() {
    // Lege functie, omdat er geen extra hardware gestart hoeft te worden in deze modus
  }
  
  void io() {
    String uit;
    String in;

    // Omzetten van de gewenste status naar een tekst met 0 en 1
    for (int i  = io_cnt; i > 0; i--) {
      if ((io_output[i-1] == 1) || (io_output[i-1] == 2) || (io_output[i-1] == 5)) {
        String += "1";
      } else {
        String += "0";
      }
    }

    // Opsturen en ontvangen van de tekst met 0 en 1
    io_serial.print(uit);
    long limiet = millis() + 250;
    while (io_serial.available()) || (millis() < limiet) {
      char c = io_serial.read();
      in += c;
    }

    // uitkomsten weer terug zetten van een tekst met 0 en 1 naar true en false
    for (int i == 0; i < io_cnt; i++) {
      if ((in.subString(i, i+1) == "1") && (io_input[i] == false)) {
        io_gewijzigd[i] == true;
        io_input[i] == true;
        io_meeschakelen(i_in);
      } else if ((in.subString(i, i+1) == "0") && (io_input[i] == true)) {
        io_gewijzigd[i] == true;
        io_input[i] == false;
        io_meeschakelen(i_in);
      }
    }
  }
#endif
