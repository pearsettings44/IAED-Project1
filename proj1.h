#ifndef MAIN_H
#define MAIN_H

#define ID_LENGTH 3
#define COUNTRY_LENGTH 30
#define CITY_LENGTH 50
#define AIRPORT_MAX 40

typedef struct
{
    char identity[ID_LENGTH];
    char country[COUNTRY_LENGTH];
    char city[CITY_LENGTH];
} airport;


/* proj.c */
int handle_command();

#endif