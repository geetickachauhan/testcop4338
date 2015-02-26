#include<stdio.h>
#include "lib.h"

/*
Method to calculate the best defense and the best offense value
*/
void C(List *list)
{
    // I'm assuming this game is baseball and I dont know how to play it 
    // so I'm not sure if best defence value is the highest value?
    // same for offense
    // let me know if its supposed to be the least value and I'll fix the
    // code accordingly
    float defense = 0, offense = 0; // assuming these are the current least defense and offense values
    char *nD, *nO; // name of the best defense and offense player
    for(int i = 0; i< list->filled; i++)
    {
        Player p = (list->players)[i]; // store the current player just to make code less complicated
        float currDefense = (p.RPG *5 + p.SPG *3)/ (p.MPG); //calculate current defense and offense
        float currOffense = (p.PPG + p.APG *2 + (p.RPG)/2)/ (p.MPG);
        if(currDefense > defense)
        {
            defense = currDefense; //store the largest defense value
            nD = p.name; // store the name of the player cause it will be needed later
        }
        if(currOffense > offense)
        {
            offense = currOffense;
            nO = p.name;
        }
    }
    printf("The best defense player is %s, with the defense value %f\n", nD, defense);
    printf("The best offense player is %s, with the offense value %f\n", nO,offense);
}