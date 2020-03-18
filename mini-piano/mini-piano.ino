/*
  SparkFun Inventor’s Kit
  Circuit 2C-Simon Says

  The Simon Says game flashes a pattern using LED lights, then the player must repeat the pattern.

  This sketch was written by SparkFun Electronics, with lots of help from the Arduino community.
  This code is completely free for any use.

  View circuit diagram and instructions at: https://learn.sparkfun.com/tutorials/sparkfun-inventors-kit-experiment-guide---v40
  Download drawings and code at: https://github.com/sparkfun/SIK-Guide-Code
*/

//set the pins where the buttons, LEDs and buzzer connect
int button[] = {2, 3, 8, 9};  //red is button[0], yellow is button[1], green is button[2], blue is button[3]
int led[] = {4, 5, 6, 7};     //red is led[0], yellow is led[1], green is led[2], blue is led[3]
int tones[] = {262, 392, 440, 349};   //tones to play with each button (c, g, a, f)
int order[] = {0, 0, 1, 1, 0, 2, 3, 2, 3};
        //number of rounds the player has to play before they win the game (the array can only hold up to 16 rounds)
int maxNotes = 9; // number of notes in song
int buzzerPin = 10;           //pin that the buzzer is connected to
int count = 0;
int pressedButton = 4; 
int ledOn = 4;//a variable to remember which button is being pressed. 4 is the value if no button is being pressed.


void setup() {

  //set all of the button pins to input_pullup (use the built-in pull-up resistors)
  pinMode(button[0], INPUT_PULLUP);
  pinMode(button[1], INPUT_PULLUP);
   pinMode(button[2], INPUT_PULLUP);
  pinMode(button[3], INPUT_PULLUP);


  //set all of the LED pins to output
  pinMode(led[0], OUTPUT);
  pinMode(led[1], OUTPUT);
   pinMode(led[2], OUTPUT);
  pinMode(led[3], OUTPUT);


  pinMode(buzzerPin, OUTPUT);   //set the buzzer pin to output
}

void loop() {
  allLEDoff();
  flashLED(order[count]);
  ledOn = ledCheck();
 
  while (digitalRead(led[order[count]]) == HIGH)
  {
  pressedButton = buttonCheck();

  if(pressedButton == ledOn)
  {
   
    allLEDoff();
  }
   makeSound(pressedButton);
  }
 
count ++;
if(count > maxNotes)
{
  count = 0;
}
}

//----------FUNCTIONS------------

//FLASH LED
void flashLED (int ledNumber) {
  digitalWrite(led[ledNumber], HIGH);
}
//SOUND

void makeSound (int ledNumber){
  if(ledNumber != 4)
  {
  tone(buzzerPin,tones[ledNumber], 300);
   delay(300);
  }
}

//TURN ALL LEDS OFF
void allLEDoff () {
  //turn all the LEDs off
  digitalWrite(led[0], LOW);
  digitalWrite(led[1], LOW);
  digitalWrite(led[2], LOW);
  digitalWrite(led[3], LOW);
  //turn the buzzer off
  noTone(buzzerPin);
}

//CHECK WHICH BUTTON IS PRESSED
int buttonCheck() {
  //check if any buttons are being pressed
  if (digitalRead(button[0]) == LOW) {
    return 0;
  } else if (digitalRead(button[1]) == LOW) {
    return 1;
  } else if (digitalRead(button[2]) == LOW) {
    return 2;
  } else if (digitalRead(button[3]) == LOW) {
    return 3;
  } else {
    return 4; //this will be the value for no button being pressed
  }
}
int ledCheck() {
  //check if any buttons are being pressed
  if (digitalRead(led[0]) == HIGH) {
    return 0;
  } else if (digitalRead(led[1]) == HIGH) {
    return 1;
  } else if (digitalRead(led[2]) == HIGH) {
    return 2;
  } else if (digitalRead(led[3]) == HIGH) {
    return 3;
  } else {
    return 4; //this will be the value for no button being pressed
  }
}
