#include "keuzescherm.h"
#include "schakelscherm.h"
#include "instellingen.h"
#include "sensorscherm.h"
#include "sensor_grafisch.h"
#include "spelkeuze.h"
#include "nummeriek.h"
#include "tekst_invoer.h"

byte actief_scherm = 0;
byte opstart_scherm = 0;

void (*run_scherm[])() = {run_keuzescherm,
                          run_schakelscherm, run_sensor_grafisch, run_sensorscherm,
                    run_keuzescherm, run_keuzescherm,
                    run_keuzescherm, run_keuzescherm, run_spel,

                    run_io_instellingen, run_instellingen_io_poort, run_instellingen_io_cnt
};
void (*bouw_scherm[])() = {bouw_keuzescherm,
                           bouw_schakelscherm, bouw_sensor_grafisch, bouw_sensorscherm,
                  bouw_keuzescherm, bouw_keuzescherm,
                  bouw_keuzescherm, bouw_keuzescherm, bouw_spel,

                  bouw_io_instellingen, bouw_instellingen_io_poort, bouw_instellingen_io_cnt
};
