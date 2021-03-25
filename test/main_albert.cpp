#include <Arduino.h>
int LED1=5;
int LED2=18;
int nTasks=2;
SemaphoreHandle_t barrierSemaphore = xSemaphoreCreateCounting( nTasks, 0 );
void Tarea1( void * parameter )
{
    while(1){
    Serial.println("EMPEZANDO TAREA 1");
    digitalWrite(LED1,HIGH);
    digitalWrite(LED2,LOW);
    delay(1000);
    xSemaphoreGive(barrierSemaphore); //El semàfor 'incrementa
    vTaskDelete(NULL);

    }
}

void Tarea2( void * parameter)
{
    while (1)
    {    
    Serial.println("EMPEZANDO TAREA 2");
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,HIGH);
    delay(1000);
    xSemaphoreGive(barrierSemaphore); //El semàfor 'incrementa

    vTaskDelete(NULL);
    }
}


void setup() {

  Serial.begin(9600);
    pinMode(LED1,OUTPUT);
    pinMode(LED2,OUTPUT);

  delay(1000);

  xTaskCreate(Tarea1,"Tarea1",10000,NULL,0,NULL);
  xTaskCreate(Tarea2,"Tarea2",10000,NULL,0,NULL);
/*Hi ha una funció que va incrementant el semàfor, llavors, aquest bucle està fet per a que el semàfor reculli totes les tasques a executar. */ 
    for(int i= 0; i<nTasks; i++){ //Puesto que habrá las tareas que incrementan el semáforo, debemos garantizar que la función de configuración arduino sólo terminará después de que finalicen todas las tareas.
        xSemaphoreTake(barrierSemaphore, portMAX_DELAY); 
    }

}

void loop() {
   vTaskSuspend(NULL); //Dewjamos de ejecutar el void loop();
}