void bouw_sensor_grafisch() {
  header_plaatsen("Sensor_grafisch");
  achtergrond(kleur_donker);

  if (scherm_ili == 9341) {
    for (int i = 0; i < io_ruimtes_cnt; i++) {
      grafisch_lijnen_200x100(i, 20, 50, kleur_licht, 1);
//      grafisch_vlakken_200x100(i, 20, 50, kleur_oranje, 1);
    }
  } else if (scherm_ili == 9488) {
    for (int i = 0; i < io_ruimtes_cnt; i++) {
      grafisch_lijnen_200x100(i, 20, 50, kleur_licht, 1.5);
    }
  } else {
    for (int i = 0; i < io_ruimtes_cnt; i++) {
      grafisch_lijnen_200x100(i, 20, 50, kleur_licht);
    }
  }

  homeknop_plaatsen(true);
  
}

void grafisch_lijnen_200x100(int item, int x, int y, uint16_t kleur) {
  grafisch_lijnen_200x100(item, x, y, kleur, 1);
}
void grafisch_lijnen_200x100(int item, int x, int y, uint16_t kleur, long factor) {

  byte cnt = io_ruimtes[item][0][0];
  
  int x1;
  int y1;
  int x2;
  int y2;

  x1 = (io_ruimtes[item][cnt][0] * factor) + x;
  y1 = (io_ruimtes[item][cnt][1] * factor) + y;

  for (int i = 1; i <= cnt; i++) {
    x2 = x1;
    y2 = y1;
    x1 = (io_ruimtes[item][i][0] * factor) + x;
    y1 = (io_ruimtes[item][i][1] * factor) + y;

    tft.drawLine(x1, y1, x2, y2, kleur);
  }
}

void grafisch_vlakken_200x100(int item, int x, int y, uint16_t kleur) {
  grafisch_vlakken_200x100(item, x, y, kleur, 1);
}

void grafisch_vlakken_200x100(int item, int x, int y, uint16_t kleur, long factor){
  byte cnt = io_ruimtes[item][0][0];
  int x_gem = 0;
  int y_gem = 0;
  for (int i = 1; i <= cnt; i++) {
    x_gem += io_ruimtes[item][i][0];
    y_gem += io_ruimtes[item][i][1];
  }
  x_gem = x_gem / cnt;
  y_gem = y_gem / cnt;

  

  
  if (cnt >= 3) {
    int x1 = naar_gemiddelde(io_ruimtes[item][1][0], x_gem) + x;
    int x2 = naar_gemiddelde(io_ruimtes[item][2][0], x_gem) + x;
    int x3 = naar_gemiddelde(io_ruimtes[item][3][0], x_gem) + x;
    int y1 = naar_gemiddelde(io_ruimtes[item][1][1], y_gem) + y;
    int y2 = naar_gemiddelde(io_ruimtes[item][2][1], y_gem) + y;
    int y3 = naar_gemiddelde(io_ruimtes[item][3][1], y_gem) + y;
    tft.fillTriangle(x1, y1, x2, y2, x3, y3, kleur);

    for (int i = 4; i <= cnt; i++){
      x2 = x3;
      y2 = y3;
      x3 = naar_gemiddelde(io_ruimtes[item][i][0], x_gem) + x;
      y3 = naar_gemiddelde(io_ruimtes[item][i][1], y_gem) + y;
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, kleur);
    }
  }
}

int naar_gemiddelde(int getal, int gemiddelde) {
  if (getal - 2 > gemiddelde) {
    return getal - 2;
  } else if (getal + 2 < gemiddelde) {
    return getal + 2;
  }
  return getal;
}


uint16_t grafisch_vlakken_tekenen_sensoren_kleur(int i) {
  if (io_input[i] == 0) {
    if (io_alert[i] == 0) {
      return kleur_passief_rood;
    }  else if (io_alert[i] == 1) {
      return kleur_passief_groen;
    } else {
      return kleur_zwart;
    }
  } else if (io_input[i] == 1) {
    if (io_alert[i] == 1) {
      return kleur_actief_rood;
    }  else if (io_alert[i] == 0) {
      return kleur_actief_groen;
    } else {
      return kleur_wit;
    }
  } else {
    return kleur_zwart;
  }
}

void grafisch_vlakken_intekenen_sensoren() {
  for (int i = 0; i < io_cnt; i++) {
    if ((io_object_ruimte[i] >= 0) && (io_object_ruimte[i] != 255)) {
      grafisch_vlakken_200x100(io_object_ruimte[i], 20, 50, grafisch_vlakken_tekenen_sensoren_kleur(i), 1);
    }
  }
}

void run_sensor_grafisch() {
  grafisch_vlakken_intekenen_sensoren();
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
