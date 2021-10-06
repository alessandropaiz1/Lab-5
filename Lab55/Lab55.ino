//*****************************************************************************
// Universidad del Valle de Guatemala
// BE3015 - Electrónica Digital 2
// Alessandro Paiz - 19572
// Laboratorio #5 - UART
//*****************************************************************************

//*****************************************************************************
// Librerías
//*****************************************************************************
#include <Arduino.h>
#include <LiquidCrystal.h>

//*****************************************************************************
// Definición de pines
//*****************************************************************************

#define d4 26            // Definir pines del display
#define d5 25            
#define d6 33
#define d7 32
#define en 12
#define rs 13

#define b1 4             // Definir botones
#define b2 0

#define pot1 36          // Definir potenciometros
#define pot2 39

#define ledRojo 19
#define ledVerde 5
#define ledAzul 18

//*****************************************************************************
// Variables Globales
//*****************************************************************************

void UART (void);


//*****************************************************************************
// Variables Globales
//*****************************************************************************
// Create An LCD Object. Signals: [ RS, EN, D4, D5, D6, D7 ]
LiquidCrystal LCD(rs, en, d4, d5, d6, d7);
uint8_t decenas1, unidades1, decimal1;     // Unidad, decimal 1 y decimal 2
uint8_t decenas2, unidades2, decimal2;
uint8_t centenas, decenas, unidades;

int contador = 0;             // Crear variable para el contador 
int adcRaw;
float voltaje;                // Variable para voltaje potenciometro 1
float voltaje2;               // Variable para voltaje potenciometro 2
byte estadob1 = 0;
byte estadob2 = 0;
char operacion = 0;
int poti1 = 0;
int poti2 = 0;


//*****************************************************************************
// Configuración
//*****************************************************************************
void setup() {
  Serial.begin(115200);                    // Configuración serial 
 
  LCD.begin(16, 2);                        // Configurar LCD 16*2

  pinMode(ledRojo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAzul, OUTPUT);

  digitalWrite(ledRojo, 0);
  digitalWrite(ledVerde, 0);
  digitalWrite(ledAzul, 0);
  
  ledcSetup(1, 50, 8);         // Configuración de led verde
  ledcAttachPin(ledRojo, 1);
  
  ledcSetup(2, 50, 8);         // Configuración de led rojo
  ledcAttachPin(ledVerde, 2);

  ledcSetup(3, 50, 8);         // Configuración de led azul
  ledcAttachPin(ledAzul, 3);

}

//*****************************************************************************
// Loop principal
//*****************************************************************************

void loop() {

  voltaje = analogReadMilliVolts(pot1) / 10.0;        // Separar valores del voltaje P1
  int temp = voltaje;
  decenas1 = temp / 100.0;
  temp = temp - decenas1 *100.0;
  unidades1 = temp / 10.0;
  temp = temp - unidades1 *10.0;
  decimal1 = temp;

  voltaje2 = analogReadMilliVolts(pot2) / 10.0;       // Separar valores del voltaje P2
  int temp2 = voltaje2;
  decenas2 = temp2 / 100.0;
  temp2 = temp2 - decenas2 *100.0;
  unidades2 = temp2 / 10.0;
  temp2 = temp2 - unidades2 *10.0;
  decimal2 = temp2;

  UART();
//*****************************************************************************
// Funcion UART
//*****************************************************************************
void UART (void){
  if (Serial.available() > 0){
    operacion = Serial.read();
    Serial.print("Potenciometro 1: ");
    Serial.print(decenas1);
    Serial.print('.');
    Serial.print(unidades1);
    Serial.println(decimal1);
    Serial.print("Potenciometro 2: ");
    Serial.print(decenas2);
    Serial.print('.');
    Serial.print(unidades2);
    Serial.println(decimal2);
    
    if (operacion == '+'){
      contador++;
      if (contador > 255){
        contador = 0;
      }
    }
    
    if (operacion == '-'){
      contador--;
      if (contador < 0){
        contador = 255;
      }

    }

  }
}
