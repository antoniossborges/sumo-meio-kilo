#include "Motor.h"
#include "Accelerometer.h"
#include <Servo.h>
#include "Maxbotix.h"
#include "LineSensor.h"


/*
    Port of driver motor        Port of sensor range (Sonar)

    ---------------------           --------------------- 
    |   Port  | Number  |           |   Port  | Number  |    
    ---------------------           ---------------------
    | pinENA  |     6   |           |   PW    |    10   |
    | pinIN1  |     7   |           ---------------------
    | pinIN2  |     5   |
    | pinENB  |     3   |        Port of servo motor   
    | pinIN3  |     4   |           
    | pinIN4  |     2   |           ----------------------------
    ---------------------           |   Port         | Number  |
                                    ----------------------------
                                    | Servo Right   |  8       |
                                    | Servo Left    |  9       |
                                    ----------------------------
   
   Port of sensor line                          Port of accelerometer

   ---------------------------------            ---------------------------- 
   |            Port     | Number  |            |   Port         | Number  |
   ---------------------------------            ---------------------------- 
   | Port line sensor    |  1      |            | Port axis X    |   ?     |
   |    right rear       |         |            | Port axis Y    |   ?     |
   =================================            | Port axis Z    |   ?     |
   | Port line sensor    |  13     |            ----------------------------
   |    left rear        |         |
   =================================
   | Port line sensor    |  11     |
   |    right front      |         |
   =================================
   | Port line sensor    |  12     |
   |    left front       |         |
   ---------------------------------



*/

//Definição portas do motor do arduino
int powerMotorLeft          = 6;
int motorE1                 = 7;
int motorE2                 = 5;
int powerMotorRight         = 3;
int motorD1                 = 4;
int motorD2                 = 2;

int servoPortRigth          = 8;
int servoPortLeft           = 9;
int x;
int y;
int z;

//Porta dos sensores de linha
int portLineSensorRightRear     = 13;
int portLineSensorLeftRear      = 12;
int portLineSensorRightFront    = 1;
int portLineSensorLeftFront     = 11;

//Definição das variaveis de controle

long duration       = 0;
long tempo          = 0;
int variacao        = 0;
//Verifica se encontrou o oponente em algum momento
bool find          = false;
unsigned int range  = 0;
int pot;
int pot1;
int controle;

int atualX;
int atualY;
int atualZ;

int valueLineRightRear;
int valueLineLeftRear;
int valueLineRightFront;
int valueLineLeftFront;

int posicaoServo =138;


//Criação das instancias dos motores
Motor motorRight(motorE1, motorE2, powerMotorLeft);
Motor motorLeft(motorD1, motorD2, powerMotorRight);
Servo servoMotorRight;
Servo servoMotorLeft;
Accelerometer accelerometer(x, y, z);
Maxbotix rangeSensor(10, Maxbotix::PW, Maxbotix::LV);

LineSensor lineSensorRightRear(portLineSensorRightRear);
LineSensor lineSensorLeftRear(portLineSensorLeftRear);
LineSensor lineSensorRightFront(portLineSensorRightFront);
LineSensor lineSensorLeftFront(portLineSensorLeftFront);

//Variaveis de controle de velocidade
int const speedMax = 230;

void setup() {

   //Serial.begin(9600);  
    //Iniciando o servo
    servoMotorRight.attach(servoPortRigth);
    servoMotorLeft.attach(servoPortLeft);
    
    controleServo(143);

    //Abaixar o servo
    //servoMotorRight.write(180);    
    //servoMotorLeft.write(0);    
  
}

void loop() {    

 //   range = rangeSensor.getRange();

    valueLineRightRear = lineSensorRightRear.readSensor();
    valueLineLeftRear = lineSensorLeftRear.readSensor();
    valueLineRightFront = lineSensorRightFront.readSensor();
    valueLineLeftFront = lineSensorLeftFront.readSensor();
    
    //Lendo dados acelerometro
    //readAccelerometer();


    //Serial.print("Range = ");
    //Serial.println(range);
   /*Serial.print("EF = ");
    Serial.print(valueLineLeftFront);
    Serial.print("       DF = ");
    Serial.println(valueLineRightFront);
    Serial.print("ET = ");
    Serial.print(valueLineLeftRear);
    Serial.print("       DT = ");
    Serial.println(valueLineRightRear);*/
    //Serial.println(tempo);
    
    
    
    //Verifica o estado dos sensores de linha
   if(valueLineRightRear == 0 || valueLineLeftRear == 0 || valueLineRightFront == 0 || valueLineLeftFront == 0){

        //Se os dois sensores de linha da frente forem acionado significa que ele chegou ao fim do campo
        //com a parte da frente
        if(valueLineLeftFront == 0 && valueLineRightFront == 0){

            stopMotor();
            retire(255);
            delay(25);
            turnLeft(255);
            delay(25);

        }else if(valueLineRightRear == 0 || valueLineLeftRear == 0){

            kamikaze(255);
            delay(25);
            turnRight(255);
            delay(25);

        }else{
            retire(255);
            delay(25);
            turnLeft(255);
            delay(25); 
            
        }
    }else{
        //stopMotor();

       
        kamikaze(255);    
    }

    

     

    

   // tempo++;  */
}

/*
    Metodo utilizado para fazer com que os motores alterem entre 
    fazer uma curva a direita e esquerda
*/
void zigZag(){
    controle = 3;
    
    if(variacao < 8){
        
        pot=1;
        pot1=1;

        while(pot < 200){

            motorRight.forward(pot);
            motorLeft.forward(pot1);   
            pot = pot + 10;
            pot1++;

            delay(2);
        }

    }else if (variacao < 11){

        pot=1;
        pot1=1;

        while(pot < 200){

            motorRight.forward(pot1);
            motorLeft.forward(pot);
            pot = pot + 8;
            pot1++;

            delay(2);
        }

    }else{

        variacao = 0;

    }  
            
    variacao++;
    Serial.println(variacao);
    
}

void kamikaze(int power){

    if(controle ==1){

        controle =1;
        pot = 1;
        while(pot < power){

            motorRight.forward(pot);
            motorLeft.forward(pot);    
            pot++;
            delay(1);
        }

    }else{
        motorRight.forward(power);
        motorLeft.forward(power);  


    }

    
}

void retire(int power){
    controle =2;

    pot = 1;
    while(pot < power){

        motorRight.forBack(pot);
        motorLeft.forBack(pot);
        pot++;
        delay(1);

    }
}

void readAccelerometer(){

    atualX = accelerometer.getAxisValueX();
    atualY = accelerometer.getAxisValueY();
    atualZ = accelerometer.getAxisValueZ();
}

void turnRight(int power){

    pot=1;
    while(pot < power){
        
        motorRight.forward(pot);
        motorLeft.forBack(pot);
        pot++;
        delay(1);

    }
}

void turnLeft(int power){

    pot = 1;
    while(pot < power){

        motorRight.forBack(power);
        motorLeft.forward(power);
        pot++;
        delay(1);

    }
}

void stopMotor(){

    motorLeft.stop();
    motorRight.stop();

}

void controleServo(int posicao){
    
    servoMotorRight.write(posicao + 10);   //143
    servoMotorLeft.write(180 - posicao);

}
