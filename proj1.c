/* José Pereira - ist1103252 */
#include "proj1.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main()
{
    airport airports[AIRPORT_MAX];
    setup_airports(airports);
    /* execute program until the user sends the 'q' command */
    while (handle_command(airports))
    {
    }

    return 0;
}

/**
 * Handles command input.
 * Returns 1 if the program should continue after running the command.
 * Otherwise, returns 0.
 */
int handle_command(airport airports[])
{
    char command = getchar();
    switch (command)
    {
    case 'a':
        handle_add_airport_command(airports);
        return 1;
    case 'l':
        handle_list_airports_command(airports);
        return 1;
    case 'v':
        /* handle_add_flight_command(); */
        return 1;
    case 'p':
        /* handle_list_flight_departure_command(); */
        return 1;
    case 'c':
        /* handle_list_flight_arrival_command(); */
        return 1;
    case 't':
        /* handle_forward_date_command(); */
        return 1;
    case 'q':
        /* stop the program */
        return 0;
    default:
        /* ignore undefined commands */
        return 1;
    }
}

/**
 * Handles the 'a' command.
 * Adds to the system a new airport with the specified id, country and
 * city.
 * input format: a <IDAirport> <country> <city>
 * output format: airport <IDAirport>
 */
void handle_add_airport_command(airport airports[])
{
    int value;
    char id[ID_LENGTH], country[COUNTRY_LENGTH], city[CITY_LENGTH];
    scanf("%s %s %s", id, country, city);

    /* Add aiport to the airport system */
    value = add_airport(airports, id, country, city);

    if (value == INVALID_AIPORT_ID)
        printf(ERROR_INVALID_AIPORT_ID);
    else if (value == TOO_MANY_AIPORTS_ID)
        printf(ERROR_TOO_MANY_AIPORTS);
    else if (value == DUPLICATE_AIRPORT_ID)
        printf(ERROR_DUPLICATE_AIRPORT);
    else
        printf("airport %s\n", id);
}

/**
 * Handles the 'l' command.
 * Adds to the system a new airport with the specified id, country and
 * city.
 * input format: a <IDAirport> <country> <city>
 * output format: airport <IDAirport>
 */
void handle_list_airports_command(airport airports[])
{
    int counter, empty = 0;
    char c, id[ID_LENGTH];
    while ((c = getchar()) != '\n')
    {
        counter = 0;
        scanf("%s", id);
        while (strcmp(airports[counter].id, id) && counter < AIRPORT_MAX - 1)
            counter++;
        /* Check if the ID exists */
        if (counter == AIRPORT_MAX - 1)
            printf(ERROR_NO_SUCH_AIRPORT_ID, id);
        else
        {
            printf("%s %s %s\n", airports[counter].id,
                   airports[counter].country, airports[counter].city);
            empty++;
        }
    }
    /* If no IDs were provided, prints all airports. */
    if (!empty)
    {
        list_all_airports(airports);
    }
}