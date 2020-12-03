#define SERIAL_BAUD_RATE 9600

//=================================================================================================
//                                     INTERRUPT HANDLING
//=================================================================================================
#define INTERRUPT_COUNT 2

class InterruptHandler{
public:
	virtual void handle_interrupt() = 0;	
};


class DefaultHandler: public InterruptHandler{
public:
	void handle_interrupt(){
		Serial.println("Default interrupt handler called.");
	}
};


DefaultHandler default_handler;
InterruptHandler* interrupt_handlers[INTERRUPT_COUNT];

void irs_0(){Serial.print("WTF");interrupt_handlers[0]->handle_interrupt();}
void irs_1(){interrupt_handlers[1]->handle_interrupt();}

void(* irs_functions[])() = {irs_0, irs_1};

void initialize_interrupt_handlers(){
	for(int i=0; i<INTERRUPT_COUNT; i++){
		interrupt_handlers[i] = &default_handler;
		attachInterrupt(i,irs_functions[i],RISING);
	}
}

void assign_interrupt_handler(int interrupt_id, InterruptHandler* handler, int mode){
	interrupt_handlers[interrupt_id] = handler;
	attachInterrupt(interrupt_id, irs_functions[interrupt_id], mode);
}



//=================================================================================================
//                                         ENCODER CLASS 
//=================================================================================================
class Encoder: public InterruptHandler{

private:
	int pin_impulse;
	int pin_direction;
	unsigned long impule_count;
	unsigned long timestamp;
	double velocity;

public:

	Encoder(int pin_impulse, int pin_direction){
		this->pin_impulse = pin_impulse;
		this->pin_direction = pin_direction;
		this->impule_count = 0;
		this->timestamp = millis();
		this->velocity = 0; 
		pinMode(pin_impulse, INPUT);
		pinMode(pin_direction, INPUT);
		assign_interrupt_handler(digitalPinToInterrupt(pin_impulse), this, RISING);
	}

	void handle_interrupt(){
	}
};



//=================================================================================================
//                                          MOTOR CLASS 
//=================================================================================================
class Motor{

private:
	int pin_direction_forward;
	int pin_direction_reverse;
	int pin_pwm;
	

};

//=================================================================================================
//                                          MAIN CODE
//=================================================================================================

void setup(){
	Serial.begin(SERIAL_BAUD_RATE);
	initialize_interrupt_handlers();
}

void loop(){
}
