/* José Pereira - ist1103252 */
#include "proj1.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/**
 * Sets the value of all flights code to UNDEFINED_FLIGHT.
 */
void setup_flights(flight flights[])
{
    int counter;
    for (counter = 0; counter < FLIGHT_MAX; counter++)
    {
        strcpy(flights[counter].code, UNDEFINED_FLIGHT);
    }
}

/**
 * CHecks if the code is valid.
 */
int check_flight_code(char code[])
{
    int counter, code_length = strlen(code) - 1;
    if (!isupper(code[0]) || !isupper(code[1]))
        return INVALID_FLIGHT_CODE_ID;
    for (counter = 2; counter <= code_length; counter++)
    {
        if (!isdigit(code[counter]))
            return INVALID_FLIGHT_CODE_ID;
    }
    return 0;
}

/**
 * Check if there's already a flight with the same code on the same day.
 */
int check_same_day_flights(flight flights[], char code[], char date_departure[])
{
    int counter;
    for (counter = 0; counter < FLIGHT_MAX; counter++)
    {
        if (!(strcmp(flights[counter].code, code)))
        {
            if (!strcmp(flights[counter].date_departure, date_departure))
                return FLIGHT_ALREADY_EXISTS_ID;
        }
    }
    return 0;
}

int check_airport_departure_exist(airport airports[], char airport_departure[])
{
    int counter;
    for (counter = 0; counter < AIRPORT_MAX; counter++)
    {
        /* If it gets to UNDEFINED_AIRPORT, means it did not find the airport */
        if (!(strcmp(airports[counter].id, UNDEFINED_AIRPORT)))
            return NO_SUCH_AIRPORT_DEPARTURE_ID;

        /* Check if the ID already exists. */
        if (!(strcmp(airports[counter].id, airport_departure)))
        {
            break;
        }
    }
    return 0;
}

int check_airport_arrival_exist(airport airports[], char airport_arrival[])
{
    int counter;
    for (counter = 0; counter < AIRPORT_MAX; counter++)
    {
        /* If it gets to UNDEFINED_AIRPORT, means it did not find the airport */
        if (!(strcmp(airports[counter].id, UNDEFINED_AIRPORT)))
            return NO_SUCH_AIRPORT_ARRIVAL_ID;

        /* Check if the ID already exists. */
        if (!(strcmp(airports[counter].id, airport_arrival)))
        {
            break;
        }
    }
    return 0;
}

int check_dates(int date_departure_year, int date_departure_month,
                int date_departure_day, int current_year, int current_month,
                int current_day)
{
    /* Check if date is in the accepted range */
    if (date_departure_year > MAX_DATE_YEAR ||
        date_departure_year < MIN_DATE_YEAR)
    {
        return INVALID_DATE_ID;
    }
    /* Check is year difference is greater then 1 year */
    if (current_year - date_departure_year > 1)
    {
        return INVALID_DATE_ID;
    }
    /* Check if it's more then 1 year difference but less then 2 years. */
    if (date_departure_year < current_year)
    {
        if (date_departure_month < current_month)
        {
            return INVALID_DATE_ID;
        }
        if (date_departure_month == current_month)
        {
            if (date_departure_day < current_day)
            {
                return INVALID_DATE_ID;
            }
        }
    }
    /* Check dates in the same year */
    if (date_departure_year == current_year)
    {
        if (date_departure_month < current_month)
        {
            return INVALID_DATE_ID;
        }
        if (date_departure_month == current_month)
        {
            if (date_departure_day < current_day)
            {
                return INVALID_DATE_ID;
            }
        }
    }
    return 0;
}

int check_duration(char duration[])
{
    if ((duration[0] >= '1' && duration[1] > '2') ||
        (duration[0] == '1' && duration[1] == '2' &&
         (duration[3] != '0' || duration[4] != '0')))
        return INVALID_DURATION_ID;
    return 0;
}

int check_capacity(int capacity)
{
    if (capacity < MIN_CAPACITY || capacity > MAX_CAPACITY)
        return INVALID_CAPACITY_ID;
    return 0;
}
/**
 * Adds a flight to the system.
 * Returns the ID that represents a new flight.
 * If the flight code is invalid, returns INVALID_FLIGHT_CODE_ID.
 */
int add_flights(airport airports[], flight flights[], char code[],
                char airport_departure[],
                char airport_arrival[], char date_departure[],
                char time_departure[], char duration[], int capacity)
{
    int counter;
    int date_departure_year, date_departure_month, date_departure_day;
    int current_year, current_month, current_day;

    /* Check if the code is valid. */
    if (check_flight_code(code) == INVALID_FLIGHT_CODE_ID)
        return INVALID_FLIGHT_CODE_ID;
    /* Check if there's already a flight with the same code on the same day. */
    if (check_same_day_flights(flights, code, date_departure) ==
        FLIGHT_ALREADY_EXISTS_ID)
        return FLIGHT_ALREADY_EXISTS_ID;

    /* Check if both airports exist */
    if (check_airport_departure_exist(airports, airport_departure) ==
        NO_SUCH_AIRPORT_DEPARTURE_ID)
        return NO_SUCH_AIRPORT_DEPARTURE_ID;
    if (check_airport_arrival_exist(airports, airport_arrival) ==
        NO_SUCH_AIRPORT_ARRIVAL_ID)
        return NO_SUCH_AIRPORT_ARRIVAL_ID;

    /* Get date as ints  */
    date_departure_year = get_date_year(date_departure);
    date_departure_month = get_date_month(date_departure);
    date_departure_day = get_date_day(date_departure);

    current_year = get_date_year(date);
    current_month = get_date_month(date);
    current_day = get_date_day(date);

    /* Check if dates are valid */
    if (check_dates(date_departure_year, date_departure_month,
                    date_departure_day, current_year, current_month,
                    current_day) == INVALID_DATE_ID)
        return INVALID_DATE_ID;

    /* Check if duration is valid */
    if (check_duration(duration) == INVALID_DURATION_ID)
        return INVALID_DURATION_ID;

    /* Check if capacity is valid */
    if (check_capacity(capacity) == INVALID_CAPACITY_ID)
        return INVALID_CAPACITY_ID;

    for (counter = 0; counter < FLIGHT_MAX; counter++)
    {
        /* Check if a slot is available for a new flight. */
        if (!(strcmp(flights[counter].code, UNDEFINED_FLIGHT)))
        {
            strcpy(flights[counter].code, code);
            strcpy(flights[counter].airport_departure, airport_departure);
            strcpy(flights[counter].airport_arrival, airport_arrival);
            strcpy(flights[counter].date_departure, date_departure);
            strcpy(flights[counter].time_departure, time_departure);
            strcpy(flights[counter].duration, duration);
            flights[counter].capacity = capacity;
            return 0;
        }
    }
    return TOO_MANY_FLIGHTS_ID;
}

/**
 * Lists all flights in the system
 */
void list_all_flights(flight flights[])
{
    int counter;
    for (counter = 0; counter < FLIGHT_MAX &&
                      strcmp(flights[counter].code, UNDEFINED_FLIGHT);
         counter++)
        printf("%s %s %s %s %s\n", flights[counter].code,
               flights[counter].airport_departure,
               flights[counter].airport_arrival,
               flights[counter].date_departure,
               flights[counter].time_departure);
}
/**
 * Lists all flights with airport_departure of airport_id.
 */
void list_all_flights_from_departure(flight flights[], char airport_id[])
{
    int counter;
    for (counter = 0; counter < FLIGHT_MAX; counter++)
        {
            if (!strcmp(flights[counter].code, UNDEFINED_FLIGHT))
                break;
            if (!strcmp(flights[counter].airport_departure, airport_id))
            {
                printf("%s %s %s %s\n", flights[counter].code,
                       flights[counter].airport_arrival,
                       flights[counter].date_departure,
                       flights[counter].time_departure);
            }
        }
}

void list_all_flights_from_arrival(flight flights[], char airport_id[])
{
    int counter;
    for (counter = 0; counter < FLIGHT_MAX; counter++)
        {
            if (!strcmp(flights[counter].code, UNDEFINED_FLIGHT))
                break;
            if (!strcmp(flights[counter].airport_departure, airport_id))
            {
                printf("%s %s %s %s\n", flights[counter].code,
                       flights[counter].airport_departure,
                       flights[counter].date_departure,
                       flights[counter].time_departure);
            }
        }
}