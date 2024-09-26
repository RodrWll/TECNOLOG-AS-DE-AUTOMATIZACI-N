#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <math.h>

FILE *hfiletxt;
float planta(float Rk);
float algoritmo_pi(float data2, float data1);
float respuestaLC[100]; // respuesta en el tiempo
float T = 100; // en milisegundos

float SP = 1;
float salida_proceso = 0;
float u = 0;
int puntos = 90;
pthread_mutex_t mutex;

void* control_pi_thread(void* arg) {
    float valor_sp, sensor;
    for (int t = 0; t < puntos; t++) {
        pthread_mutex_lock(&mutex);
        valor_sp = SP; // actualiza SP
        sensor = salida_proceso;
        u = algoritmo_pi(valor_sp, sensor);
        pthread_mutex_unlock(&mutex);
        usleep(T * 1000); // Espera T milisegundos
    }
    return NULL;
}

void* dinamica_proceso_thread(void* arg) {
    for (int t = 0; t < puntos; t++) {
        pthread_mutex_lock(&mutex);
        salida_proceso = planta(u);
        respuestaLC[t] = salida_proceso;
        pthread_mutex_unlock(&mutex);
        usleep(T * 1000); // Espera T milisegundos
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    pthread_mutex_init(&mutex, NULL);

    printf("Ingrese un valor de SP -->");
    scanf("%f", &SP);

    pthread_create(&thread1, NULL, control_pi_thread, NULL);
    pthread_create(&thread2, NULL, dinamica_proceso_thread, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    hfiletxt = fopen("c:\\resultado.txt", "wb+");
    if (hfiletxt != NULL) {
        for (int n = 0; n < puntos; n++)
            fprintf(hfiletxt, "%lf ", respuestaLC[n]);
        fclose(hfiletxt);
    }

    pthread_mutex_destroy(&mutex);

    // Llamar a gnuplot para graficar los resultados
    system("gnuplot -e \"plot 'c:\\resultado.txt' with lines\"");

    return 0;
}

float planta(float Rk) {
    static float Rk_1 = 0, Rk_2 = 0;
    static float Ck_1 = 0, Ck_2 = 0;
    float Ck = 0;
    Ck = 1.5327 * Ck_1 - 0.6607 * Ck_2 + 0.4673 * Rk_1 - 0.3393 * Rk_2;
    Rk_2 = Rk_1; // se actualiza el mas pasado
    Rk_1 = Rk;
    Ck_2 = Ck_1; // se actualiza el mas pasado
    Ck_1 = Ck;
    return Ck; // retorna la salida del proceso en un instante
}

float algoritmo_pi(float data2, float data1) {
    static float salida_ant = 0, e_ant = 0;
    float e_act, salida, kp, ki;
    kp = 0.1; // actualiza Kp
    ki = 1.0; // actualiza Ki
    e_act = data2 - data1; // SP - Vp
    salida = salida_ant + kp * (e_act - e_ant) + ki * e_act * (T / 1000.0);
    e_ant = e_act;
    salida_ant = salida;
    return salida;
}