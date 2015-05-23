#include "lineSensor.h"
#include <arduino.h>

/*
*	Contructor
*/

LineSensor::LineSensor(int portLineSensor){
	this->port = portLineSensor;
	
	pinMode(this->port, INPUT);	

}

int LineSensor::readSensor(){

	return digitalRead(port);

}
