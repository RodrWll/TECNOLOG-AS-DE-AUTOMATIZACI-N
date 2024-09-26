
/********************************************************************
 2 hilos escriben en pantalla alternandose sin el uso de un mutex
*********************************************************************/

#include <stdio.h>
#include <pthread.h>

int variable=0;
//-----------------------------------------
void hacer1(int *nombre)
{
  int vuelta;
  for(;;){
    variable +=5;
    for(vuelta=1; vuelta<1000000; vuelta++); //el punto y coma es temporizador
    printf("%d..",variable);
    variable-=5;
  }
}
//-------------------------------
void hacer2(int *nombre)
{
  int vuelta;
  for(;;) {
    variable+=6;
    for(vuelta=1; vuelta<1000000; vuelta++);
    printf("%d--",variable);
    variable-=6;
  }
}
//---------------------------------
int main()
{  
  pthread_t hilo1,hilo2;
  int nombre[2]={1,2};
  pthread_mutex_t mutex;
  pthread_mutex_init(&mutex, NULL);

  printf("Hola. Creo dos hilos y espero a que acaben\n");

  /* Creo dos hilos */
  pthread_create(&hilo1, NULL, (void *)hacer1, (void *)nombre[0]);
  pthread_create(&hilo2, NULL, (void *)hacer2, (void *)nombre[1]);
  
  sleep(1);
  
//  pthread_cancel(hilo1);
  pthread_cancel(hilo2);
 
  /* Hemos acabado y estoy aqui otra vez */
  printf("\n Los hilos han acabado y estoy aqui otra vez\n Adios...\n");
  
}












