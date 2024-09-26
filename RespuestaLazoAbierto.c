#include <stdlib.h>
#include <stdio.h>
#include <math.h>

FILE *hfiletxt;

//---------------- Inicio de Programa ----------------------
void main(void) {
    int n;
    float Rk; // amplitud del escalon
    float respuestaLA[100]; // respuesta en el tiempo
    float Rk_1 = 0, Rk_2 = 0;
    float Ck = 0;
    float Ck_1 = 0, Ck_2 = 0;
    int puntos = 35;
    Rk = 1;

    for (int t = 0; t < puntos; t++) {
        Ck = 1.5327 * Ck_1 - 0.6607 * Ck_2 + 0.4673 * Rk_1 - 0.3393 * Rk_2;
        Rk_2 = Rk_1; // se actualiza el mas pasado
        Rk_1 = Rk; // se actualiza el pasado
        Ck_2 = Ck_1; // se actualiza el mas pasado
        Ck_1 = Ck; // se actualiza el pasado
        respuestaLA[t] = Ck;
    }

    //--------------------escribir archivo--------------------
    hfiletxt = fopen((char*)("resultado.txt"), "wb+");
    if (hfiletxt != NULL) {
        for (n = 0; n < puntos; n++)
            fprintf(hfiletxt, "%lf ", respuestaLA[n]);
        fclose(hfiletxt);
    }
}