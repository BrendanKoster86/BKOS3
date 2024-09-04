void bouw_spel_mijnveger();
void run_spel_mijnveger();
void spel_mijnveger_veld_plaatsen(byte x_cnt, byte y_cnt, byte cnt);
void spel_mijnveger_veld_tekenen(int x, int y, int breedte, int hoogte, byte x_cnt, byte y_cnt);
void spel_mijnveger_bom_plaatsen(byte x_bom, byte y_bom, byte x_cnt, byte y_cnt);


void spel_mijnveger_veldje_kleuren(byte x_veld, byte y_veld, uint16_t kleur);
void spel_mijnveger_veldje_cijfer(byte x_veld, byte y_veld);
void spel_mijnveger_omliggende_velden(byte x_veld, byte y_veld);
void spel_mijnveger_draai(byte x_veld, byte y_veld);
void spel_mijnveger_bommen_tonen();
void spel_mijnveger_vakjes_heropenen(byte x_cnt, byte y_cnt);

byte** spel_mijnveger_mijnenveld;
byte spel_mijnveger_x_cnt;
byte spel_mijnveger_y_cnt;
int spel_mijnveger_dichte_velden;
int spel_mijnveger_bommen_cnt;


bool spel_actief = false;
