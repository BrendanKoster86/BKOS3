void bouw_spel() {
  bouw_spel_scherm[actief_spel]();
}
void run_spel() {
  run_spel_scherm[actief_spel]();
}


void bouw_spelkeuze() {
  // knoppen_teken_positie = spelkeuze_knoppen;
  delete[]knoppen_teken_positie;
  delete[]knoppen_positie;
  delete[]knoppen_basiskleur;
  delete[]knoppen_tekst;
  delete[]knoppen_tekst_kleur;
  
  aantal_knoppen = spelkeuze_knoppen_cnt;
  knoppen_teken_positie = new int*[spelkeuze_knoppen_cnt];
  knoppen_positie = new int*[spelkeuze_knoppen_cnt];
  knoppen_basiskleur = new uint16_t*[spelkeuze_knoppen_cnt];
  knoppen_tekst = new char*[spelkeuze_knoppen_cnt];
  knoppen_tekst_kleur = new uint16_t*[spelkeuze_knoppen_cnt];
  knoppen_status = spelkeuze_knoppen_status;

  
  for (int i=0 ; i<spelkeuze_knoppen_cnt ; i++) {
    knoppen_teken_positie[i] = spelkeuze_knoppen[i];
    knoppen_positie[i] = spelkeuze_knoppen[i];
    knoppen_basiskleur[i] = spelkeuze_knoppen_kleur[i];
    knoppen_tekst[i] = spelkeuze_knoppen_tekst[i];
    knoppen_tekst_kleur[i] = spelkeuze_knoppen_tekst_kleur[i];
    
  }

  header_plaatsen("spelkeuze");

  fillRect(0, header_vlak[3], 240, 360-header_vlak[3], tft.color565(0, 100, 0));

  alle_knoppen_plaatsen();
  homeknop_plaatsen(true);

}

void run_spelkeuze() {
  int druk;
  if (ts.tirqTouched()) {
    if (ts.touched()) {
      

      int x = touch_x();
      int y = touch_y();
      
      druk = klik(x, y);

      if (druk > -1){
        actief_spel = druk + 1;
        scherm_bouwen = true;
      } else if (y < 30) {
        klik_header(x, y);
      } else if (y >= home_knop[1]) {
        actief_scherm = 0;
        actief_spel = 0;
        scherm_bouwen = true;
      }

      while (ts.touched()) {
        ts.begin();
      }

    }
  }
  ts.begin();
}
