#include "spi.h"

#if controller <= 1
  void start_spi() {
    // chip select en led pin benoemen
    pinMode(cs_tft, OUTPUT);
    pinMode(cs_ts, OUTPUT);
    pinMode(cs_sd, OUTPUT);
    pinMode(led, OUTPUT);
    
    // start waarde ingeven
    digitalWrite(cs_tft, HIGH);
    digitalWrite(cs_ts, HIGH);
    digitalWrite(cs_sd, HIGH);
    digitalWrite(led, HIGH);
  
    // spi starten
    SPI.setRX(miso);
    SPI.setTX(mosi);
    SPI.setSCK(sck);

    SD.begin(cs_sd);
    XPT2046_Touchscreen ts(cs_ts, irq);
  }
    
#elif controller == 2
  void start_spi() {
    // chip select en led pin benoemen
    pinMode(cs_tft, OUTPUT);
    pinMode(cs_ts, OUTPUT);
    pinMode(cs_sd, OUTPUT);
    pinMode(led, OUTPUT);
    
    // start waarde ingeven
    digitalWrite(cs_tft, HIGH);
    digitalWrite(cs_ts, HIGH);
    digitalWrite(cs_sd, HIGH);
    digitalWrite(led, HIGH);
  
    SPIClass sd_spi = SPIClass(VSPI);
    SD.begin(cs_sd, sd_spi, 80000000);

    SPIClass ts_spi = SPIClass(CSPI);
    ts_spi.begin(clk_ts, miso_ts, mosi_ts, cs_ts);
    ts.begin(ts_spi);
  }
#endif
