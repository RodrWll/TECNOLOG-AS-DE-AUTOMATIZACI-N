### Prueba de entrda

---

Rodrigo Agurto `20202021`
---


### 3. Para qué sirve la función pthread_self, de un ejemplo.
La función `pthread_self` devuelve el identificador del hilo que la llama. Este identificador es único para cada hilo y es un valor entero de tipo `pthread_t`. 


### Mencione 4 funciones de la librería pthread.h relacionados a los atributos de un hilo. Agregue ejemplos concisos
* pthread_create: crea un hilo y devuelve el identificador del hilo creado.
* pthread_self: devuelve el identificador del hilo que la llama.
*	pthread_joint: espera a que el hilo termine.
*pthread_detach: desvincula el hilo de su hilo principal.

Cuáles son los argumentos de pthread_create y de qué tipo son?
El prototipo de la función pthread_create es el siguiente:
```c

```
En qué casos se usa la exclusión mutua? 
La exclusión mutua se utiliza cuando se quiere evitar que dos o más hilos accedan a un recurso compartido al mismo tiempo.

Qué significan los conceptos de Deadlocks y Starvation y a qué concepto se encuentran relacionados? 


 Mencione los 2 mecanismos para sincronización de hilos y las 2 operaciones asociadas a cada uno.
Los dos mecanismos para sincronización de hilos son:
* Mutex: Los dos operaciones asociadas a los mutex son `pthread_mutex_lock` y `pthread_mutex_unlock`.
* Semáforos: Los dos operaciones asociadas a los semáforos son `sem_wait` y `sem_post`.