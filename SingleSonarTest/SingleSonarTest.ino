#define SERIAL_BAUD_RATE 9600
#define TRIGER 3
#define ECHO 2  // This must be an interrupt pin


class Bubbler{
private:
	long *data;
	int size;
	bool finished;
	unsigned long timestamp_start;
	unsigned long timestamp_end;

public:
	
	Bubbler(int size){
		randomSeed(micros());
		this->size = size;
		this->data = (long*)malloc(size);
		this->finished = false;
		for(int i=0; i<size; i++){
			this->data[i] = random();
		}
		timestamp_start = micros();
		timestamp_end = micros();
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
	Serial.println("Enter size of sorted array:");
	int array_size = int_from_serial();
	Bubbler bubbler(array_size);
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
	}
}
