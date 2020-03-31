#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "nrutil.h"
#include "nrutil.c"
#include "tred2.c"
#include "tqli.c"


void print_matrix(float** Matrix, const int N) //wyswietla macierze
{
	
	printf("\n");
	for(int i = 1; i <=N; i++)
	{
		for(int j = 1; j <= N; j++)
		{
			printf("%10g ", Matrix[i][j]);
		}
		printf("\n");
	}	
    printf("\n");
}

void print_vector(float *vector, const int N) {
    printf("\n");
    for(int i = 1; i <= N; i++) {
        printf("%g \n", vector[i]);
    }
    printf("\n");
}



int main(void) {
    const int n = 5;
    float **A, *d, *e, **I, **x, **A_copy;

    A = matrix(1, n, 1, n);
    I = matrix(1, n, 1, n);
    d = vector(1, n);
    e = vector(1, n);
    x = matrix(1, n, 1, n);
    A_copy = matrix(1, n, 1, n);

    // zadanie 1
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            A[i][j] = sqrt(i+j);
            A_copy[i][j] = A[i][j];
        }
    }
    // zadanie 2
    tred2(A, n, d, e);
    // zadanie 3
    printf("Macierz przekształcenia P: \n");
    print_matrix(A, n);
    // zadanie 4
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <=n; j++) {
            I[i][j] = 0;
        }
        I[i][i] = 1;
    }
    tqli(d, e, n, I);
    // zadanie 5
    printf("Wartosci własne macierzy T:\n");
    print_vector(d, n);
    printf("Wektory własne macierzy T:(kolumna - wektor)");
    print_matrix(I, n);
    // zadanie 6
    for(int i = 1; i <= n; i++){
        for(int j =1; j <= n; j++){
            x[i][j] = 0;
            for(int k = 1; k <= n; k++){
                x[i][j] += A[i][k] * I[k][j];
            }
        }
    }
    printf("Wektory własne macierzy A:(kolumna - wektor) \n");
    print_matrix(x, n);
    // zadanie 7
    float *licznik, *mianownik, *b;
    licznik = vector(1 , n);
    mianownik = vector(1, n);
    b = vector(1, n);
	
	for(int i = 1; i <= n; i++) {
        licznik[i] = 0;
        mianownik[i] = 0;
        b[i] = 0;
		for(int j = 1; j <= n; j++) {
            mianownik[i] += x[j][i]*x[j][i]; 
			for(int k = 1; k <= n; k++) {
					licznik[i]+= x[j][i]*A_copy[j][k]*x[k][i];
            }
        }
    }
	
	for(int i=1; i<=n; i++)
		b[i]=licznik[i]/mianownik[i];

    printf("Wartosci B: \n");
    print_vector(licznik, n);

    free_matrix(A, 1, n, 1, n);
    free_matrix(A_copy, 1, n, 1, n);
    free_matrix(I, 1, n, 1, n);
    free_matrix(x, 1, n, 1, n);
    free_vector(d, 1, n);
    free_vector(e, 1, n);
    free_vector(licznik, 1, n);
    free_vector(mianownik, 1, n);
    free_vector(b, 1, n);

    return 0;
}