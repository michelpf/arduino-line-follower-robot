//Inclusao da biblioteca da Vespa
#include <RoboCore_Vespa.h>
#include "model.h"

Eloquent::ML::Port::RandomForest classifier;

// Pinos de entrada analógica
int sensor1 = 39;
int sensor2 = 36; 

// Inicializando valores
int sensorLeftValue = 0; 
int sensorRightValue = 0;

bool sensorLeftLine = false; 
bool sensorRightLine = false;

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
//Objeto botão
VespaButton button;

bool MACHINE_LEARNING = false;

void setup(){
  
  if (SERIAL_LOG) {
    Serial.begin(115200);
  }
  
  led.off();

  if (button.pressed()){
    MACHINE_LEARNING = true;
    led.on();
    Serial.println("Machine Learning ativado.");
  }

}

bool classify(float value) {
    float x_sample[] = { value };
    bool returnValue;

    Serial.print("Valor: ");
    Serial.print(value);
    Serial.print(", Predição: ");
    returnValue = classifier.predict(x_sample);
    Serial.println(returnValue);

    return returnValue;
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

void manualProcess(){
  
}

void loop(){
  
  sensorRightValue = analogRead(sensor1); 
  sensorLeftValue = analogRead(sensor2); 
    
  if (SERIAL_LOG) {
    Serial.print("Sensor Esquerdo = ");
    Serial.print(sensorLeftValue);
    Serial.print(", ");
    Serial.print("Sensor Direito = ");
    Serial.println(sensorRightValue);
    
  
  }

  if (MACHINE_LEARNING) {
    sensorLeftLine = classify(sensorLeftValue);
    sensorRightLine = classify(sensorRightValue);

    if (sensorLeftLine && sensorRightLine) {
    Serial.println("Ambos sensores na linha.");
    Serial.println("Acionando motores na velocidade máxima.");

    motores.forward(MAXIMUM_VELOCITY);
    }
    else if (sensorLeftLine && !sensorRightLine) {
      Serial.println("Sensor Direito fora da linha.");
      Serial.println("Fazendo curva esquerda.");

      motores.turn(0, MAXIMUM_VELOCITY);
    }
    else if (sensorRightLine && !sensorLeftLine) {
      Serial.println("Sensor Esquerdo fora da linha.");
      Serial.println("Fazendo curva direita.");

      motores.turn(MAXIMUM_VELOCITY, 0);
    }

  }
  else
  {
    if (sensorLeftValue > LINE_THRESHOLD && sensorRightValue > LINE_THRESHOLD) {
      Serial.println("Ambos sensores na linha.");
      Serial.println("Acionando motores na velocidade máxima.");

      motores.forward(MAXIMUM_VELOCITY);
    }
    else if (sensorLeftValue > LINE_THRESHOLD && sensorRightValue < LINE_THRESHOLD) {
      Serial.println("Sensor Direito fora da linha.");
      Serial.println("Fazendo curva esquerda.");

      motores.turn(0, MAXIMUM_VELOCITY);
    }
    else if (sensorRightValue > LINE_THRESHOLD && sensorLeftValue < LINE_THRESHOLD) {
      Serial.println("Sensor Esquerdo fora da linha.");
      Serial.println("Fazendo curva direita.");

      motores.turn(MAXIMUM_VELOCITY, 0);
    } 
  }

  if (!Serial){
    batteryStatus();
  }
  
  delay(0);

}