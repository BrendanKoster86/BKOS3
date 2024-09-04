long uit_check = 0;

// #include "scherm.h"
// void bkos_logo(int32_t x, int32_t y, int32_t schaal, bool naam) {
//   bkos_logo(x, y, schaal, naam, 2);
// }

void bkos_logo(int32_t x, int32_t y, uint32_t kleur) {
  int k = 0;
  int r = 0;
  bool teken = false;
  for (int i = 0; i < sizeof(bkos_logo_200_75)/sizeof(byte); i ++) {
    if (teken) {
      if (bkos_logo_200_75[i] > 0) {
        tft.drawLine(x+k, y+r, x+k+bkos_logo_200_75[i], y+r, kleur);
      }
      teken = false;
    } else {
      teken = true;
    }
    k += bkos_logo_200_75[i];
    if (k >= 200) {
      r += 1;
      k = 0;
    }
  }

}

void start_scherm() {
  // scherm opstarten
  Serial.println("Scherm starten");
  tft.begin();
  tft.setRotation(rotation);
  ts.begin();
  ts.setRotation(rotation);
  // tft.setTextSize(2);
  // tft.setTextColor(tft.color565(0, 128, 0));
  tft.fillScreen(tft.color565(0, 0, 0));
  bkos_logo(20, 10, kleur_donker);
  // bkos_logo(120, 10, 2, true, 1);
  tft.setCursor(25, 95);
  tft.setTextSize(8);
  // tft.setTextColor(kleur_donker);
  tft.setTextColor(kleur_licht);
  tft.println("BKos");
  tft.setTextSize(2);
  tft.println("  Boordcomputer OS");
  tft.println("        door");
  tft.println("   Brendan Koster");
  tft.print("  versie ");
  tft.println(BKOS_VERSIE);
  tft.setTextSize(1);
  tft.setTextColor(tft.color565(0, 0, 0));
  tft.setTextColor(tft.color565(255, 255, 255));
  tft.println("");
  spi_starten();
}


void beeld_melding(String hoofdmelding) {
  beeld_melding(hoofdmelding, "", "");
}

void beeld_melding(String hoofdmelding, String submelding) {
  beeld_melding(hoofdmelding, submelding, "");
}

void beeld_melding(String hoofdmelding, String submelding, String titel){
  beeld_melding(hoofdmelding, submelding, titel, {}, false);
}

void beeld_melding(String hoofdmelding, String submelding, String titel, String sec_icon[10]){
  beeld_melding(hoofdmelding, submelding, titel, sec_icon, false);
}

void beeld_melding(String hoofdmelding, String submelding, String titel, String sec_icon[10], bool sec_icon_bool) {
  if (waas != true) {
    gewaasd_scherm();
    waas = true;
  }
  fillRoundRect(15, 100, 210, 30, 10, kleur_donker);
  fillRect(15, 120, 10, 10, kleur_licht);
  fillRect(215, 120, 10, 10, kleur_licht);
  fillRoundRect(15, 120, 210, 80, 10, kleur_licht);
  drawRoundRect(15, 100, 210, 100, 10, kleur_zwart);
  drawIconWifi10x10(205, 105, kleur_licht, false);
  drawIcon10x10(190, 105, icon_sd, kleur_licht, SD_connect);
  if (sec_icon_bool) {
    drawIcon10x10(175, 105, sec_icon, kleur_licht);
  }
  center_tekst(120, 106, titel, 1, kleur_licht);
  if (submelding == "") {
    center_tekst(120, 150, hoofdmelding, 2, kleur_donker);
  } else {
    center_tekst(120, 140, hoofdmelding, 2, kleur_donker);
    center_tekst(120, 170, submelding, 1, kleur_zwart);
  }
  tft.setTextSize(1.5);
  tft.setTextColor(kleur_zwart);
  scherm_bouwen = true;
}

void fillRoundRect(int x, int y, int w, int h, int d, uint16_t kleur) {
  tft.fillRoundRect(scherm_x(x), scherm_y(y), scherm_x(w), scherm_y(h), scherm_y(d), kleur);
}
void fillRect(int x, int y, int w, int h, uint16_t kleur) {
  tft.fillRect(scherm_x(x), scherm_y(y), scherm_x(w), scherm_y(h), kleur);
}
void drawRoundRect(int x, int y, int w, int h, int d, uint16_t kleur) {
  tft.drawRoundRect(scherm_x(x), scherm_y(y), scherm_x(w), scherm_y(h), scherm_y(d), kleur);
}
void setCursor(int x, int y) {
  tft.setCursor(scherm_x(x), scherm_y(y));
}
void fillCircle(int x, int y, int r, uint16_t kleur) {
  tft.fillCircle(scherm_x(x), scherm_y(y), scherm_y(r), kleur);
}
void drawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t kleur) {
  tft.drawLine(scherm_x(x1), scherm_y(y1), scherm_x(x2), scherm_y(y2), kleur);
}

// boolean string_in_array(String element, String array[], int lengte)
// byte beeld_vraag(String hoofdmelding, String submelding, String array[], byte opties_cnt)
byte beeld_vraag(String hoofdmelding, String submelding, String optie1) {
  return beeld_vraag(hoofdmelding, submelding, 1, optie1, "", "", "", "");
}
byte beeld_vraag(String hoofdmelding, String submelding, String optie1, String optie2) {
  return beeld_vraag(hoofdmelding, submelding, 2, optie1, optie2, "", "", "");
}
byte beeld_vraag(String hoofdmelding, String submelding, String optie1, String optie2, String optie3) {
  return beeld_vraag(hoofdmelding, submelding, 3, optie1, optie2, optie3, "", "");
}
byte beeld_vraag(String hoofdmelding, String submelding, String optie1, String optie2, String optie3, String optie4) {
  return beeld_vraag(hoofdmelding, submelding, 4, optie1, optie2, optie3, optie4, "");
}
byte beeld_vraag(String hoofdmelding, String submelding, String optie1, String optie2, String optie3, String optie4, String optie5) {
  return beeld_vraag(hoofdmelding, submelding, 5, optie1, optie2, optie3, optie4, optie5);
}
byte beeld_vraag(String hoofdmelding, String submelding, byte opties_cnt, String optie1, String optie2, String optie3, String optie4, String optie5){
  String array[5] = {optie1, optie2, optie3, optie4, optie5};
  return beeld_vraag(hoofdmelding, submelding, array, opties_cnt);
}

byte beeld_vraag(String hoofdmelding, String submelding, String array[], byte opties_cnt) {
  

  if (waas != true) {
    gewaasd_scherm();
    waas = true;
  }
  fillRoundRect(15, 80, 210, 30, 10, kleur_donker);
  fillRect(15, 100, 10, 10, kleur_licht);
  fillRect(215, 100, 10, 10, kleur_licht);
  fillRoundRect(15, 100, 210, 120, 10, kleur_licht);
  drawRoundRect(15, 80, 210, 140, 10, kleur_zwart);
  drawIconWifi10x10(205, 85, kleur_licht, false);
  if (submelding == "") {
    center_tekst(120, 125, hoofdmelding, 2, tft.color565(0, 100, 0));
  } else {
    center_tekst(120, 115, hoofdmelding, 2, tft.color565(0, 100, 0));
    center_tekst(120, 145, submelding, 1, tft.color565(0, 0, 0));
  }

  int B = 210 / opties_cnt;

  for (byte i = 0; i < opties_cnt; i++){
    fillRoundRect(i*B + 20, 170, B-10, 35, 5, kleur_donker);
    center_tekst(i*B + B/2 + 20, 180, array[i], 1.5, kleur_wit);
  }

  bool verder = false;

  while (!verder) {
    io();
    if (ts.tirqTouched()) {
      if (ts.touched()) {
        int x = touch_x();
        int y = touch_y();

        while (ts.touched()) {
          ts.begin();
        }
        
        for (byte i = 0; i < opties_cnt; i++) {
          if ((x > i*B + 15) & (x < (i+1)*B + 15)  &  (y > 165) & (y < 225)) {
            verder = true;
            while (ts.touched()){
              ts.begin();
            }
            return i;
          }
        }

        while (ts.touched()) {
          ts.begin();
        }

      }
    }

    while (ts.touched()) {
      ts.begin();
    }

    ts.begin();
  }

  return -1;
}

void gewaasd_scherm() {
  byte factor = 2;
  for ( int i = 0; i < tf_maxY / factor; i++) {
    tft.drawLine(0, i*factor, tf_maxX, i*factor, tft.color565(0,0,0));
  }
}

void center_tekst(int16_t x, int16_t y, String tekst, int tekst_grootte=1, uint16_t tekst_kleur=tft.color565(255,255,255)) {

  x = scherm_x(x);
  y = scherm_y(y);
  
  tft.setTextSize(tekst_grootte);
  tft.setTextColor(tekst_kleur);
  tft.setCursor((x - tekst.length()*tekst_grootte*3), y);
  tft.print(tekst);

}




int touch_x() {
  TS_Point p = ts.getPoint();
  float x = (p.x - xcorrectie) / xfactor;
  Serial.print("x: ");
  Serial.println(x);
  // actie = 1;
  return x;
}
int touch_y() {
  TS_Point p = ts.getPoint();
  float y = (p.y - ycorrectie) / yfactor;
  Serial.print("y: ");
  Serial.println(y);
  scherm_touched = millis();
  // actie = 1;
  return y;
}

int16_t scherm_x(int16_t invoer) {
  int16_t max_in;
  max_in = 240;
  return scherm_x(invoer, max_in);
}
int16_t scherm_x(int16_t invoer, int16_t max_in) {
  int16_t max_uit;
  if (scherm_ili == 9341) {
    max_uit = 240;
  } else if (scherm_ili == 9488) {
    max_uit = 320;
  } else {
    Serial.print("Er gaat iets mis met scherm_ili. Dit is nu: ");
    Serial.println(scherm_ili);
    max_uit = 320;
  }
  return scherm_x(invoer, max_in, max_uit);
}
int16_t scherm_x(int16_t invoer, int16_t max_in, int16_t max_uit) {
//  Serial.print("X : " );
//  Serial.print(invoer);
//  Serial.print(" > ");
  int16_t uitvoer = invoer * max_uit / max_in;
//  Serial.println(uitvoer);
  return uitvoer;
}

int16_t scherm_y(int16_t invoer) {
  int16_t max_in;
  max_in = 320;
  return scherm_y(invoer, max_in);
}
int16_t scherm_y(int16_t invoer, int16_t max_in) {
  int16_t max_uit;
  if (scherm_ili == 9341) {
    max_uit = 320;
  } else if (scherm_ili == 9488) {
    max_uit = 480;
  } 
  return scherm_y(invoer, max_in, max_uit);
}
int16_t scherm_y(int16_t invoer, int16_t max_in, int16_t max_uit){
//  Serial.print("Y : " );
//  Serial.print(invoer);
//  Serial.print(" > ");
  int16_t uitvoer = invoer * max_uit / max_in;
//  Serial.println(uitvoer);
  return uitvoer;
}

void run_scherm_pauze() {
  if (ts.tirqTouched()) {
    if (ts.touched()) {
      if (scherm_helderheid == 100) {
        digitalWrite(led, HIGH);
      } else if (scherm_helderheid < 100) {
        Serial.println(round(255*(scherm_helderheid/100)));
        analogWrite(led, round(255*(scherm_helderheid/100)));
      }
      scherm_actief = true;

      while (ts.touched()) {
        ts.begin();
      }

      scherm_touched = millis();
      ts.begin();
    }
  }
  else if (uit_check + 60000 > millis()) {
    digitalWrite(led, LOW);
    uit_check = millis();
  }
}
