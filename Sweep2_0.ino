/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

short VRx = A0;
short VRy = A1;
short SW = 2;

short xPosition = 0;
short yPosition = 0;
short SW_state = 0;
short mapX = 0;
short mapY = 0;
char state = 'm';
char action = 'n';
char prev_action = 'n';
const byte interruptPin = 2;
void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(0);
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), change_state, RISING);
  Serial.begin(9600);
}

void loop() {

  
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);

  if (mapY < -300 and state == 'm'){
    action = 'r'; // right
    }
  else if (mapY > 300 and state == 'm'){
    action = 'l'; // left
    }  
  else{
    action = 'n';
    
    }
  Serial.print(pos);
  Serial.print(action);
  Serial.print(state);
  Serial.print(mapY);
  Serial.print('\n');
  switch(action){
    case 'l':
      if (pos < 180){
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);
        pos += 1;
        }
      break;
    case 'r':
      if (pos > 0){
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);   
        pos -= 1;
        }
      break;
    case 'n':
      break;
    }
   //delay();  
}
void change_state(){
  if (state == 'm'){
    state = 's';
    }
  else{
    state = 'm';}

  }

  
