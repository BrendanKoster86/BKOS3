void bouw_spel_boterkaaseneieren() {
  header_plaatsen("Boter kaas en eieren");
  achtergrond(kleur_licht);
  spel_boterkaaseneieren_veld();
  homeknop_plaatsen();
}

void spel_boterkaaseneieren_veld() {
  tft.fillRect(spel_speelveld[0]-4 , spel_speelveld[1]-4, spel_speelveld[2]+8, spel_speelveld[3]+8, kleur_donker);
  tft.drawRect(spel_speelveld[0]-6 , spel_speelveld[1]-6, spel_speelveld[2]+12, spel_speelveld[3]+12, kleur_donker);
  tft.drawLine(spel_speelveld[0] + spel_speelveld[2]/3, spel_speelveld[1], spel_speelveld[0] + spel_speelveld[2]/3, spel_speelveld[1] + spel_speelveld[3], kleur_licht);
  tft.drawLine(spel_speelveld[0] + spel_speelveld[2]/3 * 2, spel_speelveld[1], spel_speelveld[0] + spel_speelveld[2]/3 * 2, spel_speelveld[1] + spel_speelveld[3], kleur_licht);
  tft.drawLine(spel_speelveld[0], spel_speelveld[1] + spel_speelveld[3]/3, spel_speelveld[0] + spel_speelveld[2], spel_speelveld[1] + spel_speelveld[3]/3, kleur_licht);
  tft.drawLine(spel_speelveld[0], spel_speelveld[1] + spel_speelveld[3]/3 * 2, spel_speelveld[0] + spel_speelveld[2], spel_speelveld[1] + spel_speelveld[3]/3 * 2, kleur_licht);
  for (int i = 0; i < 9; i++) {
    if (spel_boterkaaseneieren_status[i] > 0) {
      spel_boterkaaseneieren_teken_symbool(i);
    }
  }
}

void spel_boterkaaseneieren_teken_symbool(int hokje) {
  if (hokje <= 2) {
    if (spel_boterkaaseneieren_status[hokje] == 1) {
      center_tekst(spel_speelveld[0] + spel_speelveld[2] / 6 * (hokje * 2 + 1) + spel_speelveld[2] / 30, spel_speelveld[1], "x", 8, kleur_licht);
    } else if (spel_boterkaaseneieren_status[hokje] == 2) {
      center_tekst(spel_speelveld[0] + spel_speelveld[2] / 6 * (hokje * 2 + 1) + spel_speelveld[2] / 30, spel_speelveld[1], "o", 8, kleur_licht);
    }
  } else if (hokje <= 5) {
    if (spel_boterkaaseneieren_status[hokje] == 1) {
      center_tekst(spel_speelveld[0] + spel_speelveld[2] / 6 * ((hokje - 3) * 2 + 1) + spel_speelveld[2] / 30, spel_speelveld[1] + spel_speelveld[3] / 3, "x", 8, kleur_licht);
    } else if (spel_boterkaaseneieren_status[hokje] == 2) {
      center_tekst(spel_speelveld[0] + spel_speelveld[2] / 6 * ((hokje - 3) * 2 + 1) + spel_speelveld[2] / 30, spel_speelveld[1] + spel_speelveld[3] / 3, "o", 8, kleur_licht);
    }
  } else {
    if (spel_boterkaaseneieren_status[hokje] == 1) {
      center_tekst(spel_speelveld[0] + spel_speelveld[2] / 6 * ((hokje - 6) * 2 + 1) + spel_speelveld[2] / 30, spel_speelveld[1] + spel_speelveld[3] - spel_speelveld[3] / 3, "x", 8, kleur_licht);
    } else if (spel_boterkaaseneieren_status[hokje] == 2) {
      center_tekst(spel_speelveld[0] + spel_speelveld[2] / 6 * ((hokje - 6) * 2 + 1) + spel_speelveld[2] / 30, spel_speelveld[1] + spel_speelveld[3] - spel_speelveld[3] / 3, "o", 8, kleur_licht);
    }
  }
}

void spel_boterkaaseneieren_beurt_computer() {
  if (spel_boterkaaseneieren_winnen() < 9) {
    spel_boterkaaseneieren_zet(2, spel_boterkaaseneieren_winnen());
  } else if (spel_boterkaaseneieren_verlies_voorkomen() < 9) {
    spel_boterkaaseneieren_zet(2, spel_boterkaaseneieren_verlies_voorkomen());
  } else {
    spel_boterkaaseneieren_zet(2, spel_boterkaaseneieren_willekeurig());
  }
}

int spel_boterkaaseneieren_winnen() {
  for (int i = 0; i < 8; i++) {
    int x_cnt = 0;
    int o_cnt = 0;
    for (int j = 0; j < 9; j++) {
      if (spel_boterkaaseneieren_winnen_opties[i].indexOf(String(j)) > -1) {
        if (spel_boterkaaseneieren_status[j] == 2) {
          o_cnt++;
        } else if (spel_boterkaaseneieren_status[j] == 1) {
          x_cnt++;
        } 
      }
    }
    if ((o_cnt == 2) && (x_cnt == 0)) {
      for (int j = 0; j < 9; j++) {
        if (spel_boterkaaseneieren_winnen_opties[i].indexOf(String(j)) > -1) {
          if (spel_boterkaaseneieren_status[j] == 2) {
            o_cnt++;
          } else {
            return j;
          } 
        }
      }
    }
  }
  return 9;
}

int spel_boterkaaseneieren_verlies_voorkomen() {
  for (int i = 0; i < 8; i++) {
    int x_cnt = 0;
    int o_cnt = 0;
    for (int j = 0; j < 9; j++) {
      if (spel_boterkaaseneieren_winnen_opties[i].indexOf(String(j)) > -1) {
        if (spel_boterkaaseneieren_status[j] == 2) {
          o_cnt++;
        } else if (spel_boterkaaseneieren_status[j] == 1) {
          x_cnt++;
        } 
      }
    }
    if ((o_cnt == 0) && (x_cnt == 2)) {
      for (int j = 0; j < 9; j++) {
        if (spel_boterkaaseneieren_winnen_opties[i].indexOf(String(j)) > -1) {
          if (spel_boterkaaseneieren_status[j] == 1) {
            x_cnt++;
          } else {
            return j;
          } 
        }
      }
    }
  }
  return 9;
}

int spel_boterkaaseneieren_willekeurig() {
  byte cnt = 0;
  for (int i = 0; i < 9; i++) {
    if (spel_boterkaaseneieren_status[i] == 0) {
      cnt++;
    }
  }
  int keuze = random(cnt);

  for (int i = 0; i < 9; i++) {
    if (spel_boterkaaseneieren_status[i] == 0) {
      cnt--;
      if (cnt <= keuze) {
        return i;
      }
    }
  }
  return 10;
}

void spel_boterkaaseneieren_zet(int speler, int zet) {
  if (spel_boterkaaseneieren_status[zet] == 0) {
    spel_boterkaaseneieren_status[zet] = speler;
    spel_boterkaaseneieren_teken_symbool(zet);
    if (speler == 1) {
      spel_boterkaaseneieren_beurt = 2;
    } else {
      spel_boterkaaseneieren_beurt = 1;
    }
  }
}

void spel_boterkaaseneieren_isergewonnen() {
  for (int i = 0; i < 8; i++) {
    int x_cnt = 0;
    int o_cnt = 0;
    for (int j = 0; j < 9; j++) {
      if (spel_boterkaaseneieren_winnen_opties[i].indexOf(String(j)) > -1) {
        if (spel_boterkaaseneieren_status[j] == 2) {
          o_cnt++;
        } else if (spel_boterkaaseneieren_status[j] == 1) {
          x_cnt++;
        } 
      }
    }
    
    if ((o_cnt == 3) || (x_cnt == 3)) {
      if (i < 3) {
        tft.drawLine(spel_speelveld[0], spel_speelveld[1] + spel_speelveld[3] / 6 * (i * 2 + 1), spel_speelveld[0] + spel_speelveld[2], spel_speelveld[1] + spel_speelveld[3] / 6 * (i * 2 + 1), kleur_licht);
        tft.drawLine(spel_speelveld[0], spel_speelveld[1] + spel_speelveld[3] / 6 * (i * 2 + 1)-1, spel_speelveld[0] + spel_speelveld[2], spel_speelveld[1] + spel_speelveld[3] / 6 * (i * 2 + 1)-1, kleur_licht);
        tft.drawLine(spel_speelveld[0], spel_speelveld[1] + spel_speelveld[3] / 6 * (i * 2 + 1)+1, spel_speelveld[0] + spel_speelveld[2], spel_speelveld[1] + spel_speelveld[3] / 6 * (i * 2 + 1)+1, kleur_licht);
      } else if (i < 6) {
        tft.drawLine(spel_speelveld[0] + spel_speelveld[2] / 6 * ((i - 3) * 2 + 1), spel_speelveld[1], spel_speelveld[0] + spel_speelveld[2] / 6 * ((i - 3) * 2 + 1), spel_speelveld[1] + spel_speelveld[3], kleur_licht);
        tft.drawLine(spel_speelveld[0] + spel_speelveld[2] / 6 * ((i - 3) * 2 + 1)-1, spel_speelveld[1], spel_speelveld[0] + spel_speelveld[2] / 6 * ((i - 3) * 2 + 1)-1, spel_speelveld[1] + spel_speelveld[3], kleur_licht);
        tft.drawLine(spel_speelveld[0] + spel_speelveld[2] / 6 * ((i - 3) * 2 + 1)+1, spel_speelveld[1], spel_speelveld[0] + spel_speelveld[2] / 6 * ((i - 3) * 2 + 1)+1, spel_speelveld[1] + spel_speelveld[3], kleur_licht);
      } else if (i == 6) {
        tft.drawLine(spel_speelveld[0], spel_speelveld[1], spel_speelveld[0] + spel_speelveld[2], spel_speelveld[1] + spel_speelveld[3], kleur_licht);
        tft.drawLine(spel_speelveld[0]+1, spel_speelveld[1], spel_speelveld[0] + spel_speelveld[2], spel_speelveld[1] + spel_speelveld[3]-1, kleur_licht);
        tft.drawLine(spel_speelveld[0], spel_speelveld[1]+1, spel_speelveld[0] + spel_speelveld[2]-1, spel_speelveld[1] + spel_speelveld[3], kleur_licht);
        tft.drawLine(spel_speelveld[0], spel_speelveld[1]+2, spel_speelveld[0] + spel_speelveld[2]-2, spel_speelveld[1] + spel_speelveld[3], kleur_licht);
      } else {
        tft.drawLine(spel_speelveld[0] + spel_speelveld[2], spel_speelveld[1], spel_speelveld[0], spel_speelveld[1] + spel_speelveld[3], kleur_licht);
        tft.drawLine(spel_speelveld[0] + spel_speelveld[2]-1, spel_speelveld[1], spel_speelveld[0], spel_speelveld[1] + spel_speelveld[3]-1, kleur_licht);
        tft.drawLine(spel_speelveld[0] + spel_speelveld[2], spel_speelveld[1]+1, spel_speelveld[0]+1, spel_speelveld[1] + spel_speelveld[3], kleur_licht);
        tft.drawLine(spel_speelveld[0] + spel_speelveld[2], spel_speelveld[1]+2, spel_speelveld[0]+2, spel_speelveld[1] + spel_speelveld[3], kleur_licht);
      }
      delay(500);
      gewaasd_scherm();
      if (x_cnt == 3) {
        center_tekst(120, 170, "GEWONNEN!", 4, kleur_actief_groen);
      } else {
        center_tekst(120, 170, "GAME OVER", 4, kleur_actief_rood);
      }
      delay(1000);
      spel_boterkaaseneieren_nieuwspel();
    }
  }
  int leeg = 0;
  for (int i = 0; i < 9; i++) {
    if (spel_boterkaaseneieren_status[i] == 0) {
      leeg ++;
    }
  }
  if (leeg == 0) {
    delay(500);
    gewaasd_scherm();
    center_tekst(120, 170, "gelijk spel", 4, kleur_actief_groen);
    delay(1000);
    spel_boterkaaseneieren_nieuwspel();
  }

}

void spel_boterkaaseneieren_nieuwspel() {
  for (int i = 0; i < 9; i++) {
    spel_boterkaaseneieren_status[i] = 0;
  }
  spel_boterkaaseneieren_beurt = 0;
  bouw_spel_boterkaaseneieren();
}

void spel_boterkaaseneieren_klik(int x, int y) {
  int hokje = 0;
  byte y_stapjes = spel_speelveld[3] / 3;
  byte x_stapjes = spel_speelveld[2] / 3;
  if (y < spel_speelveld[1] + y_stapjes) {
    hokje = hokje; // niks doen, bovenste rij
  } else if (y < spel_speelveld[1] + y_stapjes * 2) {
    hokje = hokje + 3; // 2e rij
  } else {
    hokje = hokje + 6; // 3e rij
  }

  if (x < spel_speelveld[0] + x_stapjes) {
    hokje = hokje; // niks doen, linker kolom
  } else if (x < spel_speelveld[0] + x_stapjes * 2) {
    hokje = hokje + 1; // middelste kolom
  } else {
    hokje = hokje + 2; // rechter kolom
  }

  spel_boterkaaseneieren_zet(1, hokje);

}

void spel_boterkaaseneieren_beurt_speler() {
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
        spel_boterkaaseneieren_klik(x, y);
      }

      while (ts.touched()) {
        ts.begin();
      }
    }
  }
  ts.begin(); 
}

void run_spel_boterkaaseneieren() {
  spel_boterkaaseneieren_isergewonnen();
  if (spel_boterkaaseneieren_beurt == 1) {
    // speler is aan de beurt
    spel_boterkaaseneieren_beurt_speler();
  } else if (spel_boterkaaseneieren_beurt == 2) {
    // computer aan de beurt
    spel_boterkaaseneieren_beurt_computer();
  } else {
    // Nog geen speler gekozen? dan wordt nu een speler gekozen
    spel_boterkaaseneieren_beurt = random(1, 3);
    Serial.print("Speler : ");
    Serial.println(spel_boterkaaseneieren_beurt);
  }
}
