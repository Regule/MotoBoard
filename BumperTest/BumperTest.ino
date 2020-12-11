#define SERIAL_BAUDRATE 9600
#define BUMPER_PIN 2

void bumper_handler(){
	Serial.println("BUMP");
}

void setup(){
	Serial.begin(9600);
	pinMode(BUMPER_PIN, INPUT);
	attachInterrupt(digitalPinToInterrupt(BUMPER_PIN), bumper_handler, FALLING);
}

void loop(){
}
