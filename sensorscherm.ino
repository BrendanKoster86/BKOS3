void bouw_sensorscherm() {
  header_plaatsen("Sensorscherm");
  achtergrond(kleur_donker);

  tft.setTextSize(1.5);
  tft.setTextColor(kleur_licht);

  for (int i = 0 ; i < io_sensoren_cnt; i++) {
    setCursor(sensorscherm_bolletjes[i][0] + 15, sensorscherm_bolletjes[i][1] - 8);
    tft.print(io_namen[io_sensoren[i]]);
  }

  sensorscherm_indicator_bolletjes();

  ts.begin();

  homeknop_plaatsen(true);

}

uint16_t sensorscherm_indicator_bolletjes_kleur(int i) {
  if (io_input[io_sensoren[i]] == 0) {
    if (io_alert[io_sensoren[i]] == 0) {
      return kleur_passief_rood;
    }  else if (io_alert[io_sensoren[i]] == 1) {
      return kleur_passief_groen;
    } else {
      return kleur_zwart;
    }
  } else if (io_input[io_sensoren[i]] == 1) {
    if (io_alert[io_sensoren[i]] == 1) {
      return kleur_actief_rood;
    }  else if (io_alert[io_sensoren[i]] == 0) {
      return kleur_actief_groen;
    } else {
      return kleur_wit;
    }
  } else {
    return kleur_zwart;
  }
}

void sensorscherm_indicator_bolletjes() {
  for (int i = 0 ; i < io_sensoren_cnt; i++) {
    fillCircle(sensorscherm_bolletjes[i][0], sensorscherm_bolletjes[i][1], 10, sensorscherm_indicator_bolletjes_kleur(i));
  }
}

void run_sensorscherm() {
  sensorscherm_indicator_bolletjes();
  ts.begin();
  if (ts.tirqTouched()) {
    if (ts.touched()) {
      
      int x = touch_x();
      int y = touch_y();
      
      if (y >= home_knop[1]) {
        actief_scherm = 0;
        scherm_bouwen = true;
      } else if (y < 30) {
        klik_header(x, y);
      }

      while (ts.touched()) {
        ts.begin();
      }
    }
  }
  ts.begin(); 
}
