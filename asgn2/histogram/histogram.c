#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BINS_TOTAL 16

int main() {
    int array_bins[BINS_TOTAL] = {0};
    int largeness = 1;
    int span = largeness * BINS_TOTAL;

    printf("%d bins of size %d for range [%d,%d)\n", BINS_TOTAL, largeness, 0, span);

    while (1) {
        int input_number;
        if (scanf("%d", &input_number) == 1) {
            if (input_number >= span) {
                while (input_number >= span) {
		   // printf("bins[] = [");
               	   // for (int i = 0; i < NUM_BINS; i++) {
                   //     printf("%d", bins[i]);
                   //     if (i < NUM_BINS - 1) {
                   //         printf(", ");
                   //     }
                   // }
		   // printf("]\n");
                    
                    int j = 0;

                    for (int i = 0; i < BINS_TOTAL; i += 2) {
			array_bins[j] = array_bins[i] + array_bins[i + 1];
			j += 1;

		    }
		    for (int i = 0; i < BINS_TOTAL / 2; i++) {
		        array_bins[i + (BINS_TOTAL / 2)] = 0;
		    }

                    largeness *= 2;
                    span = largeness * BINS_TOTAL;
		    printf("%d bins of size %d for range [%d,%d)\n", BINS_TOTAL, largeness, 0, span);
		    //printf("bins[] = [");
                    //for (int i = 0; i < NUM_BINS; i++) {
                    //    printf("%d", bins[i]);
                    //    if (i < NUM_BINS - 1) {
                    //        printf(", ");
                    //    }
                    //}
                    //printf("]\n");
                }
                
            }

            array_bins[input_number / largeness]++;
        } else if (feof(stdin)) {
            break;
        }
    }

    for (int i = 0; i < BINS_TOTAL; i++) {
        int low_of_bin = i * largeness;
        int high_of_bin = (i + 1) * largeness;
        printf("[%3d:%3d] ", low_of_bin, high_of_bin - 1);
        for (int j = 0; j < array_bins[i]; j++) {
            printf("*");
        }
    printf("\n");
    }


    return 0;
}

