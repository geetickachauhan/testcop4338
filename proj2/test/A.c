#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "lib.h"

/*
Method to find a player in the list by name and then output all
statistics about the player by name. 
Duplicate names might be present so that is why I'm going all the 
way to the end of the list
*/
void A(List *list, const char *n)
{
    int num = 0; // number of players with the same name
    char *s = malloc(300 * sizeof(char)); //initially giving it 300 bytes
    if(s == NULL)
    {
        perror("Malloc failed");
        exit(0);
    }
    int i;
    for(i = 0; i<list->filled; i++)
    {
        Player p = get(list, i);
        if(strcmp(p.name, n) == 0)
        {
            //Geeticka: I am not sure if printf will print pointer to char
            // if I say %s
            if(num>1)
            {
                char *temp = realloc(s, num*300 * sizeof(char)); //reallocating more than 2 times the previous memory to store what is coming afterward
               // free(s); //technically we should be freeing the memory that was stored in s 
                // realloc gets more memory and then copties the contents of 
                if(temp != NULL)
                    s = temp;
            }
            num++;
            Player p = get(list, i);
            sprintf(s + strlen(s), "The statistics of %s (ID: %d) are:\n", n, p.id);
            sprintf(s + strlen(s), "%f point (s) per game;\n", p.PPG);
            sprintf(s + strlen(s),"%f assist (s) per game;\n", p.APG);
            sprintf(s + strlen(s), "%f rebound (s) per game;\n", p.RPG);
            sprintf(s + strlen(s), "%f steal (s) per game;\n", p.SPG);
            sprintf(s + strlen(s), "%s plays %f minute (s) per game;\n\n", n, p.MPG);
        }
    }
    // according to the output online, we're supposed to include this
    // statement before anything else, but we cannot determine the number
    // of players with the same name in the list until we have 
    // traversed the whole list. That is why I had to include this at the end
    // suggestions? do you think he cares if we have the following in the beginning
    // or the end?
    printf("\nThere are %d player (s) with the name %s\n", num, n);
    printf("%s", s);
    free(s);
}
