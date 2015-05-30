#ifndef lineSensor_h
#define lineSensor_h

#include <arduino.h>
class LineSensor{
public:
	LineSensor(int portLineSensor);

	int readSensor();


private:

	int port;	

};

#endif