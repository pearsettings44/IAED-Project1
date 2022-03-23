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

#define ERROR_INVALID_AIPORT_ID "invalid airport ID\n"
#define ERROR_TOO_MANY_AIPORTS "too many airports\n"
#define ERROR_DUPLICATE_AIRPORT "duplicate airport\n"
#define ADD_AIRPORT_SUCCESSFULLY "airport %s\n"

#define ERROR_NO_SUCH_AIRPORT_ID "%s: no such airport ID\n"

#define FLIGHT_CODE 7
#define FLIGHT_MAX 30000
#define UNDEFINED_FLIGHT "zzzzzz"
#define DATE_LENGTH 11
#define TIME_LENGTH 6

#define INVALID_FLIGHT_CODE_ID -1
#define TOO_MANY_FLIGHTS_ID -2
#define INVALID_DURATION_ID -3
#define INVALID_CAPACITY_ID -4
#define INVALID_DATE_ID -5
#define NO_SUCH_AIRPORT_DEPARTURE_ID -6
#define NO_SUCH_AIRPORT_ARRIVAL_ID -7
#define FLIGHT_ALREADY_EXISTS_ID -8

#define ERROR_INVALID_FLIGHT_CODE "invalid flight code\n"
#define ERROR_FLIGHT_ALREADY_EXISTS "flight already exists\n"
#define ERROR_TOO_MANY_FLIGTS "too many flights\n"
#define ERROR_INVALID_DATE "invalid date\n"
#define ERROR_INVALID_DURATION "invalid duration\n"
#define ERROR_INVALID_CAPACITY "invalid capacity\n"

#define STARTING_DATE "01-01-2021"
#define MAX_DATE_YEAR 2023
#define MIN_DATE_YEAR 2021

/* global variable: system date */
extern char date[DATE_LENGTH];

#define MIN_CAPACITY 10
#define MAX_CAPACITY 100

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
void handle_add_flight_command(airport airports[], flight flights[]);

/* airport.c */
void setup_airports(airport airports[]);
int add_airport(airport airports[], char id[], char country[], char city[]);
void sort_airports(airport airports[]);
void list_all_airports(airport airports[]);

/* flights.c */
void setup_flights(flight flights[]);
int get_date_year(char char_date[]);
int get_date_month(char char_date[]);
int add_flights(airport airports[], flight flights[], char code[],
                char airport_departure[],
                char airport_arrival[], char date_departure[],
                char time_departure[], char duration[], int capacity);
void list_all_flights(flight flights[]);

#endif