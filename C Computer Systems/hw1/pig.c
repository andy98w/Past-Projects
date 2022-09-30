/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include "names.h"

#include <stdio.h>
#include <stdlib.h>
/*main section of code which will run the simulation of the pig game.*/
int main() {
    typedef enum { SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER } Position;
    const Position pig[7] = { SIDE, SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER, JOWLER

    };
    int numberofplayers = 0;
    int seed = 0;
    int input = 0;
    printf("How many players? ");
    /*checks for errors using scanf bool return*/
    if (scanf("%d", &input)) {
        if (input < 2 || input > 10) {
            fprintf(stderr, "Invalid number of players. Using 2 instead.\n");
            numberofplayers = 2;
        } else
            numberofplayers = input;
    } else {
        fprintf(stderr, "Invalid number of players. Using 2 instead.\n");
        numberofplayers = 2;
    }
    printf("Random seed: ");
    if (scanf("%d", &input)) {
        seed = input;
    } else {
        fprintf(stderr, "Invalid random seed. Using 2021 instead.\n");
        seed = 2021;
    }
    srandom(seed); /*sets random seed*/
    int scores[numberofplayers]; /*declares player score array*/
    int i = 0;
    for (i = 0; i < numberofplayers; i++)
        scores[i] = 0;
    for (i = 0; i < numberofplayers; i++) { /*runs the simulation*/
        printf("%s", names[i]);
        printf(" rolls the pig...");
        while (1) {
            char thing = pig[random() % 7];
            if (thing == SIDE) {
                printf(" pig lands on side");
                printf("\n");
                break;
            }
            if (thing == RAZORBACK) {
                scores[i] += 10;
                printf(" pig lands on back");
            }
            if (thing == TROTTER) {
                scores[i] += 10;
                printf(" pig lands upright");
            }
            if (thing == SNOUTER) {
                scores[i] += 15;
                printf(" pig lands on snout");
            }
            if (thing == JOWLER) {
                scores[i] += 5;
                printf(" pig lands on ear");
            }
            if (scores[i] >= 100) {
                printf("\n");
                printf("%s", names[i]);
                printf(" wins with ");
                printf("%d", scores[i]);
                printf(" points!");
                printf("\n");
                exit(0);
            }
        }
        if (i == numberofplayers - 1)
            i = -1; /*this is for when the last player takes their turn, it will return the counter to 0. I used -1 because the for loop will increment i again to 0.*/
    }
    return (0);
}
