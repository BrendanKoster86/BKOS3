void naar_io_instellingen() {
  actief_scherm = 9;
  scherm_bouwen = true;
}

void start_io_instellingen() {
  instellingen_io_knoppen_reeks_cnt = 0;
  int i = io_sd_cnt;
  while (i > 0) {
    instellingen_io_knoppen_reeks_cnt++;
    i -= 8;
  }
  Serial.print("instellingen_io_knoppen_reeks_cnt : ");
  Serial.println(instellingen_io_knoppen_reeks_cnt);
}
void bouw_io_instellingen () {
  header_plaatsen("io instellingen");
  achtergrond(kleur_zwart, false);
  delete[]knoppen_positie;
  delete[]knoppen_teken_positie;
  delete[]knoppen_basiskleur;
  delete[]knoppen_tekst;
  delete[]knoppen_tekst2;
  delete[]knoppen_tekst_kleur;

  aantal_knoppen = instellingen_io_knoppen_cnt;
  knoppen_positie = new int*[aantal_knoppen];
  knoppen_teken_positie = new int*[aantal_knoppen];
  knoppen_tekst = new char*[aantal_knoppen];
  knoppen_tekst2 = new char*[aantal_knoppen];
  knoppen_basiskleur = new uint16_t*[aantal_knoppen];
  knoppen_tekst_kleur = new uint16_t*[aantal_knoppen];
  knoppen_status = io_instellingen_knoppen_status;


  for (int i = 0; i < aantal_knoppen; i++) {
    knoppen_teken_positie[i] = instellingen_io_knoppen_positie[i];
    knoppen_positie[i] = instellingen_io_knoppen_positie[i];
    knoppen_basiskleur[i] = instellingen_io_knoppen_kleur;
    knoppen_tekst[i] = instellingen_io_knoppen_tekst[i];
    knoppen_tekst2[i] = instellingen_io_knoppen_tekst2[i];
    knoppen_tekst_kleur[i] = instellingen_io_knoppen_tekstkleur;
  }
  bouw_io_instellingen_knoppen();
}
void bouw_io_instellingen_knoppen() {

  // Bepalen of de knoppen voor een reeks eerder of later actief gemaakt moeten worden
  if (instellingen_io_knoppen_reeks == 0) {
    knoppen_status[12] = 5;
  } else {
    knoppen_status[12] = 2;
  }
  if (instellingen_io_knoppen_reeks+1 <= instellingen_io_knoppen_reeks_cnt) {
    knoppen_status[13] = 2;
  } else {
    knoppen_status[13] = 5;
  }

  char buf[10];

  String(io_sd_cnt).toCharArray(knoppen_tekst[0], 10);
  // knoppen_tekst[0] = buf;

  // Nummering van de io poorten aan de knoppen toewijzen. Dit enkel als cijfer.
  for (int i = 0; i < 8; i++) {
    Serial.print(i);
    Serial.print(" : ");
    if ((i + instellingen_io_knoppen_reeks*8) < io_sd_cnt) {
      String(i + instellingen_io_knoppen_reeks*8).toCharArray(knoppen_tekst[i+2], 10);
      io_sd[i + instellingen_io_knoppen_reeks*8].substring(4).toCharArray(knoppen_tekst2[i+2], 10);
      // Serial.println(buf);
      // knoppen_tekst[i+2] = buf;
      knoppen_status[i+2] = SD_byte(io_sd[i + instellingen_io_knoppen_reeks*8].substring(0, 1));
    } else {
      String tmp_string = "";
      tmp_string.toCharArray(knoppen_tekst[i+2], 10);
      // Serial.println(buf);
      // knoppen_tekst[i+2] = buf;
      knoppen_status[i+2] = 5;
    }
  }

  alle_knoppen_plaatsen(true);

}

void run_io_instellingen() {
  if (ts.tirqTouched()) {
    if (ts.touched()) {
      int x = touch_x();
      int y = touch_y();

      Serial.print(x);
      Serial.print("; ");
      Serial.println(y);

      while (ts.touched()) {
        ts.begin();
      }

      int knop = klik(x, y);

      Serial.println(knop);

      if (knop == 0) {
        actief_scherm = 11;
        scherm_bouwen = true;
      } else if ((knop >= 1) & (knop < 11) & (knoppen_status[knop] != 5)) {
        actief_scherm = 10;
        scherm_bouwen = true;
        naar_instellingen_io_poort(String(knoppen_tekst[knop]).toInt());
      } else if (knop == 11) {
        actief_scherm = 0;
        scherm_bouwen = true;
      } else if (knop == 14) {
        if (beeld_vraag("Opslaan", "Aanpassingen opslaan?", "JA", "NEE") == 0) {
          beeld_melding("Even geduld . . .", "Aanpassingen worden opgeslagen", "opslaan");
          delay(1000);
          if (sd_save_io()) {
            SD_connect = true;
            beeld_melding("opgeslagen","IO instellingen opgeslagen", "opslaan");
            delay(1000);
            sd_io();
            start_io();
          } else {
            SD_connect = false;
            beeld_vraag("mislukt","niet opgeslagen", "das balen :(");
          }
          actief_scherm = 0;
          scherm_bouwen = true;
        } else {
          scherm_bouwen = true;
        }
      } else if ((knop == 12) & (knoppen_status[12] == 2)) {
        instellingen_io_knoppen_reeks--;
        bouw_io_instellingen_knoppen();
      } else if ((knop == 13) & (knoppen_status[13] == 2)) {
        instellingen_io_knoppen_reeks++;
        bouw_io_instellingen_knoppen();
      // } else if ((knop >= 2) & (knop <= 10) & (knoppen_status[knop] != 5)) {
      //   beeld_melding("Knop instellingen in aanbouw");
      // } else {
        
      }
      if (y < 40) {
        klik_header(x, y);
      }

    }
  }
  ts.begin();
}
