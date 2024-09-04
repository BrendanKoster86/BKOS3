

void sd_maken();
void blanco_sd_maken();
bool sd_save_io(int cnt);
bool sd_save_io();

/*
Hieronder vindt je de standaard inhoud van de bestanden op de SD kaart.

Er zal een functie zijn dat deze bestanden op de SD kaart plaatst zodat er een mooie start ontstaat voor het doen van de instellingen.
*/

String SD__io_objecten[] = {"8     ",
                            "De eerste 4 tekens staan voor het type item en het gewenste gedrag",
                            "Het eerste teken staat voor het type aansluiting:__________________0: niet aangesloten, 1: knop, 2: sensor, 3: knop zonder check, 4: io doorgelust om functioneren te testen",
                            "Het 2e teken staat voor de 'opgeslagen' output:____________________0: uit, 1: aan, 2: inv uit (hoog), 3: inv aan (laag), 4: geblokeerd (laag), 5: inv geblokeerd (hoog)",
                            "het 3e teken staat voor of wordt gereset in de vorige status:______0: nee, 1: ja (bij het schakelen wordt de reset status aangepast. hier is nog onderzoek voor nodig)",
                            "het 4e teken staat voor wanneer er een alert moet owrden gegeven:__0: bij passief worden, 1: bij actief worden, 2: bij alle verandering, 3: nooit",
                            "Tot slot volgt de naam van het aangesloten object",
                            "2003io1       ",
                            "2003io2       ",
                            "2003io3       ",
                            "2003io4       ",
                            "2003io5       ",
                            "2003io6       ",
                            "2003io7       ",
                            "2003io8       "
};

String SD__app[] = {"1 ",
                    "Het bovenstaande cijfer geeft aan hoeveel nummers zijn opgeslagen.",
                    "Neem hieronder telkens 3 regels voor je gegevens. De eerste voor de gebruikte app, de tweede je telefoonnummer en de derde voor je key",
                    "signal",
                    "telefoonnummer",
                    "key"
};

String SD__login[] = {"1  ",
                      "2",
                      "In dit bestand staan de instellingen voor de wifi netwerken en de wens om er mee om te gaan opgeslagen.",
                      "Het bovenste cijfer geeft aan hoeveel netwerken staan opgeslagen hieronder. Dit is van belang bij het correct uitvragen.",
                      "Het cijfer er onder geeft de connectie modus aan: 0 = niet verbinden, 1 = permanent verbinden, 2 = automatisch (enkel verbinding maken voor het verzenden van berichten)",
                      "Hieronder kan je de beschikbare netwerken invullen. Telkens over 2 regels waarbij de bovenste de naam (ssid) van het netwerk is en de onderste het wachtwoord.",
                      "ssid",
                      "wachtwoord"
};
