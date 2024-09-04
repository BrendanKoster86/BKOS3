void bouw_tekstinvoer();
void bouw_tekstinvoer(String titel);
void bouw_tekstinvoer(byte max_lengtem, String beginwaarde);
void bouw_tekstinvoer(String titel, String beginwaarde);
void bouw_tekstinvoer(String titel, byte max_lengte, String beginwaarde);
void toetsen_aanmaken(byte aantal);
void toetsen_positie_maken(byte eerste_knop, byte laatste_knop, byte modus, int x, int y, int b, int h);
void tekstinvoer_toetsenbord_inhoud(int aantal_toetsen);
void toetsen_positie_spatie_maken(byte eerste_knop, byte laatste_knop, byte modus, int x, int y, int b, int h);
void tekstinvoer_toetsenbord_maken();
void tekstinvoer_invoer(char invoer);
void tekstinvoer_shift_actie();
void tekstinvoer_capslock_actie();
void tekstinvoer_backspace();
void tekstinvoer_knop_ingedrukt(int knop);
void run_tekstinvoer();

String tekst_invoer;
bool tekstinvoer_actief = false;
bool tekstinvoer_shift = false;
byte tekstinvoer_maximaal = 0;

byte toetsenbord_type = 0; // 0 = niet gekozen
                           // 1 = kleine letters
                           // 2 = hoofdletters
                           // 3 = speciale tekens 1
                           // 4 = speciale tekens 2
                           // 5 = cijfers

int** toetsenbord_toetsen;

char toetsenbord_knoppen[][113][10] = {
  {},
  {"@", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "<=",
 "<=>", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "[", "]", "ENTER",
 "CAP", "a", "s", "d", "f", "g", "h", "j", "k", "l", ";", "'", "\\",
  "^^", "z", "x", "c", "v", "b", "n", "m", ",", ".", "/", "^^"
  "CTRL", "123", "ALT", " ", "ALT", "SYM", "CTRL"}, 
  {"~", "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "_", "+", "<=",
 "<=>", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "{", "}", "ENTER",
 "CAP", "A", "S", "D", "F", "G", "H", "J", "K", "L", ":", "\"", "|",
  "^^", "Z", "X", "C", "V", "B", "N", "M", "<", ">", "?", "^^"
  "CTRL", "123", "ALT", " ", "ALT", "SYM", "CTRL"},
  {},
  {},
  {"abc", "/", "*", "-",
   "7", "8", "9", "+",
   "4", "5", "6",
   "1", "2", "3", "ENTER"
   "0",      "."          }
};
