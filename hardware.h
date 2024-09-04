void start_hardware();
void spi_starten();


// Selectie gebruikte hardware
// #define hoofd_module__model  3     // 0 : Raspberry pi pico + ESP8266 s01
//                                    // 1 : Raspberry pi pico W
//                                    // 2 : ESP32-2432s028r (nog niet functionerend)
//                                    // 3 : ESP32 VROOM (38 pin versie)
#if defined(ARDUINO_ARCH_MBED_RP2040) || defined(ARDUINO_ARCH_RP2040)

  #define hoofd_module__model  1    // Dit kan in principe 0 of 1 zijn
#elif defined(ESP_PLATFORM)
  #define hoofd_module__model  3    // Dit kan in principe 2 of 3 zijn waarbij 2 nog niet functioneerd
#endif

#define io_versie            2     // 1   : Hoofdmodule maximaal versie 2.0 Uitbreidingsmodulen versie 1 (zonder versie nummer)
                                   // 2   : Hoofdmodule alle versies mogelijk, uitbreidings module versie 2.0 of nieuwer zonder gebruik te maken van de ID functionaliteit.
                                   // 2.1 : Hoofdmodule versie 2.1 of nieuwer, Uitbreidings module versie 2.0 of nieuwer met gebruik maken van de ID functionaliteit.
                                   
#define scherm_ili        9341     // 9341 voor 240 x 320 (2,8 inch) of 9488 voor 320 x 480 (4 inch)



// Scherm afmetingen
#if scherm_ili == 9341
  #define tf_minX 0
  #define tf_maxX 320
  #define tf_minY 0
  #define tf_maxY 240
#elif scherm_ili == 9488
  #define tf_minX 0
  #define tf_maxX 480
  #define tf_minY 0
  #define tf_maxY 320
#endif

  
#if hoofd_module__model <= 1
  // Hardware instellingen bij het gebruik van de eigen printplaten met een Raspberry Pi Pico of Raspberry Pi Pico W als micro controller
  
  // Pin selectie SPI
  #define cs_ts  13
  #define cs_tft 17
  #define cs_sd  12
  #define mosi   19
  #define miso   16
  #define rst    14
  #define sck    18
  #define dc     15
  #define irq    11
  #define led    10

  // IO aansturing Verschil per versie is het gebruik van pin 4
  #define hc_pck 2  // paralelle klok (latch)
  #define hc_sck 1  // seriele klok (clock)
  #define hc_in  0  // data in
  #define hc_uit 3  // data uit
  #define hc_id  4  // id pin

  #if hoofd_module__model == 0
    // Voor de gewone Raspberry Pi Pico wordt via softwareserial verbinding gemaakt met wifi.
    SoftwareSerial wifi(20,21);
  #endif

#elif hoofd_module__model == 2
  // Hardware instellingen voor de ESP32-2432s028r 

  
  // SPI. Dit type display heeft een compleet eigen SPI poort per item in plaats van een gedeelde poort
  #define cs_tft 15
  #define mosi   13
  #define rst    12
  #define sck    14
  #define dc     2
  #define led    21

  #define cs_ts     33
  #define mosi_ts   32
  #define miso_ts   39
  #define sck_ts    25
  #define irq       36
  
  #define cs_sd     5
  #define mosi_sd   23
  #define miso_sd   19
  #define sck_sd    18

  // Voor communicatie met de uitbreidings modulen wordt gebruik gemaakt van SoftwareSerial over poorten 22 en 27. Dit kan worden omgeschreven over 9600 boud
  SoftwareSerial io_serial(22, 27);
  #define io_serial_boud  9600

#elif hoofd_module__model == 3
  // Hardware instellingen bij het gebruik van de eigen printplaten met een Raspberry Pi Pico of Raspberry Pi Pico W als micro controller
  
  // Pin selectie SPI
  #define cs_ts  22
  #define cs_tft 15
  #define cs_sd  0
  #define mosi   13
  #define miso   12
  #define rst    16
  #define sck    14
  #define dc     23
  #define irq    21
  #define led    19

  // IO aansturing Verschil per versie is het gebruik van pin 4
  #define hc_pck 18  // eigenlijk 8, D1 (andere pin zoeken) paralelle klok (latch)
  #define hc_sck 17  // eigenlijk 7, D0 (andere pin zoeken) seriele klok (clock)
  #define hc_in  35  // data in
  #define hc_uit 2  // data uit
  #define hc_id  34  // id pin

  // #if hoofd_module__model == 0
  //   // Voor de gewone Raspberry Pi Pico wordt via softwareserial verbinding gemaakt met wifi.
  SoftwareSerial wifi(32,33);
  // #endif

#endif
