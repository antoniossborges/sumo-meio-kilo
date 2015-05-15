#include "motor.h"
#include <Servo.h>

#define echoPin 2 //Pino 13 recebe o pulso do echo  
#define trigPin 4 //Pino 12 envia o pulso para gerar o echo  

//Definição portas do motor do arduino
int powerMotorLeft	= 2;
int motorE1 		= 3;
int motorE2 		= 4;
int powerMotorRight	= 5;
int motorD1 		= 6;
int motorD2 		= 7;
int servoPort       = 8;

//Definição das variaveis de controle
long distancia		= 0;
long duration 		= 0;
long tempo          = 0;
int variacao        = 0;
bool encontrou      = false;

//Criação das instancias dos motores
Motor motorRight(motorE1, motorE2, powerMotorLeft);
Motor motorLeft(motorD1, motorD2, powerMotorRight);
Servo servoMotor;

//Variaveis de controle de velocidade
int const speedMax = 230;

void setup() {

    Serial.begin(9600);  

    servoMotor.attach(servoPort);
    //Abaixar o servo
    servomotor.write(100);
    
    pinMode(echoPin, INPUT); // define o pino 13 como entrada (recebe)  
    pinMode(trigPin, OUTPUT); // define o pino 12 como saida (envia)   
    
  
}

void loop() {    

    //seta o pino 12 com um pulso baixo "LOW" ou desligado ou ainda 0  
    digitalWrite(trigPin, LOW);  
    // delay de 2 microssegundos  
    delayMicroseconds(2);  
    //seta o pino 12 com pulso alto "HIGH" ou ligado ou ainda 1  
    digitalWrite(trigPin, HIGH);  
    //delay de 10 microssegundos  
    delayMicroseconds(10);  
    //seta o pino 12 com pulso baixo novamente  
    digitalWrite(trigPin, LOW);  
    //pulseInt lê o tempo entre a chamada e o pino entrar em high  
    duration = pulseIn(echoPin,HIGH);  
    //Esse calculo é baseado em s = v . t, lembrando que o tempo vem dobrado  
    //porque é o tempo de ida e volta do ultrassom  

    distancia = duration /29 / 2 ; 
    

    if (distancia > 15 && distancia < 50 && encontrou != true){ //verifica se o oponente está fora do alcance e procura
      
      	if(tempo <= 4000){ // nos primeiros 4 segundos fica girando para o lado esquerdo lembrando que o oponente no inicio está a esquerda

       		motorRight.forward(100);
        	motorLeft.forBack(100);

      	} else if (tempo <= 7000){// dos 4 s a 7 s vai para frente para achar outro ponto

        	motorRight.forward(200);
        	motorLeft.forBack(200);

      	}else if(tempo <= 11000){ //dos 7 aos 11 s ele fica girando novamente mais para o lado direito

        	motorRight.forBack(100);
        	motorLeft.forward(100);

      	}else if (tempo > 11000){//Caso ele não tenha encontrado ainda sai procurando em zigue e zague
        
        	zigZag();
      }

    }else if (encontrou){
        /*
            verifica se a variavel encontrou foi alterada alguma vez 
            para true, se isso aconteceu significa que ele perdeu o oponente
            e e mais eficiente procurar em zig zag tendo em vista que o oponente estará perto
        */
        zigZag();
    } else if(distancia <= 15 ){// verifica se encontrou o oponente e liga o modo kamikaze
      
        /*
            Adiciona a encontrou true pois o oponente está perto, assim entrando 
            na condição acima
         */
        encontrou = true;
        //potencia total a frente, oponente está perto              
        motorRight.forward(speedMax);
        motorLeft.forward(speedMax);
        
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
