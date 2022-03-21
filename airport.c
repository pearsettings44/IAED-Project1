/* José Pereira - ist1103252 */
#include "proj1.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/**
 * Sets the value of all aiports id to UNDEFINED_AIRPORT.
 */
void setup_airports(airport airports[])
{
    int counter;
    for (counter = 0; counter < AIRPORT_MAX; counter++)
    {
        strcpy(airports[counter].id, UNDEFINED_AIRPORT);
    }
}

/**
 * Adds an airport to the system.
 * Returns the ID that represents a new airpor.
 * If the aiport id is invalid, returns INVALID_AIRPORT_ID.
 * If the airport already exists, returns DUPLICATE_AIRPORT_ID.
 * If the system has no more slots for new airports,
 * returns TOO_MANY_AIRPORTS_ID.
 */
int add_airport(airport airports[], char id[], char country[], char city[])
{
    int counter;
    for (counter = 0; counter < ID_LENGTH - 1; counter++)
    {
        /* Check if ID has anything else then uppercase chars. */
        if (islower(id[counter]) || !isalpha(id[counter]))
        {
            return INVALID_AIPORT_ID;
        }
    }

    for (counter = 0; counter < AIRPORT_MAX; counter++)
    {
        /* Check if the ID already exists. */
        if (!(strcmp(airports[counter].id, id)))
        {
            return DUPLICATE_AIRPORT_ID;
        }

        /* Check if a slot is available for a new airport. */
        if (!(strcmp(airports[counter].id, UNDEFINED_AIRPORT)))
        {
            strcpy(airports[counter].id, id);
            strcpy(airports[counter].country, country);
            strcpy(airports[counter].city, city);
            return 0;
        }
    }

    return TOO_MANY_AIPORTS_ID;
}

/**
 * Sorts the aiports by their ID, in alphabetical order.
 */
void sort_airports(airport airports[])
{
    int counter, counterAux;
    airport temp_airport;

    /* Loop through airports */
    for (counterAux = 0; counterAux < AIRPORT_MAX - 1; counterAux++)
    {
        /* Loop through airports ID */
        for (counter = 0; counter < AIRPORT_MAX - 1; counter++)
        {
            /* Sort airports by alphabetical order of the ID */
            if (strcmp(airports[counter].id, airports[counter + 1].id) > 0)
            {
                temp_airport = airports[counter];
                airports[counter] = airports[counter + 1];
                airports[counter + 1] = temp_airport;
            }
        }
    }
}

/**
 * Lists all aiports in the system.
 */
void list_all_airports(airport airports[])
{
    int counter;
    for (counter = 0; counter < AIRPORT_MAX &&
                      strcmp(airports[counter].id, UNDEFINED_AIRPORT);
         counter++)
        printf("%s %s %s\n", airports[counter].id,
               airports[counter].country, airports[counter].city);
}