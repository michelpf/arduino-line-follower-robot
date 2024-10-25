//Inclusao da biblioteca da Vespa
#include <RoboCore_Vespa.h>

// Pinos de entrada analógica
int sensor1 = 39;
int sensor2 = 36; 

// Inicializando valores
int sensorLeftValue = 0; 
int sensorRightValue = 0;

// Parâmetros
const bool SERIAL_LOG = true;

//Declaracao da variavel que armazena a velocidade maxima para o acionamento dos motores
const int MAXIMUM_VELOCITY = 65;
const int LINE_THRESHOLD = 3000;

//Criacao do objeto "motores" para o acionamento dos motores
VespaMotors motores;
//Criacao do objeto "bateria" para a leitura da bateria
VespaBattery bateria;
//Criacao do objeto "led"
VespaLED led;

void setup(){
  
  if (SERIAL_LOG) {
    Serial.begin(115200);
  }
  
  led.off();

}

void batteryStatus() {

  // Declaracao das variaveis que armazenam as leituras de tensao
  int battery_mV = bateria.readVoltage(); // Leitura em mV
  float battery_V = battery_mV / 1000.0; // Conversao para V

  Serial.print("Tensao da bateria em V: ");
  Serial.print(battery_V);
  Serial.println(" V");
  Serial.println("");

  if (battery_V < 3.5){
    led.on();
    Serial.println("Bateria baixa. Recarregue.");
  }
  else
  {
    led.off();
  }
}

void loop(){
  
  sensorRightValue = analogRead(sensor1); 
  sensorLeftValue = analogRead(sensor2); 
    
  if (SERIAL_LOG) {
    Serial.print("Sensor Esquerdo = ");
    Serial.print(sensorLeftValue);
    Serial.print(" | ");
    Serial.print("Sensor Direito = ");
    Serial.println(sensorRightValue);
  }

  if (sensorLeftValue > LINE_THRESHOLD && sensorRightValue > LINE_THRESHOLD) {
    Serial.print("Ambos sensores na linha.");
    Serial.print("Acionando motores na velocidade máxima.");

    motores.forward(MAXIMUM_VELOCITY);
    
  }
  else if (sensorLeftValue > LINE_THRESHOLD && sensorRightValue < LINE_THRESHOLD) {
    Serial.print("Sensor Direito fora da linha.");
    Serial.print("Fazendo curva esquerda.");

    motores.turn(0, MAXIMUM_VELOCITY);
  }
  else if (sensorRightValue > LINE_THRESHOLD && sensorLeftValue < LINE_THRESHOLD) {
    Serial.print("Sensor Esquerdo fora da linha.");
    Serial.print("Fazendo curva direita.");

    motores.turn(MAXIMUM_VELOCITY, 0);
  } 
  
  batteryStatus();
  delay(0);
}