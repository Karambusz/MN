#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "nrutil.h"
#include "nrutil.c"
#include "bessi0.c"
#include "gauher.c"

# define M_PI 3.14159265358979323846

int main(void) {
    float *x1, *w1, *x2, *w2;
    FILE *file1;
	file1 = fopen("out.dat", "w");
    int n;
    float x20;
    float sigma = 1/sqrtf(2);

    for(n = 5; n <= 35; n += 5) {
        x1 = vector(1, n);
        w1 = vector(1, n);
        x2 = vector(1, n+1);
        w2 = vector(1, n+1);
        gauher(x1, w1, n);
        gauher(x2, w2, n+1);
        for(x20 = 0.1; x20 < 6.0001; x20 += 0.1) {
            float vnum = 0.0;
            for(int i = 1; i <= n; i++){
                for(int j = 1; j <= n+1; j++){
                    for(int k = 1; k <= n; k++){
                        for(int l = 1; l <= n+1; l++){
                            vnum+=(w1[i]*w2[j]*w1[k]*w2[l]) / (sqrt(pow(x1[i] - x2[j] + x20, 2) + pow(x1[k] - x2[l], 2)));
                        }
                    }
                }
            }
            float tmp = (pow(x20, 2)) / (8 * pow(sigma,2));
            float vdok = pow(2*M_PI, 2) * pow(sigma, 4) * (sqrt(M_PI) / (2 * sigma)) * exp(-tmp) * bessi0(tmp);
            float epsilon = fabsf((vdok - vnum) / vdok);
            fprintf(file1, "%g %g \n", x20, epsilon);
        }
        fprintf(file1, "\n\n");
        free_vector(x1, 1, n);
        free_vector(w1, 1, n);
        free_vector(x2, 1, n+1);
        free_vector(w2, 1, n+1);
    }

    fclose(file1);


    return 0;
}
