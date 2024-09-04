void header_plaatsen(String headertitel) {
  header_titel = headertitel;
  header_plaatsen();
}

void header_plaatsen() {
  fillRect(header_vlak[0], header_vlak[1], header_vlak[2], header_vlak[3], kleur_zwart);
  center_tekst(100, 7, header_titel, 1, tft.color565(255, 255, 255));
  klok_update();
  header_alert();
}

void klok_update() {
  fillRect(160, 0, 45, header_vlak[3], kleur_zwart);
  setCursor(190, 7);
  tft.setTextSize(1);
  tft.setTextColor(kleur_wit);
  tft.print(tijd());
  h_klok_millis = millis();
  drawIcon10x10(225, 5, icon_instellingen, kleur_wit);
  drawIconWifi10x10(175, 5);
  drawIcon10x10(160, 5, icon_sd, SD_connect);
  
}


void achtergrond(uint16_t kleur) {
  fillRect(0, header_vlak[3], 240, home_knop[1] - header_vlak[3], kleur);
}

void overligger(uint16_t kleur, int hoogte, int dicht) {
  
  fillRect(0, header_vlak[3], 240, dicht - header_vlak[3], kleur);
  
  int i = dicht + 1;
  while (i <= hoogte) {
    drawLine(0, i, 240, i, kleur);
    i ++;
    drawLine(0, i, 240, i, kleur);
    i += 2;
  }
  while (i < 360) {
    drawLine(0, i, 240, i, kleur);
    i += 2;
  }
}

void overligger(uint16_t kleur, int hoogte) {
  int i = header_vlak[3] + 1;
  while (i <= hoogte) {
    drawLine(0, i, 240, i, kleur);
    i ++;
    drawLine(0, i, 240, i, kleur);
    i += 2;
  }
  while (i < 360) {
    drawLine(0, i, 240, i, kleur);
    i += 2;
  }
}

void achtergrond(uint16_t kleur, bool plaats_home_knop) {
  achtergrond(kleur);
  if (plaats_home_knop) {
    homeknop_plaatsen();
  } else {
    fillRect(0, home_knop[1], 240, 360-home_knop[1], kleur);
  }
}

void achtergrond(uint16_t kleur, bool plaats_home_knop, uint16_t home_knop_kleur) {
  achtergrond(kleur);
  if (plaats_home_knop) {
    homeknop_plaatsen(home_knop_kleur);
  } else {
    fillRect(0, home_knop[1], 240, 360-home_knop[1], kleur);
  }
}

void header_alert() {
  if (io_alert_cnt > 0) {
    if (io_alert_app > 0) {
      drawIcon10x10(5, 5, icon_bel, kleur_actief_rood);
    } else if (!io_diepcheck) {
      drawIcon10x10(5, 5, icon_bel, tft.color565(255, 255, 0));
    } else {
      drawIcon10x10(5, 5, icon_bel, kleur_oranje);
    }
    // tft.setCursor(header_vlak[0] + 3, header_vlak[1] + 5);
    // tft.setTextSize(2);
    // tft.print("!");
    // tft.setTextSize(1.5);
    // tft.setTextColor(kleur_wit)l;
    // tft.print(io_alert_cnt);
  } else if (io_diepcheck_pins_cnt == 0) {
    drawIcon10x10(5, 5, icon_bel, tft.color565(255, 0, 255));
  } else {
    tft.fillRect(header_vlak[0], header_vlak[1], 20, header_vlak[3], kleur_zwart);
  }
}

void bouw_alert() {
  fillRect(0, 25, 240, 100, tft.color565(50, 50, 50));
  int h = 30;
  tft.setTextColor(kleur_wit);
  tft.setTextSize(1);
  if (!wifi__aangesloten) {
    drawIcon10x10(10, h-1, icon_wifi, tft.color565(100, 100, 100));
    drawIcon10x10(10, h-1, icon_kruis, tft.color565(255, 0, 0));
    setCursor(24, h);
    tft.print("WiFi adapter niet aangesloten!");
    h += 15;
  }
  if (io_diepcheck_pins_cnt == 0) {
    drawIcon10x10(10, h-1, icon_bel, tft.color565(255, 0, 255));
    setCursor(25, h);
    tft.print("Geen diepcheck pins toegewezen !");
    h += 15;
  }
  if (!io_diepcheck) {
    drawIcon10x10(10, h-1, icon_bel, tft.color565(0, 255, 255));
    setCursor(25, h);
    tft.print("Diepcheck gefaald !");
    h += 15;
  }
  if (io_alert_cnt > 0) {
    drawIcon10x10(10, h-1, icon_bel, kleur_oranje);
    setCursor(25, h);
    tft.print(io_alert_cnt);
    tft.print(" open alert");
    if (io_alert_cnt > 1) {
      tft.print("s");
    }
    h += 15;
  }
  if  (io_alert_app > 0){
    drawIcon10x10(10, h-1, icon_bel, tft.color565(255, 0, 0));
    setCursor(25, h);
    tft.print(io_alert_app);
    tft.print(" onverzonden triger");
    if (io_alert_app > 1) {
      tft.print("s");
    }
    tft.print("!");
    h += 15;
  }

  h = 75;
  setCursor(10, h);
  tft.print("status resetten?");

  fillRoundRect(40, 90, 75, 30, 5, kleur_passief_rood);
  fillRoundRect(125, 90, 75, 30, 5, kleur_passief_groen);
  center_tekst(77, 95, "NEE", 2, kleur_wit);
  center_tekst(163, 95, "JA", 2, kleur_wit);

  ts.begin();
}

void run_alert() {
  while (ts.touched()) {
    ts.begin();
  }

  bool verder = false;

  while (!verder) {
    io();
    if (ts.tirqTouched()) {
      if (ts.touched()) {
        int x = touch_x();
        int y = touch_y();

        while (ts.touched()) {
          ts.begin();
        }

        if ((x > 125)&(x < 200) & (y > 80)&(y < 130)) {
          // ja
          io_reset_alert();
          scherm_bouwen = true;
          verder = true;
        
        } else if ((x > 40)&(x < 115) & (y > 80)&(y < 130)) {
          // nee
          scherm_bouwen = true;
          verder = true;
        }

      }
    }
  }
}

void klik_header(int x, int y) {
  if (x > 150) {
    bouw_instellingen(true);
    loop_instellingen();
  } else if (x < 100) {
    bouw_alert();
    run_alert();
  }
}
