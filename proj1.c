/* José Pereira - ist1103252 */
#include "proj1.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* global variable: system date */
date system_date;
int main()
{
    airport airports[AIRPORT_MAX];
    flight flights[FLIGHT_MAX];
    system_date = setup_default_date(system_date);
    setup_airports(airports);
    setup_flights(flights);
    /* execute program until the user sends the 'q' command */
    while (handle_command(airports, flights, system_date))
    {
    }

    return 0;
}

/**
 * Handles command input.
 * Returns 1 if the program should continue after running the command.
 * Otherwise, returns 0.
 */
int handle_command(airport airports[], flight flights[], date system_date)
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
        handle_add_flight_command(airports, flights, system_date);
        return 1;
    case 'p':
        handle_list_flight_departure_command(airports, flights);
        return 1;
    case 'c':
        handle_list_flight_arrival_command(airports, flights);
        return 1;
    case 't':
        handle_forward_date_command();
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
    int i = 0;
    char c;
    char id[ID_LENGTH], country[COUNTRY_LENGTH], city[CITY_LENGTH];
    scanf("%s %s", id, country);
    c =getchar();
    while ((c = getchar()) != '\n' && i < CITY_LENGTH - 1)
    {
        city[i] = c;
        i++;
    }
    city[i] = '\0';

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
        /* Check if the ID already exists */
        if (counter == AIRPORT_MAX - 1)
        {
            printf(ERROR_NO_SUCH_AIRPORT_ID, id);
            empty++;
            continue;
            ;
        }
        else
        {
            printf("%s %s %s %d\n", airports[counter].id,
                   airports[counter].city, airports[counter].country,
                   airports[counter].flights_quantity);
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
void handle_add_flight_command(airport airports[], flight flights[],
                               date system_date)
{
    char c;
    char code[FLIGHT_CODE], airport_departure[ID_LENGTH],
        airport_arrival[ID_LENGTH];
    int departure_day, departure_month, departure_year;
    int departure_hour, departure_minutes;
    int duration_hour, duration_minutes;
    int capacity, value, counter, empty = 0;
    date date_departure;
    time time_departure, duration;

    while ((c = getchar()) != '\n')
    {
        scanf("%s %s %s %d-%d-%d %d:%d %d:%d %d", code, airport_departure,
              airport_arrival,
              &departure_day, &departure_month, &departure_year,
              &departure_hour, &departure_minutes,
              &duration_hour, &duration_minutes,
              &capacity);

        empty++;

        date_departure.day = departure_day;
        date_departure.month = departure_month;
        date_departure.year = departure_year;

        time_departure.hours = departure_hour;
        time_departure.minutes = departure_minutes;

        duration.hours = duration_hour;
        duration.minutes = duration_minutes;
    }

    /* If it's just the 'v' command without arguments */
    if (!empty)
    {
        list_all_flights(flights);
        return;
    }

    /* Add flight to the airport system */
    value = add_flights(airports, flights, code, airport_departure, airport_arrival,
                        date_departure, time_departure, duration, capacity,
                        system_date);

    switch (value)
    {
    case INVALID_FLIGHT_CODE_ID:
        printf(ERROR_INVALID_FLIGHT_CODE);
        break;
    case TOO_MANY_AIPORTS_ID:
        printf(ERROR_TOO_MANY_FLIGTS);
        break;
    case INVALID_DURATION_ID:
        printf(ERROR_INVALID_DURATION);
        break;
    case INVALID_CAPACITY_ID:
        printf(ERROR_INVALID_CAPACITY);
        break;
    case INVALID_DATE_ID:
        printf(ERROR_INVALID_DATE);
        break;
    case NO_SUCH_AIRPORT_DEPARTURE_ID:
        printf(ERROR_NO_SUCH_AIRPORT_ID, airport_departure);
        break;
    case NO_SUCH_AIRPORT_ARRIVAL_ID:
        printf(ERROR_NO_SUCH_AIRPORT_ID, airport_arrival);
        break;
    case FLIGHT_ALREADY_EXISTS_ID:
        printf(ERROR_FLIGHT_ALREADY_EXISTS);
        break;
    default:
        /* Add flight to the airport */
        for (counter = 0; counter < AIRPORT_MAX; counter++)
        {
            if (!(strcmp(airports[counter].id, airport_departure)))
            {
                airports[counter].flights_quantity += 1;
                break;
            }
        }
    }
}

/**
 * Handles the 'p' command.
 * Lists the flights with departure airport of IDairport.
 * input format: p <IDAirport>
 * output format: <code> <IDAirport Arrival> <date_departure> <time_departure>
 * If no arguments are passed, list all airport in ID's alphabetically order.
 * If multiplate arguments are passed, list airport in order of input.
 */
void handle_list_flight_departure_command(airport airports[], flight flights[])
{
    char airport_id[ID_LENGTH];
    scanf("%s", airport_id);

    if (check_airport_departure_exist(airports, airport_id) ==
        NO_SUCH_AIRPORT_DEPARTURE_ID)
        printf(ERROR_NO_SUCH_AIRPORT_ID, airport_id);
    else
    {
        list_flights_sorted_departure(flights, airport_id);
    }
}

/**
 * Handles the 'c' command.
 * Lists the flights with arrival airport of IDairport.
 * input format: p <IDAirport>
 * output format: <code> <IDAirport departure> <date_arrival> <time_arrival>
 * If no arguments are passed, list all airport in ID's alphabetically order.
 * If multiplate arguments are passed, list airport in order of input.
 */
void handle_list_flight_arrival_command(airport airports[], flight flights[])
{
    char airport_id[ID_LENGTH];
    scanf("%s", airport_id);

    if (check_airport_departure_exist(airports, airport_id) ==
        NO_SUCH_AIRPORT_DEPARTURE_ID)
        printf(ERROR_NO_SUCH_AIRPORT_ID, airport_id);
    else
    {
        list_flights_sorted_arrival(flights, airport_id);
    }
}

/**
 * Handles the 't' command.
 * Forwards the system date.
 * input format: t <date>
 * output format: <date>
 */
void handle_forward_date_command()
{
    int day, month, year;
    date new_date;
    scanf("%d-%d-%d", &day, &month, &year);
    new_date.day = day;
    new_date.month = month;
    new_date.year = year;
    if (check_dates(new_date, system_date) == INVALID_DATE_ID)
        printf(ERROR_INVALID_DATE);
    else
    {
        system_date.day = new_date.day;
        system_date.month = new_date.month;
        system_date.year = new_date.year;
        printf("%02d-%02d-%04d\n", system_date.day, system_date.month,
               system_date.year);
    }
}

