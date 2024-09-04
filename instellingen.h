#include "io_instellingen.h"
#include "instellingen_io_poort.h"
#include "instellingen_io_cnt.h"

// void start_io_instellingen();
// void bouw_io_instellingen(int groep);
void bouw_instellingen();
void run_instellingen();
void loop_instellingen();

void instellingen_leven();
void instellingen_sd_reset();
void instellingen_restart();



int instellingen_mean_knoppen_cnt = 6;
int instellingen_overlay_dicht_tot = 70;
int instellingen_overlay_hoogte = 180;

void (*instellingen_mean_knoppen_functies[])() = {naar_io_instellingen, run_instellingen, run_instellingen,
                                                  instellingen_leven, instellingen_sd_reset, instellingen_restart,
                                                  run_instellingen, run_instellingen, run_instellingen,
                                                  instellingen_leven, instellingen_sd_reset, instellingen_restart
};

int instellingen_mean_knoppen_positie[12][4] = {{10, 80, 65, 40}, {85, 80, 65, 40}, {160, 80, 65, 40},
                                                {10, 130, 65, 40}, {85, 130, 65, 40}, {160, 130, 65, 40},
                                                {10, 180, 65, 40}, {85, 180, 65, 40}, {160, 180, 65, 40},
                                                {10, 230, 65, 40}, {85, 230, 65, 40}, {160, 230, 65, 40}};

char instellingen_mean_knoppen_tekst[12][10] = {"IO","","",
                                                "leven","SD","reset",
                                                "","","",
                                                "leven","SD","reset"};

uint16_t instellingen_mean_knoppen_kleur[12][1] = {{tft.color565(255,255,255)},{tft.color565(0,0,0)},{tft.color565(0,0,0)},
                                                   {kleur_donker},{kleur_licht},{tft.color565(255,0,0)},
                                                   {tft.color565(0,0,0)},{tft.color565(0,0,0)},{tft.color565(0,0,0)},
                                                   {kleur_donker},{kleur_licht},{tft.color565(255,0,0)}};

uint16_t instellingen_mean_knoppen_tekstkleur[12][1] = {{tft.color565(0,0,0)},{tft.color565(0,0,0)},{tft.color565(0,0,0)},
                                                        {tft.color565(255,255,255)},{tft.color565(0,0,0)},{tft.color565(0,0,0)},
                                                        {tft.color565(0,0,0)},{tft.color565(0,0,0)},{tft.color565(0,0,0)},
                                                        {tft.color565(255,255,255)},{tft.color565(0,0,0)},{tft.color565(0,0,0)}};

byte instellingen_main_status[12] = {0, 0, 0,
                                     0, 0, 0,
                                     0, 0, 0,
                                     0, 0, 0};
