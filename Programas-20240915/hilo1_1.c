
/******************************************************************
* Este programa demuestra la creacion y terminacion de hilos 
*******************************************************************/


#include <pthread.h>
#include <stdio.h>
#define NUM_THREADS 5

//------rutina llamada por cada hilo -----//

void *imprimir(void *threadid)
{
   printf("\n ¡Hola, yo soy el hilooo...!: %d\n", threadid);
   pthread_exit(NULL);
}
//---------- Hilo Principal -----------------//

int main()
{
   pthread_t threads[NUM_THREADS];
   int rc, t;

   for(t=0;t<NUM_THREADS;t++){
      printf("Creando thread %d\n", t);
      rc = pthread_create(&threads[t], NULL, imprimir, (void*)t);
      if (rc){
         printf("ERROR; return code from pthread_create() is %d\n", rc);
         exit(-1);
      }
   }
   pthread_exit(NULL);
}
