#include <stdio.h>
#include <math.h>
#include <time.h>
#include </usr/include/gsl/gsl_math.h>
#include </usr/include/gsl/gsl_linalg.h>

const double sigma = 4.0;
const double x0 = 2.0;

double funkcja(double x, double alfa){
    double a0 = -pow(x0, 2) / (2 * pow(sigma, 2));
    double a1 = x0 / pow(sigma, 2);
    double a2 = -1 / (2 * pow(sigma, 2));
    double U = rand() / (RAND_MAX + 1.0);

    return exp(a0 + a1*x + a2*pow(x,2)) * (1.0 + alfa * (U - 0.5));
}

double funkcjaG(double x, gsl_vector *vector){
    double b0 = gsl_vector_get(vector, 0);
    double b1 = gsl_vector_get(vector, 1);
    double b2 = gsl_vector_get(vector, 2);
    double b3 = gsl_vector_get(vector, 3);

    return exp(b0 + b1*x + b2*pow(x,2) + b3*pow(x,3));

}

double odleglosc(double n){
    return ( (3*sigma + x0) - (-3*sigma+x0) ) / (n - 1);
}

void zapiszDoPliku(int n, gsl_vector *vector, FILE *file){
    for(int i = 0; i <= n; i++){
        double xZnaczenie = (-3*sigma+x0) + 0.1 * i;
        double znaczenieG = funkcjaG(xZnaczenie, vector);
        fprintf(file, "%g %g \n",xZnaczenie, znaczenieG);
    }
    fprintf(file, "\n \n");
}

void zapiszWezly(int n, gsl_vector *wezly, gsl_vector *wartosc, FILE *file){
    for(int i = 0; i < n; i++){
        fprintf(file, "%g %g \n",gsl_vector_get(wezly, i),gsl_vector_get(wartosc, i));
    }
    fprintf(file, "\n \n");
}


int main(void) {

    const int n1 = 11;
    const int m1 = 4;
    const int n2 = 101;

    FILE *file1;
	file1 = fopen("pkt.dat", "w");
    FILE *file2;
	file2 = fopen("G.dat", "w");

    gsl_vector *wezly = gsl_vector_calloc(n1);
    gsl_vector *wezly2 = gsl_vector_calloc(n2);

    gsl_vector *wartosci_g = gsl_vector_calloc(n1);
    gsl_vector *wartosci_g2 = gsl_vector_calloc(n1);
    gsl_vector *wartosci_g3 = gsl_vector_calloc(n2);

    gsl_vector *wartosci_f = gsl_vector_calloc(n1);
    gsl_vector *wartosci_f2 = gsl_vector_calloc(n1);
    gsl_vector *wartosci_f3 = gsl_vector_calloc(n2);

    gsl_vector *wektor_rg = gsl_vector_calloc(m1);
    gsl_vector *wektor_rg2 = gsl_vector_calloc(m1);
    gsl_vector *wektor_rg3 = gsl_vector_calloc(m1);

    gsl_matrix *macierz_Gg = gsl_matrix_calloc(m1, m1);
    gsl_matrix *macierz_Gg2 = gsl_matrix_calloc(m1, m1);
    gsl_matrix *macierz_Gg3 = gsl_matrix_calloc(m1, m1);
 

    for(int i = 0; i < n1; i++){
        gsl_vector_set(wezly, i, -3*sigma + x0 + odleglosc(n1) * i);
        gsl_vector_set(wartosci_g, i, funkcja(gsl_vector_get(wezly, i), 0.0));
        gsl_vector_set(wartosci_g2, i, funkcja(gsl_vector_get(wezly, i), 0.5));
        gsl_vector_set(wartosci_f, i, log(gsl_vector_get(wartosci_g, i)));
        gsl_vector_set(wartosci_f2, i, log(gsl_vector_get(wartosci_g2, i)));
    }

    for(int i = 0; i < n2; i++){
        gsl_vector_set(wezly2, i, -3*sigma + x0 + odleglosc(n2) * i); 
        gsl_vector_set(wartosci_g3, i, funkcja(gsl_vector_get(wezly2, i), 0.5));
        gsl_vector_set(wartosci_f3, i, log(gsl_vector_get(wartosci_g3, i)));   
    }

    zapiszWezly(n1, wezly, wartosci_g, file1);
    zapiszWezly(n1, wezly, wartosci_g2, file1);
    zapiszWezly(n2, wezly2, wartosci_g3, file1);


    for(int i = 0; i < m1; i++){
        double tmp = 0.0;
        double tmp2 = 0.0; 
        for(int j = 0; j < n1; j++){
            tmp += gsl_vector_get(wartosci_f, j) * pow(gsl_vector_get(wezly, j), i);
            tmp2 += gsl_vector_get(wartosci_f2, j) * pow(gsl_vector_get(wezly, j), i);
        }
        gsl_vector_set(wektor_rg, i, tmp);
        gsl_vector_set(wektor_rg2, i, tmp2);
    }

    for(int i = 0; i < m1; i++){
        double tmp = 0.0;
        for(int j = 0; j < n2; j++){
            tmp += gsl_vector_get(wartosci_f3, j) * pow(gsl_vector_get(wezly2, j), i);
        }
        gsl_vector_set(wektor_rg3, i, tmp);
    }

    for(int i = 0; i < m1; i++) {
		for(int k = 0; k < m1; k++) {
			double tmp = 0;
			for(int j = 0; j < n1; j++) {
				tmp += pow(gsl_vector_get(wezly,j), i + k);
			}
		gsl_matrix_set(macierz_Gg, i, k, tmp);
        gsl_matrix_set(macierz_Gg2, i, k, tmp);

		}
	}

    for(int i = 0; i < m1; i++) {
		for(int k = 0; k < m1; k++) {
			double tmp = 0;
			for(int j = 0; j < n2; j++) {
				tmp += pow(gsl_vector_get(wezly2,j), i + k);
			}
		gsl_matrix_set(macierz_Gg3, i, k, tmp);

		}
	}

    gsl_linalg_HH_svx(macierz_Gg, wektor_rg);
    gsl_linalg_HH_svx(macierz_Gg2, wektor_rg2);
    gsl_linalg_HH_svx(macierz_Gg3, wektor_rg3);


    double a0 = -pow(x0, 2) / (2 * pow(sigma, 2));
    double a1 = x0 / pow(sigma, 2);
    double a2 = -1 / (2 * pow(sigma, 2));

    printf("Analityczne(g1 oraz n = 11) \n");
    printf("%g \n", a0);
    printf("%g \n", a1);
    printf("%g \n", a2);
    printf("\n");

    printf("Numeryczne(g1 oraz n = 11) \n");
    for(int i = 0; i < m1; i++){
        printf("%g \n",gsl_vector_get(wektor_rg, i));
    }
    printf("\n");

    printf("Numeryczne(g2 oraz n = 11) \n");
    for(int i = 0; i < m1; i++){
        printf("%g \n",gsl_vector_get(wektor_rg2, i));
    }
    printf("\n");

    printf("Numeryczne(g2 oraz n = 101) \n");
    for(int i = 0; i < m1; i++){
        printf("%g \n",gsl_vector_get(wektor_rg3, i));
    }
    printf("\n");

    int krok = ((3*sigma + x0) - (-3*sigma+x0)) / 0.1;
    zapiszDoPliku(krok, wektor_rg, file2);
    zapiszDoPliku(krok, wektor_rg2, file2);
    zapiszDoPliku(krok, wektor_rg3, file2);




    gsl_vector_free(wezly);
    gsl_vector_free(wezly2);
    gsl_vector_free(wartosci_g);
    gsl_vector_free(wartosci_g2);
    gsl_vector_free(wartosci_g3);
    gsl_vector_free(wartosci_f);
    gsl_vector_free(wartosci_f2);
    gsl_vector_free(wartosci_f3);
    gsl_vector_free(wektor_rg);
    gsl_vector_free(wektor_rg2);
    gsl_vector_free(wektor_rg3);
    gsl_matrix_free(macierz_Gg);
    gsl_matrix_free(macierz_Gg2);
    gsl_matrix_free(macierz_Gg3);

    fclose(file1);
    fclose(file2);

    return 0;
}