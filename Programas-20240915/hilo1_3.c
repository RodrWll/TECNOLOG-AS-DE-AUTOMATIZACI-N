/****************************************** 
  Uso de JOIN() ;
*******************************************/

#include <pthread.h>
//------------------------------------------------
void hacer(int *nombre)
{
  int vuelta,vuelta1;

  for(vuelta=1; vuelta<10; vuelta++){
    printf("Soy el hilo %d en la vuelta %d\n",nombre, vuelta);
// for(vuelta1=1; vuelta1<10000000; vuelta1++);
  
  }
  pthread_exit(NULL);

}
//-------------------------------------------------
int main()
{  
  pthread_t hilo1,hilo2;
  int nombre[2]={1,2};
  pthread_attr_t attr;
  
  printf("\n Creador: creo 2 hilos y espero a que acaben\n\n");
  /*creo atributos de undetached para usar en la creacion de hilos*/
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);


  /* Creo dos hilos con atributos*/
  pthread_create(&hilo1, &attr, (void *)hacer, (void *)nombre[0]);
  pthread_create(&hilo2, &attr, (void *)hacer, (void *)nombre[1]);
  pthread_attr_destroy(&attr);
 
 /* Espero a que acaben*/
  pthread_join(hilo1, NULL);
  pthread_join(hilo2, NULL);
  /* Han acabado y estoy aqui otra vez */
  printf("Creador: los hilos terminaron y termino yo tambien\nAdios...\n");
  pthread_exit(NULL);

  
}
