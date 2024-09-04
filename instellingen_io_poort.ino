void naar_instellingen_io_poort(int poort) {
  instellingen_io_poort_nummer = poort;
  io_sd[poort].substring(4).toCharArray(instellingen_io_poort_naam, 10);
//  io_namen[poort].toCharArray(instellingen_io_poort_naam, 10);
  instellingen_io_poort_functie = io_sd[poort].substring(0,1).toInt();
  // instellingen_io_poort_default = io_sd[poort].substring(2,3).toInt();
  instellingen_io_poort_alert = io_sd[poort].substring(3,4).toInt();
  if (io_sd[poort].substring(1,2) == "1") {
    instellingen_io_poort_opslaan = true;
  } else {
    instellingen_io_poort_opslaan = false;
  }
  if (io_sd[poort].substring(2,3).toInt() == 0) {
    instellingen_io_poort_default = false;
    instellingen_io_poort_inverse = false;
  } else if (io_sd[poort].substring(2,3).toInt() == 1) {
    instellingen_io_poort_default = true;
    instellingen_io_poort_inverse = false;
  } else if (io_sd[poort].substring(2,3).toInt() == 2) {
    instellingen_io_poort_default = false;
    instellingen_io_poort_inverse = true;
  } else if (io_sd[poort].substring(2,3).toInt() == 3) {
    instellingen_io_poort_default = true;
    instellingen_io_poort_inverse = true;
  }
  byte instellingen_io_poort_functie = io_sd[poort].substring(0,1).toInt();
}

void io_poorten_tijdelijk_opslaan() {
  String poort_regel = "";
  poort_regel += String(instellingen_io_poort_functie);
  poort_regel += String(instellingen_io_poort_opslaan);
  if (instellingen_io_poort_inverse) {
    if (instellingen_io_poort_default) {
      poort_regel += "3";
    } else {
      poort_regel += "2";
    }
  } else {
    if (instellingen_io_poort_default) {
      poort_regel += "1";
    } else {
      poort_regel += "0";
    }
  }
  poort_regel += String(instellingen_io_poort_alert);
  poort_regel += String(instellingen_io_poort_naam);

  poort_regel += io_poorten_io_events_instellingen_toevoegen();
  poort_regel += io_poorten_io_ruimte_instellingen_toevoegen();

  io_sd[instellingen_io_poort_nummer] = poort_regel;
}

String io_poorten_io_events_instellingen_toevoegen() {
  bool maken = false;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      if ((io_events[instellingen_io_poort_nummer][i][j][0] < 255) && (io_events[instellingen_io_poort_nummer][i][j][0] >= 0)) {
        maken = true;
      }
    }
  }
  String event_string = "";
  if (maken) {
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        event_string += ";";
        for (int k = 0; k < 10; k++){
          if ((io_events[instellingen_io_poort_nummer][i][j][k] < 255) && (io_events[instellingen_io_poort_nummer][i][j][k] >= 0)) {
            if (k > 0) {
              event_string += ",";
            }
            event_string += String(io_events[instellingen_io_poort_nummer][i][j][k]);
          }
        }
      }
    }
  }
  return event_string;
}

String io_poorten_io_ruimte_instellingen_toevoegen() {
  if (io_object_ruimte[instellingen_io_poort_nummer] != 255) {
    return "|" + io_ruimtes_namen[io_object_ruimte[instellingen_io_poort_nummer]];
  }
  return "";
}

void bouw_instellingen_io_poort() {
  header_plaatsen();
  achtergrond(kleur_zwart, false);

  aantal_knoppen = instellingen_io_poort_knoppen_cnt;
  knoppen_positie = new int*[aantal_knoppen];
  knoppen_teken_positie = new int*[aantal_knoppen];
  knoppen_tekst = new char*[aantal_knoppen];
  knoppen_basiskleur = new uint16_t*[aantal_knoppen];
  knoppen_tekst_kleur = new uint16_t*[aantal_knoppen];
  knoppen_status = instellingen_io_poort_knoppen_status;


  for (int i = 0; i < aantal_knoppen; i++) {
    knoppen_teken_positie[i] = instellingen_io_poort_knoppen[i];
    knoppen_positie[i] = instellingen_io_poort_knoppen[i];
    knoppen_basiskleur[i] = instelligen_io_poort_knoppen_kleur;
    knoppen_tekst[i] = instellingen_io_poort_knoppen_tekst[i];
    knoppen_tekst_kleur[i] = instelligen_io_poort_knoppen_tekstkleur;
  }
  
  bouw_instellingen_io_poort_knoppen_plaatsen();

}

void bouw_instellingen_io_poort_knoppen_plaatsen() {
  for (int i = 0; i < 4; i++) {
    if (instellingen_io_poort_functie == i+1) {
      knoppen_status[i] = 1;
    } else {
      knoppen_status[i] = 0;
    }
  }
  knoppen_status[4] = instellingen_io_poort_default;
  knoppen_status[5] = instellingen_io_poort_inverse;
  knoppen_status[6] = instellingen_io_poort_opslaan;
  if (instellingen_io_poort_alert == 0) {
    knoppen_status[7] = 1;
    knoppen_status[8] = 0;
  } else if (instellingen_io_poort_alert == 1) {
    knoppen_status[7] = 0;
    knoppen_status[8] = 1;
  } else if (instellingen_io_poort_alert == 2) {
    knoppen_status[7] = 1;
    knoppen_status[8] = 1;
  } else if (instellingen_io_poort_alert == 3) {
    knoppen_status[7] = 0;
    knoppen_status[8] = 0;
  }
  if (instellingen_io_poort_nummer == 0) {
    knoppen_status[10] = 5;
  } else {
    knoppen_status[10] = 4;
  }
  if (instellingen_io_poort_nummer+1 == io_sd_cnt) {
    knoppen_status[11] = 5;
  } else {
    knoppen_status[11] = 4;
  }

  fillRect(5, 35, 230, 40, kleur_wit);
  center_tekst(120, 45, instellingen_io_poort_naam, 2, kleur_donker);

  tft.setTextSize(1);

  tft.setTextColor(kleur_wit);
  tft.setCursor(10, 80);
  tft.print("io functie:");
  tft.setCursor(10, 140);
  tft.print("default status:");
  tft.setCursor(10, 200);
  tft.print("alert moment:");

  alle_knoppen_plaatsen();

}

void run_instellingen_io_poort() {
  if (tekstinvoer_actief) {
    run_tekstinvoer();
  } else if (tekst_invoer != "") {
    tekst_invoer.toCharArray(instellingen_io_poort_naam, 10);
    io_namen[instellingen_io_poort_nummer] = instellingen_io_poort_naam;
    
  } else if (ts.tirqTouched()) {
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

      // Aanpassen functie van een io poort
      if ((knop >= 0) & (knop < 4)) {
        if (instellingen_io_poort_functie == 0) {
          // Als die nu op 0 (ongebruikt) staat hem zetten op de aangeklikte functie
          Serial.println("staat nu uit");
          instellingen_io_poort_functie = knop+1;
          knoppen_status[knop] = 1;
        } else if (instellingen_io_poort_functie == knop+1) {
          // Als die nu op de aangeklikte knop staat hem op 0 (ongebruikt) zetten
          instellingen_io_poort_functie = 0;
          Serial.println("staat al op dit");
          knoppen_status[knop] = 0;
        } else {
          // Anders de status van de knop waar die nu op staat aanpassen en ook de io poort op de aangeklikte functie zetten.
          Serial.println(instellingen_io_poort_functie);
          Serial.println(instellingen_io_poort_functie - 1);
          knoppen_status[instellingen_io_poort_functie - 1] = 0;
          knop_plaatsen(instellingen_io_poort_functie - 1);
          instellingen_io_poort_functie = knop + 1;
          knoppen_status[knop] = 1;
        }
      }


      // regel 2 (de standaard waarden van de uitgang van een io poort)
      if (knop == 4) {
        // default status tussen aan en uit schakelen
        instellingen_io_poort_default = !instellingen_io_poort_default;
        knoppen_status[knop] = instellingen_io_poort_default;
      } else if (knop == 5) {
        // inverse aan of uit
        instellingen_io_poort_inverse = !instellingen_io_poort_inverse;
        knoppen_status[knop] = instellingen_io_poort_inverse;
      } else if (knop == 6) {
        // automatisch opslaan aan of uit (functie werkt nog niet)
        instellingen_io_poort_opslaan = !instellingen_io_poort_opslaan;
        knoppen_status[knop] = instellingen_io_poort_opslaan;
      }

      // regel 3 alert triggers
      if (knop == 7) {
        if (instellingen_io_poort_alert == 0) {
          instellingen_io_poort_alert = 3;
          knoppen_status[knop] = 0;
        } else if (instellingen_io_poort_alert == 1) {
          instellingen_io_poort_alert = 2;
          knoppen_status[knop] = 1;
        } else if (instellingen_io_poort_alert == 2) {
          instellingen_io_poort_alert = 1;
          knoppen_status[knop] = 0;
        } else if (instellingen_io_poort_alert == 3) {
          instellingen_io_poort_alert = 0;
          knoppen_status[knop] = 1;
        }
      } else if (knop == 8) {
        if (instellingen_io_poort_alert == 0) {
          instellingen_io_poort_alert = 2;
          knoppen_status[knop] = 1;
        } else if (instellingen_io_poort_alert == 1) {
          instellingen_io_poort_alert = 3;
          knoppen_status[knop] = 0;
        } else if (instellingen_io_poort_alert == 2) {
          instellingen_io_poort_alert = 0;
          knoppen_status[knop] = 0;
        } else if (instellingen_io_poort_alert == 3) {
          instellingen_io_poort_alert = 1;
          knoppen_status[knop] = 1;
        }
      }

      if ((knop == 10) & (knoppen_status[knop] != 5)) {
        io_poorten_tijdelijk_opslaan();
        naar_instellingen_io_poort(instellingen_io_poort_nummer - 1);
        bouw_instellingen_io_poort_knoppen_plaatsen();
      } else if ((knop == 11) & (knoppen_status[knop] != 5)) {
        io_poorten_tijdelijk_opslaan();
        naar_instellingen_io_poort(instellingen_io_poort_nummer + 1);
        bouw_instellingen_io_poort_knoppen_plaatsen();
      }

      if (knop == 12) {
        io_poorten_tijdelijk_opslaan();
        naar_io_instellingen();
      }

      if ((knop >= 0) & (knop <9)) {
        knop_plaatsen(knop);
      }

      if (y < 40) {
        klik_header(x, y);
      } else if (y < 80) {
        bouw_tekstinvoer("item naam", 9, instellingen_io_poort_naam);
      }
  
    }
  }
  ts.begin();
}
