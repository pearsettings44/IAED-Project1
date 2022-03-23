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
 * Get the date year in int type.
 */
int get_date_year(char char_date[])
{
    int counterAux = 0, len = strlen(char_date), counter;
    char year[5];
    for (counter = 6; counter < len; counter++)
    {
        year[counterAux] = char_date[counter];
        counterAux++;
    }
    return atoi(year);
}

/**
 * Get the date month in int type.
 */
int get_date_month(char char_date[])
{
    int counterAux = 0, counter;
    char month[3];
    for (counter = 3; counter < 5; counter++)
    {
        month[counterAux] = char_date[counter];
        counterAux++;
    }
    return atoi(month);
}

/**
 * Get the date year in int type.
 */
int get_date_day(char char_date[])
{
    int counterAux = 0, counter;
    char day[3];
    for (counter = 0; counter < 2; counter++)
    {
        day[counterAux] = char_date[counter];
        counterAux++;
    }
    return atoi(day);
}

/**
 * Adds a flight to the system.
 * Returns the ID that represents a new flight.
 * If the flight code is invalid, returns INVALID_FLIGHT_CODE_ID.
 */
int add_flights(flight flights[], char code[], char airport_departure[],
                char airport_arrival[], char date_departure[],
                char time_departure[], char duration[], int capacity)
{
    int counter;
    int code_length = strlen(code) - 1;
    int date_departure_year, date_departure_month, date_departure_day;
    int current_year, current_month, current_day;

    /* Check if the code is valid. */
    if (!isupper(code[0]) || !isupper(code[1]))
        return INVALID_FLIGHT_CODE_ID;
    for (counter = 2; counter <= code_length; counter++)
    {
        if (!isdigit(code[counter]))
            return INVALID_FLIGHT_CODE_ID;
    }
    /* Check if there's already a flight with the same code on the same day. */

    /* Check if both airports exist */
    

    /* Check if the date is valid  */
    date_departure_year = get_date_year(date_departure);
    date_departure_month = get_date_month(date_departure);
    date_departure_day = get_date_day(date_departure);

    current_year = get_date_year(date);
    current_month = get_date_month(date);
    current_day = get_date_day(date);

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

    /* Check if duration is valid */
    if ((duration[0] >= '1' && duration[1] > '2') ||
        (duration[0] == '1' && duration[1] == '2' &&
         (duration[3] != '0' || duration[4] != '0')))
        return INVALID_DURATION_ID;

    /* Check if capacity is valid */
    if (capacity < MIN_CAPACITY || capacity > MAX_CAPACITY)
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