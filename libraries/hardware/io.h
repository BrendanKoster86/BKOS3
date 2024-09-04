#ifndef HARDWARE_IO_H
#define HARDWARE_IO_H

#include <Arduino.h>

#if controller <= 1
  // IO aansturing Verschil per versie is het gebruik van pin 4
  #define hc_pck 2  // paralelle klok (latch)
  #define hc_sck 1  // seriele klok (clock)
  #define hc_in  0  // data in
  #define hc_uit 3  // data uit

  #if io_versie < 2
    // Bij versie 1 is dat chip select
    #define hc_ce  4  // chip enable
  #elif io_versie >= 3
    // Bij versie 3 is dat ID
    #define hc_id  4  // id pin
  #endif

#elif controller == 2
  SoftwareSerial io_serial(22, 27);   // Seriele uitgang van de CYD module om io opdrachten over te versturen en ontvangen
  #define io_serial_boud 9600
#endif

//void start_io();
void io();


#endif
