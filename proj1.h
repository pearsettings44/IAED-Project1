#ifndef MAIN_H
#define MAIN_H

/* constants */
#define ID_LENGTH 4
#define COUNTRY_LENGTH 31
#define CITY_LENGTH 51
#define AIRPORT_MAX 40

#define UNDEFINED_AIRPORT "zzz"

#define INVALID_AIPORT_ID -1
#define TOO_MANY_AIPORTS_ID -2
#define DUPLICATE_AIRPORT_ID -3

#define ERROR_INVALID_AIPORT_ID "invalid airport ID"
#define ERROR_TOO_MANY_AIPORTS "too many airports"
#define ERROR_DUPLICATE_AIRPORT "duplicate airport"
#define ADD_AIRPORT_SUCCESSFULLY "airport %s\n"

#define ERROR_NO_SUCH_AIRPORT_ID "%s: no such airport ID\n"

#define FLIGHT_CODE 7
#define FLIGHT_MAX 30000
#define UNDEFINED_FLIGHT "zzzzzz"
#define DATE_LENGTH 11
#define TIME_LENGTH 6

#define ERROR_INVALID_FLIGHT_CODE "invalid flight code"
#define ERROR_FLIGHT_ALREADY_EXISTS "flight already exists"
#define ERROR_TOO_MANY_FLIGTS "too many flights"
#define ERROR_INVALID_DATE "invalid date"
#define ERROR_INVALID_DURATION "invalid duration"
#define ERROR_INVALID_CAPACITY "invalid capacity"
#define ADD_FLIGHT_SCCESSFULLY "%s %s %s %s\n"

#define INVALID_FLIGHT_CODE_ID -1
#define TOO_MANY_FLIGHTS_ID -2

/* structs */
typedef struct
{
    char id[ID_LENGTH];
    char country[COUNTRY_LENGTH];
    char city[CITY_LENGTH];
} airport;

typedef struct
{
    char code[FLIGHT_CODE];
    char airport_departure[ID_LENGTH];
    char airport_arrival[ID_LENGTH];
    char date_departure[DATE_LENGTH];
    char time_departure[TIME_LENGTH];
    char duration[TIME_LENGTH];
    int capacity;
} flight;

/* proj.c */
int handle_command(airport airports[], flight flights[]);
void handle_add_airport_command(airport airports[]);
void handle_list_airports_command(airport airports[]);
void handle_add_flight_command(flight flights[]);

/* airport.c */
void setup_airports(airport airports[]);
int add_airport(airport airports[], char id[], char country[], char city[]);
void sort_airports(airport airports[]);
void list_all_airports(airport airports[]);

/* flights.c */
void setup_flights(flight flights[]);
int add_flights(flight flights[], char code[], char airport_departure[],
                char airport_arrival[], char date_departure[],
                char time_departure[], char duration[], int capacity);

#endif