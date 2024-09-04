// String header_titel;
int header_vlak[4] = {0, 0, 240, 25};
String header_titel;

void header_plaatsen(String headertitel);
void achtergrond(uint16_t kleur);
void achtergrond(uint16_t kleur, bool plaats_home_knop);
void overligger(uint16_t kleur, int hoogte, int dicht);
void overligger(uint16_t kleur, int hoogte);
void header_alert();
void klik_header(int x, int y);
void klok_update();


long h_klok_millis;