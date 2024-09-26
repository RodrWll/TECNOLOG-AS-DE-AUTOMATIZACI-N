
/***************************************************************
2 hilos escriben en pantalla alternados mediante el uso de un mutex
**************************************************************/

#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;
int variable=0;

//---------------------------
void hacer1(int *nombre)
{
  int vuelta;
  for(;;){
    pthread_mutex_lock(&mutex);
    variable +=5;
    for(vuelta=1; vuelta<500000; vuelta++);
    printf("%d..",variable);
    variable-=5;
    pthread_mutex_unlock(&mutex);
  }
}
//-----------------------------------------------
void hacer2(int *nombre)
{
  int vuelta;
  for(;;) {
    pthread_mutex_lock(&mutex);
    variable+=6;
    for(vuelta=1; vuelta<500000; vuelta++);
    printf("%d--",variable);
    variable-=6;
    pthread_mutex_unlock(&mutex);
  }
}
//--------------------------------------------------------
int main()
{  
  pthread_t hilo1,hilo2;
  int nombre[2]={1,2};
  int retardo;  
  pthread_mutex_init(&mutex, NULL);

  printf("\n Creador: Creo 2 hilos y espero que trabajen n seg.\n");

  /* Creo dos hilos */
  pthread_create(&hilo1, NULL, (void *)hacer1, (void *)nombre[0]);
  pthread_create(&hilo2, NULL, (void *)hacer2, (void *)nombre[1]);
  
  sleep(2);
 
  pthread_cancel(hilo1);
  pthread_cancel(hilo2);
 
  /* Hemos acabado y estoy aqui otra vez */
printf("\nCreador: cancele los hilos y estoy aqui otra vez\nAdios...\n");
  
}












