long laatste_app = 0;
int levens_timer = 1440;

byte statusupdate_timer_array_cnt;
byte** statusupdate_timer_array; //[][2] = {{8, 0}, {8,30}, {9,0}, {10, 0}, {12, 0}, {15,0}, {17,0}, {20, 0}};

long timer_statusupdate;

void statusupdate();
void statusupdate_set_timer();