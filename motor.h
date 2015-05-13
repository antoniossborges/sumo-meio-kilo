#include <arduino.h>

#ifndef motor_h
#define motor_h

class Motor{
public:
	Motor(int portA, int portB, int portPower);

	void forward(int power);

	void forBack(int power);

private:

	int motorPortA;
	int motorPortB;
	int portPower;

}
