#include "io.h"


void io_schakel(int poort) {
  /*
   * Deze functie schakelt de gewenste poort tussen 0 en 1 of tussen 2 en 3 om het gekoppelde object te schakelen
   */
  if (io_output[poort] == 0) {
    io_output[poort] = 1;
  } else if (io_output[poort] == 1) {
    io_output[poort] = 0;
  } else if (io_output[poort] == 2) {
    io_output[poort] = 3;
  } else if (io_output[poort] == 3) {
    io_output[poort] = 2;
  }
}

void io_meeschakelen(int poort) {
  /*
   * Deze functie wordt gestart om de gewenste poorten mee te schakelen
   */
  
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 10; j++) {
      if (io_events[poort][io_input[poort]][i][j] > -1) {
        io_output[io_events[poort][io_input[poort]][i][j]] = i;
      }
    }
  
  }
}

void io_rst_fuse(int poort) {
  /*
   * Deze functie schakelt de gewenste poort van 4 naar 0 of van 5 naar 2 (van geblokkeerd naar uit)
   */
  if (io_output[poort] == 4) {
    io_output[poort] = 0;
  } else if (io_output[poort] == 5) {
    io_output[poort] = 2;
  }
}

void io_fusecheck() {
  /*
   * Deze functie controleert de knoppen en wanneer de teruggekomen waarde afwijkt wordt de poort geblokkeerd
   */
  bool all_ok = true;

  for (int i = 0; i < io_cnt; i++) {
    if (io_objecten[i] == 1) {
      if ((io_output[i] == 1) and (io_input[i] == 0)) {
        io_output[i] = 4;
        all_ok = false;
      } else if ((io_output[i] == 3) and (io_input[i] == 0)) {
        io_output[i] = 5;
        all_ok = false;
      }
    }
  }
  if (all_ok == false) {
    // Wanneer niet alles goed is dan io starten om direct ook de poorten uit te zetten.
    io();
  }
}

void io_invcheck() {
  /*
   * Deze functie controleert of uitgeschakelde of geblokkeerde aparaten echt uit staan.
   * Als dit niet zo is dan worden de aparaten omgedraaid uit uitgeschakeld.
   * Ook blokkades worden ongedaan gemaakt, omdat deze waarschijnlijk zijn ontstaan om deze reden
   */
  bool all_ok = true;
  
  for (int i = 0; i < io_cnt; i++) {
    if (io_objecten[i] == 1) {
      if (((io_output[i] == 0) or (io_output[i] == 4)) and (io_input[i] == 1)) {
        io_output[i] = 2;
        all_ok = false;
      } else if (((io_output[i] == 2) or (io_output[i] == 5)) and (io_input[i] == 1)) {
        io_output[i] = 0;
        all_ok = false;
      }
    } else if (io_objecten[i] == 3) { // 3 is een knop zonder check, dus hier niet de blokade om opheffen
      if (((io_output[i] == 0)) and (io_input[i] == 1)) {
        io_output[i] = 2;
        all_ok = false;
      } else if (((io_output[i] == 2)) and (io_input[i] == 1)) {
        io_output[i] = 0;
        all_ok = false;
      }
    }
  }
  if (all_ok == false) {
    // Wanneer niet alles goed is dan io starten om direct ook de poorten uit te zetten.
    io();
  }
}
