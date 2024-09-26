/******************************************************************************
* Programa que demuestra el paso de argumentos en la creacion de threads
******************************************************************************/

#include <pthread.h>
#include <stdio.h>
#define NUM_THREADS 5	

char *mensaje[NUM_THREADS];

void *imprimir(void *threadid)
{
   int *id_ptr, taskid;
   id_ptr = (int *) threadid;
   taskid = *id_ptr;
   printf("Thread %d: %s\n", taskid, mensaje[taskid]);
   pthread_exit(NULL);
}

int main()
{
   pthread_t threads[NUM_THREADS];
   int *taskids[NUM_THREADS];
   int rc, t;

   mensaje[0] = "¡ Soy el HILO 1 !";
   mensaje[1] = "¡ Soy el HILO 2 !";
   mensaje[2] = "¡ Soy el HILO 3 !";
   mensaje[3] = "¡ Soy el HILO 4 !";
   mensaje[4] = "¡ Soy el HILO 5 !";

   for(t=0;t<NUM_THREADS;t++)
   {
      taskids[t] = (int *) malloc(sizeof(int));
      *taskids[t] = t;
      printf("Creating thread %d\n", t);
      rc = pthread_create(&threads[t], NULL, imprimir, (void *) taskids[t]);
         if (rc)
         {printf("ERROR; return code from pthread_create() is %d\n",rc);
         exit(-1);}
   }
   pthread_exit(NULL);
}
