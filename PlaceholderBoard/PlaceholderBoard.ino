#define SERIAL_BAUD_RATE 9600

//=================================================================================================
//                                       STREAM HANDLING
//=================================================================================================
class Serializable{

public:
	virtual void send_as_ascii(Stream *stream) = 0;
	virtual void send_as_binary(Stream *stream) = 0;
	virtual void read_from_ascii(Stream *stream) = 0;
	virtual void read_from_binary(Stream *stream) = 0;
};

//=================================================================================================
//                                          MAIN CODE
//=================================================================================================

void setup(){
	Serial.begin(SERIAL_BAUD_RATE);
}

void loop(){
}

