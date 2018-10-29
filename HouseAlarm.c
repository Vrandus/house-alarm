#include <stdio.h>
#include <wiringPi.h>


void  off(){
        digitalWrite (1, LOW);
        digitalWrite (2, LOW);
        digitalWrite (4, LOW);
	printf("off\n");
	for(;;){
		if(digitalRead(3) == 0) {
			arming();
		}
	}
}

void arming(){
	int i;
	printf("arming\n");
	for (i=0;i<10;i++) {
		digitalWrite (1, HIGH) ; delay (500) ;
		digitalWrite (1,  LOW) ; delay (500) ;
		armed();
	}
}

void armed(){
	digitalWrite(1, LOW);
	digitalWrite(2, HIGH);
	digitalWrite(4, LOW);
	printf("armed\n");
	for( ;; ){
		if(digitalRead(3) == 0){
			off();
		}
		if(digitalRead(0) == 0){
			triggered();
		}
	}
}

void triggered(){
        printf("Triggered\n");
	int i;
	for(i = 0; i <5; i++){
		digitalWrite(1, HIGH);
		digitalWrite(2, HIGH); delay(1000);
		digitalWrite(1, LOW);
		digitalWrite(2, LOW); delay(1000);
		if(digitalRead(3) == 0){
			off();
		}
	}

}

void sounding(){
	printf("sounding\n");
	ifttt("http://red.eecs.yorku.ca:8080/trigger/event/with/key/123", "tailor", "lab05", "Alarm Sounded");
	for(;;){
		digitalWrite(1, HIGH);
		digitalWrite(2, HIGH);
		digitalWrite(4, HIGH);
		delay(2000);
		digitalWrite(1, LOW);
		digitalWrite(2, LOW);
		digitalWrite(4, LOW);
		delay(2000);
		if(digitalRead(3) == 0){
			off();
		}
	}
}

int main (int argc, char *argv[]){
 	wiringPiSetup () ;
	pinMode(0, INPUT);		/* IR INPUT */
	pinMode (1, OUTPUT) ;		/* LED 1 OUTPUT */
	pinMode (2, OUTPUT) ;		/* LED 2 OUTPUT */
	pinMode (3, INPUT) ;		/* BUTTON INPUT */
	pullUpDnControl(3, PUD_UP) ;	
	pinMode (4, OUTPUT) ;		/* BUZZER OUTPUT */

	off();

	/*UNREACHABLE*/
	return 0;
}

