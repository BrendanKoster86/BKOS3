#if hoofd_module__model <= 1 || hoofd_module__model == 3
  void start_io() {
  
    delete[]io_knoppen;
    delete[]io_sensoren;
    delete[]io_diepcheck_pins;
    
    // Alles met 1 in io_objecten verwijzen in io_knoppen omdat dit de knoppen zijn. Deze verwijzing zorgt er als het goed is voor dat het overerfbaar blijft.
    io_knoppen = new int[io_knoppen_cnt];
    io_sensoren = new int[io_sensoren_cnt];
    io_diepcheck_pins = new int[io_sensoren_cnt];
  
    // beeld_melding("IO opstarten");
    tft.println(" IO opstarten");
  
    Serial.print("io_cnt: ");
    Serial.println(io_cnt);
  
    Serial.print("io_knoppen_cnt: ");
    Serial.println(io_knoppen_cnt);
  
    Serial.print("io_sensoren_cnt: ");
    Serial.println(io_sensoren_cnt);
  
    int knop = 0;
    int sensor = 0;
    int diepcheck = 0;
  
    for (int i = 0 ; i < io_cnt ; i++) {
      Serial.print(i);
      Serial.print(" : ");
      Serial.println(io_objecten[i]);
      if ((io_objecten[i] == 1) || (io_objecten[i] == 3)){
        io_knoppen[knop] = i;
        knop++;
      } else if (io_objecten[i] == 2) {
        io_sensoren[sensor] = i;
        sensor++;
      } else if (io_objecten[i] == 4) {
        io_diepcheck_pins[diepcheck] = i;
        diepcheck++;
      }
    }
  
  }
#else
  void start_io(){
    Serial.println("geen IO te starten in deze modus");
  }
#endif

void io_reset_gewijzigd() {
  for (int i = 0 ; i < io_cnt ; i++) {
    io_gewijzigd[i] = false;
  }
}

void io_reset_alert() {
  io_reset_gewijzigd();
  io_alert_cnt = 0;
  io_alert_app = 0;
  io_diepcheck = true;
  for (int i = 0; i < io_cnt; i++) {
    io_open_alert[i] = false;
  }
}

void io_alert_check() {
  for (int i = 0 ; i < io_cnt ; i++) {
    if (io_gewijzigd[i]) {
      if (io_input[i] == 0) {
        if ((io_alert[i] == 0) || (io_alert[i] == 2)) {
          if (io_open_alert[i] == false) {
            io_alert_cnt++;
            io_open_alert[i] = true;
          }
          io_alert_app++;
        }
      } else if (io_input[i] == 1) {
        if ((io_alert[i] == 1) || (io_alert[i] == 2)) {
          if (io_open_alert[i] == false) {
            io_alert_cnt++;
            io_open_alert[i] = true;
          }
          io_alert_app++;
        }
      }
      io_gewijzigd[i] = false;
    }
  }
}

void io_diep_checken() {
  io_diepcheck_cnt++;
  // alle diepcheck pins op 0 zetten
  for (int i = 0; i < io_diepcheck_pins_cnt; i++) {
    io_output[io_diepcheck_pins[i]] = 0;
  }
  // 2 keer io draaien met een kleine pauze om er voor te zorgen dat als het goed is alle veranderingen in uit ook bij in staan
  io();
  delay(50);
  io();
  // Controleren of alle diepcheck pinst op 0 staan
  for (int i = 0; i < io_diepcheck_pins_cnt; i++) {
    if (io_input[io_diepcheck_pins[i]] == 1) {
      io_open_alert[io_diepcheck_pins[i]] = true;
      io_alert_cnt++;
      io_alert_app++;
      io_diepcheck = false;
    }
  }

  // alle diepcheck pinst op 1 zetten
  for (int i = 0; i < io_diepcheck_pins_cnt; i++) {
    io_output[io_diepcheck_pins[i]] = 1;
  }
  // 2 keer io draaien met een kleine pauze om er voor te zorgen dat als het goed is alle veranderingen in uit ook bij in staan
  io();
  delay(50);
  io();
  // Controleren of alle diepcheck pinst op 1 staan en dus veranderd zijn
  for (int i = 0; i < io_diepcheck_pins_cnt; i++) {
    if (io_input[io_diepcheck_pins[i]] == 0) {
      io_open_alert[io_diepcheck_pins[i]] = true;
      io_alert_cnt++;
      io_alert_app++;
      io_diepcheck = false;
    }
  }

  // alle diepcheck pins terug op 0 zetten
  for (int i = 0; i < io_diepcheck_pins_cnt; i++) {
    io_output[io_diepcheck_pins[i]] = 0;
  }
  // 2 keer io draaien met een kleine pauze om er voor te zorgen dat als het goed is alle veranderingen in uit ook bij in staan
  io();
  delay(50);
  io();
  // Controleren of alle diepcheck pinst op 0 staan en dus weer terug veranderd zijn.
  for (int i = 0; i < io_diepcheck_pins_cnt; i++) {
    if (io_input[io_diepcheck_pins[i]] == 1) {
      io_open_alert[io_diepcheck_pins[i]] = true;
      io_alert_cnt++;
      io_alert_app++;
      io_diepcheck = false;
    }
  }
}

void io_meeschakelen(int pin) {
  Serial.println("Meeschakelen");
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 10; j++) {
      if (io_events[pin][io_input[pin]][i][j] > -1) {
        Serial.print(io_events[pin][io_input[pin]][i][j]);
        Serial.print(" : ");
        Serial.println(i);
        io_output[io_events[pin][io_input[pin]][i][j]] = i;
      }
    }
  
  }
}

#if hoofd_module__model <= 1 || hoofd_module__model == 3
  void io() {

    if (io_actief == false) {

      io_actief = true;
  
      bool tmp_status;
      int i_uit;
      int i_in;
      // int i_in_ = 0;
      // int i_in__ = -1;
    
      // Paralelle klokslag geven
      digitalWrite(hc_pck, LOW);
      delay(50);
      digitalWrite(hc_pck, HIGH);
      // delay(10);
        
      digitalWrite(hc_id, LOW);
    
      // Nu het paralelle gedeelte geklokt heeft de data serieel uitsturen en uitlezen
      for (int i = 0 ; i < io_cnt ; i++) {
    
        // Seriele klok laag
        digitalWrite(hc_sck, LOW);
        delay(50);
        
        i_uit = io_cnt - (i+1);
        i_in = i;
        
        // Gewenste object zenden (in omgekeerde volgorde)
        if ((io_output[i_uit] == 1) || (io_output[i_uit] == 2) || (io_output[i_uit] == 5)) { // 1 = aan, 2 = inv. uit, 5 = inv geblokkeerd
          digitalWrite(hc_uit, HIGH);
        } else { // 0 = uit, 3 = inv aan, 4 = geblokkeerd
          digitalWrite(hc_uit, LOW);
        }
        
        // Invoer lezen
        tmp_status = digitalRead(hc_in);
        // Controleren of de invoer is gewijzigd. Dit wel in de gewone volgorde omdat dit binnen komend signaal is.
        if (tmp_status != io_input[i_in]) {
          // Bij een wijziging vaststellen dat deze is gewijzigd en ook de aanpassing opslaan
          io_gewijzigd[i_in] = true;
          io_input[i_in] = tmp_status;
          // io_meeschakelen(i_in);
        }
    
        delay(1);
        // Seriele klok hoog
        digitalWrite(hc_sck, HIGH);
        delay(1);
      
      }
    
      // Paralelle klokslag geven
      digitalWrite(hc_pck, LOW);
      delay(50);
      digitalWrite(hc_pck, HIGH);

      io_actief = false;
    
    }
  }
#elif hoofd_module__model == 2
  void io() {
    String uit;
    String in;
    for (int i  = io_cnt; i > 0; i--) {
      if ((io_output[i-1] == 1) || (io_output[i-1] == 2) || (io_output[i-1] == 5)) {
        String += "1";
      } else {
        String += "0";
      }
    }
    
    io_serial.print(uit);
    long limiet = millis() + 250;
    while (io_serial.available()) || (millis() < limiet) {
      char c = io_serial.read();
      in += c;
    }
    for (int i == 0; i < io_cnt; i++) {
      if ((in.subString(i, i+1) == "1") && (io_input[i] == false)) {
        io_gewijzigd[i] == true;
        io_input[i] == true;
        // io_meeschakelen(i_in);
      } else if ((in.subString(i, i+1) == "0") && (io_input[i] == true)) {
        io_gewijzigd[i] == true;
        io_input[i] == false;
        // io_meeschakelen(i_in);
      }
    }
  }
#endif

void io_schakel(int knop) {
  if (io_output[io_knoppen[knop]] == 0) {
    // uit wordt aan
    io_output[io_knoppen[knop]] = 1;
    knoppen_status[knop] = 1;
  } else if (io_output[io_knoppen[knop]] == 1) {
    // aan wordt uit
    io_output[io_knoppen[knop]] = 0;
    knoppen_status[knop] = 0;
  } else if (io_output[io_knoppen[knop]] == 2) {
    // uit wordt aan (maar dan voor de omgekeerde schakeling)
    io_output[io_knoppen[knop]] = 3;
    knoppen_status[knop] = 1;
  } else if (io_output[io_knoppen[knop]] == 3) {
    // aan wordt uit (maar dan voor de omgekeerde schakeling)
    io_output[io_knoppen[knop]] = 2;
    knoppen_status[knop] = 0;
  }

  knop_plaatsen(knop);
  io();

}

void io_check_zekeringen() {
  for (int i = 0; i < io_knoppen_cnt; i++) {
    if (io_objecten[io_knoppen[i]] == 1) {
      
      // Als er geen signaal ontvangen staat, maar de knop op aan staat schakelen naar geblokkeerd
      if (io_input[io_knoppen[i]] == 0) {
        if (io_output[io_knoppen[i]] == 1) {
          io_output[io_knoppen[i]] = 4;
          if (actief_scherm == 1) {
            knoppen_status[i] = 2;
            knop_plaatsen(i);
          }
        } else if (io_output[io_knoppen[i]] == 3) {
          io_output[io_knoppen[i]] = 4;
          if (actief_scherm == 1) {
            knoppen_status[i] = 2;
            knop_plaatsen(i);
          }
        }

      } else if (io_input[io_knoppen[i]] == 1) {
        // Als er signaal wordt ontvangen terwijl de knop op geblokkeerd staat schakel tussen invert en niet invert
        if (io_output[io_knoppen[i]] == 5) {
          io_output[io_knoppen[i]] = 4;
        } else if (io_output[io_knoppen[i]] == 4) {
          io_output[io_knoppen[i]] = 5;

        // Als er signaal wordt ontvangen terwijl de knop uit staat schakelen tussen invert en niet invert 
        } else if (io_output[io_knoppen[i]] == 0) {
          io_output[io_knoppen[i]] = 2;
        } else if (io_output[io_knoppen[i]] == 2) {
          io_output[io_knoppen[i]] = 0;
        } 
      }
    }
  }
}

int io_output_status(byte output) {
  /* Deze functie zet de io_output (0 - 5) om in de weer te geven status (0 - 2) */
  
  if (output == 0) {
    return 0;
  } else if (output == 1) {
    return 1;
  } else if (output == 2) {
    return 0;
  } else if (output == 3) {
    return 1;
  } else if (output == 4) {
    return 2;
  } else if (output == 5) {
    return 2;
  }
  return 99;
}

String alert_bouwen() {
  String bericht = info_snaam + " " + io_alert_app + " alerts:";
  String naam;
  if (!io_diepcheck) {
    bericht = bericht + " Diepcheck gefaald! mogelijk werken sensoren niet correct, ";
  } else if (io_diepcheck_pins_cnt == 0) {
    bericht = bericht + " Geen diepcheck pins geregistreerd! mogelijk werken sensoren niet correct, ";
  }
  for (int i = 0; i < io_cnt; i++) {
    if (io_open_alert[i]) {
      naam = io_namen[i];
      naam.trim();
      bericht = bericht + " " + naam + " - ";
      if (io_objecten[i] == 4) {
        bericht += "diepcheckpin, ";
      } else if (io_input[i]) {
        bericht = bericht + "actief, ";
      } else {
        bericht = bericht + "passief, ";
      }
    }
  }
  return bericht.substring(0, bericht.length()-2 );
}

void io_alert_appen() {
  // app_sturen("Probleem op de boot " + info_snaam + "!");
  String alert_tekst = alert_bouwen();
  if (app_sturen(alert_tekst)) {
    Serial.println("app verstuurd. app alert gereset");
    Serial.println("reset boordcomputer status handmatig");
    io_alert_app = 0;
  } else {
    Serial.println("Verzenden mislukt");
  }
  laatste_alert_app = millis();
}
