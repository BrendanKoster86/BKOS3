/*
 * De bestanden en functies in deze map zijn ervoor om de software matige kant van de io (uitbreidingsmodulen) aan te sturen
 * 
 * De functies die hiervoor gebruikt worden zijn
 * io_schakel(poortNR)       : Schakelt de IO poort van aan naar uit en andersom tenzij deze in error modus zit
 * io_meeschakelen(poortNR)  : Kijkt wat er mee geschakeld moet worden nu de opgegeven poort is veranderd van status en schakelt deze ook mee.
 * io_rst_fuse(poortNR)      : Haalt de blokkade van de betreffende poort af en zet de instelling op uit
 * io_fusecheck()            : Controleert met de opgegeven instellingen of er geen zekeringen zijn doorgeslagen
 * io_invcheck()             : Controleert of geen uitgeschakelde of geblokkeerde aparaten stiekem toch ingeschakeld zijn en daarom verkeerd staan aangesloten
 */

#include "parameters.h"

void io_schakel(int poort);
void io_meeschakelen(int poort);
void io_rst_fuse(int poort);
void io_fusecheck();
void io_invcheck();
