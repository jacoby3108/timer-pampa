
#ifndef OLED_H
#define OLED_H
void Oled_setup(void);
void pirtext(int status);
void magtext(int status);
void sun(int status);
void print_count(int count,int cmd);

#define ON  1
#define OFF 0

#define D_INIT  0
#define D_SHOW  1
#define D_OFF   2

#endif
