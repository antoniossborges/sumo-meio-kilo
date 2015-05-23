#include "motor.h"
#include "Accelerometer.h"
#include <Servo.h>
#include "Maxbotix.h"
#include "lineSensor.h"


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
int portLineSensorRightRear     = 1;
int portLineSensorLeftRear      = 13;
int portLineSensorRightFront    = 11;
int portLineSensorLeftFront     = 12;

//Definição das variaveis de controle

long duration       = 0;
long tempo          = 0;
int variacao        = 0;
//Verifica se encontrou o oponente em algum momento
bool find          = false;
unsigned int range  = 0;

int atualX;
int atualY;
int atualZ;

int valueLineRightRear;
int valueLineLeftRear;
int valueLineRightFront;
int valueLineLeftFront;


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

    Serial.begin(9600);  
    //Iniciando o servo
    servoMotorRight.attach(servoPortRigth);
    servoMotorLeft.attach(servoPortLeft);
    //Abaixar o servo
    servoMotorRight.write(180);    
    servoMotorLeft.write(0);    
  
}

void loop() {    

    range = rangeSensor.getRange();
    valueLineRightRear = lineSensorRightRear.readSensor();
    valueLineLeftRear = lineSensorLeftRear.readSensor();
    valueLineRightFront = lineSensorRightFront.readSensor();
    valueLineLeftRear = lineSensorLeftRear.readSensor();

    //Lendo dados acelerometro
    readAccelerometer();
    
    if(valueLineRightRear == 1 || valueLineLeftRear == 1 || valueLineRightFront == 1 || valueLineLeftFront == 1){
        motorRight.stop();
        motorLeft.stop();
        delay(5000);

    }

    if (range > 15 && range < 50 && find != true){ //verifica se o oponente está fora do alcance e procura
      
        if(tempo <= 4000){ // nos primeiros 4 segundos fica girando para o lado esquerdo lembrando que o oponente no inicio está a esquerda

            turnLeft(100);

        } else if (tempo <= 7000){// dos 4 s a 7 s vai para frente para achar outro ponto

            kamikaze(100);

        }else if(tempo <= 11000){ //dos 7 aos 11 s ele fica girando novamente mais para o lado direito

            turnLeft(100);

        }else if (tempo > 11000){//Caso ele não tenha encontrado ainda sai procurando em zigue e zague
        
            zigZag();
      }

    }else if (find){
        /*
            verifica se a variavel encontrou foi alterada alguma vez 
            para true, se isso aconteceu significa que ele perdeu o oponente
            e e mais eficiente procurar em zig zag tendo em vista que o oponente estará perto
        */
        zigZag();
    } else if(range <= 15 ){// verifica se encontrou o oponente e liga o modo kamikaze
      
        /*
            Adiciona a encontrou true pois o oponente está perto, assim entrando 
            na condição acima
         */
        find = true;
        //potencia total a frente, oponente está perto   
        kamikaze(speedMax);       
        
    }   

    tempo++;  
}

/*
    Metodo utilizado para fazer com que os motores alterem entre 
    fazer uma curva a direita e esquerda
*/
void zigZag(){
    
    if(variacao < 500){

        motorRight.forward(100);
        motorLeft.forward(30);   

    }else if (variacao < 1000){

        motorRight.forward(30);
        motorLeft.forward(100);

    }else{

        variacao = 0;

    }  
            
    variacao++;
    
}

void kamikaze(int power){
    
    motorRight.forward(power);
    motorLeft.forward(power);

}

void readAccelerometer(){

    atualX = accelerometer.getAxisValueX();
    atualY = accelerometer.getAxisValueY();
    atualZ = accelerometer.getAxisValueZ();
}

void turnRight(int power){

    motorRight.forward(power);
    motorLeft.forBack(power);

}

void turnLeft(int power){

    motorRight.forBack(power);
    motorLeft.forward(power);

}
