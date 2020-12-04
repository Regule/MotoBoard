
//------------------------------------GENERAL CONFIGURATION----------------------------------------
#define DEBUG_MODE 
#define SERIAL_BAUD_RATE 9600
#define ODOMETRY_UPDATE_PERIOD 100 // in milisceonds
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
		//Serial.println("Default interrupt handler called.");
	}
};


DefaultHandler default_handler;
InterruptHandler* interrupt_handlers[INTERRUPT_COUNT];

void irs_0(){interrupt_handlers[0]->handle_interrupt();}
void irs_1(){interrupt_handlers[1]->handle_interrupt();}

void(* irs_functions[])() = {irs_0, irs_1};


void assign_interrupt_handler(int interrupt_id, InterruptHandler* handler, int mode){
#ifdef DEBUG_MODE
	Serial.print("Attaching function ");
	unsigned long ptr = (unsigned long) handler;
	Serial.print(ptr);
	Serial.print(" to interrupt ");
	Serial.println(interrupt_id);
#endif
	interrupt_handlers[interrupt_id] = handler;
	attachInterrupt(interrupt_id, irs_functions[interrupt_id], mode);
}

void initialize_interrupt_handlers(){
	for(int i=0; i<INTERRUPT_COUNT; i++){
		assign_interrupt_handler(i, &default_handler, RISING);
	}
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
		forward = true;
	}

	Movement(double velocity){
		if(velocity < 0){
			this->velocity = 0 - velocity;
			this->forward = false;
		}else{
			this->velocity = velocity;
			this->forward = true;
		}
	}

	double to_double(){
		return forward?velocity:0-velocity;
	}

	Movement(double velocity, bool forward){
		this->velocity = velocity;
		this->forward = forward;
	}

	void send_as_ascii(){
		Serial.print("Velocity=");
		Serial.print(velocity);
		Serial.print(" direction=");
		if(forward){
			Serial.print("FORWARD");
		}else{
			Serial.print("REVERSE");
		}
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
		impulse_count = 0;
	}

	Movement get_movement(){
		return this->movement;
	}
};


//=================================================================================================
//                                          MOTOR CLASS 
//=================================================================================================
#define DIRECTION_FORWARD 0
#define DIRECTION_REVERSE 1
#define DIRECTION_STOP 2

class Motor{

private:
	int pin_direction_forward;
	int pin_direction_reverse;
	int pin_pwm;

public:
	
	Motor(int pin_direction_forward, int pin_direction_reverse, int pin_pwm){
		pinMode(pin_direction_forward, OUTPUT);
		pinMode(pin_direction_reverse, OUTPUT);
		pinMode(pin_pwm, OUTPUT);
		digitalWrite(pin_direction_forward, LOW);
		digitalWrite(pin_direction_reverse, LOW);
		analogWrite(pin_pwm, 0);
		this->pin_direction_forward = pin_direction_forward;
		this->pin_direction_reverse = pin_direction_reverse;
		this->pin_pwm = pin_pwm;
	}

	void set_pwm(int pwm){
		analogWrite(pin_pwm, pwm);
	}

	void set_direction(int direction){
		switch(direction){
			case DIRECTION_FORWARD:
				digitalWrite(pin_direction_forward, HIGH);
				digitalWrite(pin_direction_reverse, LOW);
				break;
			case DIRECTION_REVERSE:
				digitalWrite(pin_direction_forward, LOW);
				digitalWrite(pin_direction_reverse, HIGH);
				break;
			case DIRECTION_STOP: 
				// If default behaviour changes remember to write stop behaviour here instead
			default:
				digitalWrite(pin_direction_forward, HIGH);
				digitalWrite(pin_direction_reverse, HIGH);
				digitalWrite(pin_pwm,LOW);
		}
	}

	void emergency_break(){
		digitalWrite(pin_direction_forward, HIGH);
		digitalWrite(pin_direction_reverse, HIGH);
		digitalWrite(pin_pwm, HIGH);
	}	

};

//=================================================================================================
//                                       TESTS AND DEBUG
//=================================================================================================
#ifdef DEBUG_MODE

void setup(){
	Serial.begin(SERIAL_BAUD_RATE);
	initialize_interrupt_handlers();
}

void simple_encoder_test(){
	Encoder encoder(2,4);
	while(true){
		delay(ODOMETRY_UPDATE_PERIOD);
		encoder.update_velocity_data();
		encoder.get_movement().send_as_ascii();
		Serial.println();
	}
}

void simple_motor_test(){
	Motor motor(3, 4, 5);
	while(true){
		Serial.println("Select mode : ");
		Serial.println("1 - Move");
		Serial.println("2 - Normal stop");
		Serial.println("3 - Emergency break");
		while(Serial.available()==0){
		}
		int choice = Serial.parseInt();
		if(choice == 1){
			Serial.println("Select direction:");
			Serial.println("0 - forward");
			Serial.println("1 - reverse");
			while(Serial.available() == 0){
			}
			int direction = Serial.parseInt();
			Serial.println("Enter pwm");
			while(Serial.available() == 0){
			}
			int pwm = Serial.parseInt();
			motor.set_direction(direction);
			motor.set_pwm(pwm);
		}else if(choice == 2){
			motor.set_direction(DIRECTION_STOP);
		}else{
			motor.emergency_break();
		}
	}
}

void loop(){
	Serial.println("Select test :");
	Serial.println("1 - Simple encoder test");
	Serial.println("2 - Simple motor test");
	while(Serial.available()==0){
	}
	int selection = Serial.parseInt();
	switch(selection){
		case 1: simple_encoder_test();break;
		case 2: simple_motor_test();break;
		default: Serial.println("Test do not exist.");break;
	}
}
#endif

//=================================================================================================
//                                          MAIN CODE
//=================================================================================================
#ifndef DEBUG_MODE

void setup(){
	Serial.begin(SERIAL_BAUD_RATE);
	initialize_interrupt_handlers();
}

void loop(){
}

#endif
