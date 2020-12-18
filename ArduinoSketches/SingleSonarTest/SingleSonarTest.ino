#define SERIAL_BAUD_RATE 9600
#define TRIGER 3
#define ECHO 2  // This must be an interrupt pin

//=================================================================================================
//                                      SUPPORT CODE
//=================================================================================================

class Bubbler{
private:
	long *data;
	int size;
	bool finished;
	unsigned long timestamp_start;
	unsigned long timestamp_end;
	unsigned long forced_delay;

public:
	
	Bubbler(int size, unsigned long forced_delay){
		randomSeed(micros());
		this->size = size;
		this->data = (long*)malloc(size);
		this->finished = false;
		for(int i=0; i<size; i++){
			this->data[i] = random();
		}
		timestamp_start = micros();
		timestamp_end = micros();
		this->forced_delay = forced_delay;
	}

	~Bubbler(){
		free(this->data);
	}

	bool step(){
		if(finished) return true;
		int changes = 0;
		for(int i=0; i<size-1; i++){
			if(data[i]>data[i+1]){
				long tmp = data[i];
				data[i] = data[i+1];
				data[i+1] = tmp;
				changes++;
			}
		}
		if(forced_delay){
			delayMicroseconds(forced_delay);
		}
		if(changes == 0){
			finished = true;
			this->timestamp_end = micros();
		}
		return finished;
	}

    unsigned long get_execution_time(){
		return timestamp_end - timestamp_start;
	}
};

int int_from_serial(){
	while(Serial.available() == 0){
	}
	int i = Serial.parseInt();
	while(Serial.available()){
		Serial.read();
	}
	return i;
}

//=================================================================================================
//                                     ACTIVE POOL APPROACH
//=================================================================================================

void setup_active_pool(){
	pinMode(TRIGER, OUTPUT);
	pinMode(ECHO, INPUT);
}


void active_pool(){
	digitalWrite(TRIGER, LOW);
	delayMicroseconds(4);
	digitalWrite(TRIGER, HIGH);
	delayMicroseconds(10);
	digitalWrite(TRIGER, LOW);
	unsigned long duration = pulseIn(ECHO, HIGH);
	double distance = duration * 0.017;
	Serial.print(duration, DEC);
	Serial.print(" ");
	Serial.println(distance);
}

//=================================================================================================
//                                    INTERRUPT APPROACH
//=================================================================================================

unsigned long echo_timestamp;
bool awaiting_response;

void echo_interrupt(){
	if(digitalRead(ECHO) == HIGH){
		echo_timestamp = micros();
		awaiting_response = true;
	}else{
		unsigned long duration = micros() - echo_timestamp;
		double distance = duration * 0.017;
		Serial.print(duration, DEC);
		Serial.print(" ");
		Serial.println(distance);
		awaiting_response = false;
	}
}

void setup_interrupt_based(){
	pinMode(TRIGER, OUTPUT);
	pinMode(ECHO, INPUT);
	attachInterrupt(digitalPinToInterrupt(ECHO), echo_interrupt, CHANGE);
	awaiting_response = false;
}

void cleanup_interrupt_based(){
	detachInterrupt(digitalPinToInterrupt(ECHO));
}

void sonar_ping(){
	if(awaiting_response) return;
	digitalWrite(TRIGER, LOW);
	delayMicroseconds(4);
	digitalWrite(TRIGER, HIGH);
	delayMicroseconds(10);
	digitalWrite(TRIGER, LOW);
}

//=================================================================================================
//                                       MAIN LOOP
//=================================================================================================

void setup(){
	Serial.begin(SERIAL_BAUD_RATE);
}


void loop(){
	Serial.println("Enter size of sorted array:");
	int array_size = int_from_serial();
	Serial.println("Enter forced delay in sorting step:");
	unsigned long forced_delay = int_from_serial(); 
	Bubbler bubbler(array_size, forced_delay);
	Serial.println("Choose mode :");
	Serial.println("1 - Active pooling mode");
	Serial.println("2 - Interrupt mode");
	int choice = int_from_serial();
	bool finished = false;
	if(choice == 1){
		setup_active_pool();
		while(!finished){
			active_pool();
			finished = bubbler.step();
		}
		Serial.print("Execution time : ");
		Serial.println(bubbler.get_execution_time());
	}else if(choice == 2){
		setup_interrupt_based();
		while(!finished){
			sonar_ping();
			finished = bubbler.step();
		}
		Serial.print("Execution time : ");
		Serial.println(bubbler.get_execution_time());
	}else{
		Serial.println("Mode not supported");
	}
}
