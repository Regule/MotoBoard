//=================================================================================================
//                                           INCLUDES
//=================================================================================================
#include<LiquidCrystal.h>


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
class Encoder {

private:
	Movement movement;

public:

	Encoder(int pin_impulse, int pin_direction){
	}


	void update_velocity_data(){
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
	int direction;
	int locked;
	int pwm;

public:
	
	Motor(int pin_direction_forward, int pin_direction_reverse, int pin_pwm){
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
	}

	int get_pwm(){
		return this->pwm;
	}

	void set_direction(int direction){
		if(locked) return;
		this->direction = direction;
	}

	int get_direction(){
		return direction;
	}

	void emergency_break(){
		this->direction = DIRECTION_STOP;
		this->pwm = 0;
		this->locked = true;
	}	

};


//=================================================================================================
//                                             SONAR
//=================================================================================================

class Sonar{
private:

public:
	Sonar(int trigger_pin, int echo_pin){
	}

	void handle_interrupt(){
	}

	void ping(){
	}

	double get_distance(){
		return 0.22; 
	}

	~Sonar(){
	}


};

//=================================================================================================
//                                      USER INTERFACE (LCD)
//=================================================================================================
#define LCD_TITLE_SCREEN 0
#define LCD_BUTTON_DEBUG 1

#define LCD_BUTTON_NONE 10
#define LCD_BUTTON_LEFT 8
#define LCD_BUTTON_RIGHT 2
#define LCD_BUTTON_UP 5
#define LCD_BUTTON_DOWN 6
#define LCD_BUTTON_ACTION 0

#define LCD_PIN_BUTTONS 0

#define LCD_UI_ERROR_MSG "UI ERROR"

LiquidCrystal lcd(8,9,4,5,6,7);
int lcd_ui_cursor=0;
bool button_pressed=false;
int lcd_state = LCD_TITLE_SCREEN;

int lcd_read_button(){
	int button = (int)analogRead(LCD_PIN_BUTTONS)/100;
	if(!button_pressed && button != LCD_BUTTON_NONE){
		button_pressed = true;
	}else if(button_pressed && button == LCD_BUTTON_NONE){
		button_pressed = false;
	}else{
		button = LCD_BUTTON_NONE;
	}
	return button;
}

void lcd_title_screen(){
	lcd.setCursor(0,0);
	lcd.print("Oculi Mobili");
	lcd.setCursor(0,1);
	switch(lcd_ui_cursor){
		case 0 : lcd.print("Test board"); break;
		case 1 : lcd.print("Encoders"); break;
		case 2 : lcd.print("Motors"); break;
		case 3 : lcd.print("Sonars"); break;
		case 4 : lcd.print("Bumpers"); break;
		default : lcd.print(LCD_UI_ERROR_MSG); break; 
	}
	switch(lcd_read_button()){
		case LCD_BUTTON_UP:
			lcd_ui_cursor--;
			if(lcd_ui_cursor<=0) lcd_ui_cursor = 4;
			lcd.clear();
			break;
		case LCD_BUTTON_DOWN:
			lcd_ui_cursor++;
			lcd.clear();
			if(lcd_ui_cursor>4) lcd_ui_cursor = 1;
			break;
		case LCD_BUTTON_ACTION:
			lcd_state = lcd_ui_cursor;
			lcd_ui_cursor = 0;
			lcd.clear();
	}
}

void lcd_encoders(){
	lcd.setCursor(0,0);
	lcd.print("Encoders:");
	switch(lcd_read_button()){
		case LCD_BUTTON_ACTION:
			lcd_state = LCD_TITLE_SCREEN;
			lcd_ui_cursor = 0;
			lcd.clear();
	}
}

void lcd_motors(){
	lcd.setCursor(0,0);
	lcd.print("Motors:");
	switch(lcd_read_button()){
		case LCD_BUTTON_ACTION:
			lcd_state = LCD_TITLE_SCREEN;
			lcd_ui_cursor = 0;
			lcd.clear();
	}
}

void lcd_sonars(){
	lcd.setCursor(0,0);
	lcd.print("Sonars:");
	switch(lcd_read_button()){
		case LCD_BUTTON_ACTION:
			lcd_state = LCD_TITLE_SCREEN;
			lcd_ui_cursor = 0;
			lcd.clear();
	}
}

void lcd_bumpers(){
	lcd.setCursor(0,0);
	lcd.print("Bumpers:");
	switch(lcd_read_button()){
		case LCD_BUTTON_ACTION:
			lcd_state = LCD_TITLE_SCREEN;
			lcd_ui_cursor = 0;
			lcd.clear();
	}
}
 

void lcd_debug_buttons(){
	lcd.setCursor(0,0);
	lcd.print("Button input:");
	lcd.setCursor(0,1);
	lcd.print("            ");
	lcd.setCursor(0,1);
	lcd.print(analogRead(LCD_PIN_BUTTONS));
	lcd.print(" ");
	int button = lcd_read_button();
	lcd.print(button);
	lcd.print(" ");
	switch(lcd_read_button()){
		case LCD_BUTTON_NONE: lcd.print("NONE"); break;
		case LCD_BUTTON_LEFT: lcd.print("LEFT"); break;
		case LCD_BUTTON_RIGHT: lcd.print("RIGHT"); break;
		case LCD_BUTTON_UP: lcd.print("UP"); break;
		case LCD_BUTTON_DOWN: lcd.print("DOWN"); break;
		case LCD_BUTTON_ACTION: lcd.print("ACTION"); break;
		default: lcd.print("UNKNOWN");
	}
}

void(* lcd_handlers[])() = {lcd_title_screen, lcd_encoders, lcd_motors, lcd_sonars, lcd_bumpers}; 

//=================================================================================================
//                                   SETUP-LOOP + SERIAL HANDLING
//=================================================================================================


void setup(){
	Serial.begin(SERIAL_BAUD_RATE);
	lcd.begin(16,2);
	lcd_title_screen();
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

	int bumper_left = HIGH;
	int bumper_center = HIGH;
	int bumper_right = HIGH;
	// Actual loop
	while(true){
		lcd_handlers[lcd_state]();
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
