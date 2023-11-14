#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXC 100000   /* if you need a constant, #define one (or more) */

int max(int a, int b) { return (a > b)? a : b; }
// Returns the maximum value that can be put in a contenedor of capacity W

int knapsack(int W, int wt[], int val[], int n)
{
   int i, w;
   int K[n+1][W+1];

   // Build table K[][] in bottom up manner
   for (i = 0; i <= n; i++)
   {
       for (w = 0; w <= W; w++)
       {
           if (i==0 || w==0)
               K[i][w] = 0;
           else if (wt[i-1] <= w)
                 K[i][w] = max(val[i-1] + K[i-1][w-wt[i-1]],  K[i-1][w]);
           else
                 K[i][w] = K[i-1][w];
       }
   }

   return K[n][W];
}

size_t coefficients (FILE *fp, int *a, int *b)
{
    char buf[MAXC];         /* buffering para leer cada linea */ 
    size_t ncoeff = 0;      /* cantidad de numeros pares leidos */

    while (ncoeff < MAXC && fgets (buf, MAXC, fp))  /* read each line */
        /* si hay dos columnas de valores que leer */
        if (sscanf (buf, "%d %d", &a[ncoeff], &b[ncoeff]) == 2)
            ncoeff++;       /* se incrementa contador */

    return ncoeff;          /* return contador total de valores pares leidos */
}

int main (int argc, char **argv) {

    //arreglos para almacenar valores leidos desde archivos
    int val[MAXC] = {};
    int  wt[MAXC] = {};
    int capacidad_maxima=0;

    clock_t ciniIt, cfinIt;

    int a[MAXC] = {0}, b[MAXC] = {0};           /* arrays con constante maxima de enteros MAXC*/
    size_t n = 0;                               /* contador de enteros retornados */

    /* se usa para rescatar el nombre del archivo */
    FILE *fp = argc > 1 ? fopen (argv[1], "r") : stdin;
    
    capacidad_maxima = atoi(argv[2]);
    
    if (!fp) {  /* se valida la lectura del archivo */
        perror ("apertura de archivo fallida");
        return 1;
    }

    if (!(n = coefficients (fp, a, b))) {   /* validate pares de valores leidos */
        fputs ("error: sin valores que leer desde archivo.\n", stderr);
        return 1;
    }

    if (fp != stdin)   /* se cierra archivo */
        fclose (fp);

    
    for (size_t i = 0; i < n; i++){
          /* asignacion */
          val[i] = a[i];
          wt[i]  = b[i];  
          /* se muestran columnas leidas desde archivo*/
          printf ("a[%zu] : %d   b[%zu] : %d\n", i, a[i], i, b[i]);
    }  
    printf("Capacidad maxima contenedor: %d \n",capacidad_maxima);

    ciniIt = clock();
    printf("Resultado = %d \n", knapsack(capacidad_maxima, wt , val, n));
    cfinIt = clock();
    printf("tiempo solucion optima mochila-contenedor:  %f \n", (double)(cfinIt-ciniIt) / CLOCKS_PER_SEC);
    printf("\n-------------------\n\n");

    return 0;
}