// coolness.c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LOWEST_T -99
#define LOWEST_V 0.5
#define HIGHEST_T 50
#define HiGHEST_V 15

// Simply calculates and does the formula to find the coolness
double final_calc_coolness(double T, double V) {
    double res = 35.74 + 0.6215 * T - 35.75 * pow(V, 0.16) + 0.4275 * T * pow(V, 0.16);
    return res;
}

// argic tells us the total count of command-line and argv holds an array that point indvidually to the commands
int main(int argc, char *argv[]) {
    if (argc == 1) {
        // No argument was provided so we increment temp from -10 up to 40 while also doing similar for windspeed
        printf("Temp\tWind\tCoolness\n"); // Align the headers 
        for (double T = -10.0; T <= 40.0; T += 10.0) {
	    if (T != -10.0) {
	        printf("\n");
	    }// I did this so there is a newline between different temp value
            for (double V = 5.0; V <= 15.0; V += 5.0) {
                printf("%.1lf\t%.1lf\t%.1lf\n", T, V, final_calc_coolness(T, V));
            }
        }
    } else if (argc == 2) {
        // Seems Temp is the only thing provided
        double T = atof(argv[1]);//put the result in a variable
        if (T >= LOWEST_T && T <= HIGHEST_T) {
            printf("Temp\tWind\tCoolness\n"); // Align the headers
            for (double V = 5.0; V <= 15.0; V += 5.0) {
                printf("%.1lf\t%.1lf\t%.1lf\n", T, V, final_calc_coolness(T, V));
            }
        } else {
            fprintf(stderr, "Error: Coolness. Acceptable input values are -99<=T<=50 and 0.5<=V.\n");
            return 1;
        }
    } else if (argc == 3) {
        // both of the needed values are provided
        double T = atof(argv[1]);
        double V = atof(argv[2]);
        if (T >= LOWEST_T && T <= HIGHEST_T && V >= LOWEST_V) {
	    printf("Temp\tWind\tCoolness\n"); // Align the headers
            printf("%.1lf\t%.1lf\t%.1lf\n", T, V, final_calc_coolness(T, V));
        } else {
            fprintf(stderr, "Error: Coolness. Acceptable input values are -99<=T<=50 and 0.5<=V.\n");
            return 1;
        }
    } else {
        fprintf(stderr, "Usage: ./coolness [temperature] [wind speed]\n");
        return 1;
    }

    return 0;
}

