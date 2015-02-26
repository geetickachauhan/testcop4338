#include<stdio.h>
#include "lib.h"

/*
Method to find a player in the list by name and then output all
statistics about the player by name. 
Duplicate names might be present so that is why I'm going all the 
way to the end of the list
*/
void A(List *list, char *n)
{
    int num = 0; // number of players with the same name
    for(int i = 0; i<list->filled; i++)
    {
        if(strcmp((list->players)[i].name, n) == 0)
        {
            //Geeticka: I am not sure if printf will print pointer to char
            // if I say %s
            num++;
            printf("The statistics of %s (ID: %d) are:\n", n, (list->players)[i].id);
            printf("%f point (s) per game;\n", (list->players)[i].PPG);
            printf("%f assist (s) per game;\n", (list->players)[i].APG);
            printf("%f rebound (s) per game;\n", (list->players)[i].RPG);
            printf("%f steal (s) per game;\n", (list->players)[i].SPG);
            printf("%s plays %f minute (s) per game;\n\n", n, (list->players)[i].MPG);
        }
    }
    // according to the output online, we're supposed to include this
    // statement before anything else, but we cannot determine the number
    // of players with the same name in the list until we have 
    // traversed the whole list. That is why I had to include this at the end
    // suggestions? do you think he cares if we have the following in the beginning
    // or the end?
    printf("There are %d player (s) with the name %s", num, n);
}
