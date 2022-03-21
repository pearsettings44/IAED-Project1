#ifndef MAIN_H
#define MAIN_H

#define ID_LENGTH 4
#define COUNTRY_LENGTH 31
#define CITY_LENGTH 51
#define AIRPORT_MAX 40

#define UNDEFINED_AIRPORT ""

#define INVALID_AIPORT_ID -1
#define TOO_MANY_AIPORTS_ID -2
#define DUPLICATE_AIRPORT_ID -3

#define ERROR_INVALID_AIPORT_ID "invalid airport ID"
#define ERROR_TOO_MANY_AIPORTS "too many airports"
#define ERROR_DUPLICATE_AIRPORT "duplicate airport"

#define ERROR_NO_SUCH_AIRPORT_ID "%s: no such airport ID\n"

typedef struct
{
    char id[ID_LENGTH];
    char country[COUNTRY_LENGTH];
    char city[CITY_LENGTH];
} airport;

/* proj.c */
int handle_command();
void handle_add_airport_command(airport airports[]);
void handle_list_airports_command(airport airports[]);

/* airport.c */
void setup_airports(airport airports[]);
int add_airport(airport airports[], char id[], char country[], char city[]);
void list_all_airports(airport airports[]);

#endif