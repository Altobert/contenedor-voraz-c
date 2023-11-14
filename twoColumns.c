#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    char buf[MAXC];         /* buffer for reading each line */ 
    size_t ncoeff = 0;      /* number of coefficient pairs read */

    while (ncoeff < MAXC && fgets (buf, MAXC, fp))  /* read each line */
        /* if it contains 2 double values */
        //if (sscanf (buf, "%lf %lf", &a[ncoeff], &b[ncoeff]) == 2)
        if (sscanf (buf, "%d %d", &a[ncoeff], &b[ncoeff]) == 2)
            ncoeff++;       /* increment counter */

    return ncoeff;          /* return total count of pairs read */
}

int main (int argc, char **argv) {

    //arreglos para almacenar valores leidos desde archivos
    int val[MAXC] = {};
    int  wt[MAXC] = {};
    int capacidad_maxima=0;

    int a[MAXC] = {0}, b[MAXC] = {0};           /* arrays of MAXC doubles */
    size_t n = 0;                               /* count of doubles returned */
    /* use filename provided as 1st argument (stdin by default) */
    FILE *fp = argc > 1 ? fopen (argv[1], "r") : stdin;
    
    capacidad_maxima = atoi(argv[2]);
    
    if (!fp) {  /* validate file open for reading */
        perror ("file open failed");
        return 1;
    }

    if (!(n = coefficients (fp, a, b))) {   /* validate coeff pairs read */
        fputs ("error: no double values read from file.\n", stderr);
        return 1;
    }

    if (fp != stdin)   /* close file if not stdin */
        fclose (fp);

    
    for (size_t i = 0; i < n; i++){
          /* asignacion */
          val[i] = a[i];
          wt[i]  = b[i];  
          /* se muestran columnas leidas desde archivo*/
          printf ("a[%zu] : %d   b[%zu] : %d\n", i, a[i], i, b[i]);
    }  
    printf("capacidad maxima contenedor: %d",capacidad_maxima);
    printf("\n resultado = %d \n", knapsack(capacidad_maxima, wt , val, n));


    return 0;
}