
//------------------------------------GENERAL CONFIGURATION----------------------------------------
#define SERIAL_BAUD_RATE 9600
#define ODOMETRY_CHECK_INTERVAL 100 // in milisceonds
#define VELOCITY_MEASURE_INTERVAL 100 //in miliseconds

//----------------------------------ROBOT PHYSICAL PROPERTIES--------------------------------------
#define INTERRUPTS_TO_MM 0.615998
#define ROBOT_WIDTH 295
#define LIN_DISPLACEMENT_RATIO INTERRUPTS_TO_MM / 2
#define THETA_RATIO INTERRUPTS_TO_MM / ROBOT_WIDTH

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
//                                         MOVEMENT CLASS
//=================================================================================================
class Movement{
public:
	double velocity;
	bool forward;

	Movement(){
		velocity = 0.0;
		forward = false;
	}

	Movement(double velocity, bool forward){
		this->velocity = velocity;
		this->forward = forward;
	}
};


//=================================================================================================
//                                         ENCODER CLASS 
//=================================================================================================
class Encoder: public InterruptHandler{

private:
	int pin_impulse;
	int pin_direction;
	unsigned long impulse_count;
	unsigned long timestamp;
	Movement movement;

public:

	Encoder(int pin_impulse, int pin_direction){
		this->pin_impulse = pin_impulse;
		this->pin_direction = pin_direction;
		this->impulse_count = 0;
		this->timestamp = millis();
		pinMode(pin_impulse, INPUT);
		pinMode(pin_direction, INPUT);
		assign_interrupt_handler(digitalPinToInterrupt(pin_impulse), this, RISING);
	}

	void handle_interrupt(){
		impulse_count++;
		movement.forward = digitalRead(pin_direction); 
	}

	void update_velocity_data(){
		unsigned long now = millis();
		movement.velocity = (double)(impulse_count)*INTERRUPTS_TO_MM / (now-timestamp);
		timestamp = now;
	}

	Movement get_movement(){
		return this->movement;
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
