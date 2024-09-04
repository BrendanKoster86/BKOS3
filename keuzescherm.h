void bouw_keuzescherm();
void run_keuzescherm();
void homeknop_plaatsen();
void homeknop_plaatsen(bool invert);

#define keuzescherm_knoppen_cnt 8

// Knop test_knop = Knop(Vlak(10, 10, 105, 140), Vlak(10, 10, 105, 140), tft.color565(0,255,0), tft.color565(0,0,0), "paneel");

// Knop keuzescherm_knoppen_class[keuzescherm_knoppen_cnt] = {
//   Knop({{10, 10, 105, 140},{10, 10, 105, 140}}, {tft.color565(0,255,0)}, {tft.color565(0,0,0)}, {"paneel"}),
//   Knop({{125, 10, 105, 140},{125, 10, 105, 140}}, {tft.color565(0,255,0)}, {tft.color565(0,0,0)}, {"sensoren"}),
//   Knop({{10, 160, 65, 65},{10, 160, 65, 65}}, {tft.color565(0,255,0)}, {tft.color565(0,0,0)}, {"INFO"}),
//   Knop({{87, 160, 65, 65},{87, 160, 65, 65}}, {tft.color565(0,255,0)}, {tft.color565(0,0,0)}, {"Dobbel"}),
//   Knop({{165, 160, 65, 65},{165, 160, 65, 65}}, {tft.color565(0,255,0)}, {tft.color565(0,0,0)}, {"app"}),
// };

int home_knop[7] = {0, 280, 240, 40, 0, 100, 0};

int keuzescherm_knoppen[keuzescherm_knoppen_cnt][4] = {{10, 35, 105, 125}, {125, 35, 105, 125}, {10, 170, 65, 65}, {87, 170, 65, 65}, {165, 170, 65, 65}, {10, 245, 65, 65}, {87, 245, 65, 65}, {165, 245, 65, 65}};
uint16_t keuzescherm_knoppen_kleur[keuzescherm_knoppen_cnt][3] = {{tft.color565(0, 255, 0)}, {tft.color565(0, 255, 0)}, {tft.color565(0, 255, 0)}, {tft.color565(0, 255, 0)}, {tft.color565(0, 255, 0)}, {tft.color565(0, 255, 0)}, {tft.color565(0, 255, 0)}, {tft.color565(0, 255, 0)}};

uint16_t keuzescherm_knoppen_tekst_kleur[keuzescherm_knoppen_cnt][3] = {{tft.color565(0, 0, 0)}, {tft.color565(0, 0, 0)}, {tft.color565(0, 0, 0)}, {tft.color565(0, 0, 0)}, {tft.color565(0, 0, 0)}, {tft.color565(0, 0, 0)}, {tft.color565(0, 0, 0)}, {tft.color565(0, 0, 0)}};

byte keuzescherm_knoppen_status[keuzescherm_knoppen_cnt] = {0, 0, 0, 0, 0, 0, 0, 0};

char keuzescherm_knoppen_tekst[keuzescherm_knoppen_cnt][10] {"Bediening", "Sensoren",
                                                             "Sensoren2", "", "",
                                                             "","","Spellen"};

int keuzescherm_knop[7] = {0, 280, 240, 40, 0, 100, 0};

// void test_knoppen[][12] = {{"paneel", 10, 10, 105, 140, "scherm", 1, 0, tft.color565(0,255, 0), tft.color565(255,255,255)}, {"sensor", 125, 10, 105, 140, "scherm", 2, 0, tft.color565(0,255, 0), tft.color565(255,255,255)}};
