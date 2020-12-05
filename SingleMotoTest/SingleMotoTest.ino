
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
//                                       SERIAL SUPPORT
//=================================================================================================

int int_from_serial(){
	while(Serial.available() == 0){
	}
	int i = Serial.parseInt();
	while(Serial.available()){
		Serial.read();
	}
	return i;
}

double double_from_serial(){
	while(Serial.available() == 0){
	}
	double f = Serial.parseFloat();
	while(Serial.available()){
		Serial.read();
	}
	return f;
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
		analogWrite(pin_pwm, pwm<0?0:pwm>255?255:pwm);
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
				// TODO: THIS (COMMENTED PART) DO NOT WORK AS INTENDED, FIND OUT WHY
				//digitalWrite(pin_direction_forward, HIGH);
				//digitalWrite(pin_direction_reverse, HIGH);
				//analogWrite(pin_pwm, 0);
				digitalWrite(pin_direction_forward, HIGH);
				digitalWrite(pin_direction_reverse, HIGH);
				digitalWrite(pin_pwm, HIGH);
		}
	}

	void emergency_break(){
		digitalWrite(pin_direction_forward, HIGH);
		digitalWrite(pin_direction_reverse, HIGH);
		digitalWrite(pin_pwm, HIGH);
	}	

};

//=================================================================================================
//                                       PID CONTROLLER
//=================================================================================================

class Derivative{

private:
	double previous_signal_value;
	double derivative_value;

public:
	Derivative(){
		previous_signal_value = 0;
		derivative_value = 0;
	}

	void update(double signal_value){
		derivative_value = signal_value - previous_signal_value;
		previous_signal_value = signal_value;
	}

	double get_value(){
		return derivative_value;
	}
};


class Integral{

private:
	double value;

public:
	Integral(){
		value = 0;
	}

	void update(double signal_value){
		value += signal_value;
	}

	double get_value(){
		return value;
	}
};


class PIDsettings{
public:
	double p;
	double i;
	double d;

	PIDsettings(){
		p=1;
		i=0;
		d=0;
	}

	PIDsettings(double p, double i, double d){
		this->p = p;
		this->i = i;
		this->d = d;
	}
};


class PIDcontroller{

private:
	Derivative derivative;
	Integral integral;
	PIDsettings settings;
	double target;
	double response;
	bool locked;

public:
	
	PIDcontroller(){
		target = 0;
		response = 0;
		locked = false;
	}

	PIDcontroller(double p, double i, double d){
		settings = PIDsettings(p, i, d);
		target = 0;
		response = 0;
		locked = false;
	}

	bool update(double readout){
		if(locked){
			return false;
		}
		double error = target - readout;
		derivative.update(error);
		integral.update(error);
		response += settings.p*error;
		response += settings.i*integral.get_value();
		response += settings.d*derivative.get_value();
		return true;
	}

	void change_settings(PIDsettings settings){
		this->settings = settings;
	}

	void force_stop(){
		target = 0;
		response = 0;
		locked = true;
	}

	void reset(){
		locked = false;
	}
	
	bool is_locked(){
		return locked;
	}

	double get_response(){
		return response;
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
		int choice = int_from_serial();
		if(choice == 1){
			Serial.println("Select direction:");
			Serial.println("0 - forward");
			Serial.println("1 - reverse");
			int direction = int_from_serial();
			Serial.println("Enter pwm");
			int pwm = int_from_serial();
			motor.set_direction(direction);
			motor.set_pwm(pwm);
		}else if(choice == 2){
			motor.set_direction(DIRECTION_STOP);
		}else{
			motor.emergency_break();
		}
	}
}

void test_readouts_for_pid(){
	Encoder encoder(2,4);
	Derivative derivative;
	Integral integral;
	while(true){
		delay(ODOMETRY_UPDATE_PERIOD);
		encoder.update_velocity_data();
		double velocity = encoder.get_movement().to_double();
		derivative.update(velocity);
		integral.update(velocity); 
		Serial.print("Velocity=");
		Serial.print(velocity);
		Serial.print(" Integral=");
		Serial.print(integral.get_value());
		Serial.print(" Derivative=");
		Serial.println(derivative.get_value());
	}
}

void pid_test(){
	Encoder encoder(2,4);
	Motor motor(5, 6, 7);
	double p,i,d;
	double target;
	Serial.println("Configure PID controller.");
	Serial.println("What value should be assigned to proportional gain ?");
	p = double_from_serial();
	Serial.println("What value should be assigned to integral gain ?");
	i = double_from_serial();
	Serial.println("What value should be assigned to derivative gain ?");
	d = double_from_serial();
	PIDcontroller controller(p, i, d);
	Serial.println("From now on you can enter target speed into serial port");
	Serial.println("In response a nonstop stream of encoder readouts will show up");	
	target = double_from_serial();
	while(true){
		delay(ODOMETRY_UPDATE_PERIOD);
		encoder.update_velocity_data();
		double velocity = encoder.get_movement().to_double();
		controller.update(velocity);
		motor.set_pwm(controller.get_response()); // FIXME: Motor should be set with pwm/dir
		                                          //        at this time this can be negative
		encoder.get_movement().send_as_ascii();
		Serial.println();
		if(Serial.available()){
			target = double_from_serial();
		}
	}
}

void loop(){
	Serial.println("Select test :");
	Serial.println("1 - Simple encoder test");
	Serial.println("2 - Simple motor test");
	Serial.println("3 - Test readouts for PID");
	Serial.println("4 - Test PID");
	int selection = int_from_serial(); 
	switch(selection){
		case 1: simple_encoder_test();break;
		case 2: simple_motor_test();break;
		case 3: test_readouts_for_pid();break;
		case 4: pid_test();break;
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
