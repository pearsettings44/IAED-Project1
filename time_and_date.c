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