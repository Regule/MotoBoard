//=================================================================================================
//                                            CONFIG
//=================================================================================================

//------------------------------------------PINOUT-------------------------------------------------
#define PIN_ENCODER_LEFT_IMPULSE 2 // Must be external interrupt
#define PIN_ENCODER_LEFT_DIRECTION 4

#define PIN_ENCODER_RIGHT_IMPULSE 3 // Must be external interrupt
#define PIN_ENCODER_RIGHT_DIRECTION 5 

#define PIN_MOTOR_LEFT_FWD 6
#define PIN_MOTOR_LEFT_REV 7
#define PIN_MOTOR_LEFT_PWM 8

#define PIN_MOTOR_RIGHT_FWD 9
#define PIN_MOTOR_RIGHT_REV 10
#define PIN_MOTOR_RIGHT_PWM 11

#define PIN_BUMPER_LEFT 12
#define PIN_BUMPER_CENTER 13
#define PIN_BUMPER_RIGHT 14 

#define PIN_SONAR_LEFT_TRIGGER 15
#define PIN_SONAR_LEFT_ECHO 18 // Must be external interrupt

#define PIN_SONAR_CENTER_TRIGGER 16
#define PIN_SONAR_CENTER_ECHO 19 // Must be external interrupt

#define PIN_SONAR_RIGHT_TRIGGER 17
#define PIN_SONAR_RIGHT_ECHO 20 // Must be external interrupt

//------------------------------------GENERAL CONFIGURATION----------------------------------------
#define DEBUG_MODE 
#define SERIAL_BAUD_RATE 9600
#define ODOMETRY_UPDATE_PERIOD 100 // in milisceonds
#define VELOCITY_MEASURE_INTERVAL 100 //in miliseconds

//----------------------------------ROBOT PHYSICAL PROPERTIES--------------------------------------
#define INTERRUPTS_TO_MM 0.615998 // mm/impulse
#define ROBOT_WIDTH 295 // mm
#define LIN_DISPLACEMENT_RATIO INTERRUPTS_TO_MM / 2 // mm/impulse
#define THETA_RATIO INTERRUPTS_TO_MM / ROBOT_WIDTH // 1/impulse
#define SPEED_OF_SOUND 0.0343 // cm/micro-s
#define DURATION_TO_DISTACNE_FACTOR SPEED_OF_SOUND / 2 // cm/micro-s 

//-----------------------------------COMMAND ENCODING----------------------------------------------
#define DIRECTION_FORWARD 0
#define DIRECTION_REVERSE 1
#define DIRECTION_STOP 2
#define COMMAND_WRITE '>'
#define COMMAND_READ '<'
#define COMMAND_RESET 'r'
#define COMMAND_STOP 's'
#define SERIAL_SEPARATOR '#'
#define INDICATOR_MOTOR_UNLOCKED 'U'
#define INDICATOR_MOTOR_LOCKED 'L'
#define INDICATOR_BUMPER_RELEASED 'R'
#define INDICATOR_BUMPER_PRESSED 'P'

//=================================================================================================
//                                     INTERRUPT HANDLING
//=================================================================================================
#define INTERRUPT_COUNT 6

class InterruptHandler{
public:
	virtual void handle_interrupt() = 0;	
};

InterruptHandler* interrupt_handlers[INTERRUPT_COUNT];

void irs_0(){interrupt_handlers[0]->handle_interrupt();}
void irs_1(){interrupt_handlers[1]->handle_interrupt();}
void irs_2(){interrupt_handlers[2]->handle_interrupt();}
void irs_3(){interrupt_handlers[3]->handle_interrupt();}
void irs_4(){interrupt_handlers[4]->handle_interrupt();}
void irs_5(){interrupt_handlers[5]->handle_interrupt();}

void(* irs_functions[])() = {irs_0, irs_1, irs_2, irs_3, irs_4, irs_5};

void assign_interrupt_handler(int interrupt_id, InterruptHandler* handler, int mode){
	interrupt_handlers[interrupt_id] = handler;
	attachInterrupt(interrupt_id, irs_functions[interrupt_id], mode);
}

void disable_interrupt_handler(int interrupt_id){
	interrupt_handlers[interrupt_id] = NULL;
	detachInterrupt(interrupt_id);	
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

class Motor{

private:
	int pin_direction_forward;
	int pin_direction_reverse;
	int pin_pwm;
	int direction;
	int locked;
	int pwm;

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
		this->direction = DIRECTION_STOP;
		this->locked = false;
		this->pwm = 0;
	}

	void reset(){
		locked = false;
	}

	bool is_locked(){
		return locked;
	}

	void set_pwm(int pwm){
		if(locked) return;
		this->pwm = pwm<0?0:pwm>255?255:pwm;
		analogWrite(pin_pwm, this->pwm);
	}

	int get_pwm(){
		return this->pwm;
	}

	void set_direction(int direction){
		if(locked) return;
		this->direction = direction;
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
				this->direction = DIRECTION_STOP;
		}
	}

	int get_direction(){
		return direction;
	}

	void emergency_break(){
		digitalWrite(pin_direction_forward, HIGH);
		digitalWrite(pin_direction_reverse, HIGH);
		digitalWrite(pin_pwm, HIGH);
		this->direction = DIRECTION_STOP;
		this->pwm = 0;
		this->locked = true;
	}	

};


//=================================================================================================
//                                             SONAR
//=================================================================================================

class Sonar: public InterruptHandler{
private:
	int trigger_pin;
	int echo_pin;
	unsigned long timestamp;
	unsigned long duration;
	bool awaiting_response;

public:
	Sonar(int trigger_pin, int echo_pin){
		this->trigger_pin = trigger_pin;
		this->echo_pin = echo_pin;
		this->timestamp = 0;
		this->duration = 0;
		this->awaiting_response = false;
		pinMode(trigger_pin, OUTPUT);
		pinMode(echo_pin, INPUT);
		assign_interrupt_handler(digitalPinToInterrupt(echo_pin), this, CHANGE);	
	}

	void handle_interrupt(){
		if(digitalRead(echo_pin) == HIGH){
			timestamp = micros();
			awaiting_response = true;
		}else{
			duration = micros() - timestamp;
			awaiting_response = false;
		}
	}

	void ping(){
		if(!awaiting_response){
			digitalWrite(trigger_pin, LOW);
			delayMicroseconds(4);
			digitalWrite(trigger_pin, HIGH);
			delayMicroseconds(10);
			digitalWrite(trigger_pin, LOW);
		}
	}

	double get_distance(){
		return duration * DURATION_TO_DISTACNE_FACTOR;
	}

	~Sonar(){
		disable_interrupt_handler(digitalPinToInterrupt(echo_pin));
	}


};


//=================================================================================================
//                               SETUP-LOOP + SERIAL HANDLING
//=================================================================================================


void setup(){
	Serial.begin(SERIAL_BAUD_RATE);
}

void loop(){
	// This is more of a setup, also bumpers are ugly in this version
	Motor motor_left(PIN_MOTOR_LEFT_FWD, PIN_MOTOR_LEFT_REV, PIN_MOTOR_LEFT_PWM);
	Motor motor_right(PIN_MOTOR_RIGHT_FWD, PIN_MOTOR_RIGHT_REV, PIN_MOTOR_RIGHT_PWM);
	Encoder encoder_left(PIN_ENCODER_LEFT_IMPULSE, PIN_ENCODER_LEFT_DIRECTION);
	Encoder encoder_right(PIN_ENCODER_RIGHT_IMPULSE, PIN_ENCODER_RIGHT_DIRECTION);
	Sonar sonar_left(PIN_SONAR_LEFT_TRIGGER, PIN_SONAR_LEFT_ECHO);
	Sonar sonar_center(PIN_SONAR_CENTER_TRIGGER, PIN_SONAR_CENTER_ECHO);
	Sonar sonar_right(PIN_SONAR_RIGHT_TRIGGER, PIN_SONAR_RIGHT_ECHO);
	pinMode(PIN_BUMPER_LEFT, INPUT);
	pinMode(PIN_BUMPER_CENTER, INPUT);
	pinMode(PIN_BUMPER_RIGHT, INPUT);
	int bumper_left = digitalRead(PIN_BUMPER_LEFT);
	int bumper_center = digitalRead(PIN_BUMPER_CENTER);
	int bumper_right = digitalRead(PIN_BUMPER_RIGHT);

	// Actual loop
	while(true){
		bumper_left = digitalRead(PIN_BUMPER_LEFT);
		bumper_center = digitalRead(PIN_BUMPER_CENTER);
		bumper_right = digitalRead(PIN_BUMPER_RIGHT);
		if(bumper_left == LOW || bumper_center == LOW || bumper_right == LOW){
			motor_left.emergency_break();
			motor_right.emergency_break();
		}
		sonar_left.ping();
		sonar_center.ping();
		sonar_right.ping();
		if(Serial.available()){
			int cmd_char = Serial.read();
			//Serial.print("Command code = ");
			//Serial.println(cmd_char);
			if(cmd_char == COMMAND_WRITE){
				//Serial.println("Recieved write command");
				int dir_left = Serial.parseInt();
				Serial.read();
				int pwm_left = Serial.parseInt();
				Serial.read();
				int dir_right = Serial.parseInt();
				Serial.read();
				int pwm_right = Serial.parseInt();
				motor_left.set_direction(dir_left);
				motor_right.set_direction(dir_right);
				motor_left.set_pwm(pwm_left);
				motor_right.set_pwm(pwm_right);
			}else if(cmd_char == COMMAND_READ){
				encoder_left.update_velocity_data();
				encoder_right.update_velocity_data();
				Serial.print(encoder_left.get_movement().to_double());
				Serial.print(SERIAL_SEPARATOR);
				Serial.print(encoder_right.get_movement().to_double());
				Serial.print(SERIAL_SEPARATOR);
				Serial.print(motor_left.is_locked()?INDICATOR_MOTOR_LOCKED:INDICATOR_MOTOR_UNLOCKED);
				Serial.print(SERIAL_SEPARATOR);
				Serial.print(motor_left.get_direction());
				Serial.print(SERIAL_SEPARATOR);
				Serial.print(motor_left.get_pwm());
				Serial.print(SERIAL_SEPARATOR);
				Serial.print(motor_right.is_locked()?INDICATOR_MOTOR_LOCKED:INDICATOR_MOTOR_UNLOCKED);
				Serial.print(SERIAL_SEPARATOR);
				Serial.print(motor_right.get_direction());
				Serial.print(SERIAL_SEPARATOR);
				Serial.print(motor_right.get_pwm());
				Serial.print(SERIAL_SEPARATOR);
				Serial.print(sonar_left.get_distance());
				Serial.print(SERIAL_SEPARATOR);
				Serial.print(sonar_center.get_distance());
				Serial.print(SERIAL_SEPARATOR);
				Serial.print(sonar_right.get_distance());
				Serial.print(SERIAL_SEPARATOR);
				Serial.print(bumper_left==LOW?INDICATOR_BUMPER_PRESSED:INDICATOR_BUMPER_RELEASED);
				Serial.print(SERIAL_SEPARATOR);
				Serial.print(bumper_center==LOW?INDICATOR_BUMPER_PRESSED:INDICATOR_BUMPER_RELEASED);
				Serial.print(SERIAL_SEPARATOR);
				Serial.println(bumper_right==LOW?INDICATOR_BUMPER_PRESSED:INDICATOR_BUMPER_RELEASED);
			}else if(cmd_char == COMMAND_STOP){
				motor_left.emergency_break();
				motor_right.emergency_break();
			}else if(cmd_char == COMMAND_RESET){
				motor_left.reset();
				motor_right.reset();
			}
		}
	}
}
