
/*************************************************************************
*  Usa variables de condicion. El hilo principal crea 3 hilos
*  Dos de ellos incrementan una variable 'count'.El tercer hilo
*  espera que el valor de "count" llegue al valor limite predefinido, 
*  momento en que es 'signaled' por uno de los otros hilos
***************************************************************************/

#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS  3
#define TCOUNT 9
#define COUNT_LIMIT 10

int     count = 0;
int     thread_ids[3] = {0,1,2};
pthread_mutex_t  count_mutex;
pthread_cond_t   count_limite_cv;

//------------------------------
void *incremento(void *idp) 
{
  int j,i;
  double result=0.0;
  int *my_id = idp;

  for (i=0; i < TCOUNT; i++) {
    pthread_mutex_lock(&count_mutex);  
    count++;

/* Chequea 'count' and envia una señal al hilo en espera si la condicion
 es alcanzada.  Notar que esto ocurre mientras el mutex esta locked. */

   if (count == COUNT_LIMIT) {
       pthread_cond_signal(&count_limite_cv);
       printf(" Hilo %d,incrementa count = %d  Limite llegado.\n",*my_id,count);
      }
    
     printf(" Hilo %d, incrementa count = %d, unlocking mutex\n",*my_id,count);
     pthread_mutex_unlock(&count_mutex);


/* algo de trabajo para que los hilos alternen on mutex lock */
    for (j=0; j < 100000000; j++);

    }
  pthread_exit(NULL);
}
//----------------------------------------------------------
void *espera_count(void *idp) 
{
  int *my_id = idp;

  printf(" hilo %d --> inicio espera de count \n", *my_id);

 /* Lock el mutex y wait por la signal. Pthread_cond_wait y automaticamente 
  unlock el mutex mientras waits.*/

  pthread_mutex_lock(&count_mutex);
  while (count < COUNT_LIMIT) {
    pthread_cond_wait(&count_limite_cv, &count_mutex);
    printf(" hilo %d --> Señal de Condition recibida.\n", *my_id);
    }
  pthread_mutex_unlock(&count_mutex);
  pthread_exit(NULL);
}
//---------------------------------------------------------
int main()
{
  int i, rc;
  pthread_t threads[3];
  pthread_attr_t attr;

  /* Initialize mutex and condition variable objects */
  pthread_mutex_init(&count_mutex, NULL);
  pthread_cond_init (&count_limite_cv, NULL);

  /* explicitamente crea hilos 'undetached' para ser joined despues */
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  /*creacion de los 3 hilos*/
  pthread_create(&threads[0], &attr, incremento, (void*)&thread_ids[0]);
  pthread_create(&threads[1], &attr, incremento, (void *)&thread_ids[1]);
  pthread_create(&threads[2], &attr, espera_count, (void*)&thread_ids[2]);

  /* Espera que todos los hilos terminen */

  printf (" Hilo Creador: espere a los %d  hilos acaben...\n",NUM_THREADS);

  for (i = 0; i < NUM_THREADS; i++) 
	 { pthread_join(threads[i], NULL); }

  printf (" Hilo Creador: Adios...\n", NUM_THREADS);

  /* elimina variables y exit */
  pthread_attr_destroy(&attr);
  pthread_mutex_destroy(&count_mutex);
  pthread_cond_destroy(&count_limite_cv);
  pthread_exit (NULL);

}

