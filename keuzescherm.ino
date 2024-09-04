void bouw_keuzescherm() {
  // knoppen_teken_positie = keuzescherm_knoppen;
  delete[]knoppen_teken_positie;
  delete[]knoppen_positie;
  delete[]knoppen_basiskleur;
  delete[]knoppen_tekst;
  delete[]knoppen_tekst_kleur;
  
  
  aantal_knoppen = keuzescherm_knoppen_cnt;
  knoppen_teken_positie = new int*[keuzescherm_knoppen_cnt];
  knoppen_positie = new int*[keuzescherm_knoppen_cnt];
  knoppen_basiskleur = new uint16_t*[keuzescherm_knoppen_cnt];
  knoppen_tekst = new char*[keuzescherm_knoppen_cnt];
  knoppen_tekst_kleur = new uint16_t*[keuzescherm_knoppen_cnt];
  knoppen_status = keuzescherm_knoppen_status;

  for (int i=0 ; i<keuzescherm_knoppen_cnt ; i++) {
    knoppen_teken_positie[i] = keuzescherm_knoppen[i];
    knoppen_positie[i] = keuzescherm_knoppen[i];
    knoppen_basiskleur[i] = keuzescherm_knoppen_kleur[i];
    knoppen_tekst[i] = keuzescherm_knoppen_tekst[i];
    knoppen_tekst_kleur[i] = keuzescherm_knoppen_tekst_kleur[i];
    
  }
  
  header_plaatsen("Keuzescherm");

  fillRect(0, header_vlak[3], 240, 360-header_vlak[3], tft.color565(0, 100, 0));

  alle_knoppen_plaatsen();

}

void run_keuzescherm() {
  int druk;
  if (ts.tirqTouched()) {
    if (ts.touched()) {
      

      int x = touch_x();
      int y = touch_y();
      
      druk = klik(x, y);

      if (druk > -1){
        actief_scherm = druk + 1;
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

void homeknop_plaatsen() {
  fillRect(home_knop[0], home_knop[1], home_knop[2], home_knop[3], kleur_donker);
  center_tekst(home_knop[0] + home_knop[2]/2, home_knop[1] + 10, "Home", 2, kleur_licht);
}

void homeknop_plaatsen(bool invert) {
  if (invert) {
    fillRect(home_knop[0], home_knop[1], home_knop[2], home_knop[3], kleur_licht);
    center_tekst(home_knop[0] + home_knop[2]/2, home_knop[1] + 10, "Home", 2, kleur_donker);
  } else {
    fillRect(home_knop[0], home_knop[1], home_knop[2], home_knop[3], kleur_donker);
    center_tekst(home_knop[0] + home_knop[2]/2, home_knop[1] + 10, "Home", 2, kleur_licht);
  }
}
