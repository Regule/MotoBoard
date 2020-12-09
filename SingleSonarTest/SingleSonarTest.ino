#define SERIAL_BAUD_RATE 9600
#define TRIGER 3
#define ECHO 2  // This must be an interrupt pin



int int_from_serial(){
	while(Serial.available() == 0){
	}
	int i = Serial.parseInt();
	while(Serial.available()){
		Serial.read();
	}
	return i;
}

void setup(){
	Serial.begin(SERIAL_BAUD_RATE);
}

void setup_active_pool(){
	pinMode(TRIGER, OUTPUT);
	pinMode(ECHO, INPUT);
}

void active_pool(){
	digitalWrite(TRIGER, LOW);
	delayMicroseconds(2);
	digitalWrite(TRIGER, HIGH);
	delayMicroseconds(10);
	digitalWrite(TRIGER, LOW);
	unsigned long duration = pulseIn(ECHO, HIGH);
	double distance = duration * 0.017;
	Serial.print(duration, DEC);
	Serial.print(" ");
	Serial.println(distance);
}


void loop(){
	Serial.println("Choose mode :");
	Serial.println("1 - Active pooling mode");
	Serial.println("2 - Interrupt mode");
	int choice = int_from_serial();
	bool finished = false;
	if(choice == 1){
		setup_active_pool();
		while(!finished){
			active_pool();
		}
	}
}
