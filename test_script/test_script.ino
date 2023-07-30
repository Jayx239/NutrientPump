#include <ArduinoJson.h>
#define PUMP_INDEX "pid"
#define PUMP_DURATION_MILLISECONDS "dms"
#define MAX_MESSAGE_SIZE 256

uint8_t PUMP_PINS[] = {PD2, PD3, PD4, PD5};

char* message;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  for(int i=0; i<sizeof(PUMP_PINS); i++) {
    pinMode(PUMP_PINS[i], OUTPUT);
    Serial.print("initialize output for Pin");
    Serial.println(PUMP_PINS[i]);
  }
  message = malloc(MAX_MESSAGE_SIZE);
}

void runPumpForMs(long duration, int pumpIndex) {
  
  Serial.print("Running pump_");
  Serial.print(pumpIndex);
  Serial.print(" for ");
  Serial.print(duration);
  Serial.println(" milliseconds");

  uint8_t pump_pin = PUMP_PINS[pumpIndex];
  
  Serial.print("Pump pin: ");
  Serial.println(pump_pin);
  
  digitalWrite(pump_pin, HIGH);
  
  delay(duration);
  digitalWrite(pump_pin, LOW);

  Serial.print("Stopped pump_");
  Serial.println(pumpIndex);
}

bool isTerminatingCharacter(char nextChar) {
  if(nextChar == '\n') {
    return true;
  }

  return false;
}

void readInput() {
  while(Serial.available() < 1) {

  };

  unsigned int currentIndex = 0;
  while(true) {
    while(Serial.available() > 0) {
      // Serial.println("Serial available");
      char nextValue = Serial.read();
      if(isTerminatingCharacter(nextValue)) {
        message[currentIndex] = NULL;
        Serial.print("Input from serial: ");
        Serial.println(message);
        return;
      }
      message[currentIndex++] = nextValue;
    }
  }
  return;
}

bool isFirstRun = true;
void loop() {
    readInput();
    Serial.println("Message recieved");
    Serial.println(message);
    StaticJsonDocument<MAX_MESSAGE_SIZE> doc;
    DeserializationError error = deserializeJson(doc, message);
    if(!error) {
      Serial.println(doc[PUMP_INDEX].as<int>());
      Serial.println(doc[PUMP_DURATION_MILLISECONDS].as<long>());
      runPumpForMs(doc[PUMP_DURATION_MILLISECONDS].as<long>(), doc[PUMP_INDEX].as<int>());
  }

  // put your main code here, to run repeatedly:
    // if(isFirstRun) {
    //   runPumpForMs(200);
    //   isFirstRun = false;
    // }
}