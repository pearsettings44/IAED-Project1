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
    
    /* Check if the code is valid. */
    if (!isupper(code[0]) || !isupper(code[1]))
        return INVALID_FLIGHT_CODE_ID;
    for (counter = 2; counter <= code_length; counter++)
    {
        if (!isdigit(code[counter]))
        return INVALID_FLIGHT_CODE_ID;
    }

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