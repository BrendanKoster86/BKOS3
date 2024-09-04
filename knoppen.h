#include <string>
// /*
// Hieronder wordt gedefiniëerd wat er moet gebeuren als er op een knop wordt gedrukt.
// */
int aantal_knoppen = 0;          //  Het aantal knoppen waar doorheen geloopt moet worden
// int knoppen_positie[20][4] = {}; //  De positie van het klikbare gebied van de knoppen op het scherm (Dit mag afwijken van het tekengebied, omdat er bijvoorbeeld een tekst onder kan staan die ook klikbaar is)
// int knoppen_status[20] = {};  //  De status van de knop. Het eerste getal geeft het aantal mogelijke statussen aan en het 2e getal de werkelijke status
// char knoppen_actie[20][80] = {};   //  De gewenste uit te voeren actie wanneer de knop wordt ingedrukt.



// /*
// Hieronder wordt bewaard hoe knoppen moeten worden getekend. Bij het klikken op knoppen worden mogelijk de kleuren (bewust) aangepast
// Dit moet daarna weer worden hersteld naar het origineel, of evt. een andere kleur om daarmee ook de status aan te geven
// */
// int (*knoppen_teken_positie[][4]) = {};  // De tekenpositie van de knop
// uint16_t knoppen_basiskleur[20][20] = {};     // De basiskleur van de knop
// int knoppen_tekst_positie[20][2] = {};  // De tekstpositie t.o.v. de knop
// uint16_t knoppen_tekst_kleur[20][20] = {{tft.color565(235, 235, 100)}, {tft.color565(235, 235, 100)}, {tft.color565(235, 235, 100)}, {tft.color565(235, 235, 100)}, {tft.color565(235, 235, 100)}, {tft.color565(235, 235, 100)}, {tft.color565(235, 235, 100)}, {tft.color565(235, 235, 100)}, {tft.color565(235, 235, 100)}, {tft.color565(235, 235, 100)}, {tft.color565(235, 235, 100)}, {tft.color565(235, 235, 100)}};  //
// String knoppen_tekst[20] = {};          // De tekst die in of bij de knop moet staan

// // void knop_plaatsen(int knop_nummer);
// // void alle_knoppen_plaatsen();
// // void klik(int x, int y)


// class Vlak {
// public:
//   int X;
//   int Y;
//   int B;
//   int H;

//   Vlak(int x, int y, int b, int h) {
//     X = x;
//     Y = y;
//     B = b;
//     H = h;
//   }
// };

// class Knop {
// public:
//   Vlak Gebied;
//   Vlak Locatie;
//   uint16_t Kleur;
//   uint16_t Tekstkleur;
//   std::string Tekst;

//   byte Status;
  
  
//   Knop(Vlak gebied,Vlak locatie, uint16_t kleur, uint16_t tekstkleur, std::string tekst) {
//     Gebied = gebied;
//     Locatie = locatie;
//     Kleur = kleur;
//     Tekstkleur = tekstkleur;
//     Tekst = tekst;

//     Status = 0;
//   }
  
// };

int** knoppen_positie;
byte* knoppen_status;
int** knoppen_actie;
int** knoppen_teken_positie;
uint16_t** knoppen_basiskleur;
int** knoppen_tekst_positie;
uint16_t** knoppen_tekst_kleur;
char** knoppen_tekst;
char** knoppen_tekst2;



void knop_plaatsen(int knop_nummer);
void knop_plaatsen(int knop_nummer, bool tekst2);
void alle_knoppen_plaatsen();
void alle_knoppen_plaatsen(bool tekst2);
int klik(int x, int y);