/* José Pereira - ist1103252 */
#include "proj1.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

date setup_default_date(date system_date)
{
    system_date.day = STARTING_DATE_DAY;
    system_date.month = STARTING_DATE_MONTH;
    system_date.year = STARTING_DATE_YEAR;
    return system_date;
}

int check_dates(date departure_date, date system_date)
{
    /* Check if date is in the accepted range */
    if (departure_date.year > MAX_DATE_YEAR ||
        departure_date.year < MIN_DATE_YEAR)
    {
        return INVALID_DATE_ID;
    }
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

