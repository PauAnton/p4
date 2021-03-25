# PRACTICA 4: Real-Time Operating System

*Hay varios casos de uso para querer realizar múltiples tareas en un microcontrolador. Por
ejemplo: puede tener un microcontrolador que lee un sensor de temperatura, lo muestra en
una pantalla LCD y lo envía a la nube.
Puede hacer los tres sincrónicamente, uno tras otro. Pero, ¿qué sucede si está utilizando una
pantalla de tinta electrónica que tarda unos segundos en actualizarse?*

Pongamos que el tiempo de proceso de las dos primeras tareas es de Tp, mientras que el tiempo de la escriptura de a pantalla son 3Tp. 

En el caso síncrono, se representará la muestra de t0 en t=Tp+Tp+3Tp=5Tp. Cada 5Tp instantes de tiempo podremos ver la temperatura acutalizada, pero no a tiempo real, sino la que había hace 5Tp. 

Si en vez de ser síncrono se hacen los procesos a la vez, entonces la temperatura se actualizará segun el tiempo de processo maximo. Por tanto podremos ver actualizada la temperatura cada 3Tp (sigue sin ser a tiempo real pero se aproxima más que en el anterior caso). 
Además, de esta forma, podemos medir la temperatura cada Tp (casi a tiempo real) y tener más precisón en caso de que fusese necesario para alguna otra tarea. 


## Ejercicio 1

Este programa crea una tarea que llamada *anotherTask* la cual se va a ejecutar en paralelo con el *loop* del main. 

En el puerto serie se muestra los mensajes "this is ESP32 Task" y "this is another Task" cada una cada 1000ms, idependientemente una de la otra. 

Si por ejemplo cambiamos la funcion *anotherTask* tal que el tiempo de repeticion sea la mitad tal que 

```cpp
void anotherTask( void * parameter )
{
/* loop forever */
for(;;){
Serial.println("this is another Task");
delay(500);
}
/* delete a task when finish,
this will never happen because this is infinity loop */
vTaskDelete( NULL );
}
```
entonces aparecerá "this is another Task" cada 500ms sin influir en el período de realizacion de la "this is ESP32 Task".

## Ejercicio 2

Para este ejercicio utilizamos un semaforo mutex (mutual exclusion) para cooridnar el encendido y apagado del led. 

```cpp
#include <Arduino.h>

void ledON (void * pvParameters);
void ledOFF(void * pvParameters);
int LED =2; 

SemaphoreHandle_t semafor;

void setup(){

Serial.begin(9600);
pinMode(LED, OUTPUT);
semafor= xSemaphoreCreateMutex();

xTaskCreate(
    ledON,
    "LED ON",
    10000,
    NULL,
    1,
    NULL);

xTaskCreate(
    ledOFF,
    "LED OFF",
    10000,
    NULL,
    1,
    NULL);

}

void loop(){}

void ledON (void * pvParameters){
    for(;;){
        xSemaphoreTake(semafor, portMAX_DELAY);
        digitalWrite(LED, HIGH);
        delay(3000);
        xSemaphoreGive(semafor);
    }
}

void ledOFF (void * pvParameters){
    for(;;){
        xSemaphoreTake(semafor, portMAX_DELAY);
        digitalWrite(LED, LOW);
        delay(1500);
        xSemaphoreGive(semafor);
    }
}

```
