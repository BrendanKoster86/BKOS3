/*
 * Nummeriek werkt door de parameter bouw_nummeriek te starten
 * 
 * Zorg dat in je functie staat 'if (nummeriek_actief) {run_nummeriek();}
 * 
 * wanneer nummeriek_actief op false staat zal de uitkomst op te halen zijn als 'nummeriek_invoer'
 */
void bouw_nummeriek() {
  bouw_nummeriek("");
}
void bouw_nummeriek(String naam) {
  delete[]knoppen_teken_positie;
  delete[]knoppen_positie;
  delete[]knoppen_basiskleur;
  delete[]knoppen_tekst;
  delete[]knoppen_tekst_kleur;

  aantal_knoppen = 12;
  knoppen_teken_positie = new int*[aantal_knoppen];
  knoppen_positie = new int*[aantal_knoppen];
  knoppen_basiskleur = new uint16_t*[aantal_knoppen];
  knoppen_tekst = new char*[aantal_knoppen];
  knoppen_tekst_kleur = new uint16_t*[aantal_knoppen];
  knoppen_status = knoppen_nummeriek_status;

  for (int i=0 ; i<aantal_knoppen ; i++) {
    knoppen_teken_positie[i] = knoppen_nummeriek_positie[i];
    knoppen_positie[i] = knoppen_nummeriek_positie[i];
    knoppen_basiskleur[i] = instellingen_io_knoppen_kleur;
    knoppen_tekst[i] = knoppen_nummeriek_inhoud[i];
    knoppen_tekst_kleur[i] = instellingen_io_knoppen_tekstkleur;
    
  }

  nummeriek_invoer = 0;
  nummeriek_actief = true;
  header_plaatsen(naam);
  achtergrond(kleur_wit, true);
  alle_knoppen_plaatsen();
  fillRect(5, 30, 230, 40, kleur_zwart);
//  homeknop_plaatsen();
}


void nummeriek_cijfer_toevoegen(int invoer) {
  // Deze functie voegt een cijfer toe
  center_tekst(120, 35, String(nummeriek_invoer), 4, kleur_zwart);
  nummeriek_invoer = nummeriek_invoer * 10 + invoer;
  center_tekst(120, 35, String(nummeriek_invoer), 4, kleur_wit);
}

void nummeriek_cijfer_verwijderen() {
  // Deze functie vewijderd een cijfer en bij 0 wordt afgesloten
  if (nummeriek_invoer == 0) {
    // escape functie
    nummeriek_enter_esc();
  } else {
    center_tekst(120, 35,String(nummeriek_invoer), 4, kleur_zwart);
    nummeriek_invoer = floor(nummeriek_invoer / 10);
    center_tekst(120, 35,String(nummeriek_invoer), 4, kleur_wit);
  }
}

void nummeriek_enter_esc() {
  // Deze functie sluit nummeriek af. Bij escape is de uitkomst 0 en anders wat het moet zijn
  Serial.println("nummeriek afsluiten?");
  nummeriek_actief = false;
}

void run_nummeriek() {
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

      if (y < 40) {
        klik_header(x, y);
      } else if (y > home_knop[1]) {
        actief_scherm = 0;
        scherm_bouwen = true;
      } else if (knop <= 9) {
        // cijfer toevoegen
        nummeriek_cijfer_toevoegen(knop);
      } else if (knop == 10) {
        // cijfer weghalen
        nummeriek_cijfer_verwijderen();
      } else if (knop == 11) {
        // enter
        nummeriek_enter_esc();
      } 
      

    }
  }
  ts.begin();
}
