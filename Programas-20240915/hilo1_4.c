
/********************************************************
 * ejemplo de mutiples threads con JOIN
 *********************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>

void hace_tarea_2(int *);
void hace_tarea_1(int *);
void cuentas(int, int);

int r1 = 0, r2 = 0;

extern int
/*-----------------------------------------*/
main(void)
{
  pthread_t thread1, thread2;
 
if (pthread_create(&thread1,NULL,(void*) hace_tarea_1,(void*) &r1) != 0)
	perror("pthread_create"), exit(1); 

if (pthread_create(&thread2,NULL,(void*) hace_tarea_2,(void*) &r2) != 0)
	perror("pthread_create"), exit(1); 
  
  if (pthread_join(thread1, NULL) != 0)
	perror("pthread_join"),exit(1);

  if (pthread_join(thread2, NULL) != 0)
	perror("pthread_join"),exit(1);

  cuentas(r1, r2);
 pthread_exit(NULL);
  //return 0; 
}
/*-------------------------------------------*/
void hace_tarea_1(int *pnum_times)
{
  int i, j, x;
  
  for (i = 0;  i < 6; i++) {
    printf("haciendo tarea_1\n"); 
    for (j = 0; j < 100000000; j++) x = x + i;

    (*pnum_times)++;
  }
 pthread_exit(NULL);

}
/*-------------------------------------------*/
void hace_tarea_2(int *pnum_times)
{
  int i, j, x;
  
  for (i = 0;  i < 4; i++) {
    printf("haciendo tarea_2 \n"); 
    for (j = 0; j < 100000000; j++) x = x + i;

    (*pnum_times)++;
  }
 pthread_exit(NULL);
}
/*-------------------------------------------*/
void cuentas(int veces_tarea1, int veces_tarea2)
{
  int total;

  total = veces_tarea1 + veces_tarea2;
printf("Terminaron ->  tarea 1: %d veces, tarea 2: %d veces,  un total 
de: %d veces\n",veces_tarea1, veces_tarea2, total);
}
