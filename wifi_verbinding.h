/*  
 *  Toevoegingen om te kunnen werken met de wifi van de pico W
 */

#if hoofd_module__model == 1
  #include <WiFi.h>
  #include <HTTPClient.h>
  //#include <EEPROM.h>
  WiFiMulti multi;
  String wifi_ssid1;
  const char* wifi_ssid2;
  String wifi_pass1;
  const char* wifi_pass2;
#endif

/* 
 *  Einde toevoegingen t.b.v. de pico W
 */



int wifi_cnt;
String* wifi_ssid;
String* wifi_pass;

int wifi_cnt_sd;
String* wifi_ssid_sd;
String* wifi_pass_sd;

long laatste_wifi_check = 0;

int wifi_cnt_gevonden = 0;
int wifi_cnt_proberen = 0;

byte wifi_connectie_modus = 0;

String wifi_ssid_proberen[200];
String wifi_pass_proberen[200];

String* wifi_ssid_gevonden;
int* wifi_ecn_gevonden;

bool wifi__verbonden = false;
bool wifi__aangesloten = false;
String wifi__ip;
String wifi__ssid;
String wifi__mac;

String sendData(String command, const int timeout, boolean debug);
String sendData(String command, const int timeout);
String sendData(String command);

void netwerken_splits(String invoer);
void netwerk_volgorde();
void netwerken_zoeken();
void wifi_beschikbare_netwerken_vernieuwen();
boolean string_in_array(String element, String array[], int lengte);

void wifi_verbinden();
void wifi_verbinden(bool automatisch);
void wifi_verbinding_verbreken();
void wifi_check();


void wifi_start();

// Tijd functie als onderdeel van de wifi omdat de tijd mee komt bij het versturen van een bericht (gewoon lekker gebruik maken van dat er een tijd me komt :))
String tijd();
String tijd(String wat);
long millis_wekker(int H, int M);
long millis_timer(int H, int M, int S);
String tijd_tot_millis(long invoer);

String dagnm;
int dag;
String maand;
int jaar;
int uur;
int minuut;
int seconde;
String tijdzone;
long tijd_millis;
