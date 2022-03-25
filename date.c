/* José Pereira - ist1103252 */
#include "proj1.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/**
 * Initialize the system date with default values.
 */
date setup_default_date(date system_date)
{
    system_date.day = STARTING_DATE_DAY;
    system_date.month = STARTING_DATE_MONTH;
    system_date.year = STARTING_DATE_YEAR;
    return system_date;
}

/**
 * Check if the date is valid.
 */
int check_dates(date departure_date, date system_date)
{
    /* Check if date is in the accepted range */
    if (departure_date.year > MAX_DATE_YEAR ||
        departure_date.year < MIN_DATE_YEAR)
    {
        return INVALID_DATE_ID;
    }
    if (departure_date.year == MAX_DATE_YEAR && (departure_date.month != 1 ||
                                                 departure_date.day != 1))
        return INVALID_DATE_ID;
    /* Check is year difference is greater then 1 year */
    if (system_date.year - departure_date.year > 1)
    {
        return INVALID_DATE_ID;
    }
    /* Check if it's more then 1 year difference but less then 2 years. */
    if (departure_date.year < system_date.year)
    {
        if (departure_date.month < system_date.month)
        {
            return INVALID_DATE_ID;
        }
        if (departure_date.month == system_date.month)
        {
            if (departure_date.day < system_date.day)
            {
                return INVALID_DATE_ID;
            }
        }
    }
    /* Check dates in the same year */
    if (departure_date.year == system_date.year)
    {
        if (departure_date.month < system_date.month)
        {
            return INVALID_DATE_ID;
        }
        if (departure_date.month == system_date.month)
        {
            if (departure_date.day < system_date.day)
            {
                return INVALID_DATE_ID;
            }
        }
    }
    return 0;
}

/**
 * Find the older date.
 */
int find_older_date(date date1, date date2, time time1, time time2)
{
    if (date2.year < date1.year)
        return DATE2_IS_CLOSER;
    else if (date2.month < date1.month)
        return DATE2_IS_CLOSER;
    else if (date2.day < date1.day)
        return DATE2_IS_CLOSER;
    else if (date2.day == date1.day)
    {
        if (time2.hours < time1.hours)
            return DATE2_IS_CLOSER;
        else if (time2.hours == time1.hours)
        {
            if (time2.minutes < time1.minutes)
                return DATE2_IS_CLOSER;
            else
                return 0;
        }
    }
    else
    {
        return 0;
    }
    return 0;
}

time forward_time(time time_departure, time duration)
{
    time time_arrival;
    int time_hours, time_minutes, duration_hours, duration_minutes;
    int time_arrival_hours = 0, time_arrival_minutes = 0;
    time_hours = time_departure.hours;
    time_minutes = time_departure.minutes;
    duration_hours = duration.hours;
    duration_minutes = duration.minutes;

    if (time_minutes + duration_minutes > 59)
    {
        time_arrival_minutes = (time_minutes + duration_minutes) % 60;
        time_arrival_hours += 1;
    }
    else
    {
        time_arrival_minutes = time_minutes + duration_minutes;
    }

    if (time_hours + duration_hours > 23)
    {
        time_arrival_hours -= 24;
        time_arrival_hours += duration_hours + time_hours;
    }
    else
    {
        time_arrival_hours += time_hours + duration_hours;
    }

    time_arrival.hours = time_arrival_hours;
    time_arrival.minutes = time_arrival_minutes;
    return time_arrival;
}

date forward_date(date date_departure)
{
    int year, month, day;
    date arrival;
    year = date_departure.year, month = date_departure.month;
    day = date_departure.day;

    /* If the next day is a new year */
    if (day == 31 && month == DEC)
    {
        arrival.year = year + 1;
        arrival.month = 1;
        arrival.day = 1;
        return arrival;
        /* If the next day is a new month of a 31 days month. */
    }
    else if (day == 31 && (month == JAN || month == MAR || month == MAY ||
                           month == JUL || month == AUG || month == OUT))
    {
        arrival.day = 1;
        arrival.month = month + 1;
        arrival.year = year;
        return arrival;
    }
    /* If the next day is a new month of a 30 days month. */
    else if (day == 30 && (month == APR || month == JUN || month == SEP ||
                           month == NOV))
    {
        arrival.day = 1;
        arrival.month = month + 1;
        arrival.year = year;
        return arrival;
    }
    /* If the next day is a new month of a 28 days month. */
    else if (day == 28 && month == 2)
    {
        arrival.day = 1;
        arrival.month = month + 1;
        arrival.year = year;
        return arrival;
    }
    else
    {
        arrival.day = day + 1;
        arrival.month = month;
        arrival.year = year;
        return arrival;
    }
}
