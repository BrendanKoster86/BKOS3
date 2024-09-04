/*
 * Het doel van alle bestanden in deze map is dat de harwarekant van de boordcomputer draait zonder overwelmd te worden met veel tabjes
 * Dit rekening houdend met de verschillende opties waar in de hoofdmap keuzes voor zijn gemaakt
 * 
 * na het inladen van deze biebliotheek en het draaien van start_hardware(); is het volgende beschikbaar
 * tft.  als het scherm
 * io(); Aansturen en uitlezen van de uitbreidings modules (enkel hardwarematige gedeelte)
 */
#ifndef HARDWARE__H
#define HARDWARE__H
#pragma once

#include <Arduino.h>

#include <SoftwareSerial.h>
#include <string.h>

#include "io.h"
#include "spi.h"

void start_hardware();

#endif
