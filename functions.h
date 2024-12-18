#ifndef FUNCTIONS_H
#define FUNCTION_H

void read_file(void);
void write_file(void);
float down(int, float);
float principal(int, float);
float emi(float, int, int);
int display_emi(int);
int book(char*, char*, char*);
void display_booked(void);
void display_available(void);
int flatinfo(char*);
void pay(char*);
void flatinfoMenu();
void bookMenu();
void availableMenu();
void bookedMenu();
void paymentMenu();
void save();
void errors(int);
void backToMenu();
void menufn();


#endif