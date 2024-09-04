/*
 * Hier worden de parameters benoemd voor het aansturen van het software gedeelte van de IO.
 * 
 */

int io_cnt;          // Aantal IO aansluitingen
int io_knoppen_cnt;  // Aantal IO aansluitingen dat is gebruikt als knop
int io_sensoren_cnt; // Aantal IO aansluitingen dat is gebruikt als sensor

byte* io_objecten;   // Wat zit er aangesloten op de poorten 0: niks, 1: knop, 2: sensor
byte* io_output;     // Wat is de gewenste output 0: uit, 1: aan, 2: inv uit (hoog), 3: inv aan (laag), 4: geblokeerd (laag), 5: inv geblokeerd (hoog)
bool* io_input;      // Welke waarde wordt gemeten op een poort 0: laag, 1: hoog
bool* io_gewijzigd;  // Is de status van de meting afwijkend t.o.v. het laatste alert status 0: nee, 1: ja
byte* io_alert;      // Wanneer moet er een alert uit? 0: bij passief worden, 1: bij actief worden, 2: bij alle verandering, 3: nooit
char** io_namen;     // Namen van de aangesloten objecten

byte**** io_events;  // het automatisch mee in en uitschakelen van aparaten met sensoren {{{{}, {}}, {{}, {}}}}
                     // [?](sensor nummer)[0/1]wordt passief/actief  [0/1]maakt passief/actief [10] lijst van max 10 mee te schakelen objecten standaard = -1

int* io_knoppen;  // Mapping voor de knoppen
int* io_sensoren; // Mapping voor de sensoren

int io_alert_cnt;              // Aantal triggers sinds de laatste reset op de boordcomputer zelf
int io_alert_app;              // Aantal triggers sinsd de laatste alert app
int io_diepcheck_cnt = 0;      // Aantal uitgevoerde deepchecks
int io_diepcheck_pins_cnt = 0; // Aantal pinnen waarover de deepchecks worden uitgevoerd
int* io_diepcheck_pins;        // Pinnen waarover de deepchecks worden uitgevoerd
bool io_diepcheck = true;      // Alle deepchecks succesvol?
bool* io_open_alert;           // Register van de alerts

String io_handleiding[6];
