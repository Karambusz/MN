#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double funkcja(double x) {
    return (x - 1.2) * (x - 2.3) * pow((x - 3.3), 2);
}

double pochodnaFunkcji(double x, double delta) {
    return (funkcja(x + delta) - funkcja(x - delta)) / (2 * delta);
}

double funkcjaU(double x, double delta) {
    return funkcja(x)/pochodnaFunkcji(x, delta);
}


void metodaSiecznych(double x0, double x1){
    double x2 = 0;
    printf("Metoda siecznych dla x0 = %.3f, x1 = %.3f \n", x0, x1);
    for(int k = 1; k <= 10000; k++) {
       x2 = x1 - ((x1 - x0)/(funkcja(x1) - funkcja(x0))) * funkcja(x1);
       printf("k = %d       x2 = %10g         ε = %15g      f(x2) = %15g  \n",k, x2, fabs(x2 - x1), funkcja(x2));
       if(fabs(x2 - x1) < pow(10, -6)){
           break;
       } 
       x0 = x1;
       x1 = x2;
    }

    printf("\n \n");
}

void modyfikowanaMetodaSiecznych(double x0, double x1, double delta) {
    double x2 = 0;
    printf("Modyfikowana metoda siecznych dla x0 = %.3f, x1 = %.3f \n", x0, x1);
    for(int k = 1; k <= 10000; k++) {
        x2 = x1 - ((x1 - x0)/(funkcjaU(x1, delta) - funkcjaU(x0, delta))) * funkcjaU(x1, delta);
        printf("k = %d       x2 = %10g         ε = %15g      f(x2) = %15g  \n",k, x2, fabs(x2 - x1), funkcja(x2));
        if(fabs(x2 - x1) < pow(10, -6)){
            break;
        } 
        x0 = x1;
        x1 = x2;
    }
    printf("\n \n");
}


int main(void) {

    // Niemodyfikowana metoda siecznych
    metodaSiecznych(0.9, 1.0); // x0 = 0.9, x1 = 1.0
    metodaSiecznych(1.7, 1.75); // x0 = 1.7, x1 = 1.75
    metodaSiecznych(3.7, 3.65); // x0 = 3.7, x1 = 3.65
    // Modyfikowana metoda siecznych
    modyfikowanaMetodaSiecznych(3.7, 3.65, 0.1); // x0 = 3.7, x1 = 3.65, delta = 0.1
    modyfikowanaMetodaSiecznych(3.7, 3.65, 0.001); // x0 = 3.7, x1 = 3.65, delta = 0.001

    return 0;
}
