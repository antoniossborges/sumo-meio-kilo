#include "motor.h"
#include <arduino.h>

/*
*	Contructor
*/

Motor::Motor(int portA, int portB, int portPower){
	this->motorPortA = portA;
	this->motorPortB = portB;
	this->portPower = portPower;

	pinMode(this->motorPortA, OUTPUT);
	pinMode(this->motorPortB, OUTPUT);
	pinMode(this->portPower, OUTPUT);

}

void Motor::forward(int power){

    digitalWrite(this->motorPortA, LOW);
    digitalWrite(this->motorPortB, HIGH);
    //setando o pwm    
    analogWrite(this->portPower, power); 

}

void Motor::forBack(int power){

    digitalWrite(this->motorPortA, HIGH);
    digitalWrite(this->motorPortB, LOW);
    //setando o pwm    
    analogWrite(this->portPower, power); 

}

void Motor::stop(){

    digitalWrite(this->motorPortA, HIGH);
    digitalWrite(this->motorPortB, HIGH);

    analogWrite(this->portPower, 255); 

}
