/* José Pereira - ist1103252 */
#include "proj1.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

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

int get_time_hours(char char_time[])
{
    int counterAux = 0, counter;
    char hours[3];
    for (counter = 0; counter < 2; counter++)
    {
        hours[counterAux] = char_time[counter];
        counterAux++;
    }
    return atoi(hours);
}

int get_time_minutes(char char_time[])
{
    int counterAux = 0, counter;
    char minutes[3];
    for (counter = 0; counter < 2; counter++)
    {
        minutes[counterAux] = char_time[counter];
        counterAux++;
    }
    return atoi(minutes);
}

void get_arrival_time(char time_departure[], char duration[])
{
    int hours_departure, minutes_departure, hours_duration, minutes_duration;
    int arrival_hours, arrival_minutes;
    hours_departure = get_time_hours(time_departure);
    minutes_departure = get_time_minutes(time_departure);

    hours_duration = get_time_hours(duration);
    minutes_duration = get_time_minutes(duration);

    if (hours_departure + hours_duration >= 24)
    {
        arrival_hours = hours_departure + hours_duration - 24;
    }
    else
    {
        arrival_hours = hours_departure + hours_duration;
    }

    if (minutes_departure + minutes_duration >= 60)
    {
        arrival_minutes = (minutes_departure + minutes_duration) % 60;
        arrival_hours += 1;
    }
    else
    {
        arrival_minutes = minutes_departure + minutes_duration;
    }
}