void statusupdate() {
  String bericht = info_snaam + ": statusupdate van ca " + tijd();
  bericht += ". " + String(io_diepcheck_cnt) + " diepchecks uitgevoerd over " + String(io_diepcheck_pins_cnt) + " pins (";
  for (int i = 0; i < io_diepcheck_pins_cnt; i++) {
    bericht += String(io_diepcheck_pins[i]) + ", ";
  }
  bericht = bericht.substring(0, bericht.length()-1) + ")";
  if (io_diepcheck) {
    bericht += ", allen zonder problemen.";
  } else {
    bericht += " WAARBIJ PROBLEMEN GEVONDEN ZIJN !";
  }
  if (io_alert_cnt == 0) {
    bericht += " geen openstaande alerts.";
  } else {
    if (io_alert_cnt == 1) {
      bericht += " 1 openstaande alert!";
    } else {
      bericht += " " + String(io_alert_cnt) + " openstaande alerts!";
    }
    if (io_alert_cnt == 0) {
      bericht += " allen reeds verzonden";
    } else if (io_alert_cnt == 1) {
      bericht += " 1 trigger sinds laatste bericht!";
    } else {
      bericht += " " + String(io_alert_app) +  " trigers sinds laatste bericht!";
    }
  }

  if (app_sturen(bericht)) {
    io_diepcheck_cnt = 0;
    io_alert_app = 0;
  }

  if ((millis() > laatste_app + levens_timer*60000) || (millis() < laatste_app)) {
    Serial.println("Verzenden app mislukt.\nOver 5 minuten een 2e poging");
    laatste_app = millis() - ((levens_timer - 5) * 60000);
  }
}

void statusupdate_set_timer() {
  if (millis() > timer_statusupdate) {
    timer_statusupdate = millis_wekker(statusupdate_timer_array[0][0], statusupdate_timer_array[0][1]);
    for (int i = 1; i < statusupdate_timer_array_cnt; i++) {
      if (timer_statusupdate > millis_wekker(statusupdate_timer_array[i][0], statusupdate_timer_array[i][1])) {
        timer_statusupdate = millis_wekker(statusupdate_timer_array[i][0], statusupdate_timer_array[i][1]);
      }
    }
  }
}