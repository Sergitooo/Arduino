//@Sergitooo

#include <Servo.h>

int cm = 0;
long distancia, duracion; //long valores decimales
int posicion1 = 90;
int posicion2 = 0;
Servo miServo; //al pin 10
#define Pecho 45 //Echo al pin 45
#define Ptrig 44 //Trig pin 44
const int ledPIN1 = 52; //LED VERDE
const int ledPIN2 = 53; //LED AMARILLO
const int ledPIN3 = 51; //LED ROJO

void setup() {
  Serial.begin (9600);   //inicializa el puerto serie a 9600 baudios
  pinMode(Pecho, INPUT);  //define el pin 45 como entrada (echo)
  pinMode(Ptrig, OUTPUT); //define el pin 44 como salida (triger)
  pinMode(ledPIN1 , OUTPUT);  //definir pin como salida
  pinMode(ledPIN2 , OUTPUT);  //definir pin como salida
  pinMode(ledPIN3 , OUTPUT);  //definir pin como salida
  miServo.attach (10);         //define el pin 10 como salida para mover el servo enviando la señal de distancia menor a 10

}

void loop() {

  digitalWrite (Ptrig, LOW);
  delayMicroseconds(2);
  digitalWrite(Ptrig, HIGH); //genera el pulso de triger de 10ms
  delayMicroseconds(10);
  digitalWrite(Ptrig, LOW);

  duracion = pulseIn(Pecho, HIGH); //con esto sabemos cuanto tiempo estuvo en alto(HIGH)
  distancia = (duracion / 2) / 29; //   calcula la distancia en centimetros

  if (distancia >= 500 || distancia <= 0) { //si la distancia es mayor a 5cm o menor a 0cm
    Serial.println("---");                 //no mide nada
    digitalWrite(ledPIN3 , HIGH);
    digitalWrite(ledPIN1 , LOW);
    digitalWrite(ledPIN2 , LOW);
  }
  else {
    Serial.print(distancia);               //envia el valor de la distancia por el puerto serial
    Serial.println("cm");                  //le coloca a la distancia los centimetros "cm"
    digitalWrite(10, LOW);                   //en bajo el pin 10, no mueve el servo
  }

  if (distancia <= 10 && distancia >= 1) {
    miServo.write(posicion1);                //mueve el servo si la distancia es menor a 10cm
    Serial.println("Obstaculo");          //envia la palabra "obstaculo" por el puerto serial
    digitalWrite(ledPIN1 , HIGH);
    digitalWrite(ledPIN2 , LOW);
    digitalWrite(ledPIN3 , LOW);
    delay(3000);
    digitalWrite(ledPIN1 , LOW);
    digitalWrite(ledPIN2 , HIGH);
    delay(1000);
    digitalWrite(ledPIN2 , LOW);
    digitalWrite(ledPIN3 , HIGH);
  }
  else
  {
    miServo.write(posicion2);
  }
  delay(400);                             //espera 400ms para que logre ver la distancia

}
