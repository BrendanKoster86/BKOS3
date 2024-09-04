// void start_io_instellingen() {
//   instellingen_io_knoppen_cnt = 36; // Gebruik ik toch verder (nog niet, dus is niet aangemaakt en werkt niet... het betreft 36 knoppen)

  
  
//   for (int j = 0 ; j < 8 ; j++) {
//     for (int i = 0 ; i < 4 ; i++) {
//       instellingen_io_knoppen_positie[i + j * 4] = new int[4];
//       instellingen_io_knoppen_positie[i + j * 4] = {i * 48 + 4, (j+1) * 32 + 4, 40, 26};
//       // instellingen_io_knoppen_positie[i + j * 4][0] = i * 48 + 4;
//       // instellingen_io_knoppen_positie[i + j * 4][1] = (j+1) * 32 + 4;
//       // instellingen_io_knoppen_positie[i + j * 4][2] = 40;
//       // instellingen_io_knoppen_positie[i + j * 4][3] = 26;
//       if (i == 0) {
//         instellingen_io_knoppen_kleur[i + j * 4] = new uint16_t[4];
//         instellingen_io_knoppen_kleur[i + j * 4] = {tft.color565(255, 0, 0), tft.color565(0, 255, 0), tft.color565(0, 255, 255), tft.color565(0, 0, 0)};
//         instellingen_io_knoppen_tekstkleur[i + j * 4] = new uint16_t[4];
//         instellingen_io_knoppen_tekstkleur[i + j * 4] = {tft.color565(0, 0, 0), tft.color565(0, 0, 0), tft.color565(0, 0, 0), tft.color565(0, 0, 0)};
//         instellingen_io_knoppen_tekst[i + j * 4] = new char[4][10];
//         instellingen_io_knoppen_tekst[i + j * 4] = {"uit", "knop", "sensor"};
//       } else if (i == 1) {
//         instellingen_io_knoppen_kleur[i + j * 4] = {tft.color565(255, 0, 0), tft.color565(0, 255, 0), tft.color565(150, 0, 0), tft.color565(0, 150, 0)};
//         instellingen_io_knoppen_tekstkleur[i + j * 4] = {tft.color565(0, 0, 0), tft.color565(0, 0, 0), tft.color565(0, 0, 0), tft.color565(0, 0, 0)};
//         instellingen_io_knoppen_tekst[i + j * 4] = {"uit", "aan", "uit (inv)", "aan (inf)"};
//       } else if (i == 2) {
//         instellingen_io_knoppen_kleur[i + j * 4] = {tft.color565(255, 0, 0), tft.color565(0, 255, 0), tft.color565(0, 0, 0), tft.color565(0, 0, 0)};
//         instellingen_io_knoppen_tekstkleur[i + j * 4] = {tft.color565(0, 0, 0), tft.color565(0, 0, 0), tft.color565(0, 0, 0), tft.color565(0, 0, 0)};
//         instellingen_io_knoppen_tekst[i + j * 4] = {"uit", "aan"};
//       } else if (i == 3) {
//         instellingen_io_knoppen_kleur[i + j * 4] = {tft.color565(255, 0, 0), tft.color565(0, 255, 0), tft.color565(255, 255, 255), tft.color565(0, 0, 0)};
//         instellingen_io_knoppen_tekstkleur[i + j * 4] = {tft.color565(0, 0, 0), tft.color565(0, 0, 0), tft.color565(0, 0, 0), tft.color565(255, 255, 255)};
//         instellingen_io_knoppen_tekst[i + j * 4] = {"passief", "actief", "altijd", "nooit"};
//       }
//     }
//   }
  
//   instellingen_io_knoppen_positie[32] = {4, 324, 40, 26};
//   instellingen_io_knoppen_positie[33] = {52, 324, 40, 26};
//   instellingen_io_knoppen_positie[34] = {100, 324, 40, 26};
//   instellingen_io_knoppen_positie[35] = {148, 324, 40, 26};
  
//   instellingen_io_knoppen_kleur[32] = {tft.color565(255, 0, 0), tft.color565(0, 0, 0), tft.color565(0, 0, 0), tft.color565(0, 0, 0)};
//   instellingen_io_knoppen_kleur[33] = {tft.color565(0, 100, 0), tft.color565(0, 0, 0), tft.color565(0, 0, 0), tft.color565(0, 0, 0)};
//   instellingen_io_knoppen_kleur[34] = {tft.color565(0, 100, 0), tft.color565(0, 0, 0), tft.color565(0, 0, 0), tft.color565(0, 0, 0)};
//   instellingen_io_knoppen_kleur[35] = {tft.color565(0, 255, 0), tft.color565(0, 0, 0), tft.color565(0, 0, 0), tft.color565(0, 0, 0)};

//   instellingen_io_knoppen_tekstkleur[32] = {tft.color565(0, 0, 0), tft.color565(0, 0, 0), tft.color565(0, 0, 0), tft.color565(0, 0, 0)};
//   instellingen_io_knoppen_tekstkleur[33] = {tft.color565(255, 255, 255), tft.color565(50, 50, 50), tft.color565(0, 0, 0), tft.color565(0, 0, 0)};
//   instellingen_io_knoppen_tekstkleur[34] = {tft.color565(255, 255, 255), tft.color565(50, 50, 50), tft.color565(0, 0, 0), tft.color565(0, 0, 0)};
//   instellingen_io_knoppen_tekstkleur[35] = {tft.color565(0, 0, 0), tft.color565(0, 0, 0), tft.color565(0, 0, 0), tft.color565(0, 0, 0)};
  
//   instellingen_io_knoppen_tekst[32] = {"Esc"};
//   instellingen_io_knoppen_tekst[33] = {"<"};
//   instellingen_io_knoppen_tekst[34] = {">"};
//   instellingen_io_knoppen_tekst[35] = {"OK"};
  

// }

// void bouw_io_instellingen(int groep) {
  /* Dit is het scherm om in te kunnen stellen waar de verschillende io poorten voor worden gebruikt.
  Op het moment is het enkel te doen om de instellingen aan te passen en valt de naam niet aan te passen */

//   delete[]knoppen_teken_positie;
//   delete[]knoppen_positie;
//   delete[]knoppen_basiskleur;
//   delete[]knoppen_tekst;
//   delete[]knoppen_tekst_kleur;
  
//   aantal_knoppen = 36;

//   knoppen_teken_positie = new int*[aantal_knoppen];
//   knoppen_positie = new int*[aantal_knoppen];
//   knoppen_status = new byte[aantal_knoppen];
//   knoppen_basiskleur = new uint16_t*[aantal_knoppen];
//   knoppen_tekst_kleur = new uint16_t*[aantal_knoppen];
//   knoppen_var_tekst = new char**[aantal_knoppen];
//   for (int i = 0; i < aantal_knoppen; i++) {
//     knoppen_var_tekst[i] = new char*[4];
//     for (int j = 0; j < 4; j++) {
//       knoppen_var_tekst[i][j] = new char[10];
//     }
//   }
  
//   knoppen_teken_positie = instellingen_io_knoppen_positie;
//   knoppen_positie = instellingen_io_knoppen_positie;
//   knoppen_basiskleur = instellingen_io_knoppen_kleur;
//   knoppen_tekst_kleur = instellingen_io_knoppen_tekstkleur;
//   knoppen_var_tekst = instellingen_io_knoppen_tekst

//   // Knoppen status. Voor de eerste 32 knoppen gelijk aan de invoer uit het tekst bestand, de laatste 4 knoppen afhankelijk van de groep en beschikbare groepen
//   for (int i = 0; i < 32; i++){
//     knoppen_status[i] = &instellingen_io_status[groep*32 + i];
//   }
//   knoppen_status[32] = 0;
//   if (groep > 0) {
//     knoppen_status[33] = 0;
//   } else {
//     knoppen_status[33] = 1;
//   }
//   if (groep < io_cnt/8 -1) {
//     knoppen_status[34] = 0;
//   } else {
//     knoppen_status[34] = 1;
//   }
//   knoppen_status[35] = 0;

//   alle_knoppen_plaatsen();

// }

void bouw_instellingen() {

  bouw_instellingen(false);

}

void bouw_instellingen(bool overlay) {

  delete[]knoppen_teken_positie;
  delete[]knoppen_positie;
  delete[]knoppen_basiskleur;
  delete[]knoppen_tekst;
  delete[]knoppen_tekst_kleur;
  
  
  aantal_knoppen = instellingen_mean_knoppen_cnt;
  knoppen_teken_positie = new int*[instellingen_mean_knoppen_cnt];
  knoppen_positie = new int*[instellingen_mean_knoppen_cnt];
  knoppen_basiskleur = new uint16_t*[instellingen_mean_knoppen_cnt];
  knoppen_tekst = new char*[instellingen_mean_knoppen_cnt];
  knoppen_tekst_kleur = new uint16_t*[instellingen_mean_knoppen_cnt];
  knoppen_status = instellingen_main_status;
  
  for (int i=0 ; i<instellingen_mean_knoppen_cnt ; i++) {
    knoppen_teken_positie[i] = instellingen_mean_knoppen_positie[i];
    knoppen_positie[i] = instellingen_mean_knoppen_positie[i];
    knoppen_basiskleur[i] = instellingen_mean_knoppen_kleur[i];
    knoppen_tekst[i] = instellingen_mean_knoppen_tekst[i];
    knoppen_tekst_kleur[i] = instellingen_mean_knoppen_tekstkleur[i];
    
  }
  
  header_plaatsen("Instellingen");
  if (overlay) {
    overligger(kleur_zwart, instellingen_overlay_hoogte, instellingen_overlay_dicht_tot);
  } else {
    achtergrond(kleur_zwart, true);
  }

  drawIconWifi10x10(10, 34);
  tft.setTextColor(kleur_wit);
  tft.setTextSize(1);
  tft.setCursor(25, 35);
  if (wifi__aangesloten) {
    if (wifi__verbonden) {
      tft.print(wifi__ssid + "  -  " + wifi__ip);
    } else {
      tft.print("WiFi niet verbonden");
    }
  } else {
    tft.print("Wifi adapter niet aangesloten");
  }

  alle_knoppen_plaatsen();

  // // bouw_io_instellingen(0);
  // header_plaatsen("Instellingen");
  // achtergrond(tft.color565(0, 0, 0), false);
  // center_tekst(120, 100, "Nog niet gemaakt", 2, tft.color565(255, 255, 255));
  // center_tekst(120, 150, "Tik om terug te gaan", 1, tft.color565(255, 255, 255));
}


void instellingen_restart() {
  beeld_vraag("Helaas","De reset functie werkt nog niet", "ok");
  scherm_bouwen=true;
}

void instellingen_sd_reset() {
  
  byte druk;

  if (info_snaam.length() > 2) {
    druk = beeld_vraag("SD kaart kopie", "Wilt u een kopie maken van de SD?", "JA", "NEE");
    if (druk == 0){
      beeld_melding("SD kopie maken", "Even geduld a.u.b.  . . .");

      delay(1000);
      sd_maken();
      delay(1000);
    }
  } else {
    druk = beeld_vraag("schone SD", "Wilt u SD kaart inrichten?", "JA", "NEE");
    if (druk == 0){
      beeld_melding("schone SD", "Even geduld a.u.b.  . . .");

      delay(1000);
      blanco_sd_maken();
      delay(1000);
    }
  }

  scherm_bouwen = true;

}

void instellingen_leven() {
  beeld_vraag("Volgende update:", tijd_tot_millis(timer_statusupdate), "ok");
  scherm_bouwen = true;
}

void run_instellingen() {
  int druk;
  if (ts.tirqTouched()) {
    if (ts.touched()) {
      int x = touch_x();
      int y = touch_y();

      druk = klik(x, y);

      while (ts.touched()) {
        ts.begin();
      }

      ts.begin();

      if (druk > -1) {
        instellingen_mean_knoppen_functies[druk]();
      }

      if (y > home_knop[1]) {
        if (actief_scherm == 9) {
          actief_scherm = 0;
        }
        scherm_bouwen = true;
      }

      
    }
  }
  ts.begin(); 
}

void loop_instellingen() {
  
  while (! scherm_bouwen) {
    if (scherm_actief) {
      if ((millis() > h_klok_millis + 20000) || (millis() < h_klok_millis)) {
        klok_update();
      }
    }

    io();
    ts.begin();
    run_instellingen();
  }
}