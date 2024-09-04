////#include "logo.h"
//
//void plaats_logo(int32_t x, int32_t y, int schaal, bool naam) {
//  plaats_logo(x, y, schaal, naam, 2);
//}
//
//void plaats_logo(int32_t x, int32_t y, int schaal, bool naam, byte positie) {
//  /*
//   * Deze functie zou het logo moeten plaatsen op een manier die zowel geschikt is voor de ILI9488 aks de ILI9341
//   * x en y zijn de postiie van het logo
//   * Wanneer positie 0 is betreft dit de linker bovenhoek
//   * Wanneer positie 1 is betreft dit het midden bovenin
//   * Ongedefinieerd is het midden
//   */
//
//  int rx = 16;
//  int ry = 8;
//  
//  int32_t cx = x;
//  int32_t cy = y;
//
//  if (positie == 0) {
//    cx = x + (rx*schaal);
//    cy = y + (ry*schaal);
//  } else if (positie == 1) {
//    cy = y + (ry*schaal);
//  }
//  
//  fillEllipse(cx, cy, rx*schaal, ry*schaal, kleur_licht);
//  drawEllipse(cx, cy, rx*(schaal - 1), ry*(schaal - 1), kleur_donker);
//  drawEllipse(cx, cy, (rx*(schaal - 1)) - 1, (ry*(schaal - 1)) - 1, kleur_donker);
//  drawEllipse(cx, cy, (rx*(schaal - 1)) - 2, (ry*(schaal - 1)) - 2, kleur_donker);
//  drawEllipse(cx, cy, (rx*(schaal - 1)) - 3, (ry*(schaal - 1)) - 3, kleur_donker);
//  center_tekst(cx, cy-(schaal * 4), "BK", schaal * 4, kleur_donker);
//
//  if (naam == true) {
//    center_tekst(cx, cy + (schaal * 10), "BKOS", schaal * 2, kleur_wit);
//    center_tekst(cx, cy + (schaal * 13), "Boordcomputer besturing", schaal * 1, kleur_wit);
//    center_tekst(cx, cy + (schaal * 15), "door", schaal * 1, kleur_wit);
//    center_tekst(cx, cy + (schaal * 17), "Brendan Koster", schaal * 1, kleur_wit);
//  }
//}
