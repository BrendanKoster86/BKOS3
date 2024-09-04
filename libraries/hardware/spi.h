#ifndef HARDWARE_SPI_H
#define HARDWARE_SPI_H

#include <Arduino.h>

#include <XPT2046_Touchscreen.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <TFT_eSPI.h>
#include <SD.h>


#if controller <= 1
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

#elif controller == 2
  // Hardware instellingen voor de CYD (ESP32-2432 S29r) en aanverwanten

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

#endif

// Scherm afmetingen
#if resolutie == 2432
  #define tf_minX 0
  #define tf_maxX 320
  #define tf_minY 0
  #define tf_maxY 240
#elif resolutie == 3248
  #define tf_minX 0
  #define tf_maxX 480
  #define tf_minY 0
  #define tf_maxY 320
#endif

void start_spi();

#endif
