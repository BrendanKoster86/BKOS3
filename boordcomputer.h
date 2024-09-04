// Aanroepen van algemene bibliotheken
#include <XPT2046_Touchscreen.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <TFT_eSPI.h>
#include <SD.h>
#include <SoftwareSerial.h>
#include <string.h>

String buffer;

// Aanroepen van eigen bibliotheken
#include "hardware.h"
#include "gegevens.h"
#include "sd_lezer.h"
#include "sd_schrijven.h"
#include "scherm.h"
#include "knoppen.h"
#include "io.h"
#include "header.h"
#include "icon.h"
#include "kleuren.h"
#include "wifi_verbinding.h"
#include "app.h"
#include "statusupdate.h"

#define serialCommunicationSpeed 115200
#define DEBUG true

// Aanroepen van functies en schermen via een ondersteunende header file
#include "schermen.h"

bool scherm_bouwen;

byte SMODES = 0;
