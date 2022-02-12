const int ledPIN3 = 51; //LED ROJO
const int ledPIN2 = 52; //LED verde
const int ledPIN1 = 53; //LED AMARILLO

void setup() {
  Serial.begin (9600);   //inicializa el puerto serie a 9600 baudios

  pinMode(ledPIN3 , OUTPUT);  //definir pin como salida
  pinMode(ledPIN2 , OUTPUT);  //definir pin como salida
  pinMode(ledPIN1 , OUTPUT);  //definir pin como salida


}
void loop() {
  digitalWrite(ledPIN3 , HIGH);
  digitalWrite(ledPIN2 , LOW);
  digitalWrite(ledPIN1 , HIGH);
  delay(50);
  digitalWrite(ledPIN3 , LOW);
  digitalWrite(ledPIN2 , HIGH);
  digitalWrite(ledPIN1 , LOW);
  delay(50);
}
