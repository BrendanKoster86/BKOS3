#include <FS.H>
File myFile;

void start_sd();

void sd_info();
void sd_io();
void sd_wifi();
void sd_app();
void sd_leven();
void sd_startscherm();
void sd_ruimtes();

byte SD_byte(String invoer);
String SD_string(String invoer);

bool SD_connect = true;
