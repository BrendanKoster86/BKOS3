#if io_versie == 1
  void start_hardware() {
    // laten weten wat de 74HC pinnen moeten zijn
    pinMode(hc_pck, OUTPUT);  // paralelle klok (latch)
    pinMode(hc_sck, OUTPUT);  // seriele klok (clock)
    pinMode(hc_in , INPUT);   // data in
    pinMode(hc_uit, OUTPUT);  // data uit
    pinMode(hc_ce , OUTPUT);  // chip enable
    digitalWrite(hc_ce, LOW);
  
    // sd kaart voorlopig uit zetten
    pinMode(cs_tft, OUTPUT);
    pinMode(cs_ts, OUTPUT);
    pinMode(cs_sd, OUTPUT);
    pinMode(led, OUTPUT);
    digitalWrite(cs_tft, HIGH);
    digitalWrite(cs_ts, HIGH);
    digitalWrite(cs_sd, HIGH);
    Serial.print("PWM : ");
    Serial.println(round(255*(scherm_helderheid/100)));
    digitalWrite(led, HIGH);
    scherm_actief = true;
    // if (scherm_helderheid < 100) {
    //   analogWrite(led, round(255*(scherm_helderheid/100)));
    // }
    // analogWrite(led, 127);
    
    spi_starten();
  }
#elif io_versie > 2
  void start_hardware() {
    // laten weten wat de 74HC pinnen moeten zijn
    pinMode(hc_pck, OUTPUT);  // paralelle klok (latch)
    pinMode(hc_sck, OUTPUT);  // seriele klok (clock)
    pinMode(hc_in , INPUT);   // data in
    pinMode(hc_uit, OUTPUT);  // data uit
    pinMode(hc_id , INPUT);   // ID pin
    
    // sd kaart voorlopig uit zetten
    pinMode(cs_tft, OUTPUT);
    pinMode(cs_ts, OUTPUT);
    pinMode(cs_sd, OUTPUT);
    pinMode(led, OUTPUT);
    digitalWrite(cs_tft, HIGH);
    digitalWrite(cs_ts, HIGH);
    digitalWrite(cs_sd, HIGH);
    Serial.print("PWM : ");
    Serial.println(round(255*(scherm_helderheid/100)));
    digitalWrite(led, HIGH);
    scherm_actief = true;
    // if (scherm_helderheid < 100) {
    //   analogWrite(led, round(255*(scherm_helderheid/100)));
    // }
    // analogWrite(led, 127);
    
    spi_starten();
  }
#else
  void start_hardware() {
    // laten weten wat de 74HC pinnen moeten zijn
    pinMode(hc_pck, OUTPUT);  // paralelle klok (latch)
    pinMode(hc_sck, OUTPUT);  // seriele klok (clock)
    pinMode(hc_in , INPUT);   // data in
    pinMode(hc_uit, OUTPUT);  // data uit
    
    // sd kaart voorlopig uit zetten
    pinMode(cs_tft, OUTPUT);
    pinMode(cs_ts, OUTPUT);
    pinMode(cs_sd, OUTPUT);
    pinMode(led, OUTPUT);
    digitalWrite(cs_tft, HIGH);
    digitalWrite(cs_ts, HIGH);
    digitalWrite(cs_sd, HIGH);
    Serial.print("PWM : ");
    Serial.println(round(255*(scherm_helderheid/100)));
    digitalWrite(led, HIGH);
    scherm_actief = true;
    // if (scherm_helderheid < 100) {
    //   analogWrite(led, round(255*(scherm_helderheid/100)));
    // }
    // analogWrite(led, 127);
    
    spi_starten();
  }
#endif

#if hoofd_module__model <= 1
  void spi_starten() {
    Serial.println("SPI instellingen doen");
    // spi starten
    SPI.setRX(miso);
    SPI.setTX(mosi);
    SPI.setSCK(sck);
  }
#elif hoofd_module__model == 2
  void spi_starten() {
    Serial.println("SPI instellingen doen");
    // spi starten
    SPI.setTX(mosi);
    SPI.setSCK(sck);
  }  
#elif hoofd_module__model == 3
  void spi_starten() {
    Serial.println("SPI instellingen doen");
    // spi starten
    SPI.begin(sck, miso, mosi, cs_tft);

    // SPI.setRX(miso);
    // SPI.setTX(mosi);
    // SPI.setSCK(sck);
  }
#endif
