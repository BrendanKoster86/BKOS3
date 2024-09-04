void knop_plaatsen(int knop_nummer) {
  knop_plaatsen(knop_nummer, false);
}

void knop_plaatsen(int knop_nummer, bool tekst2) {
  fillRoundRect(knoppen_teken_positie[knop_nummer][0], knoppen_teken_positie[knop_nummer][1], knoppen_teken_positie[knop_nummer][2], knoppen_teken_positie[knop_nummer][3], 5, knoppen_basiskleur[knop_nummer][knoppen_status[knop_nummer]]);
  // tft.fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color)
  if ((tekst2)){// & (!knoppen_tekst2[knop_nummer] == "          ")) {
    center_tekst(knoppen_teken_positie[knop_nummer][0]+knoppen_teken_positie[knop_nummer][2]/2, knoppen_teken_positie[knop_nummer][1]+5, knoppen_tekst[knop_nummer], 1.5, knoppen_tekst_kleur[knop_nummer][knoppen_status[knop_nummer]]); // tijdelijk
    center_tekst(knoppen_teken_positie[knop_nummer][0]+knoppen_teken_positie[knop_nummer][2]/2, knoppen_teken_positie[knop_nummer][1]+20, knoppen_tekst2[knop_nummer], 1.5, knoppen_tekst_kleur[knop_nummer][knoppen_status[knop_nummer]]); // tijdelijk
  } else {
    center_tekst(knoppen_teken_positie[knop_nummer][0]+knoppen_teken_positie[knop_nummer][2]/2, knoppen_teken_positie[knop_nummer][1]+10, knoppen_tekst[knop_nummer], 1.5, knoppen_tekst_kleur[knop_nummer][knoppen_status[knop_nummer]]); // tijdelijk
  }
  // tft.setCursor(knoppen_teken_positie[knop_nummer][0] + knoppen_tekst_positie[knop_nummer][0], knoppen_teken_positie[knop_nummer][1] + knoppen_tekst_positie[knop_nummer][1]);
  // tft.println(knoppen_tekst[knop_nummer]);
}

void alle_knoppen_plaatsen() {
  alle_knoppen_plaatsen(false);
}
void alle_knoppen_plaatsen(bool tekst2) {
  for (byte i = 0; i < aantal_knoppen; i++) {
    knop_plaatsen(i, tekst2);
  }
  Serial.print("knoppen staan");
}

int klik(int x, int y) {
  for (byte i = 0; i < aantal_knoppen; i++) {
    if ((x >= knoppen_positie[i][0]) && (x <= knoppen_positie[i][0]+knoppen_positie[i][2]) && (y >= knoppen_positie[i][1]) && (y <= knoppen_positie[i][1]+knoppen_positie[i][3])) {
      Serial.println(i);
      return i;
    }
  }
  Serial.println(-1);
  return -1;
}
