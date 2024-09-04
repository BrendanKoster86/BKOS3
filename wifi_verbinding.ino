#if hoofd_module__model == 0
  String sendData(String command, const int timeout, boolean debug) {
      String response = "";                                             
      wifi.print(command);                                          
      long int time = millis();                                      
      while( (time+timeout) > millis())                                 
      {      
        while(wifi.available())                                      
        {
          char c = wifi.read();                                     
          response+=c;                                                  
        }  
      }    
      if(debug)                                                        
      {
        Serial.print(response);
      }
  
      // Onerdeel om de tijd uit een response te halen. zodat er toch een klokje op de boordcomputer kan staan :)
      int dt = response.indexOf("Date");
      if (dt > 1) {
        tijd_millis = millis();
        dagnm = response.substring(dt+6, response.indexOf(" ", dt+7));
        dt = response.indexOf(" ", dt+7);
        dag = response.substring(dt+1, response.indexOf(" ", dt+1)).toInt();
        dt = response.indexOf(" ", dt+1);
        maand = response.substring(dt+1, response.indexOf(" ", dt+1));
        dt = response.indexOf(" ", dt+1);
        jaar = response.substring(dt+1, response.indexOf(" ", dt+1)).toInt();
        dt = response.indexOf(" ", dt+1);
        uur = response.substring(dt+1, response.indexOf(";", dt+1)).toInt();
        dt = response.indexOf(":", dt+1);
        minuut = response.substring(dt+1, response.indexOf(";", dt+1)).toInt();
        dt = response.indexOf(":", dt+1);
        seconde = response.substring(dt+1, response.indexOf(" ", dt+1)).toInt();
        dt = response.indexOf(" ", dt+1);
        tijdzone = response.substring(dt+1, response.indexOf("\n", dt+1));
        dt = response.indexOf("\n", dt+1);
      }
      return response;                                                  
  }
#else
  String sendData(String command, const int timeout, boolean debug) {
    return "";
    }
#endif

String sendData(String command, const int timeout){
  return sendData(command, timeout, true);
}

String sendData(String command){
    return sendData(command, 2000, true);
}

String sendData(String command, bool debug){
    return sendData(command, 2000, debug);
}

#if hoofd_module__model == 0
void wifi_start() {
  wifi.begin(serialCommunicationSpeed);
  delay(100);
  wifi_beschikbare_netwerken_vernieuwen();
  wifi_verbinden();
  app_sturen("Boordcomputer boot '" + info_snaam + "' opgestart.");
}  
#else
void wifi_start() {
  wifi_beschikbare_netwerken_vernieuwen();
  wifi_verbinden();
  app_sturen("Boordcomputer boot '" + info_snaam + "' opgestart.");
}  
#endif

void netwerken_splits(String invoer) {
  int reg_start = 0;
  int ssid_start = 0;
  int ssid_eind = 0;
  
  while (reg_start != -1) {
    reg_start = invoer.indexOf("+CWLAP:(", ssid_eind);
    if (reg_start != -1) {
      ssid_start = invoer.indexOf(",\"", reg_start + 1);
      ssid_eind = invoer.indexOf("\",", ssid_start + 2);
      wifi_cnt_gevonden ++;
    }
  }

  delete[]wifi_ssid_gevonden;
  delete[]wifi_ecn_gevonden;
  
  wifi_ssid_gevonden = new String[wifi_cnt_gevonden];
  wifi_ecn_gevonden = new int[wifi_cnt_gevonden];

  reg_start = 0;
  ssid_start = 0;
  ssid_eind = 0;
  int i = 0;
  
  while (reg_start != -1) {
    reg_start = invoer.indexOf("+CWLAP:(", ssid_eind);
    if (reg_start != -1) {
      ssid_start = invoer.indexOf(",\"", reg_start + 1);
      ssid_eind = invoer.indexOf("\",", ssid_start + 2);
      wifi_ssid_gevonden[i] = invoer.substring(ssid_start + 2, ssid_eind);
      wifi_ecn_gevonden[i] = invoer.substring(ssid_start-1, ssid_start).toInt();
      i += 1;
    }
  }
  
  // Serial.print(wifi_cnt_gevonden);
  // for (int i =0; i < wifi_cnt_gevonden; i++) {
  //   Serial.println(wifi_ecn_gevonden[i]);
  //   Serial.println(wifi_ssid_gevonden[i]);
  // }
}

void netwerk_volgorde() {

  // Te maken overzicht beginnen met de netwerken die opgeslagen zijn en zijn gevonden
  for (int i = 0;  i < wifi_cnt_sd; i++) {
    if (string_in_array(wifi_ssid_sd[i], wifi_ssid_gevonden, wifi_cnt_gevonden)) {
      wifi_ssid_proberen[wifi_cnt_proberen] = wifi_ssid_sd[i];
      wifi_pass_proberen[wifi_cnt_proberen] = wifi_pass_sd[i];
      Serial.print("opgeslagen en gevonden: ");
      Serial.print(wifi_ssid_proberen[wifi_cnt_proberen]);
      Serial.print("  -  ");
      Serial.println(wifi_pass_proberen[wifi_cnt_proberen]);
      Serial.print("Zoals opgeslagen      : ");
      Serial.print(wifi_ssid_sd[i]);
      Serial.print("  -  ");
      Serial.println(wifi_pass_sd[i]);
      wifi_cnt_proberen += 1;
    }
  }

  // Vervolgens de open netwerken opnemen
  for (int i = 0; i < wifi_cnt_gevonden; i++) {
    if ((wifi_ecn_gevonden[i] == 0) && ( not string_in_array(wifi_ssid_gevonden[i], wifi_ssid_proberen, wifi_cnt_proberen))) {
      wifi_ssid_proberen[wifi_cnt_proberen] = wifi_ssid_gevonden[i];
      wifi_pass_proberen[wifi_cnt_proberen] = "";
      Serial.print("Gevonden open netwerken: ");
      Serial.println(wifi_ssid_proberen[i]);
      wifi_cnt_proberen += 1;
    }
  }

  // Tot slot de opgeslagen netwerken opnemen. Het kan namelijk zijn dat deze op onzichtbaar staan ingesteld, of door een tijdelijke hickup niet worden gevonden.
  for (int i = 0; i < wifi_cnt_sd; i++) {
    if (not string_in_array(wifi_ssid_sd[i], wifi_ssid_proberen, wifi_cnt_proberen)) {
      wifi_ssid_proberen[wifi_cnt_proberen] = wifi_ssid_sd[i];
      wifi_pass_proberen[wifi_cnt_proberen] = wifi_pass_sd[i];
      wifi_cnt_proberen += 1;
      Serial.print("opgeslagen, dus toch maar proberen: ");
      Serial.println(wifi_ssid_proberen[i]);
      
    }
  }

  // Overzich tonen van de gevonen netwerken in de gewenste volgorde.
  Serial.println("");
  Serial.println("");
  Serial.println("nr:   naam     -     Wachtwoord");
  Serial.println("-------------------------------------------");
  for (int i = 0; i < wifi_cnt_proberen; i++) {
    Serial.print(i+1);
    Serial.print(" : ");
    Serial.print(wifi_ssid_proberen[i]);
    Serial.print("  -  ");
    Serial.println(wifi_pass_proberen[i]);
  }
}

#if hoofd_module__model == 1
  void netwerken_zoeken_pico_W() {
    /* 
     *  Dit is de funcite om met wifi te verbinden voor wanneer er een pico W wordt gebruikt
     */
    wifi_cnt_gevonden = WiFi.scanNetworks();
    
    delete[]wifi_ssid_gevonden;
    delete[]wifi_ecn_gevonden;
    
    wifi_ssid_gevonden = new String[wifi_cnt_gevonden];
    wifi_ecn_gevonden = new int[wifi_cnt_gevonden];
    
    for (int i = 0; i < wifi_cnt_gevonden; i++) {
      wifi_ssid_gevonden[i] = WiFi.SSID(i);
    }
  }
#else
  void netwerken_zoeken_pico_W() {
    wifi__aangesloten = false;
    wifi__verbonden = false;
    Serial.println("Hier kan je als het goed is toch niet terecht komen, maar toch maar een error print :)");
  }
#endif

void netwerken_zoeken() {
  /*
   *  Deze functie maakt een overzicht van de gewenste netwerken. 
   *  Afhankelijk van of er een pico W of een gewone pico met losse wifi adapter wordt gebruikt wordt een andere onderliggende functie gebruikt.
   */
   
  if (hoofd_module__model == 0) {
    Serial.println("ESP modus");
    sendData("AT+RST\r\n");
    sendData("AT+CWMODE=1\r\n");
    sendData("AT+CWLAP\r\n");
    netwerken_splits(sendData("AT+CWLAP\r\n"));
//    netwerken_zoeken_pico_W();
    sendData("AT+RST\r\n");
    netwerk_volgorde();
  delay(100);
  } else if (hoofd_module__model == 1) {
    Serial.print("pico W modus");
  //  sendData("AT+RST\r\n");
  //  sendData("AT+CWMODE=1\r\n");
  //  sendData("AT+CWLAP\r\n");
  //  netwerken_splits(sendData("AT+CWLAP\r\n"));
    netwerken_zoeken_pico_W();
  //  sendData("AT+RST\r\n");
    netwerk_volgorde();
  //  delay(100);

  }

}

#if hoofd_module__model == 1
  int encToInt(uint8_t enc) {
    switch (enc) {
      case ENC_TYPE_NONE: return 0;
      case ENC_TYPE_TKIP: return 1;
      case ENC_TYPE_CCMP: return 2;
      case ENC_TYPE_AUTO: return 3;
    }
    return 99;
  }
  
  
  void wifi_beschikbare_netwerken_vernieuwen() {
    if((hoofd_module__model == 1) || (sendData("AT\r\n").indexOf("OK") > -1)) {
      wifi__aangesloten = true;
    }
    if (wifi__aangesloten) {
      Serial.println("Netwerken zoeken");
      netwerken_zoeken();
      Serial.print(wifi_cnt_gevonden);
      Serial.println(" netwerken gevonden");
      for (int i = 0 ; i < wifi_cnt_gevonden; i++) {
        Serial.println(wifi_ssid_gevonden[i]);
      }
    } else {
      delay (1000);
    }
  }
#else
  void wifi_beschikbare_netwerken_vernieuwen() {
    if(sendData("AT\r\n").indexOf("OK") > -1) {
      wifi__aangesloten = true;
    }
    if (wifi__aangesloten) {
      Serial.println("Netwerken zoeken");
      netwerken_zoeken();
      Serial.print(wifi_cnt_gevonden);
      Serial.println(" netwerken gevonden");
      for (int i = 0 ; i < wifi_cnt_gevonden; i++) {
        Serial.println(wifi_ssid_gevonden[i]);
      }
    } else {
      delay (1000);
    }
  }
#endif
boolean string_in_array(String element, String array[], int lengte) {
  for (int i = 0; i < lengte; i++) {
    if (array[i] == element) {
      return true;
    }
  }
  return false;
}

#if hoofd_module__model == 1
  void wifi_verbinden(){
    if (hoofd_module__model == 0) {
      wifi_verbinden(true);
    } else if (hoofd_module__model == 1) {
      wifi_verbinden(false);
    }
  }
  
  void wifi_verbinden(bool automatisch) {
    String response;
    Serial.println("Verbinden");
    int i = 0;
    Serial.println(wifi_cnt);
    Serial.println(i);
  
    sendData("AT+RST\r\n", 2000, DEBUG);
    if ((hoofd_module__model == 0) && (automatisch)) {
      // Verbinden met het vorige netwerk waarmee verbonden was.
      response = sendData("AT+CWJAP\r\n", 5000, DEBUG);
      if (response.indexOf("WIFI CONNECTED") > 0) {
        i = -1;
      }
    } else if (hoofd_module__model == 1) {
      sendData("AT+CWQAP\r\n");
      response = "niet verbonden";
    } else {
      response = "niet verbonden";
    }
  
    while ((response.indexOf("WIFI CONNECTED") <= 0) && (i < wifi_cnt_proberen)) {
  
      Serial.print("Verbinding maken met: ");
      Serial.println(wifi_ssid_proberen[i]);
      // Opgeslagen netwerken in login.h af gaan tot daarmee verbinding is gemaakt.
      if (hoofd_module__model == 0) {
        sendData("AT+RST\r\n", 2000, DEBUG);
        delay(500);
        response = sendData("AT+CWJAP=\"" + wifi_ssid_proberen[i] + "\",\"" + wifi_pass_proberen[i] + "\"\r\n", 5000, DEBUG);
        delay(5000);
      } else if (hoofd_module__model == 1) {
        
  //      write_StringEE(0, wifi_ssid_proberen[i]);
  //      wifi_ssid1 = read_StringEE(0, wifi_ssid_proberen[i].length());
        wifi_ssid2 = wifi_ssid_proberen[i].c_str();
        
  //      write_StringEE(0, wifi_pass_proberen[i]);
  //      wifi_pass1 = read_StringEE(0, wifi_pass_proberen[i].length());
        wifi_pass2 = wifi_pass_proberen[i].c_str();
        
        multi.addAP(wifi_ssid2, wifi_pass2);
        if (multi.run() != WL_CONNECTED) {
          response = "WIFI UNCONNECT";
        } else {
          response = "verbonden :) WIFI CONNECTED :)";
        }
      }
      
      if (response.indexOf("WIFI CONNECTED") > 0) {
      } else {
        i += 1;
      }
    }
  
    wifi_check();
    if (wifi__verbonden) {
      delay(1000);
    } else {
    }
  }
#else
  void wifi_verbinden(){
    if (hoofd_module__model == 0) {
      wifi_verbinden(true);
    } else if (hoofd_module__model == 1) {
      wifi_verbinden(false);
    }
  }
  
  void wifi_verbinden(bool automatisch) {
    String response;
    Serial.println("Verbinden");
    int i = 0;
    Serial.println(wifi_cnt);
    Serial.println(i);
  
    sendData("AT+RST\r\n", 2000, DEBUG);
    if ((hoofd_module__model == 0) && (automatisch)) {
      // Verbinden met het vorige netwerk waarmee verbonden was.
      response = sendData("AT+CWJAP\r\n", 5000, DEBUG);
      if (response.indexOf("WIFI CONNECTED") > 0) {
        i = -1;
      }
    } else if (hoofd_module__model == 1) {
      sendData("AT+CWQAP\r\n");
      response = "niet verbonden";
    } else {
      response = "niet verbonden";
    }
  
    while ((response.indexOf("WIFI CONNECTED") <= 0) && (i < wifi_cnt_proberen)) {
  
      Serial.print("Verbinding maken met: ");
      Serial.println(wifi_ssid_proberen[i]);
      // Opgeslagen netwerken in login.h af gaan tot daarmee verbinding is gemaakt.
      if (hoofd_module__model == 0) {
        sendData("AT+RST\r\n", 2000, DEBUG);
        delay(500);
        response = sendData("AT+CWJAP=\"" + wifi_ssid_proberen[i] + "\",\"" + wifi_pass_proberen[i] + "\"\r\n", 5000, DEBUG);
        delay(5000);
      } else if (hoofd_module__model == 1) {
        
        Serial.println("Hier had je niet mogen komen omdat deze functie niet bestaat met de ingestelde hoofd_module__model");
        wifi__verbonden = false;
        response = "WIFI UNCONNECT";
      }
      
      if (response.indexOf("WIFI CONNECTED") > 0) {
      } else {
        i += 1;
      }
    }
  
    wifi_check();
    if (wifi__verbonden) {
      delay(1000);
    } else {
    }
  }
#endif

#if hoofd_module__model == 0
  void wifi_verbinding_verbreken() {
    sendData("AT+CWQAP\r\n", 1500, DEBUG);
    delay(500);
    wifi_check();
  }
#else
  void wifi_verbinding_verbreken() {
    
  }
#endif

void wifi_check(bool debug) {
  /* debug ombouw voor wifi_check */
  wifi_check();
  if (debug) {
    if (wifi__verbonden) {
      Serial.print("Verbonden met : ");
      Serial.println(wifi__ssid);
      Serial.print("IP adres is :   ");
      Serial.println(wifi__ip);
      Serial.print("MAC adres is :  ");
      Serial.println(wifi__mac);
    } else {
      Serial.println("Wifi niet verbonden");
    }
  }
  laatste_wifi_check = millis();
}


String IpAddress2String(const IPAddress& ipAddress)
{
  return String(ipAddress[0]) + String(".") +\
  String(ipAddress[1]) + String(".") +\
  String(ipAddress[2]) + String(".") +\
  String(ipAddress[3])  ; 
}

#if hoofd_module__model == 1
  void wifi_check() {
    if (hoofd_module__model == 0) {
      wifi_check_esp();
    } else if (hoofd_module__model == 1) {
      wifi_check_pico_w();
    }
  }
  
  void wifi_check_pico_w() {
    if (multi.run() == WL_CONNECTED) {
      wifi__verbonden = true;
      wifi__ip = IpAddress2String(WiFi.localIP());
      wifi__mac = "nog even uitzoeken hoe dit werkt";
      wifi__ssid = "nog even uitzoeken hoe dit werkt";
      
    } else {
      wifi__verbonden = false;
      wifi__ip = "";
      wifi__ssid = "";
    }
  }
#else
  void wifi_check() {
    if (hoofd_module__model == 0) {
      wifi_check_esp();
    } else if (hoofd_module__model == 1) {
      Serial.println("U kunt geen pico w wifi adapter gebruiken met een gewone raspberry pi pico.");
      Serial.println("Indien u een pico w gebruikt pas dan het hoofd_module__model aan naar 1. Gebruik anders een losse wifi controller");
      wifi__verbonden = false;
      wifi__aangesloten = false;
      wifi__ip = "";
      wifi__ssid = "";
    }
  }
#endif


void wifi_check_esp() {
  String response = sendData("AT+CIPSTATUS\r\n", false);
  delay(500);
  response = response.indexOf("\r");
  if ((response.substring(0, response == "STATUS:2")) || (response.substring(0, response.length()-1) == "STATUS:2")) {
    wifi__verbonden = true;

    // IP adres uitvragen
    String buffer = sendData("AT+CWJAP?\r\n", 1500, false);
    int quote1 = buffer.indexOf("\"");
    int quote2 = buffer.indexOf("\"", quote1 + 1);
    wifi__ssid = buffer.substring(quote1+1, quote2);

    // IP adres uitvragen
    buffer = sendData("AT+CIFSR\r\n", 1500, false);
    quote1 = buffer.indexOf("\"");
    quote2 = buffer.indexOf("\"", quote1 + 1);
    wifi__ip = buffer.substring(quote1+1, quote2);
    quote1 = buffer.indexOf("\"", quote2 + 1);
    quote2 = buffer.indexOf("\"", quote1 + 1);
    wifi__mac = buffer.substring(quote1+1, quote2);
  } else {
    wifi__verbonden = false;
    wifi__ssid = "";
    wifi__ip = "";
  }

  if (wifi__ssid.substring(0, 9) == "AT+CWJAP?"){
    wifi__verbonden = false;
    wifi__ssid = "";
    wifi__ip = "";
  }
}


String tijd() {
  return tijd("HM");
}

String tijd(String wat) {
  /* Deze functie update de laatste wifi ontvangen tijd met de verstreken mili secondes en corrigeerd deze naar de tijdzonde.
  Vervolgens wordt een String van de tijd terug gegeven om elders te kunnen gebruiken */

  long mili_buffer = millis();
  seconde = seconde + ((mili_buffer - tijd_millis) / 1000);
  if ((tijdzone == "GMT") || (tijdzone.substring(0, tijdzone.length()-1) == "GMT")) {
    uur++;
    tijdzone = "GMT +1";
  }
  tijd_millis = mili_buffer;
  int buffer = seconde / 60;
  minuut = minuut + buffer;
  seconde = seconde - buffer * 60;
  buffer = minuut / 60;
  uur = uur + buffer;
  minuut = minuut - buffer * 60;
  buffer = uur / 60;
  uur = uur - buffer * 60;

  while (uur >= 24) {
    dag++; // Dag is plus 1. Omdat dit aan het einde van de maand niet klopt gaat het niet perfect, maar dit wordt gereset zodra er een app wordt verstuurd.
    uur -= 24;
    dagnm = ""; // Nog een functie maken om de dagnaam te veranderen. Voor nu omdat deze niet meer klopt weg halen
  }

  String response;
  if (wat.indexOf("H") > -1) {
    response += String(uur) + ":";
    if (wat.indexOf("M") > -1) {
      if (String(minuut).length() == 1) {
        response += "0";
      }
      response += String(minuut) + ":";
      if (wat.indexOf("S") > -1) {
        if (String(seconde).length() == 1) {
          response += "0";
        }
        response += String(seconde) + ":";
      }
    }
    response = response.substring(0, response.length()-1);
    if (wat.indexOf("Z") > -1) {
      response += " " + tijdzone;
    } else if (wat.indexOf("uur") > -1) {
      response += " uur";
    }
  }
  
  return response;
}

long millis_wekker(int H, int M) {
  /* Deze functie op welke millis() het een gewenste tijd is om een timer te kunnen zetten... erg handig (denk ik)*/

  // Tijd aanroepen zodat ook de tijdzone wordt gecorrigeerd
  tijd();

  Serial.print("Huidige tijd : ");
  Serial.println(String(uur) + ":" + String(minuut) + ":" + String(seconde));
  Serial.print("Wekker tijd : ");
  Serial.println(String(H) + ":" + String(M));

  // Tijd bepalen tot de triger sinds de laatste meting
  int sec = 60 - seconde;
  int min = 60 - minuut + M - 1; // Oorspronkelijk nog -1, maar omdat het bericht nu 1 minuut te vroeg verstuurd werd deze verwijderd.
  int hr = 24 - uur + H - 1;
  
  // // Correctie voor een volle minuut, uur of dag
  while (sec >= 60) {
    sec -= 60;
    min++;
  }
  while (min >= 60) {
    min -= 60;
    hr++;
  }
  while (hr >= 24) {
    hr -= 24;
  }

  Serial.println("Te verstrijken tijd:");
  Serial.println("uur : "+ String(hr) + ", minuten : " + String(min) + ", seconde : " + String(sec));

  // Omzetten in te verstrijken milli seconden
  return tijd_millis + (hr * 3600000) + (min * 60000) + (sec * 1000);
}

long millis_timer(int H, int M, int S) {
  /* Deze heel eenvoudige functie zet een millis timer voor over een bepaalde tijd */
  return millis() + (H * 3600000) + (M * 60000) + (S * 1000);
}

String tijd_tot_millis(long invoer) {
  long tijd = invoer - millis();
  int sec = tijd / 1000;
  if (sec < 60) {
    return String(sec) + " seconde";
  }
  
  int min = sec / 60;
  sec = sec - min * 60;
  if (sec < 0) {
    sec += 60;
    min--;
  }
  if (min < 60) {
    return String(min) + " minuten, " + String(sec) + " seconde";
  }

  int uur = min / 60;
  min = min - uur * 60;
  if (uur < 24) {
    return String(uur) + " uur, " + String(min) + " minuten";
  }

  int dag = uur / 24;
  uur = uur - dag * 24;
  return String(dag) + " dagen, " + String(uur) + " uur";
}
