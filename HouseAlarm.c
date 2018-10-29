#include <stdio.h>
#include <wiringPi.h>
#include <time.h>

void  off(){
	delay(1000);
	printf("%d\n",time(NULL));
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
	int endTime = time(NULL)+ 10;
	for (i=time(NULL);i<endTime;i = time(NULL)) {
		if( i % 2 == 0) {
			digitalWrite (1, HIGH) ; delay (500) ;
			digitalWrite (1,  LOW) ; delay (500) ;
		}
	}
	armed();
}

void armed(){
	digitalWrite(1, LOW);
	digitalWrite(2, HIGH);
	digitalWrite(4, LOW);
	printf("armed\n");
	for( ;; ){
        printf("%d\n",time(NULL));
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
	int endingTime = time(NULL) + 10;
	for(i = time(NULL); i <endingTime; i = time(NULL)){
	        if(time(NULL) % 2 == 0){
			digitalWrite(1, HIGH);
			digitalWrite(2, HIGH);
		}
		else if(time(NULL) % 2 != 0){
			digitalWrite(1, LOW);
			digitalWrite(2, LOW);
		}
		if(digitalRead(3) == 0){
			off();
		}
	}
	sounding();

}

void sounding(){
	printf("sounding\n");
	ifttt("https://maker.ifttt.com/trigger/alarm_triggered/with/key/mo6d38TDr4os0kDHywen84HzsyRomndILcmO7VGdVgz", "tailor", "lab05", "Alarm Sounded");
	for(;;){
		if(time(NULL) % 2 == 0){
			digitalWrite(1, HIGH);
			digitalWrite(2, HIGH);
			digitalWrite(4, HIGH);
		}
		else if(time(NULL) % 2 != 0){
			digitalWrite(1, LOW);
			digitalWrite(2, LOW);
			digitalWrite(4, LOW);
		}
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

