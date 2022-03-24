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
 * Check if a airport of departure actually exists.
 */
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

/**
 * Check if a airport of arrival actually exists.
 */
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

/**
 * Check if there's already a flight with the same code on the same day.
 */
int check_same_day_flights(flight flights[], char code[], date date_departure)
{
    int counter;
    for (counter = 0; counter < FLIGHT_MAX; counter++)
    {
        if (!(strcmp(flights[counter].code, code)))
        {
            if (flights[counter].date_departure.day == date_departure.day &&
                flights[counter].date_departure.month == date_departure.month &&
                flights[counter].date_departure.year == date_departure.year)
                return FLIGHT_ALREADY_EXISTS_ID;
        }
    }
    return 0;
}

/**
 * Check if duration is no longer than the accepted time limit.
 */
int check_duration(time duration)
{
    if (duration.hours > 12 || (duration.hours == 12 && duration.minutes != 0))
        return INVALID_DURATION_ID;
    return 0;
}

/**
 * Check if the capacity is in the accepted range.
 */
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
                char airport_arrival[], date date_departure,
                time time_departure, time duration, int capacity,
                date system_date)
{
    int counter;

    /* Check if the code is valid. */
    if (check_flight_code(code) == INVALID_FLIGHT_CODE_ID)
        return INVALID_FLIGHT_CODE_ID;

    /* Check if there's already a flight with the same code on the same day. */
    if (check_same_day_flights(flights, code, date_departure))
        return FLIGHT_ALREADY_EXISTS_ID;

    /* Check if both airports exist */
    if (check_airport_departure_exist(airports, airport_departure) ==
        NO_SUCH_AIRPORT_DEPARTURE_ID)
        return NO_SUCH_AIRPORT_DEPARTURE_ID;
    if (check_airport_arrival_exist(airports, airport_arrival) ==
        NO_SUCH_AIRPORT_ARRIVAL_ID)
        return NO_SUCH_AIRPORT_ARRIVAL_ID;

    /* Check if dates are valid */
    if (check_dates(date_departure, system_date) == INVALID_DATE_ID)
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
            flights[counter].date_departure.day = date_departure.day;
            flights[counter].date_departure.month = date_departure.month;
            flights[counter].date_departure.year = date_departure.year;
            flights[counter].time_departure.hours = time_departure.hours;
            flights[counter].time_departure.minutes = time_departure.minutes;
            flights[counter].duration.hours = duration.hours;
            flights[counter].duration.minutes = duration.minutes;
            flights[counter].capacity = capacity;
            return 0;
        }
    }
    return TOO_MANY_FLIGHTS_ID;
}

/**
 * Sorts flights by date and time.
 */
void sort_flights(flight flights[], int len)
{
    int counter, counterAux;
    flight temp_flight;
    for (counterAux = 0; counterAux < len - 1; counterAux++)
    {
        for (counter = 0; counter < len -1 ; counter++)
        {
            /* Sort airports by date and time */

            if (find_older_date(flights[counter].date_departure,
                                flights[counter + 1].date_departure,
                                flights[counter].time_departure,
                                flights[counter + 1].time_departure) ==
                DATE2_IS_CLOSER)
            {
                temp_flight = flights[counter];
                flights[counter] = flights[counter + 1];
                flights[counter + 1] = temp_flight;
            }
        }
    }
}

/**
 * Lists all flights in the system
 */
void list_all_flights_sorted(flight flights[])
{
    int len = 0;
    flight flights_aux[FLIGHT_MAX];
    int counter;

    for (counter = 0; counter < FLIGHT_MAX; counter++)
    {
        if (!strcmp(flights[counter].code, UNDEFINED_FLIGHT))
            break;
        strcpy(flights_aux[counter].code,
               flights[counter].code);
        strcpy(flights_aux[counter].airport_arrival,
               flights[counter].airport_arrival);
        strcpy(flights_aux[counter].airport_departure,
               flights[counter].airport_departure);

        flights_aux[counter].date_departure.day = flights[counter].date_departure.day;
        flights_aux[counter].date_departure.month = flights[counter].date_departure.month;
        flights_aux[counter].date_departure.year = flights[counter].date_departure.year;

        flights_aux[counter].time_departure.hours = flights[counter].time_departure.hours;
        flights_aux[counter].time_departure.minutes = flights[counter].time_departure.minutes;
        len++;
    }
    sort_flights(flights_aux, len);
    for (counter = 0; counter < len; counter++)
        printf("%s %s %s %02d-%02d-%d %02d:%02d\n", flights_aux[counter].code,
               flights_aux[counter].airport_departure,
               flights_aux[counter].airport_arrival,
               flights_aux[counter].date_departure.day,
               flights_aux[counter].date_departure.month,
               flights_aux[counter].date_departure.year,
               flights_aux[counter].time_departure.hours,
               flights_aux[counter].time_departure.minutes);
}

/**
 * Lists all flights in the system, by creation date
 */
void list_all_flights(flight flights[])
{
    int counter;
    for (counter = 0; counter < FLIGHT_MAX &&
                      strcmp(flights[counter].code, UNDEFINED_FLIGHT);
         counter++)
        printf("%s %s %s %02d-%02d-%d %02d:%02d\n", flights[counter].code,
               flights[counter].airport_departure,
               flights[counter].airport_arrival,
               flights[counter].date_departure.day,
               flights[counter].date_departure.month,
               flights[counter].date_departure.year,
               flights[counter].time_departure.hours,
               flights[counter].time_departure.minutes);
}
