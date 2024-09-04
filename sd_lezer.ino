void start_sd() {
  
  // beeld_melding("SD lezen", "Gegevens lezen op de SD kaart", "SD lezen");
  tft.println(" SD kaart lezen.");
//  ts.begin();
  delay(10);

  digitalWrite(cs_tft, HIGH);
  digitalWrite(cs_ts, HIGH);
  digitalWrite(cs_sd, HIGH);
  
  SD.begin(cs_sd);
  
  // SD kaart starten
  Serial.println("SD kaart starten");
  SD.begin(cs_sd);
  if (!SD.begin(cs_sd)) {
    SD_connect = false;
    Serial.println("Kaart niet gevonden.");
    // beeld_melding("niet gevonden", "Lezen SD kaart mislukt", "SD lezen");
    tft.println(" niet gevonden");
    // delay(2000);
    // tft.fillScreen(tft.color565(0, 0, 0));
  } else {
    sd_info();
    sd_ruimtes();
    sd_io();
    sd_wifi();
    sd_app();
    sd_leven();
    sd_startscherm();
    tft.println(" Gereed");
    // beeld_melding("gereed", "SD lezen gereed", "SD lezen");
  }
//  SD.end();
  digitalWrite(cs_sd, HIGH);

}

void sd_info() {
  // Info gegevens beschikbaar maken
  myFile = SD.open("info/snaam.txt");
  info_snaam = SD_string(myFile.readStringUntil('\n'));
  myFile.close();
  
  myFile = SD.open("info/eigenaar.txt");
  info_eigenaar = SD_string(myFile.readStringUntil('\n'));
  myFile.close();
  
  myFile = SD.open("info/telefoon.txt");
  info_telefoon = SD_string(myFile.readStringUntil('\n'));
  myFile.close();
   
}

void sd_io() {
  // Inladen IO objecten (ingewikkeld)
  myFile = SD.open("io/objecten.txt");
  buffer = myFile.readStringUntil('\n');
  io_cnt = buffer.toInt();
  io_sd_cnt = buffer.toInt();

  Serial.print("io_cnt: ");
  Serial.println(io_cnt);

  delete[]io_objecten;
  delete[]io_object_ruimte;
  delete[]io_output;
  delete[]io_input;
  delete[]io_gewijzigd;
  delete[]io_open_alert;
  delete[]io_alert;
  delete[]io_namen;
  delete[]io_sd;
  delete[]io_events;
  
  io_objecten = new byte[io_cnt];
  io_object_ruimte = new byte[io_cnt];
  io_output = new byte[io_cnt];
  io_input = new bool[io_cnt];
  io_gewijzigd = new bool[io_cnt];
  io_open_alert = new bool[io_cnt];
  io_alert = new byte[io_cnt];
  io_namen = new char*[io_cnt];
  for (int i = 0 ; i < io_cnt ; i++) {
    io_namen[i] = new char[11];
  }
  io_events = new byte***[io_cnt];
  for (int i = 0; i < io_cnt; i++) {
    io_object_ruimte[i] = 255;
    io_events[i] = new byte**[2];
    for (int j = 0; j < 2; j++) {
      io_events[i][j] = new byte*[2];
      for (int k = 0; k < 2; k++) {
        io_events[i][j][k] = new byte[10];
        for (int l = 0; l < 10; l++) {
          io_events[i][j][k][l] = 255;
        }
      }
    }
  }
  io_sd = new String[io_cnt];

  int object = -6;
  io_knoppen_cnt = 0;
  io_sensoren_cnt = 0;

  // Nodige regels (met toelichting in het txt bestand) overslaan om bij de inhoud aan te komen
  for (int i = 0 ; i < 8 ; i++) {
    Serial.print(io_output[i]);
  }
  

  while (myFile.available()) {
    char buff[1];
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println("Inlezen IO informatie");
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    if (object >= 0) {
      buffer = myFile.readStringUntil('\n');
      io_objecten[object] = SD_byte(buffer.substring(0,1));
      io_output[object] = SD_byte(buffer.substring(1,2));
      io_input[object] = SD_byte(buffer.substring(2,3));
      io_alert[object] = SD_byte(buffer.substring(3,4));
      
      io_sd[object] = buffer;

      String buff2;
      int item1;
      int item2;
      int item3;
      int item4;
      int item5;
      int item6;
      String ruimte_naam;
      Serial.print("buffer: ");
      Serial.println(buffer);
      item6 = buffer.indexOf('|');
      if (item6 > 0) {
        ruimte_naam = SD_string(buffer.substring(item6+1));
        for (byte i = 0; i < io_ruimtes_cnt; i++) {
          if ((ruimte_naam == io_ruimtes_namen[i])) { // || (SD_string(ruimte_naam) == io_ruimtes_namen[i])) {
            io_object_ruimte[object] = i;
//          } else {
//            Serial.print(ruimte_naam);
//            Serial.print("(");
//            Serial.print(ruimte_naam.length());
//            Serial.print(")");
//            Serial.print("!=");
//            Serial.print(io_ruimtes_namen[i]);
//            Serial.print("(");
//            Serial.print(io_ruimtes_namen[i].length());
//            Serial.println(")");
            
          }
        }
        Serial.println(ruimte_naam);
        Serial.println(io_object_ruimte[object]);
      }
      if (buffer.indexOf(';') > -1) {
        buffer.substring(4, buffer.indexOf(';')).toCharArray(io_namen[object], 11);
        item1 = buffer.indexOf(';');
        item5 = buffer.indexOf('\n');
        for (int i = 0; i < 4; i++) {
          if (item1 > -1) {
            if (buffer.indexOf(';', item1+1) > -1){
              buff2 = buffer.substring(item1+1, buffer.indexOf(';', item1+1));
            } else {
              buff2 = buffer.substring(item1+1);
            }
            item4 = buffer.indexOf(';', item1+1);
            if (buff2.length() > 0) {
              item2 = 0;
              for (int j = 0; j < 10; j++) {
                if (item2 > -1) {
                  item3 = buff2.indexOf(',', item2);
                  Serial.print("event : ");
                  Serial.print(i);
                  Serial.print(" - ");
                  Serial.println(j);
                  if (i < 2) {
                    if (item3 > -1) {
                      io_events[object][0][i][j] = SD_byte(buff2.substring(item2, item3));
                    } else {
                      io_events[object][0][i][j] = SD_byte(buff2.substring(item2));
                    }
                  } else {
                    if (item3 > -1) {
                      io_events[object][1][i-2][j] = SD_byte(buff2.substring(item2, item3));
                    } else {
                      io_events[object][1][i-2][j] = SD_byte(buff2.substring(item2));
                    }
                  }
                  if (item3 > -1) {
                    item2 = item3+1;
                  } else {
                    item2 = item3;
                  }
                  
                }
              }
            }
            item1 = buffer.indexOf(';', item1+1);
          }

          // // int item2 = item2;
          // // int item3 = buffer.indexOf(',', item1+1);
          // int item4 = buffer.indexOf(';', item1+1);
          // if (item1 > -1) {
          //   for (int j = 0; i < 10; j++) {
          //     if (item3 > -1) {
          //       if ((item3 < item4) || (item4 == -1)){
          //         if (i < 2) {
          //           io_events[object][0][i][j] = SD_byte(buffer.substring(item2+1, item3));
          //         } else {
          //           io_events[object][1][i-2][j] = SD_byte(buffer.substring(item2+1, item3));
          //         }

          //         if ((item3 == item4) || (item3 == item5)){
          //           item2 = item3;
          //           item3 = buffer.indexOf(',', item2+1);
          //         } else {
          //           item2 = item3;
          //           item3 = buffer.indexOf(',', item2+1);
          //           if (item3 > item4)
          //         }
          //       }
          //     }
          //   }
          //   item1 = item4;
          // }
        }
      } else {
        buffer.substring(4).toCharArray(io_namen[object], 11);
      }
  

      // Bepalen of de invoer een knop of sensor is zodat er later een mapping kan worden gemaakt voor alle knoppen en sensoren
      if ((io_objecten[object] == 1) || (io_objecten[object] == 3)) {
        io_knoppen_cnt++;
      } else if (io_objecten[object] == 2) {
        io_sensoren_cnt++;
      } else if (io_objecten[object] == 4) {
        io_diepcheck_pins_cnt++;
      }


      // tft.print("io_namen[object] : ");
      // tft.println(io_namen[object]);
      // Serial.print("io_namen[object] : ");
      Serial.print(object);
      Serial.print(" - ");
      Serial.print(io_namen[object]);
      Serial.print(" : ");
      Serial.println(io_output[object]);
      if (object > 0) {
        Serial.println(io_output[object-1]);
        if (object > 1) {
          Serial.println(io_output[object-2]);
        }
      }

    } else {
      // randinformatie ophalen om het later makkelijker te maken om het bestand te herschrijven.
      io_handleiding[object + 6] = myFile.readStringUntil('\n');
    }

    object++;

  }
  myFile.close();
}

// void sd_io_events() {
//   io_events = new byte***[io_cnt];
//   for (int i = 0; i < io_cnt; i++) {
//     io_events[i] = new byte**[2];
//     for (int j = 0; j < 2; j++) {
//       io_events[i][j] = new byte*[2];
//       for (int k = 0; k < 2; k++) {
//         io_events[i][j][k] = new byte[10];
//       }
//     }
//   }

// }

void sd_wifi() {
  // Inladen wifi gegevens (semi ingewikkeld)
  myFile = SD.open("wifi/login.txt");
  
  buffer = myFile.readStringUntil('\n');
  wifi_cnt_sd = buffer.toInt();
  buffer = myFile.readStringUntil('\n');
  wifi_connectie_modus = buffer.toInt();
  wifi_ssid_sd = new String[wifi_cnt_sd];
  wifi_pass_sd = new String[wifi_cnt_sd];

  // regels (4) met toelichting overslaan
  for (int i = 0; i < 4; i++) {
    buffer = myFile.readStringUntil('\n');
  }

  for (int i = 0; i < wifi_cnt_sd; i++) {
    buffer = myFile.readStringUntil('\n');
    wifi_ssid_sd[i] = buffer.substring(0, buffer.length()-1);
    buffer = myFile.readStringUntil('\n');
    wifi_pass_sd[i] = buffer.substring(0, buffer.length()-1);
  }
  myFile.close();
}

void sd_app() {
  // Inladen signal gegevens (semi ingewikkeld)
  myFile = SD.open("wifi/app.txt");
  
  buffer = myFile.readStringUntil('\n');
  app_cnt = buffer.toInt();
  app_app = new String[app_cnt];
  app_tel = new String[app_cnt];
  app_key = new String[app_cnt];
  

  // regels (2) met toelichting overslaan
  for (int i = 0; i < 2; i++) {
    buffer = myFile.readStringUntil('\n');
  }
  for (int i = 0; i < app_cnt; i++) {
    app_app[i] = SD_string(myFile.readStringUntil('\n'));
    app_tel[i] = SD_string(myFile.readStringUntil('\n'));
    app_key[i] = SD_string(myFile.readStringUntil('\n'));
  }
  myFile.close();
}

void sd_leven() {
  // Inladen van de timers voor een statusupdate (status update)

  Serial.println("LEVEN");

  myFile = SD.open("wifi/leven.txt");

  buffer = myFile.readStringUntil('\n');
  statusupdate_timer_array_cnt = buffer.toInt();
  statusupdate_timer_array = new byte*[statusupdate_timer_array_cnt];
  
  Serial.println(statusupdate_timer_array_cnt);

  // regels (4) met toelichting overslaan
  for (int i = 0; i < 4; i++) {
    buffer = myFile.readStringUntil('\n');
  }

  for (int i = 0; i < statusupdate_timer_array_cnt; i++) {
    Serial.println(i);
    statusupdate_timer_array[i] = new byte[2];
    // buffer = myFile.readStringUntil('\n')
    statusupdate_timer_array[i][0] = SD_byte(myFile.readStringUntil(':'));
    Serial.println(statusupdate_timer_array[i][0]);
    statusupdate_timer_array[i][1] = SD_byte(myFile.readStringUntil('\n'));
    Serial.println(statusupdate_timer_array[i][1]);
  }
  myFile.close();
}

void sd_startscherm() {
  // Inladen van de timers voor een statusupdate (status update)

  myFile = SD.open("io/starten.txt");
  
  opstart_scherm = SD_byte(myFile.readStringUntil('\n'));
  actief_scherm = opstart_scherm;

  myFile.close();
}

void sd_ruimtes() {
  /*
   * Deze functie leest de informatie uit over de ruimtes in de boot uit het bestand io/ruimtes.txt
   * Deze worden opgeslagen in:
   * io_ruimtes       (coordinaten in een 200x100 vlak van de ruimten (3 of 4 per ruite)
   * io_ruimtes_namen (de namen van de ruimtes)
   * io_ruimtes_cnt   (het aantal ruimtes)
   */
  //openen bestand
  Serial.println("ruitmes");
  myFile = SD.open("io/ruimtes.txt");

  buffer = myFile.readStringUntil('\n');
  Serial.println(buffer);
  io_ruimtes_cnt = SD_byte(buffer);

  // Leeg aanmaken van de plek waar de informatie opgeslagen wordt
  delete[]io_ruimtes_namen;
  delete[]io_ruimtes;

  io_ruimtes_namen = new String[io_ruimtes_cnt];
  io_ruimtes = new byte**[io_ruimtes_cnt];
  for (int i = 0; i < io_ruimtes_cnt; i++) {
    io_ruimtes[i] = new byte*[9];
    for (int j = 0; j < 9; j++) {
      io_ruimtes[i][j] = new byte[2];
    }
  }

  // uitlezen
  int item;
  int vorige;
  int komma;
  int line_end;
  for (int i = 0; i < io_ruimtes_cnt; i++) {
    buffer = myFile.readStringUntil('\n');
    Serial.println(buffer);
    item = buffer.indexOf(';');
    io_ruimtes_namen[i] = buffer.substring(0, item);
    int j = 1;
    line_end = buffer.indexOf('\n', item);
    Serial.print("item:");
    Serial.println(item);
    Serial.print("line_end");
    Serial.println(line_end);
    while ((item > 0) && (j <= 8)) { // && (item < line_end)) {
      Serial.print(j);
      Serial.print(item);
      vorige = item + 1;
      item = buffer.indexOf(';', vorige);
      komma = buffer.indexOf(',', vorige);
      if (item > 0) {
        io_ruimtes[i][j][0] =  SD_byte(buffer.substring(vorige, komma));
        io_ruimtes[i][j][1] =  SD_byte(buffer.substring(komma+1, item));
      } else {
        io_ruimtes[i][j][0] =  SD_byte(buffer.substring(vorige, komma));
        io_ruimtes[i][j][1] =  SD_byte(buffer.substring(komma+1, line_end));
      }
      j++;
    }
    io_ruimtes[i][0][0] = j-1;
  }
  myFile.close();
}

byte SD_byte(String invoer) {
  Serial.print("invoer: ");
  Serial.println(invoer);
  
  if (invoer.indexOf('\r') > -1) {
    invoer = invoer.substring(0, invoer.indexOf('\r'));
  }
  if (invoer.indexOf('\n') > -1) {
    invoer = invoer.substring(0, invoer.indexOf('\n'));
  }
  byte uitvoer = invoer.toInt();
  Serial.print("uitvoer: ");
  Serial.println(uitvoer);
  return uitvoer;

  
  // if (invoer == "0") {
  //   return 0;
  // } else if (invoer == "1") {
  //   return 1;
  // } else if (invoer == "2") {
  //   return 2;
  // } else if (invoer == "3") {
  //   return 3;
  // } else if (invoer == "4") {
  //   return 4;
  // } else if (invoer == "5") {
  //   return 5;
  // } else if (invoer == "6") {
  //   return 6;
  // } else if (invoer == "7") {
  //   return 7;SD_byte
  // } else if (invoer == SD_byte
  //   return 8;
  // } else if (invoer == SD_byte
  //   return 9;
  // }
  // Serial.print("ERROR (SD_byte()) !");
  // return 99;
}

String SD_string(String invoer) {
  int lengte = invoer.length();
  if ((invoer.indexOf('\r') >= 0) && (invoer.indexOf('\r') < lengte)) {
    lengte = invoer.indexOf('\r');
  }
  if ((invoer.indexOf('\n') >= 0) && (invoer.indexOf('\n') < lengte)) {
    lengte = invoer.indexOf('\n');
  }
  return invoer.substring(0, lengte);
}
