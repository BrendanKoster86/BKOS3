void bouw_schakelscherm() {

  header_plaatsen("Schakelscherm");
  achtergrond(kleur_licht);
  // achtergrond(tft.color565(235, 235, 100));

  if (io_knoppen_cnt < 10) {
    aantal_knoppen = io_knoppen_cnt;
  } else {
    aantal_knoppen = 10;
  }
  
  delete[]knoppen_positie;
  delete[]knoppen_teken_positie;
  delete[]knoppen_tekst;
  delete[]knoppen_basiskleur;
  delete[]knoppen_tekst_kleur;
  
  knoppen_positie = new int*[aantal_knoppen];
  knoppen_teken_positie = new int*[aantal_knoppen];
  knoppen_tekst = new char*[aantal_knoppen];
  knoppen_basiskleur = new uint16_t*[aantal_knoppen];
  knoppen_tekst_kleur = new uint16_t*[aantal_knoppen];
  knoppen_status = new byte[aantal_knoppen];

  // aantal_knoppen = keuzescherm_knoppen_cnt;
  // knoppen_teken_positie = new int*[keuzescherm_knoppen_cnt];
  // knoppen_positie = new int*[keuzescherm_knoppen_cnt];
  // knoppen_basiskleur = new uint16_t*[keuzescherm_knoppen_cnt];
  // knoppen_tekst = new char*[keuzescherm_knoppen_cnt];
  // knoppen_tekst_kleur = new uint16_t*[keuzescherm_knoppen_cnt];
  // knoppen_status = keuzescherm_knoppen_status;


  for (int i  = 0 ; i < aantal_knoppen ; i++) {
    knoppen_positie[i] = schakelscherm_knoppen_positie[i];
    knoppen_teken_positie[i] = schakelscherm_knoppen_positie[i];
    knoppen_tekst[i] = io_namen[io_knoppen[i]];
    knoppen_status[i] = io_output_status(io_output[io_knoppen[i]]);
    knoppen_basiskleur[i] = schakelscherm_knoppen_kleur;
    knoppen_tekst_kleur[i] = schakelscherm_knoppen_tekst_kleur;
    
  }
  
  alle_knoppen_plaatsen();
  schakelscherm_indicator_bolletjes();

  homeknop_plaatsen();

}

void schakelscherm_indicator_bolletjes() {
  for (int i = 0; i < aantal_knoppen; i++) {
    if (io_input[io_knoppen[i]]) {
      fillCircle(schakelscherm_bolletjes[i][0], schakelscherm_bolletjes[i][1], 10, kleur_wit);
    } else {
      fillCircle(schakelscherm_bolletjes[i][0], schakelscherm_bolletjes[i][1], 10, kleur_zwart);
    }
  }
}

void run_schakelscherm() {
  schakelscherm_indicator_bolletjes();
  ts.begin();
  int druk;
  if (ts.tirqTouched()) {
    if (ts.touched()) {
      
      int x = touch_x();
      int y = touch_y();
      
      druk = klik(x, y);

      if (druk > -1){
        io_schakel(druk);
        io_wijziging = true;
      }

      while (ts.touched()) {
        ts.begin();
      }

      if (y >= home_knop[1]) {
        actief_scherm = 0;
        scherm_bouwen = true;
      } else if (y < 30) {
        klik_header(x, y);
      }

    }
  }
  ts.begin(); 
}
