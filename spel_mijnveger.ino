void bouw_spel_mijnveger() {
  header_plaatsen("Mijnveeger");
  achtergrond(kleur_donker);
  tft.fillRect(spel_speelveld[0]-5, spel_speelveld[1]-5, spel_speelveld[2]+10, spel_speelveld[3]+10, kleur_licht);
  tft.drawRect(spel_speelveld[0]-3, spel_speelveld[1]-3, spel_speelveld[2]+6, spel_speelveld[3]+6, kleur_donker);
  tft.drawRect(spel_speelveld[0]-1, spel_speelveld[1]-1, spel_speelveld[2]+2, spel_speelveld[3]+2, kleur_donker);
  spel_mijnveger_veld_plaatsen(10, 10, 10);
  spel_mijnveger_dichte_velden = 100;
  spel_mijnveger_bommen_cnt = 10;
  homeknop_plaatsen(true);
  
}
void spel_mijnveger_veld_plaatsen(byte x_cnt, byte y_cnt, byte cnt) {
  spel_mijnveger_x_cnt = x_cnt;
  spel_mijnveger_y_cnt = y_cnt;
  
  if (spel_actief == false) {
    Serial.println("Mijnenveld verwijderen");
    delete[]spel_mijnveger_mijnenveld;
  
    Serial.println("Mijnenveld creeren");
    spel_mijnveger_mijnenveld = new byte*[x_cnt];
    
    Serial.println("Mijnenveld vullen met 0");
    for (byte ix = 0; ix < x_cnt; ix++) {
      spel_mijnveger_mijnenveld[ix] = new byte[y_cnt];
      for (byte iy = 0; iy < y_cnt; iy++) {
        spel_mijnveger_mijnenveld[ix][iy] = 0;
      }
    }

  
    Serial.println("Bommen plaatsen");
    byte geplaatst = 0;
    long rx;
    long ry;
    while (geplaatst < cnt) {
      
      rx = random(x_cnt);
      ry = random(y_cnt);
      if (spel_mijnveger_mijnenveld[rx][ry] < 9) {
        spel_mijnveger_bom_plaatsen(rx, ry, x_cnt, y_cnt);
        geplaatst++;
        Serial.println(geplaatst);
      }
    }
  }

  spel_mijnveger_veld_tekenen(spel_speelveld[0], spel_speelveld[1], spel_speelveld[2], spel_speelveld[3], x_cnt, y_cnt);

  if (spel_actief) {
    spel_mijnveger_vakjes_heropenen(x_cnt, y_cnt);
  }

  spel_actief = true;
  
}

void spel_mijnveger_vakjes_heropenen(byte x_cnt, byte y_cnt) {
  for (int x = 0; x < x_cnt; x++) {
    for (int y = 0; y < y_cnt; y++) {
      if (spel_mijnveger_mijnenveld[x][y] == 10) {
        spel_mijnveger_veldje_kleuren(x, y, kleur_passief_groen);
        spel_mijnveger_dichte_velden--;
      } else if (spel_mijnveger_mijnenveld[x][y] > 10) {
        spel_mijnveger_veldje_cijfer(x, y);
        spel_mijnveger_dichte_velden--;
      }
    }
  }
}

void spel_mijnveger_veld_tekenen(int x, int y, int breedte, int hoogte, byte x_cnt, byte y_cnt) {
  tft.drawRect(x, y, breedte, hoogte, kleur_donker);
  int var_punt;
  for (int i = 1; i < x_cnt; i++) {
    var_punt = x + (i * (breedte / x_cnt));
    tft.drawLine(var_punt, y, var_punt, y + hoogte, kleur_donker);
  }
  for (int i = 1; i < y_cnt; i++) {
    var_punt = y + (i * (breedte / y_cnt));
    tft.drawLine(x, var_punt, x + breedte, var_punt, kleur_donker);
  }
  
}


void spel_mijnveger_bom_plaatsen(long x_bom, long y_bom, byte x_cnt, byte y_cnt) {
  // 9 om aan te geven dat op deze plek een mijn ligt
  spel_mijnveger_mijnenveld[x_bom][y_bom] = 9;

  // Omliggende cellen 1 bij de waarde optellen
  for (long dx = -1; dx <= 1; dx++) {
    if ((x_bom + dx >= 0) && (x_bom + dx < x_cnt)) {
      for (long dy = -1; dy <= 1; dy++) {
        if ((y_bom + dy >= 0) && (y_bom + dy < y_cnt)) {
          if (spel_mijnveger_mijnenveld[x_bom+dx][y_bom+dy] < 9) {
            spel_mijnveger_mijnenveld[x_bom+dx][y_bom+dy]++;
          }
        }
      }
    }
  }
}

int spel_mijnveger_klik_xy(int xy, int min, int max, byte cnt) {
  int d = max - min;
  int p = d / cnt;
  int i = 0;
  
  while (xy > min + ((i+1) * p)) {
    i++;
  }
  return i;
}


void spel_mijnveger_veldje_kleuren(byte x_veld, byte y_veld, uint16_t kleur) {
  int x = spel_speelveld[0];
  int y = spel_speelveld[1];
  int b = spel_speelveld[2];
  int h = spel_speelveld[3];
  
  b = b / spel_mijnveger_x_cnt;
  h = h / spel_mijnveger_y_cnt;

  x = x + x_veld * b;
  y = y + y_veld * h;

  x += 2;
  y += 2;

  b -= 4;
  h -= 4;

  tft.fillRect(x, y, b, h, kleur);
}

void spel_mijnveger_veldje_cijfer(byte x_veld, byte y_veld) {
  int x = spel_speelveld[0];
  int y = spel_speelveld[1];
  int b = spel_speelveld[2];
  int h = spel_speelveld[3];
  
  b = b / spel_mijnveger_x_cnt;
  h = h / spel_mijnveger_y_cnt;

  x = x + x_veld * b;
  y = y + y_veld * h;

  x = x + (b / 2);
  y = y + (h / 2);

  if (spel_mijnveger_mijnenveld[x_veld][y_veld] > 10) {
    center_tekst(x, y, String(spel_mijnveger_mijnenveld[x_veld][y_veld] - 10), 1, kleur_zwart);
  } else {
    center_tekst(x, y, String(spel_mijnveger_mijnenveld[x_veld][y_veld]), 1, kleur_zwart);
  }
}

void spel_mijnveger_omliggende_velden(byte x_veld, byte y_veld) {
  for (int dx = -1; dx <= 1; dx++) {
    if ((x_veld + dx >= 0) && (x_veld + dx < spel_mijnveger_x_cnt)){
      for (int dy = -1 ; dy <= 1; dy ++) {
        if ((y_veld + dy >= 0) && (y_veld + dy < spel_mijnveger_y_cnt)){
          if (spel_mijnveger_mijnenveld[x_veld + dx][y_veld + dy] < 10) {
            spel_mijnveger_draai(x_veld + dx, y_veld + dy);
          }
        }
      }
    }
  }
}

void spel_mijnveger_bommen_tonen() {
  for (int x_veld = 0; x_veld < spel_mijnveger_x_cnt; x_veld++) {
    for (int y_veld = 0; y_veld < spel_mijnveger_y_cnt; y_veld++) {
      if (spel_mijnveger_mijnenveld[x_veld][y_veld] == 9) {
        spel_mijnveger_veldje_kleuren(x_veld, y_veld, kleur_passief_rood);
      }
    }
  }
}

void spel_mijnveger_draai(byte x_veld, byte y_veld) {
  if (spel_mijnveger_mijnenveld[x_veld][y_veld] == 0) {
    // Vak groen kleuren en omliggende vakken ook omdraaien
    spel_mijnveger_veldje_kleuren(x_veld, y_veld, kleur_donker);
    spel_mijnveger_mijnenveld[x_veld][y_veld] = 10;
    spel_mijnveger_omliggende_velden(x_veld, y_veld);
    spel_mijnveger_dichte_velden--;
  } else if (spel_mijnveger_mijnenveld[x_veld][y_veld] == 9) {
    // Vak rood kleuren en game over gaan
    spel_mijnveger_veldje_kleuren(x_veld, y_veld, kleur_actief_rood);
    spel_mijnveger_mijnenveld[x_veld][y_veld] += 10;
    delay(50);
    spel_mijnveger_bommen_tonen();
    delay(500);
    gewaasd_scherm();
    center_tekst(120, 170, "GAME OVER", 4, kleur_actief_rood);
    spel_actief=false;
    delay(500);
    center_tekst(120, 200, "tik om te herstarten", 2, kleur_passief_rood);
    ts.begin();
    while(not ts.touched()) {
      ts.begin();
    }
    scherm_bouwen = true;
  } else if (spel_mijnveger_mijnenveld[x_veld][y_veld] <= 8){
    // Cijfer in het vak zetten
    spel_mijnveger_veldje_cijfer(x_veld, y_veld);
    spel_mijnveger_mijnenveld[x_veld][y_veld] += 10;
    spel_mijnveger_dichte_velden--;
  }

  if (spel_mijnveger_dichte_velden == spel_mijnveger_bommen_cnt) {
    delay(50);
    spel_mijnveger_bommen_tonen();
    delay(500);
    gewaasd_scherm();
    center_tekst(120, 170, "GEWONNEN!", 4, kleur_actief_groen);
    center_tekst(120, 200, "gefeliciteerd ! ! !", 2, kleur_actief_groen);
    spel_actief=false;
    delay(1500);
    center_tekst(120, 220, "tik om te herstarten", 2, kleur_passief_groen);
    ts.begin();
    while(not ts.touched()) {
      ts.begin();
    }
    scherm_bouwen = true;
  }
}

void spel_mijnveger_klik(int x, int y) {
  byte x_veld;
  byte y_veld;
  if (scherm_ili == 9341) {
    x_veld = spel_mijnveger_klik_xy(x, 10, 230, spel_mijnveger_x_cnt);
    y_veld = spel_mijnveger_klik_xy(y, 50, 270, spel_mijnveger_y_cnt);
  } else if (scherm_ili == 9341) {
    x_veld = spel_mijnveger_klik_xy(x, 10, 350, spel_mijnveger_x_cnt);
    y_veld = spel_mijnveger_klik_xy(y, 50, 390, spel_mijnveger_y_cnt);
  } else {
    x_veld = spel_mijnveger_klik_xy(x, 10, 230, spel_mijnveger_x_cnt);
    y_veld = spel_mijnveger_klik_xy(y, 50, 270, spel_mijnveger_y_cnt);
  }
  spel_mijnveger_draai(x_veld, y_veld);
}

void run_spel_mijnveger() {
  ts.begin();
  if (ts.tirqTouched()) {
    if (ts.touched()) {
      
      int x = touch_x();
      int y = touch_y();
      
      if (y >= home_knop[1]) {
        actief_spel = 0;
        spel_actief = false;
        scherm_bouwen = true;
      } else if (y < 30) {
        klik_header(x, y);
      } else {
        spel_mijnveger_klik(x, y);
      }

      while (ts.touched()) {
        ts.begin();
      }
    }
  }
  ts.begin(); 
}
