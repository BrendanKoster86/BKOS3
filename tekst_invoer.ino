void bouw_tekstinvoer() {
  bouw_tekstinvoer("", 0, "");
}

void bouw_tekstinvoer(String titel) {
  bouw_tekstinvoer(titel, 0, "");
}

void bouw_tekstinvoer(byte max_lengtem, String beginwaarde) {
  bouw_tekstinvoer("", max_lengtem, beginwaarde);
}

void bouw_tekstinvoer(String titel, String beginwaarde) {
  bouw_tekstinvoer(titel, 0, beginwaarde);
}

void bouw_tekstinvoer(String titel, byte max_lengte, String beginwaarde) {
  header_plaatsen(titel);
  fillRect(0, 25, 240, 5, kleur_zwart);
  fillRect(0, 30, 5, 40, kleur_zwart);
  fillRect(5, 30, 230, 40, kleur_wit);
  fillRect(235, 30, 5, 40, kleur_zwart);
  Serial.print(1);
  tekstinvoer_actief = true;
  Serial.print(2);
  tekst_invoer = beginwaarde;
  Serial.print(3);
  fillRect(0, 170, 240, home_knop[1] - 170, kleur_zwart);
  Serial.println(4);
  tekstinvoer_toetsenbord_maken();
  Serial.println("done");
  

  homeknop_plaatsen();
}

void toetsen_aanmaken(byte aantal) {
  
  Serial.print(1);
  delete[]knoppen_positie;
  Serial.print(1);
  delete[]knoppen_teken_positie;
  Serial.print(1);
  delete[]knoppen_tekst;
  Serial.print(1);
  delete[]knoppen_basiskleur;
  Serial.print(1);
  delete[]knoppen_tekst_kleur;
  Serial.print(1);
  
  Serial.print(2);
  knoppen_positie = new int*[aantal];
  Serial.print(2);
  knoppen_teken_positie = new int*[aantal];
  Serial.print(2);
  knoppen_tekst = new char*[aantal];
  Serial.print(2);
  knoppen_basiskleur = new uint16_t*[aantal];
  Serial.print(2);
  knoppen_tekst_kleur = new uint16_t*[aantal];
  Serial.print(2);
  knoppen_status = new byte[aantal];
  Serial.println(2);
  
}

void toetsen_positie_maken(byte eerste_knop, byte laatste_knop, byte modus, int x, int y, int b, int h) {
  byte aantal_knoppen = laatste_knop - eerste_knop;
  int knop_breedte;
  int breedte_eerste;
  int rol_x = x;

  Serial.print("modus :");
  
  // Voorbehandeling
  if (modus == 1) {
    // Eerste rij normaal toetsenbord
    Serial.print(1);
    knop_breedte = b / (aantal_knoppen + 1);
    breedte_eerste = knop_breedte - 2;
  } else if (modus == 2) {
    // 2e rij normaal toetsenbord
    Serial.print(2);
    knop_breedte = b / (aantal_knoppen + 1);
    breedte_eerste = knop_breedte * 3 / 2;
  } else if (modus == 3) {
    // 3e rij normaal toetsenbord
    Serial.print(3);
    knop_breedte = b / (aantal_knoppen + 2);
    breedte_eerste = knop_breedte * 2 - knop_breedte / 4;
  } else if (modus == 4) {
    // 4e rij normaal toetsenbord
    Serial.print(4);
    knop_breedte = b / (aantal_knoppen + 2);
    breedte_eerste = knop_breedte + knop_breedte / 4;
  } else if (modus == 0) {
    // Evenwichtige verdeling
    Serial.print(0);
    knop_breedte = b / aantal_knoppen;
    breedte_eerste = knop_breedte;
  } else if (modus == 5) {
    // Evenwichtige verdeling, maar achteraan een lege ruimte laten (voor knop over meer rijen
    Serial.print(5);
    knop_breedte = b / (aantal_knoppen +1);
    breedte_eerste = knop_breedte;
  } else if (modus == 6) {
    // Enkel de laatset van 4 knoppen
    Serial.print(6);
    knop_breedte = b / 4;
    breedte_eerste = knop_breedte;
    rol_x = x + (knop_breedte * 3) + 1;
  }

  Serial.println();
  Serial.print("  knop: ");
  Serial.print(eerste_knop);
  Serial.print(" ");
  Serial.print(rol_x);
  // Plaatsen eerste knop
  knoppen_positie[eerste_knop][0] = rol_x;
  Serial.print(" ");
  Serial.print(y);
  knoppen_positie[eerste_knop][1] = y;
  Serial.print(" ");
  Serial.print(breedte_eerste);
  knoppen_positie[eerste_knop][2] = breedte_eerste;
  Serial.print(" ");
  Serial.print(h);
  knoppen_positie[eerste_knop][3] = h;
  
  Serial.print(" ");
  Serial.print(rol_x);
  knoppen_teken_positie[eerste_knop][0] = rol_x;
  Serial.print(" ");
  Serial.print(y);
  knoppen_teken_positie[eerste_knop][1] = y;
  Serial.print(" ");
  Serial.print(breedte_eerste);
  knoppen_teken_positie[eerste_knop][2] = breedte_eerste;
  Serial.print(" ");
  Serial.print(h);
  knoppen_teken_positie[eerste_knop][3] = h;

  Serial.print(" ");
  Serial.print(rol_x + breedte_eerste + 2);
  rol_x = rol_x + breedte_eerste + 2;
  Serial.print(" ");
  Serial.print(rol_x);
  

  // Plaatsen van de grote reeks aan knoppen
  for (int i = eerste_knop+1; i < laatste_knop; i++) {
    Serial.println();
    Serial.print("  knop: ");
    Serial.print(i);
    Serial.print(" ");
    Serial.print(rol_x);
    knoppen_positie[i][0] = rol_x;
    Serial.print(" ");
    Serial.print(y);
    knoppen_positie[i][1] = y;
    Serial.print(" ");
    Serial.print(knop_breedte - 2);
    knoppen_positie[i][2] = knop_breedte - 2;
    Serial.print(" ");
    Serial.print(h);
    knoppen_positie[i][3] = h;
    
    Serial.print(" ");
    Serial.print(rol_x);
    knoppen_teken_positie[i][0] = rol_x;
    Serial.print(" ");
    Serial.print(y);
    knoppen_teken_positie[i][1] = y;
    Serial.print(" ");
    Serial.print(knop_breedte - 2);
    knoppen_teken_positie[i][2] = knop_breedte - 2;
    Serial.print(" ");
    Serial.print(h);
    knoppen_teken_positie[i][3] = h;

    Serial.println();
    Serial.println(rol_x + knop_breedte + 1);
    
    rol_x = rol_x + knop_breedte + 1;

    Serial.println(rol_x);
  }

  if (eerste_knop != laatste_knop) {
    // Plaatsen laatste knop
    Serial.print(laatste_knop);
    knoppen_positie[laatste_knop][0] = rol_x;
    knoppen_positie[laatste_knop][1] = y;
    knoppen_positie[laatste_knop][2] = b - rol_x;
    knoppen_positie[laatste_knop][3] = h;
    
    knoppen_teken_positie[laatste_knop][0] = rol_x;
    knoppen_teken_positie[laatste_knop][1] = y;
    knoppen_teken_positie[laatste_knop][2] = b - rol_x;
    knoppen_teken_positie[laatste_knop][3] = h;
  }
}

void tekstinvoer_toetsenbord_inhoud(int aantal_toetsen) {
  for (int i = 0; i < aantal_toetsen; i++) {
    knoppen_tekst[i] = toetsenbord_knoppen[toetsenbord_type][i];
    knoppen_basiskleur[i][0] = kleur_wit;
    knoppen_tekst_kleur[i][0] = kleur_zwart;
    knoppen_status[i] = 0;
    
  }
}

void toetsen_positie_spatie_maken(byte eerste_knop, byte laatste_knop, byte modus, int x, int y, int b, int h) {
  int knop_breedte = b / (aantal_knoppen * 2);
  int rol_x = x;
  for (int i = eerste_knop; i <= laatste_knop; i++) {
    knoppen_positie[i][0] = rol_x;
    knoppen_positie[i][1] = y;
    knoppen_positie[i][3] = h;
    
    knoppen_teken_positie[i][0] = rol_x;
    knoppen_teken_positie[i][1] = y;
    knoppen_teken_positie[i][3] = h;

    if (toetsenbord_knoppen[toetsenbord_type][i] == " ") {
      knoppen_positie[i][2] = knop_breedte * 2 - 2;
      knoppen_teken_positie[i][2] = knop_breedte * 2 - 2;
      rol_x = rol_x + knop_breedte * 2 + 1;
    } else {
      knoppen_positie[i][2] = knop_breedte - 2;
      knoppen_teken_positie[i][2] = knop_breedte - 2;
      rol_x = rol_x + 1;
    }
  }
}

void tekstinvoer_toetsenbord_maken() {
  if (toetsenbord_type == 0) {
    toetsenbord_type = 1;
  }

  Serial.print("Toetsenbord_type: ");
  Serial.println(toetsenbord_type);

  fillRect(0, 70, 240, 100, kleur_zwart);
  
  if ((toetsenbord_type == 1) || (toetsenbord_type == 2)) {
    Serial.print("toetsen_aanmaken: ");
    toetsen_aanmaken(14+14+13+12+7);
    Serial.print("positie maken: ");
    toetsen_positie_maken(0, 13, 1, 5, 75, 230, 15);
    toetsen_positie_maken(14, 27, 2, 5, 92, 230, 15);
    toetsen_positie_maken(28, 40, 2, 5, 109, 230, 15);
    toetsen_positie_maken(41, 52, 2, 5, 126, 230, 15);
    toetsen_positie_spatie_maken(53, 112, 2, 5, 143, 230, 15);
    tekstinvoer_toetsenbord_inhoud(113);
  } else if (toetsenbord_type == 5) {
    toetsen_aanmaken(17);
    toetsen_positie_maken(0, 3, 0, 5, 75, 230, 15);
    toetsen_positie_maken(4, 6, 5, 5, 92, 230, 15);
    toetsen_positie_maken(7, 7, 6, 5, 92, 230, 32);
    toetsen_positie_maken(8, 10, 5, 5, 109, 230, 15);
    toetsen_positie_maken(11, 13, 5, 5, 126, 230, 15);
    toetsen_positie_maken(14, 14, 6, 5, 92, 230, 32);
    toetsen_positie_maken(15, 16, 5, 5, 143, 230, 15);
    tekstinvoer_toetsenbord_inhoud(17);
  }
  

  alle_knoppen_plaatsen();
  
}

void tekstinvoer_invoer(char invoer) {
  
  center_tekst(120, 35, tekst_invoer, 3, kleur_wit);
  if ((tekstinvoer_maximaal == 0) || (tekstinvoer_maximaal > tekst_invoer.length())) {
    tekst_invoer += invoer;
  } else {
    tekst_invoer = tekst_invoer.substring(0, tekstinvoer_maximaal-1) + invoer;
  }
  center_tekst(120, 35, tekst_invoer, 3, kleur_zwart);
  if (tekstinvoer_shift) {
    tekstinvoer_shift_actie();
  }
}

void tekstinvoer_shift_actie() {
  if (tekstinvoer_shift) {
    tekstinvoer_shift = false;
  } else {
    tekstinvoer_shift = true;
  }
  if (toetsenbord_type == 1) {
    toetsenbord_type = 2;
  } else if (toetsenbord_type == 2) {
    toetsenbord_type = 1;
  }
  tekstinvoer_toetsenbord_maken();
}

void tekstinvoer_capslock_actie() {
  tekstinvoer_shift = false;
  
  if (toetsenbord_type == 1) {
    toetsenbord_type = 2;
  } else if (toetsenbord_type == 2) {
    toetsenbord_type = 1;
  }
  tekstinvoer_toetsenbord_maken();
}

void tekstinvoer_backspace() {
  center_tekst(120, 35, tekst_invoer, 3, kleur_wit);
  tekst_invoer = tekst_invoer.substring(0, tekst_invoer.length()-1);
  center_tekst(120, 35, tekst_invoer, 3, kleur_zwart);
}

void tekstinvoer_knop_ingedrukt(int knop) {
  if (knoppen_tekst[knop] == "ENTER") {
    // enter actie
    tekstinvoer_actief = false;
    
  } else if (knoppen_tekst[knop] == "<=") {
    // backspace actie
    tekstinvoer_backspace();
    
  } else if (knoppen_tekst[knop] == "CAP") {
    // capslock actie
    tekstinvoer_capslock_actie();
    
  } else if (knoppen_tekst[knop] == "^^") {
    // shift actie
    tekstinvoer_shift_actie();
    
  } else if (knoppen_tekst[knop] == "CTRL") {
    // control actie
  } else if (knoppen_tekst[knop] == "ALT") {
    // alt actie
  } else if (knoppen_tekst[knop] == "SYM") {
    // symbool actie
  } else if (knoppen_tekst[knop] == "abc") {
    // tekst actie
    toetsenbord_type = 1;
    tekstinvoer_toetsenbord_maken();
    
  } else if (knoppen_tekst[knop] == "123") {
    // cijfer actie
    toetsenbord_type = 5;
    tekstinvoer_toetsenbord_maken();
    
  } else if (knoppen_tekst[knop] == "<=>") {
    // tab actie
  } else {
    // invoer
    tekstinvoer_invoer(knoppen_tekst[knop][0]);
  }
}



void run_tekstinvoer() {
  ts.begin();
  int druk;
  if (ts.tirqTouched()) {
    if (ts.touched()) {
      
      int x = touch_x();
      int y = touch_y();
      
      druk = klik(x, y);

      if (druk > -1){
        tekstinvoer_knop_ingedrukt(druk);
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
