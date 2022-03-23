/* José Pereira - ist1103252 */
#include "proj1.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char date[DATE_LENGTH] = STARTING_DATE;

int main()
{
    airport airports[AIRPORT_MAX];
    flight flights[FLIGHT_MAX];
    setup_airports(airports);
    setup_flights(flights);
    /* execute program until the user sends the 'q' command */
    while (handle_command(airports, flights))
    {
    }

    return 0;
}

/**
 * Handles command input.
 * Returns 1 if the program should continue after running the command.
 * Otherwise, returns 0.
 */
int handle_command(airport airports[], flight flights[])
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
        handle_add_flight_command(airports, flights);
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
    char c;
    char id[ID_LENGTH], country[COUNTRY_LENGTH], city[CITY_LENGTH] = {0},
                                                 cityaux[CITY_LENGTH];
    scanf("%s %s", id, country);
    while ((c = getchar()) != '\n')
    {
        scanf("%s", cityaux);
        /* If the city has more then one word */
        if (c == ' ')
        {
            strcat(cityaux, " ");
        }
        strcat(city, cityaux);
    }

    /* Add aiport to the airport system */
    value = add_airport(airports, id, country, city);

    if (value == INVALID_AIPORT_ID)
        printf(ERROR_INVALID_AIPORT_ID);
    else if (value == TOO_MANY_AIPORTS_ID)
        printf(ERROR_TOO_MANY_AIPORTS);
    else if (value == DUPLICATE_AIRPORT_ID)
        printf(ERROR_DUPLICATE_AIRPORT);
    else
        printf(ADD_AIRPORT_SUCCESSFULLY, id);
}

/**
 * Handles the 'l' command.
 * Lists the airports.
 * input format: l [<IDAairport> <IDAirport> ...]
 * output format: <IDAirport> <city> <country> #flights
 * If no arguments are passed, list all airport in ID's alphabetically order.
 * If multiplate arguments are passed, list airport in order of input.
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
                   airports[counter].city, airports[counter].country);
            empty++;
        }
    }
    /* If it's just the 'l' command without arguments */
    if (!empty)
    {
        sort_airports(airports);
        list_all_airports(airports);
    }
}

/**
 * Handles the 'v' command.
 * Adds a flight to the system or lists all flights.
 * input format: v [<code> <airport_departure> <airport_arrival>
 * <date_departure> <time_departure> <duration> <capacity>]
 * output format: <code> <airport_departure> <airport_arrival>
 * <date_departure> <time_departure>
 * If no arguments are passed, list all flights.
 */
void handle_add_flight_command(airport airports[], flight flights[])
{
    char c;
    char code[FLIGHT_CODE], airport_departure[ID_LENGTH],
        airport_arrival[ID_LENGTH], date_departure[DATE_LENGTH],
        time_departure[TIME_LENGTH], duration[TIME_LENGTH];
    int capacity, value, empty = 0;

    while ((c = getchar()) != '\n')
    {
        scanf("%s %s %s %s %s %s %d", code, airport_departure, airport_arrival,
              date_departure, time_departure, duration, &capacity);
        empty++;
    }

    /* If it's just the 'v' command without arguments */
    if (!empty)
    {
        list_all_flights(flights);
        return;
    }

    /* Add flight to the airport system */
    value = add_flights(airports, flights, code, airport_departure, airport_arrival,
                        date_departure, time_departure, duration, capacity);

    if (value == INVALID_FLIGHT_CODE_ID)
        printf(ERROR_INVALID_FLIGHT_CODE);
    if (value == TOO_MANY_AIPORTS_ID)
        printf(ERROR_TOO_MANY_FLIGTS);
    if (value == INVALID_DURATION_ID)
        printf(ERROR_INVALID_DURATION);
    if (value == INVALID_CAPACITY_ID)
        printf(ERROR_INVALID_CAPACITY);
    if (value == INVALID_DATE_ID)
        printf(ERROR_INVALID_DATE);
    if (value == NO_SUCH_AIRPORT_DEPARTURE_ID)
        printf(ERROR_NO_SUCH_AIRPORT_ID, airport_departure);
    if (value == NO_SUCH_AIRPORT_ARRIVAL_ID)
        printf(ERROR_NO_SUCH_AIRPORT_ID, airport_arrival);
    if (value == FLIGHT_ALREADY_EXISTS_ID)
        printf(ERROR_FLIGHT_ALREADY_EXISTS);
}