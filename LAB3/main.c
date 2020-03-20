#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 1000
#define m 5
#define max(X,Y) ((X)>(Y)? (X):(Y))
#define min(X,Y) ((X)<(Y)? (X):(Y))
#define abs(X) ((X)>0? (X):-(X))


void iloczynMW(double a[N][N], double wektor_x[N][1], double wektor_temp[N][1], const int n) {
	for(int i = 0; i < n; i++) {
		wektor_temp[i][0] = 0;
		for(int j = max(0, i - m); j <= min(i + m, n -1); j++) {
			wektor_temp[i][0] += (a[i][j] * wektor_x[j][0]); 
			}
		}
}

double iloczynSkalarny(double wektor_1[N][1], double wektor_2[N][1],const int n) {
	double wynik = 0.0;
	for(int i = 0; i < N; i++)
		wynik += wektor_1[i][0] * wektor_2[i][0];

	return wynik;  
}

void sumWektor(double wektor_1[N][1], double wektor_2[N][1], const int n) {
	for(int i =0; i < n; i++) 
		wektor_2[i][0] = wektor_1[i][0] + wektor_2[i][0];
}

int main(void) {

	
	double licznik = 0.0;
	double mianownik = 0.0;
	double alfa = 0.0;
	double A[N][N];
	double b[N][1];
	double x[N][1];
	double r[N][1];
	double temp[N][1];
	
	// zadanie 1
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			if(abs(i - j) > m){
				A[i][j] = 0.0;
			}
			else {
				A[i][j] = 1.0 / (1.0 + abs(i - j));
			}
		}
	}

	// zadanie 2
	for(int i = 0; i < N; i++)
		b[i][0] = i + 1;
	
	// zadanie 3
	
	int k = 0;

	// a) wektor x = 0
	/*for(int i = 0; i < N; i++)
		x[i][0] = 0.0;
	
	do {
		// r_{k}
		iloczynMW(A, x, temp, N); // iloczyn Ax
		// wektor r_{k}
		for(int i = 0; i < N; i++)
			r[i][0] = b[i][0] - temp[i][0];

		//alfa_{k}
		iloczynMW(A, r, temp, N); // iloczyn Ar
		licznik = iloczynSkalarny(r, r, N);
		mianownik = iloczynSkalarny(r, temp, N);
		alfa = licznik/mianownik;


		//x_{k+1}
		for(int i = 0; i < N; i++)
			temp[i][0] = r[i][0] * alfa;
		sumWektor(temp, x, N);

		k++;
		printf("%d ", k);
		printf("%.6f ",sqrt(iloczynSkalarny(r, r, N)));
		printf("%g ",alfa);
		printf("%.6f ",sqrt(iloczynSkalarny(x, x, N)));
		printf("\n");
	}while(sqrt(iloczynSkalarny(r, r, N)) > pow(10, -6)); */

	// b) x = 1.0
	for(int i = 0; i < N; i++)
		x[i][0] = 1.0;
	
	k = 0;

	do {
		// r_{k}
		iloczynMW(A, x, temp, N); // iloczyn Ax
		// wektor r_{k}
		for(int i = 0; i < N; i++)
			r[i][0] = b[i][0] - temp[i][0];

		//alfa_{k}
		iloczynMW(A, r, temp, N); // iloczyn Ar
		licznik = iloczynSkalarny(r, r, N);
		mianownik = iloczynSkalarny(r, temp, N);
		alfa = licznik/mianownik;


		//x_{k+1}
		for(int i = 0; i < N; i++)
			temp[i][0] = r[i][0] * alfa;
		sumWektor(temp, x, N);

		k++;
		printf("%d ", k);
		printf("%.6f ",sqrt(iloczynSkalarny(r, r, N)));
		printf("%g ",alfa);
		printf("%.6f ",sqrt(iloczynSkalarny(x, x, N)));
		printf("\n");
	}while(sqrt(iloczynSkalarny(r, r, N)) > pow(10, -6));

	return 0;
}