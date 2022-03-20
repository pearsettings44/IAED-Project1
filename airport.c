/* José Pereira - ist1103252 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "proj1.h"

/**
 * Sets the value of all aiports identity to UNDEFINED_AIRPORT.
 */
void setup_airports(airport airports[])
{
    int counter;
    for (counter = 0; counter < AIRPORT_MAX; counter++)
    {
        strcpy(airports[counter].identity, UNDEFINED_AIRPORT);
    }
}

/**
 * Adds an airport to the system.
 * Returns the ID that represents a new airpor.
 * If the aiport identity is invalid, returns INVALID_AIRPORT_ID.
 * If the airport already exists, returns DUPLICATE_AIRPORT_ID.
 * If the system has no more slots for new airports,
 * returns TOO_MANY_AIRPORTS_ID.
 */
int add_airport(airport airports[], char identity[], char country[], char city[])
{
    int counter;
    for (counter = 0; counter < ID_LENGTH - 1; counter++)
    {
        /* Check if ID has anything else then uppercase chars. */
        if (islower(identity[counter]) || !isalpha(identity[counter]))
        {
            return INVALID_AIPORT_ID;
        }
    }

    for (counter = 0; counter < AIRPORT_MAX; counter++)
    {
        /* Check if the ID already exists. */
        if (!(strcmp(airports[counter].identity, identity)))
        {
            return DUPLICATE_AIRPORT_ID;
        }

        /* Check if a slot is available for a new airport. */
        if (!(strcmp(airports[counter].identity, UNDEFINED_AIRPORT)))
        {
            strcpy(airports[counter].identity, identity);
            strcpy(airports[counter].country, country);
            strcpy(airports[counter].city, city);
            return 0;
        }
    }

    return TOO_MANY_AIPORTS_ID;
}
