#include "IRremote.h"
#include <Servo.h>

#define LED1 4
#define LED2 5
#define LED3 6
#define LED4 7
#define LED5 8

const int LEDPin1 = 4;
const int LEDPin2 = 5;
const int LEDPin3 = 6;
const int LEDPin4 = 7;
const int LEDPin5 = 8;

int cm = 0;
long distancia, duracion; //long valores decimales
int posicion1 = 90;
int posicion2 = 180;
Servo miServo; //al pin 13
#define Pecho 2 //Echo al pin 6
#define Ptrig 3 //Trig pin 7

// Pin analogico de entrada para el LDR
int pinLDR = 0;

// Variable donde se almacena el valor del LDR
int valorLDR = 0;

int receiver = 11;
IRrecv irrecv(receiver);
decode_results results;

void translateIR() {
  switch (results.value) {
    case 0xFFA25D: Serial.println("POWER");
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
      digitalWrite(LED5, LOW);
      break;

    case 0xFFC23D: Serial.println("FAST FORWARD");
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, HIGH);
      digitalWrite(LED5, HIGH);
      break;

    case 0xFF6897: Serial.println("0");
      pinMode(LED1, OUTPUT);
      digitalWrite(LED1, HIGH);
      break;

    case 0xFF30CF: Serial.println("1");
      pinMode(LED2, OUTPUT);
      digitalWrite(LED2, HIGH);
      break;

    case 0xFF18E7: Serial.println("2");
      pinMode(LED3, OUTPUT);
      digitalWrite(LED3, HIGH);
      break;

    case 0xFF7A85: Serial.println("3");
      pinMode(LED4, OUTPUT);
      digitalWrite(LED4, HIGH);
      break;

    case 0xFF10EF: Serial.println("4");
      pinMode(LED5, OUTPUT);
      digitalWrite(LED5, HIGH);
      break;

    case 0xFF52AD: Serial.println("9");
      // Apagar todos los leds siempre que se inicia el ciclo
      digitalWrite(LEDPin1, LOW);
      digitalWrite(LEDPin2, LOW);
      digitalWrite(LEDPin3, LOW);
      digitalWrite(LEDPin4, LOW);
      digitalWrite(LEDPin5, LOW);

      break;

    case 0xFFFFFFFF: Serial.println("ERROR"); break;

    default:
      Serial.println("Otro botón");
  }

  delay(500);
}

void setup() {
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode");
  irrecv.enableIRIn();

  pinMode(LEDPin1, OUTPUT);
  pinMode(LEDPin2, OUTPUT);
  pinMode(LEDPin3, OUTPUT);
  pinMode(LEDPin4, OUTPUT);
  pinMode(LEDPin5, OUTPUT);

  pinMode(Pecho, INPUT);  //define el pin 6 como entrada (echo)
  pinMode(Ptrig, OUTPUT); //define el pin 7 como salida (triger)
  miServo.attach (9);         //define el pin 13 como salida para mover el servo enviando la señal de distancia menor a 10

}



void loop() {

  // Guardamos el valor leido del ADC en una variable
  // El valor leido por el ADC (voltaje) aumenta de manera directamente proporcional
  // con respecto a la luz percibida por el LDR
  valorLDR = analogRead(pinLDR);

  // Devolver el valor leido a nuestro monitor serial en el IDE de Arduino
  Serial.println(valorLDR);
  // Encender los leds apropiados de acuerdo al valor de ADC
  if (valorLDR < 300)
  {
    digitalWrite(LEDPin1, HIGH);
    digitalWrite(LEDPin2, HIGH);
    digitalWrite(LEDPin3, HIGH);
    digitalWrite(LEDPin4, HIGH);
    digitalWrite(LEDPin5, HIGH);
  }

  if (irrecv.decode(&results))
  {
    translateIR();
    irrecv.resume();
  }

  digitalWrite (Ptrig, LOW);
  delayMicroseconds(2);
  digitalWrite(Ptrig, HIGH); //genera el pulso de triger de 10ms
  delayMicroseconds(10);
  digitalWrite(Ptrig, LOW);

  duracion = pulseIn(Pecho, HIGH); //con esto sabemos cuanto tiempo estuvo en alto(HIGH)
  distancia = (duracion / 2) / 29; //   calcula la distancia en centimetros

  if (distancia >= 500 || distancia <= 0) { //si la distancia es mayor a 500cm o menor a 0cm
    Serial.println("---");                 //no mide nada
  }
  else {
    Serial.print(distancia);               //envia el valor de la distancia por el puerto serial
    Serial.println("cm");                  //le coloca a la distancia los centimetros "cm"
    digitalWrite(13, LOW);                   //en bajo el pin 13, no mueve el servo
  }

  if (distancia <= 5 && distancia >= 1) {
    miServo.write(posicion1);                //mueve el servo si la distancia es menor a 10cm
    Serial.println("Obstaculo");          //envia la palabra "obstaculo" por el puerto serial
    pinMode(LED3, OUTPUT);
    digitalWrite(LED3, HIGH);
  }
  else
  {
    miServo.write(posicion2);
  }
  delay(400);                             //espera 400ms para que logre ver la distancia

}
