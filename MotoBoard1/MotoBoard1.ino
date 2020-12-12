//=================================================================================================
//                                            CONFIG
//=================================================================================================

// Pinout
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

//=================================================================================================
//                               SETUP-LOOP + SERIAL HANDLING
//=================================================================================================

void setup(){

}

void loop(){

}
