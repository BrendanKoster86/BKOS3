int io_cnt;
int io_knoppen_cnt;
int io_sensoren_cnt;

int io_alert_cnt;
int io_alert_app;
int io_diepcheck_cnt = 0;
int* io_diepcheck_pins;
int io_diepcheck_pins_cnt = 0;
bool io_diepcheck = true;
long io_timer = 5000;  // Aantal miliseconde tussen de checks (0 = niet checken)
long io_gecheckt;   // Moment waarop de laatste check heeft plaatsgevonden.
bool io_wijziging = false;  // Of er een wijziging heeft plaatsgevonden
bool io_actief = false;

byte* io_objecten;   // Wat zit er aangesloten op de poorten 0: niks, 1: knop, 2: sensor
byte* io_object_ruimte; // Overzicht met welke ruimte hoort bij het object
byte* io_output;  // Wat is de gewenste output 0: uit, 1: aan, 2: inv uit (hoog), 3: inv aan (laag), 4: geblokeerd (laag), 5: inv geblokeerd (hoog)
bool* io_input;   // Gemete status 0: laag, 1: hoog
bool* io_gewijzigd;   // Gemete status 0: laag, 1: hoog
byte* io_alert;   // Wanneer moet er een alert uit? 0: bij passief worden, 1: bij actief worden, 2: bij alle verandering, 3: nooit
char** io_namen; // Namen van de aangesloten objecten
bool* io_open_alert;
byte**** io_events; // het automatisch mee in en uitschakelen van aparaten met sensoren {{{{}, {}}, {{}, {}}}}
                   // [?](sensor nummer)[0/1]wordt passief/actief  [0/1]maakt passief/actief [10] lijst van max 10 mee te schakelen objecten standaard = -1


int* io_knoppen;  // Mapping voor de knoppen
int* io_sensoren; // Mapping voor de sensoren

int io_ruimtes_cnt;        // Aantal gedefinieerde ruimten
String* io_ruimtes_namen;  // Namen van de ruimten
byte*** io_ruimtes;        // Coordinaten van de ruimten {{cnt}, {x,y}, {x,y}, {x,y}, {x,y}}

String io_handleiding[6];

void start_io();
void io_reset_gewijzigd();
void io_reset_alert();
void io();
void io_schakel();
void io_check_zekeringen();
void io_alert_check();
void io_diep_checken();
String alert_bouwen();
void io_alert_appen();
void io_meeschakelen(int pin);

long laatste_diepcheck = 0;
int diepcheck_timer = 5;

long laatste_alert_app = 0;
int alert_app_timer = 5;
