#define rotation 0

//#include "logo.h"
#include "ellipse.h"

void bkos_logo(int32_t x, int32_t y, int schaal, bool naam);
void bkos_logo(int x, int y, int schaal, bool naam, byte positie);

/* Gezocht naar een efficiënt format om 2 kleurige afbeeldingen op te kunnen slaan in de code en ik ben op het volgende gekomen.
 * Elk cijfer staat voor het aantal pixels in een bepaalde kleur. De 2 kleuren worden telkens afgewisseld.
 * Elke rij begint met de achtergrond kleur en eindigd met de te kleuren kleur.
 * Het aantal pixels per rij moet van de voren gedefiniëerd zijn en wanneer dat aantal is berijkt wordt er overgesprongen naar de volgende regel.
 *
 * Het is in byte format, dus het hoogst mogelijke getal is 255 wat daarom tevens het maximaal aantal breedte pixels is van een ecoon op deze manier van opslaan.
 * Idee ter verbetering is als eerste item het aantal pixels per rij toevoegen.
 */

byte bkos_logo_200_75[] = { 80, 40, 80, 0, 70, 60, 70, 0, 63, 74, 63, 0, 57, 86, 57, 0, 52, 20, 31, 45, 52, 0, 47, 21, 35, 50, 47, 0, 43, 23, 37, 54, 43, 0, 40, 24, 39, 31, 11, 15, 40, 0, 37, 25, 41, 30, 11, 19, 37, 0, 34, 27, 42, 29, 11, 20, 37, 0, 31, 29, 43, 28, 11, 24, 34, 0, 29, 30, 44, 27, 11, 28, 31, 0, 27, 32, 14, 22, 8, 26, 11, 31, 29, 0, 24, 34, 12, 25, 8, 25, 11, 34, 27, 0, 22, 36, 10, 27, 8, 24, 11, 38, 24, 0, 20, 37, 10, 28, 8, 23, 11, 41, 22, 0, 18, 39, 9, 29, 8, 22, 11, 44, 20, 0, 17, 39, 10, 29, 8, 21, 11, 47, 18, 0, 15, 41, 9, 30, 8, 20, 11, 50, 16, 0, 14, 42, 8, 31, 8, 19, 11, 52, 15, 0, 12, 43, 9, 31, 8, 18, 11, 55, 13, 0, 11, 44, 9, 31, 8, 17, 11, 57, 12, 0, 10, 45, 9, 31, 8, 16, 11, 59, 11, 0, 9, 46, 9, 31, 8, 15, 11, 61, 10, 0, 8, 48, 8, 31, 8, 14, 11, 63, 9, 0, 7, 49, 8, 31, 8, 13, 11, 65, 8, 0, 6, 50, 9, 30, 8, 12, 11, 67, 7, 0, 5, 51, 9, 30, 8, 11, 11, 69, 6, 0, 4, 53, 9, 29, 8, 10, 11, 71, 5, 0, 3, 54, 10, 28, 8, 9, 11, 73, 4, 0, 3, 55, 10, 27, 8, 8, 11, 74, 4, 0, 2, 57, 11, 25, 8, 7, 11, 76, 3, 0, 2, 58, 12, 23, 8, 6, 11, 77, 3, 0, 1, 60, 42, 5, 11, 79, 2, 0, 1, 61, 41, 4, 13, 78, 2, 0, 1, 63, 39, 3, 15, 77, 2, 0, 0, 63, 40, 2, 17, 77, 1, 0, 0, 61, 42, 1, 18, 77, 1, 0, 0, 59, 64, 76, 1, 0, 0, 58, 55, 2, 9, 75, 1, 0, 0, 57, 55, 3, 10, 74, 1, 0, 1, 55, 13, 26, 16, 5, 9, 73, 2, 0, 1, 54, 11, 29, 15, 7, 9, 72, 2, 0, 1, 53, 11, 30, 14, 8, 10, 71, 2, 0, 2, 52, 10, 31, 13, 10, 10, 69, 3, 0, 2, 51, 11, 31, 12, 12, 9, 69, 3, 0, 3, 50, 10, 32, 11, 14, 9, 67, 4, 0, 3, 49, 11, 32, 10, 15, 10, 66, 4, 0, 4, 48, 10, 33, 9, 17, 9, 65, 5, 0, 5, 47, 10, 33, 8, 19, 9, 63, 6, 0, 6, 46, 10, 33, 8, 19, 10, 61, 7, 0, 7, 45, 10, 33, 8, 20, 9, 60, 8, 0, 8, 44, 10, 33, 8, 21, 9, 58, 9, 0, 9, 43, 10, 33, 8, 21, 10, 56, 10, 0, 10, 42, 11, 32, 8, 22, 10, 54, 11, 0, 12, 40, 11, 32, 8, 22, 10, 52, 13, 0, 13, 40, 10, 32, 8, 23, 10, 50, 14, 0, 15, 38, 11, 31, 8, 23, 11, 47, 16, 0, 16, 38, 11, 30, 8, 24, 10, 46, 17, 0, 18, 36, 12, 29, 8, 24, 11, 43, 19, 0, 20, 35, 13, 27, 8, 25, 11, 40, 21, 0, 22, 33, 15, 25, 8, 26, 10, 38, 23, 0, 25, 31, 47, 26, 11, 34, 26, 0, 27, 30, 46, 27, 11, 31, 28, 0, 29, 29, 45, 28, 10, 29, 30, 0, 32, 27, 44, 28, 11, 25, 33, 0, 35, 25, 43, 29, 11, 21, 36, 0, 38, 23, 42, 30, 10, 18, 39, 0, 41, 22, 40, 30, 11, 14, 42, 0, 45, 21, 37, 31, 11, 9, 46, 0, 50, 20, 33, 46, 51, 0, 55, 89, 56, 0, 61, 77, 62, 0, 68, 63, 69, 0, 78, 43, 79, 0};



bool scherm_actief = true;
int scherm_helderheid = 100;
int scherm_timer = 20;
long scherm_touched = 0;


int xfactor = -15;
int xcorrectie = 3855;
int yfactor = -11;
int ycorrectie = 3962;

bool waas = false;



#if scherm_ili == 9341
  // Standaard scherm
  #if hoofd_module__model <= 1 || hoofd_module__model == 3
    Adafruit_ILI9341 tft = Adafruit_ILI9341(cs_tft, dc, mosi, sck, rst, miso);
  #else
    Adafruit_ILI9341 tft = Adafruit_ILI9341(cs_tft, dc, mosi, sck, rst);
  #endif
#elif scherm_ili == 9488
  // 4 inch scherm
  TFT_eSPI tft = TFT_eSPI(320, 480);
#endif
XPT2046_Touchscreen ts(cs_ts, irq);

void start_scherm();
void beeld_melding(String hoofdmelding);
void beeld_melding(String hoofdmelding , String submelding);
void beeld_melding(String hoofdmelding , String submelding, String titel);
void beeld_melding(String hoofdmelding, String submelding, String titel, String sec_icon[10]);
void beeld_melding(String hoofdmelding, String submelding, String titel, String sec_icon[10], bool sec_icon_bool);
byte beeld_vraag(String hoofdmelding, String submelding, String optie1);
byte beeld_vraag(String hoofdmelding, String submelding, String optie1, String optie2);
byte beeld_vraag(String hoofdmelding, String submelding, String optie1, String optie2, String optie3);
byte beeld_vraag(String hoofdmelding, String submelding, String optie1, String optie2, String optie3, String optie4);
byte beeld_vraag(String hoofdmelding, String submelding, String optie1, String optie2, String optie3, String optie4, String optie5);
byte beeld_vraag(String hoofdmelding, String submelding, byte opties_cnt, String optie1, String optie2, String optie3, String optie4, String optie5);
void gewaasd_scherm();
void center_tekst(int16_t x, int16_t y, String tekst, int tekst_grootte, uint16_t tekst_kleur);
void run_scherm_pauze();

int touch_x();
int touch_y();

// Omreken functie om punten naar een andere resolutie om te kunnen rekenen. Bedoeld om simpel van het 2,8 naar het 4,0 inch scherm te kunnen gaan
int16_t scherm_x(int16_t invoer);
int16_t scherm_x(int16_t invoer, int16_t max_in);
int16_t scherm_x(int16_t invoer, int16_t max_in, int16_t max_uit);
int16_t scherm_y(int16_t invoer);
int16_t scherm_y(int16_t invoer, int16_t max_in);
int16_t scherm_y(int16_t invoer, int16_t max_in, int16_t max_uit);

// Een simpele link naar de standaard tft. functies echter via de bovenstaande omreken functies om deze te kunnen toepassen door enkel tft. weg te halen :)
void fillRoundRect(int y, int x, int h, int w, int d, uint16_t kleur);
void fillRect(int y, int x, int h, int w, uint16_t kleur);
void drawRoundRect(int y, int x, int h, int w, int d, uint16_t kleur);
void setCursor(int y, int x);
void fillCircle(int y, int x, int r, uint16_t kleur);
void drawLine(int16_t y1, int16_t x1, int16_t y2, int16_t x2, uint16_t kleur);
