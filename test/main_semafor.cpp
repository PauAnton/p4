#include <Arduino.h>

void greenCar (void * pvParameters);
void greenPed(void * pvParameters);
void redCar (void * pvParameters);
void redPed(void * pvParameters);
void yellow(void * pvParameters);
int ntask=5;
int greenC=5;
int yel=18;
int redC=19;
int greenP=22;
int redP=23;

SemaphoreHandle_t semaforcount= xSemaphoreCreateCounting(ntask,0);

void setup(){

Serial.begin(9600);
pinMode(greenC, OUTPUT);
pinMode(redC, OUTPUT);
pinMode(yel, OUTPUT);
pinMode(greenP, OUTPUT);
pinMode(redP, OUTPUT);

semafor= xSemaphoreCreateMutex();

xTaskCreate(
    greenCar,
    "Green Light for car",
    10000,
    NULL,
    1,
    NULL);

xTaskCreate(
   redCar,
    "Red Light for car",
    10000,
    NULL,
    1,
    NULL);
xTaskCreate(
   yellow,
    "Yellow Light for car",
    10000,
    NULL,
    1,
    NULL);
xTaskCreate(
   greenPed,
    "Green Light for Pedestrians",
    10000,
    NULL,
    1,
    NULL);
xTaskCreate(
   redPed,
    "Red Light for Pedestrians",
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