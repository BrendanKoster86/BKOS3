void bouw_spel_boterkaaseneieren();
void spel_boterkaaseneieren_veld();
void spel_boterkaaseneieren_teken_symbool(int hokje);
void spel_boterkaaseneieren_beurt_computer();
int spel_boterkaaseneieren_winnen();
int spel_boterkaaseneieren_verlies_voorkomen();
int spel_boterkaaseneieren_willekeurig();
void spel_boterkaaseneieren_zet(int speler, int zet);
void spel_boterkaaseneieren_isergewonnen();
void spel_boterkaaseneieren_nieuwspel();
void spel_boterkaaseneieren_klik(int x, int y);
void spel_boterkaaseneieren_beurt_speler();
void run_spel_boterkaaseneieren();

int spel_boterkaaseneieren_status[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
String spel_boterkaaseneieren_winnen_opties[8] = {"012", "345", "678", "036", "147", "258", "048", "246"};
byte spel_boterkaaseneieren_beurt = 0;
