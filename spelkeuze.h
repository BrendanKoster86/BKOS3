#include "spel_mijnveger.h"
#include "spel_boterkaaseneieren.h"

void bouw_spel();
void run_spel();
void bouw_spelkeuze();
void run_spelkeuze();

#define spelkeuze_knoppen_cnt 5

// Knop test_knop = Knop(Vlak(10, 10, 105, 140), Vlak(10, 10, 105, 140), tft.color565(0,255,0), tft.color565(0,0,0), "paneel");

// Knop spelkeuze_knoppen_class[spelkeuze_knoppen_cnt] = {
//   Knop({{10, 10, 105, 140},{10, 10, 105, 140}}, {tft.color565(0,255,0)}, {tft.color565(0,0,0)}, {"paneel"}),
//   Knop({{125, 10, 105, 140},{125, 10, 105, 140}}, {tft.color565(0,255,0)}, {tft.color565(0,0,0)}, {"sensoren"}),
//   Knop({{10, 160, 65, 65},{10, 160, 65, 65}}, {tft.color565(0,255,0)}, {tft.color565(0,0,0)}, {"INFO"}),
//   Knop({{87, 160, 65, 65},{87, 160, 65, 65}}, {tft.color565(0,255,0)}, {tft.color565(0,0,0)}, {"Dobbel"}),
//   Knop({{165, 160, 65, 65},{165, 160, 65, 65}}, {tft.color565(0,255,0)}, {tft.color565(0,0,0)}, {"app"}),
// };

int spelkeuze_knoppen[spelkeuze_knoppen_cnt][4] = {{10, 35, 105, 125}, {125, 35, 105, 125},
                                                   {10, 170, 65, 65}, {87, 170, 65, 65}, {165, 170, 65, 65}};//, 
//                                                   {10, 245, 65, 65}, {87, 245, 65, 65}, {165, 245, 65, 65}};


uint16_t spelkeuze_knoppen_kleur[spelkeuze_knoppen_cnt][3] = {{tft.color565(0, 255, 0)}, {tft.color565(0, 255, 0)}, {tft.color565(0, 255, 0)}, {tft.color565(0, 255, 0)}, {tft.color565(0, 255, 0)}};//, {tft.color565(0, 255, 0)}, {tft.color565(0, 255, 0)}, {tft.color565(0, 255, 0)}};

uint16_t spelkeuze_knoppen_tekst_kleur[spelkeuze_knoppen_cnt][3] = {{tft.color565(0, 0, 0)}, {tft.color565(0, 0, 0)}, {tft.color565(0, 0, 0)}, {tft.color565(0, 0, 0)}, {tft.color565(0, 0, 0)}};//, {tft.color565(0, 0, 0)}, {tft.color565(0, 0, 0)}, {tft.color565(0, 0, 0)}};

byte spelkeuze_knoppen_status[spelkeuze_knoppen_cnt] = {0, 0, 0, 0, 0};//, 0, 0, 0};

byte actief_spel = 0;

char spelkeuze_knoppen_tekst[spelkeuze_knoppen_cnt][10] {"Mijnveger", "B K & E", "", ""};//, "","","",""};

void (*run_spel_scherm[])() = {run_spelkeuze,
                          run_spel_mijnveger, run_spel_boterkaaseneieren,
                    run_spelkeuze, run_spelkeuze, run_spelkeuze,
                    run_spelkeuze, run_spelkeuze, run_spelkeuze,

                    run_io_instellingen, run_instellingen_io_poort
};
void (*bouw_spel_scherm[])() = {bouw_spelkeuze,
                           bouw_spel_mijnveger, bouw_spel_boterkaaseneieren,
                  bouw_spelkeuze, bouw_spelkeuze, bouw_spelkeuze,
                  bouw_spelkeuze, bouw_spelkeuze, bouw_spelkeuze,

                  bouw_io_instellingen, bouw_instellingen_io_poort
};


int spelkeuze_knop[7] = {0, 280, 240, 40, 0, 100, 0};

#if scherm_ili == 9488 // 360 x 480
  int spel_speelveld[4] = {10, 50, 340, 340};
#else   // ili 9341  240 x 360
  int spel_speelveld[4] = {10, 50, 220, 220};
#endif


// void test_knoppen[][12] = {{"paneel", 10, 10, 105, 140, "scherm", 1, 0, tft.color565(0,255, 0), tft.color565(255,255,255)}, {"sensor", 125, 10, 105, 140, "scherm", 2, 0, tft.color565(0,255, 0), tft.color565(255,255,255)}};
