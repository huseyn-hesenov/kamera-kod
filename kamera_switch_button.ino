#include<AccelStepper.h>
#define dir 9
#define pul 8
#define buttonDown 11
#define ena 13
#define buttonUP 10
long startPosition=0;
int x = 900; // LIMIT step delay
char byteRead;
boolean isForceStop;
AccelStepper stepper(1, 9, 8);

void setup() {
  Serial.begin(9600);//Start serial protocol
  pinMode(dir, OUTPUT);
  pinMode(pul, OUTPUT);
  digitalWrite(dir, LOW);
  digitalWrite(pul, LOW);
}
void loop() {
  for (int j = 0; j < 1000; j++) {
  
    int buttonDownCase = digitalRead(buttonDown); //read button down
    int buttonUPCase = digitalRead(buttonUP); //read button up
    //Serial.print(buttonDownCase);
    //Serial.println(" ");
    //Serial.print(buttonUPCase);
    
    for (int i = 0; i < 50; i++) { //  for(int i=0; i<6; i++) {
      if (buttonDownCase==0) { //increase analog  the speed
       startPosition=stepper.currentPosition();
        digitalWrite(pul, HIGH);
        delayMicroseconds(x);
        digitalWrite(pul, LOW);
        // delayMicroseconds(x);
      }
    }

    if (x > 100) x -= 4;
    if  (buttonDownCase == 1) { //change direction motor
      digitalWrite(dir, HIGH);
      digitalWrite(pul, HIGH);
      delayMicroseconds(x);
      digitalWrite(pul, LOW);

    }
  if(ena==HIGH && startPosition!=0){
      digitalWrite(pul,HIGH);
     delayMicroseconds(x);
      digitalWrite(pul, LOW);
      
    }
    if (buttonUPCase == 1) {
      digitalWrite(ena, HIGH); //switch off motor
    }
    //    if (Serial.available()) {
    //      delay(100);
    while (Serial.available() && isForceStop == false) {
      byteRead = Serial.read();
      switch (byteRead) {
        case '0':
          Serial.write("stop");
          digitalWrite(ena,HIGH);
          isForceStop = true;
          break;
        case '1':
          Serial.write("up");
          digitalWrite(ena,LOW);
          digitalWrite(dir, HIGH);
          digitalWrite(pul, HIGH);
          delayMicroseconds(x);
          digitalWrite(pul, LOW);
          break;

      }

      //      }
    }
 isForceStop = false;
    /*Serial.print("buttonDown Case:");
      Serial.print(buttonDownCase);
      Serial.println(" ");
      delay(2000);//serial delay second
      Serial.print("buttonUp Case:");
      Serial.print(buttonUPCase);
      Serial.println(" ");
      delay(2000);*/

  }
}
