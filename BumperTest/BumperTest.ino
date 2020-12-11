#define SERIAL_BAUDRATE 9600
#define BUMPER_PIN 2
#define BUMPER_DEBOUNCE_PERIOD 10

unsigned long last_interrupt;

void bumper_handler(){
	if(millis()-last_interrupt<BUMPER_DEBOUNCE_PERIOD){
		return;
	}
	last_interrupt = millis();
	Serial.println("BUMP");
}

void setup(){
	Serial.begin(9600);
	pinMode(BUMPER_PIN, INPUT);
	attachInterrupt(digitalPinToInterrupt(BUMPER_PIN), bumper_handler, FALLING);
	last_interrupt = 0;
}

void loop(){
}
