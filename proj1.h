#ifndef MAIN_H
#define MAIN_H

#define ID_LENGTH 4
#define COUNTRY_LENGTH 31
#define CITY_LENGTH 51
#define AIRPORT_MAX 40

typedef struct
{
    char identity[ID_LENGTH];
    char country[COUNTRY_LENGTH];
    char city[CITY_LENGTH];
} airport;

/* proj.c */
int handle_command();
void handle_add_airport_command(airport airports[]);

/* airport.c */


#endif