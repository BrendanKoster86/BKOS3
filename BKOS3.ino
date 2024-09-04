#include "BKOS3.h"

#define BKOS_VERSIE "3.240904"

bool start_core2 = false;
byte io_core = 1;
bool boot_compleet = false;
// byte wifi_core = 1;

#if defined(ESP_PLATFORM)
  TaskHandle_t task_loop1;
  void setup() {
    setup0();

    // xTaskCreatePinnedToCore(
    //   esploop1,
    //   "loop1",
    //   1000,
    //   NULL,
    //   1,
    //   &task_loop1,
    //   !ARDUINO_RUNNING_CORE);
  }
  // void esploop1(void* pvParameters) {
  //   setup1();

  //   while (true) {
  //     loop1();
  //   }
  // }

#else
  void setup() {
    setup0();
  }
#endif

void setup0() {
  Serial.begin(serialCommunicationSpeed);
  start_hardware();
  // start_schakelscherm();
  start_scherm();
  start_sd();
  start_io();
  start_io_instellingen();
  Serial.println("io()");
  io();
  io();
  io();
  Serial.println("io_reset_alert()");
  io_reset_alert();
  Serial.println("io_reset_gewijzigd()");
  io_reset_gewijzigd();
  start_core2 = true;
  scherm_bouwen = true;
  scherm_touched = millis();
  Serial.println("loop()");
  loop();
  Serial.println("io_core = 0");
  io_core = 0;
  Serial.println("setup_einde");
  
}

void setup1() {
  /* 
   * Opstarten van de 2e kern
   * 
   */
  
  // Wachten tot de eerste voorbereidingen zijn getroffen
  while (start_core2 == false){
    Serial.println("Core 2: wachten");
    delay(50);
  }

  // Zolang core 1 nog niet gereed is zal core 2 eerst middels de loop  de IO taken uitvoeren
  Serial.println("Core 2: IO taken");
  while (io_core == 1){
    io_run();
  }
  Serial.println("Core 2: WiFi taken");
  Serial.println("Core 1 gestart");
  wifi_start();
  statusupdate_set_timer();
  Serial.println("Tijd tot volgend statusupdate: " + tijd_tot_millis(timer_statusupdate));
  if ((wifi__verbonden) & (wifi_connectie_modus != 1)) {
    wifi_verbinding_verbreken();
  } else {
    Serial.print("WiFi connectie modus: ");
    Serial.println(wifi_connectie_modus);
  }
  io_core = 1;
  Serial.println("");
  Serial.println("Setup core 2 gereed");
  boot_compleet = true;
  Serial.println("Core 2: Opstarten gereed (IO taken)");
}

#if hoofd_module__model <= 1
  void loop() {
    // Str  ing invoer;
    if (io_core == 0) {
      Serial.print("-");
      io_run();
      if (boot_compleet){
        io_alert_check();
      }
      header_alert();
    }
    ts.begin();
    if ((scherm_actief) || (scherm_bouwen)) {
      if ((millis() > scherm_touched + scherm_timer*1000) || (millis() < scherm_touched)) {
        scherm_actief = false;
        digitalWrite(led, LOW);
      } else {
        if (scherm_bouwen) {
          bouw_scherm[actief_scherm]();
          ts.begin();
          waas = false;
          scherm_bouwen = false;
          scherm_touched = millis();
        } else {
          run_scherm[actief_scherm]();
        }
      }
    } else {
      run_scherm_pauze();
    }
  
    if (boot_compleet) {
      /*
       * Checks en het uitsturen van extra berichten even laten wachten tot de boordcomputer volledig is opgestart
       */
      // Af en toe een diepe check doen waarbij een aantal als check gemaakt schakelingen worden omgezet zodat gezien kan worden of alles functioneerd
      if ((millis() > laatste_diepcheck + diepcheck_timer*60000) || (millis() < laatste_diepcheck)) {
        laatste_diepcheck = millis();
        io_diep_checken();
      }
    
      // Als er een alert te melden is deze verzenden. Indien het mislukt met enige vertraging opnieuw versturen
      if ((io_alert_app > 0) && (boot_compleet)) {
        Serial.print("alert! ");
    
        if ((millis() > laatste_alert_app + alert_app_timer*60000) || (millis() < laatste_alert_app) || (laatste_alert_app == 0)) {
          if ((wifi_connectie_modus != 0) & (wifi__aangesloten)) {
            io_alert_appen();
          } else {
            laatste_alert_app = millis();
            beeld_melding("WiFi uitgeschakeld", "Bericht wordt daarom niet veronden", "alert versturen!");
          }
        }
      }
  
      // Af en toe een statusupdate geven per app zodat bekend is dat er een verbinding is
      if (((millis() > laatste_app + levens_timer*60000) || (millis() < laatste_app) || (millis() > timer_statusupdate)) & (wifi_connectie_modus != 0)) {
        statusupdate();
        statusupdate_set_timer();
        Serial.println("Tijd tot volgend statusupdate: " + tijd_tot_millis(timer_statusupdate));
      }
    
      if (scherm_actief) {
        if ((millis() > h_klok_millis + 20000) || (millis() < h_klok_millis)) {
          klok_update();
        }
      }
    }
  }
#elif hoofd_module__model == 3
  void loop() {
    Serial.println("loop");
    // Str  ing invoer;
    if (io_core == 0) {
      Serial.print("-");
      io();
      io_check_zekeringen();
      io();
      io_alert_check();
      header_alert();
    }
    digitalWrite(cs_tft, HIGH);
    digitalWrite(cs_sd, HIGH);
    digitalWrite(cs_ts, HIGH);
    ts.begin();
    if ((scherm_actief) || (scherm_bouwen)) {
      if ((millis() > scherm_touched + scherm_timer*1000) || (millis() < scherm_touched)) {
        scherm_actief = false;
        digitalWrite(led, LOW);
      } else {
        if (scherm_bouwen) {
          Serial.println("core 1 scherm bouwen");
          bouw_scherm[actief_scherm]();
          ts.begin();
          waas = false;
          scherm_bouwen = false;
          scherm_touched = millis();
        } else {
          Serial.println("core 1 scherm checken");
          run_scherm[actief_scherm]();
        }
      }
    } else {
      run_scherm_pauze();
    }
  
    if (boot_compleet) {
      /*
       * Checks en het uitsturen van extra berichten even laten wachten tot de boordcomputer volledig is opgestart
       */
      // Af en toe een diepe check doen waarbij een aantal als check gemaakt schakelingen worden omgezet zodat gezien kan worden of alles functioneerd
      if ((millis() > laatste_diepcheck + diepcheck_timer*60000) || (millis() < laatste_diepcheck)) {
        laatste_diepcheck = millis();
        io_diep_checken();
      }
    
      // Als er een alert te melden is deze verzenden. Indien het mislukt met enige vertraging opnieuw versturen
      if (io_alert_app > 0) {
        Serial.print("alert! ");
    
        Serial.print(io_alert_cnt);
        Serial.print(" - ");
        Serial.println(io_alert_app);
        if ((millis() > laatste_alert_app + alert_app_timer*60000) || (millis() < laatste_alert_app) || (laatste_alert_app == 0)) {
          if ((wifi_connectie_modus != 0) & (wifi__aangesloten)) {
            io_alert_appen();
          } else {
            laatste_alert_app = millis();
            beeld_melding("WiFi uitgeschakeld", "Bericht wordt daarom niet veronden", "alert versturen!");
          }
        }
      }
    
      // Af en toe een statusupdate geven per app zodat bekend is dat er een verbinding is
      if (((millis() > laatste_app + levens_timer*60000) || (millis() < laatste_app) || (millis() > timer_statusupdate)) & (wifi_connectie_modus != 0)) {
        statusupdate();
        statusupdate_set_timer();
        Serial.println("Tijd tot volgend statusupdate: " + tijd_tot_millis(timer_statusupdate));
      }
    
      if (scherm_actief) {
        if ((millis() > h_klok_millis + 20000) || (millis() < h_klok_millis)) {
          klok_update();
        }
      }
    }
  }
#endif

void io_run(){
  if ((io_wijziging == true) || (io_timer > 0 and io_gecheckt + io_timer > millis())) {
    io();
    io_check_zekeringen();
    io();
    io_gecheckt = millis();
    io_wijziging = false;
  }
}

void loop1() {
  io_run();
          
}
