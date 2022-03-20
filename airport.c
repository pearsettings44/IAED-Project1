/* José Pereira - ist1103252 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "proj1.h"

void setup_airports(airport airports[])
{
    int counter;
    for (counter = 0; counter < AIRPORT_MAX; counter++)
    {
        strcpy(airports[counter].identity, UNDEFINED_AIRPORT);
    }
}

void add_airport(airport airports[], char identity[], char country[], char city[])
{
    int counter;
    for (counter = 0; counter < AIRPORT_MAX; counter++)
    {
        if (!(strcmp(airports[counter].identity, UNDEFINED_AIRPORT)))
        {
            strcpy(airports[counter].identity, identity);
            strcpy(airports[counter].country, country);
            strcpy(airports[counter].city, city);
            return;
        }
    }
}
