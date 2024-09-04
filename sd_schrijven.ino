void blanco_sd_maken() {
  /*
  Deze functie schrijft de standaard bestanden op de ingestoken SD kaart.
  */
  ts.begin();
  
  if (!SD.begin(cs_sd)) {
    Serial.println("kan SD kaart niet vinden");
  } else {
    Serial.println("SD kaart wordt beschreven");
    Serial.println("althand... dat is de bedoeling");
    
    SD.remove("info/snaam.txt");
    myFile = SD.open("info/snaam.txt", FILE_WRITE);
    myFile.println("boot 2");
    myFile.close();

    SD.remove("info/eigenaar.txt");
    myFile = SD.open("info/eigenaar.txt", FILE_WRITE);
    myFile.println("jou naam");
    myFile.close();

    SD.remove("info/telefoon.txt");
    myFile = SD.open("info/telefoon.txt", FILE_WRITE);
    myFile.println("overschrijven met telefoonnummer");
    myFile.close();

    SD.remove("io/objecten.txt");
    myFile = SD.open("io/objecten.txt", FILE_WRITE);
    for (int i = 0; i < 15; i++) {
      myFile.println(SD__io_objecten[i]);
    }
    myFile.close();

    SD.remove("wifi/login.txt");
    myFile = SD.open("wifi/login.txt", FILE_WRITE);
    for (int i = 0; i < 8; i++) {
      myFile.println(SD__login[i]);
    }
    myFile.close();
    
    SD.remove("wifi/app.txt");
    myFile = SD.open("wifi/app.txt", FILE_WRITE);
    for (int i = 0; i < 6; i++) {
      myFile.println(SD__app[i]);
    }
    myFile.close();

    SD.remove("io/starten.txt");
    myFile = SD.open("io/starten.txt", FILE_WRITE);
    myFile.println("0");
    myFile.close();
  }

  SD.end();

}


// void kopie_sd_maken() {
//   /*
//   Deze functie schrijft de huidg opgeslagen gegevens naar een SD kaart inclusief wachtwoorden
//   */
//   ts.begin();
//   digitalWrite(cs_ts, HIGH);
//   SD.begin(cs_sd);

//   if (!SD.begin(cs_sd)) {
//     Serial.println("kan SD kaart niet vinden");
//   } else {
//     Serial.println("Kopie SD kaart wordt gemaakt");
    
//     SD.remove("info/snaam.txt");
//     myFile = SD.open("info/snaam.txt", FILE_WRITE);
//     myFile.println("boot 2");
//     myFile.close();

//     SD.remove("info/eigenaar.txt");
//     myFile = SD.open("info/eigenaar.txt", FILE_WRITE);
//     myFile.println("jou naam");
//     myFile.close();

//     SD.remove("info/telefoon.txt");
//     myFile = SD.open("info/telefoon.txt", FILE_WRITE);
//     myFile.println("overschrijven met telefoonnummer");
//     myFile.close();

//     SD.remove("io/objecten.txt");
//     myFile = SD.open("io/objecten.txt", FILE_WRITE);
//     for (int i = 0; i < 15; i++) {
//       myFile.println(SD__io_objecten[i]);
//     }
//     myFile.close();

//     SD.remove("wifi/login.txt");
//     myFile = SD.open("wifi/login.txt", FILE_WRITE);
//     for (int i = 0; i < 5; i++) {
//       myFile.println(SD__login[i]);
//     }
//     myFile.close();
    
//     SD.remove("wifi/app.txt");
//     myFile = SD.open("wifi/app.txt", FILE_WRITE);
//     for (int i = 0; i < 6; i++) {
//       myFile.println(SD__app[i]);
//     }
//     myFile.close();
//     // SD.remove("info/snaam.txt");
//     // myFile = SD.open("info/snaam.txt", FILE_WRITE);
//     // myFile.println("mijn boot, test");
//     // myFile.close();

//     // SD.remove("info/eigenaar.txt");
//     // myFile = SD.open("info/eigenaar.txt", FILE_WRITE);
//     // myFile.println(info_eigenaar);
//     // myFile.close();

//     // SD.remove("info/telefoon.txt");
//     // myFile = SD.open("info/telefoon.txt", FILE_WRITE);
//     // myFile.println(info_telefoon);
//     // myFile.close();

//     // SD.remove("io/objecten.txt");
//     // myFile = SD.open("io/objecten.txt", FILE_WRITE);
//     // Serial.println(String(io_cnt) + "   ");
//     // myFile.println(String(io_cnt) + "   ");
//     // for (int i = 1; i < 7; i++) {
//     //   myFile.println(SD__io_objecten[i]);
//     // }
//     // for (int i = 0; i < io_cnt; i++) {
//     //   myFile.println(String(instellingen_io_status[i*4]) + String(instellingen_io_status[i*4+1]) + String(instellingen_io_status[i*4+2]) + String(instellingen_io_status[i*4+3]) + io_namen[i]);
//     // }
//     // myFile.close();

//     // SD.remove("wifi/login.txt");
//     // myFile = SD.open("wifi/login.txt", FILE_WRITE);
//     // myFile.println(String(wifi_cnt_sd) + "   ");
//     // for (int i = 1; i < 3; i++) {
//     //   myFile.println(SD__login[i]);
//     // }
//     // for (int i = 0; i < wifi_cnt_sd; i++) {
//     //   myFile.println(wifi_ssid_sd[i]);
//     //   myFile.println(wifi_pass_sd[i]);
//     // }
//     // myFile.close();
    
//     // SD.remove("wifi/app.txt");
//     // myFile = SD.open("wifi/app.txt", FILE_WRITE);
//     // myFile.println(String(app_cnt) + "   ");
//     // for (int i = 1; i < 3; i++) {
//     //   myFile.println(SD__app[i]);
//     // }
//     // for (int i = 0; i < app_cnt; i++) {
//     //   myFile.println(app_app[i]);
//     //   myFile.println(app_tel[i]);
//     //   myFile.println(app_key[i]);
//     // }
//     // myFile.close();    

//   }

// }

void sd_maken() {
  /*
  Deze functie schrijft de standaard bestanden op de ingestoken SD kaart.
  */
  ts.begin();
  
  if (!SD.begin(cs_sd)) {
    Serial.println("kan SD kaart niet vinden");
  } else {
    Serial.println("SD kaart wordt beschreven");
    Serial.println("althand... dat is de bedoeling");
    
    SD.remove("info/snaam.txt");
    myFile = SD.open("info/snaam.txt", FILE_WRITE);
    myFile.println(info_snaam);
    myFile.close();

    SD.remove("info/eigenaar.txt");
    myFile = SD.open("info/eigenaar.txt", FILE_WRITE);
    myFile.println(info_eigenaar);
    myFile.close();

    SD.remove("info/telefoon.txt");
    myFile = SD.open("info/telefoon.txt", FILE_WRITE);
    myFile.println(info_telefoon);
    myFile.close();

    sd_save_io();

    SD.remove("wifi/login.txt");
    myFile = SD.open("wifi/login.txt", FILE_WRITE);
    myFile.println(String(wifi_cnt_sd) + "   ");
    myFile.println(String(wifi_connectie_modus));
    for (int i = 1; i < 3; i++) {
      myFile.println(SD__login[i]);
    }
    for (int i = 0; i < wifi_cnt_sd; i++) {
      myFile.println(wifi_ssid_sd[i]);
      myFile.println(wifi_pass_sd[i]);
    }
    myFile.close();
    
    SD.remove("wifi/app.txt");
    myFile = SD.open("wifi/app.txt", FILE_WRITE);
    myFile.println(String(app_cnt) + "   ");
    for (int i = 1; i < 3; i++) {
      myFile.println(SD__app[i]);
    }
    for (int i = 0; i < app_cnt; i++) {
      myFile.println(app_app[i]);
      myFile.println(app_tel[i]);
      myFile.println(app_key[i]);
    }
    myFile.close();

    SD.remove("io/starten.txt");
    myFile = SD.open("io/starten.txt", FILE_WRITE);
    myFile.println(String(opstart_scherm));
    myFile.close();
  }

  SD.end();

}

bool sd_save_io(int cnt) {
  ts.begin();

  if (SD.begin(cs_sd)) {
    SD.remove("io/objecten.txt");
    myFile = SD.open("io/objecten.txt", FILE_WRITE);
    Serial.println(String(cnt) + "   ");
    myFile.println(String(cnt) + "   ");
    for (int i = 1; i < 7; i++) {
      myFile.println(SD__io_objecten[i]);
    }
    for (int i = 0; i < cnt; i++) {
      if (i < io_sd_cnt) {
        myFile.println(io_sd[i]);
      } else {
        myFile.println("0003          ");
      }
    }
    myFile.close();
    return true;
  } else {
    return false;
  }

}

bool sd_save_io() {
  ts.begin();

  if (SD.begin(cs_sd)) {
    SD.remove("io/objecten.txt");
    myFile = SD.open("io/objecten.txt", FILE_WRITE);
    Serial.println(String(io_sd_cnt) + "   ");
    myFile.println(String(io_sd_cnt) + "   ");
    for (int i = 1; i < 7; i++) {
      myFile.println(SD__io_objecten[i]);
    }
    for (int i = 0; i < io_sd_cnt; i++) {
      myFile.println(io_sd[i]);
    }
    myFile.close();
    return true;
  } else {
    return false;
  }

}
