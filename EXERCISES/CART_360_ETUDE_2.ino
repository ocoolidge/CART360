/**********************ETUDE 2 CART 360 2017*******************************
 OWEN COOLIDGE ANALYSIS:
 
 As electricity travels from the arduino's 5V output to the resistory ladder it is impeded by different, 
 incrementing amounts resulting in a decreased amperage.  The buttons further away from analog input A0 on 
 the resistor ladder input less amps to the arduino.  The program on the arduino tells the buzzer through 
 digital output (pulse width modulation) to emit sound at different frequencies based on the different amperage 
 that it recieves. lower amperage --> lower frequency.

 The chooseMode() function in void loop() checks BUTTON_MODE_PIN (digital pin 2) repeatedly at a very high frequency 
 for a discrete change.  If the user presses the button connected to pin 2 the function incremets the "mode" variable 
 which changes the color of the light and the arduino's interpritation of its inputs.  If the arduino is in the last 
 mode (4) the chooseMode() function loops it back to the first mode (0).
 
/**** CONSTANTS ********************************************************/

#define BUTTON_MODE_PIN 2 // Button to change the mode

// constants for RGB LED
#define LED_PIN_R 5 // R PIN
#define LED_PIN_G 9 // G PIN
#define LED_PIN_B 6 // B PIN

// constant for note in (button-resistor ladder on breadboard)
# define NOTE_IN_PIN A0

//constant for max number of notes in array
#define MAX_NOTES 16

// a constant for duration
const int duration = 50;

// constant for pin to output for buzzer 
#define BUZZER_PIN 3 // PWM

/******** VARIABLES *****************************************************/
// counter for how many notes we have
int countNotes =0;
// array to hold the notes played (for record/play mode)
int notes [MAX_NOTES];
// array to hold the tiem between notes (for record/loop mode)
int noteTime[MAX_NOTES];
int mode = 0; // start at off

/*************************************************************************/

void setup()
{
  pinMode(BUTTON_MODE_PIN, INPUT);
  Serial.begin(9600);
}

void loop()
{
  chooseMode();
  setRGB();
  selectMode();
}

void chooseMode(){

  if(digitalRead(BUTTON_MODE_PIN) == HIGH && mode == 4 ){
    delay(250);
    mode = 0;
  }
  else if(digitalRead(BUTTON_MODE_PIN) == HIGH){
    delay(250);
    mode++;
  }
  
}

void setRGB()
{
  //IMPLEMENT
  switch(mode){
    case 0:                     //OFF
    analogWrite(LED_PIN_R, 0);
    analogWrite(LED_PIN_G, 0);
    analogWrite(LED_PIN_B, 0);
    //Serial.println("mode OFF (0)");
    break;
    case 1:                     //BLUE
    analogWrite(LED_PIN_R, 0);
    analogWrite(LED_PIN_G, 0);
    analogWrite(LED_PIN_B, 255);
    //Serial.println("mode OFF (1) BLUE");
    break;
    case 2:                     //RED
    analogWrite(LED_PIN_R, 255);
    analogWrite(LED_PIN_G, 0);
    analogWrite(LED_PIN_B, 0);
    //Serial.println("mode OFF (2) RED");
    break;
    case 3:                     //GREEN
    analogWrite(LED_PIN_R, 0);
    analogWrite(LED_PIN_G, 255);
    analogWrite(LED_PIN_B, 0);
    //Serial.println("mode OFF (3) GREEN");
    break;
    case 4:                     //PURPLE
    analogWrite(LED_PIN_R, 50);
    analogWrite(LED_PIN_G, 0);
    analogWrite(LED_PIN_B, 100);
    //Serial.println("mode OFF (4) PURPLE");
    break;
  }
}

void selectMode()
{
  if(mode == 0) { 
    reset();
  }
  else if(mode == 1) {
    live();
  }
  else if(mode == 2) {
    record();
  }
  else if(mode == 3) {
    play();
  }
   else if(mode == 4) {
    loopMode();
  }
}

void reset()
{

  countNotes = 0;
  
}

void live()
{
    Serial.println(analogRead(NOTE_IN_PIN));
    if(analogRead(NOTE_IN_PIN) > 5){
      tone(BUZZER_PIN, analogRead(NOTE_IN_PIN), duration);
    }
}

void record()
{
  
  if(analogRead(NOTE_IN_PIN) > 3 && countNotes < MAX_NOTES){
    
    notes[countNotes] = (int)analogRead(NOTE_IN_PIN);
    tone(BUZZER_PIN, (int)analogRead(NOTE_IN_PIN), duration);
    countNotes++;
    
    Serial.print(countNotes);
    delay(200);
    
  }
  
}

void play()
{
  for(int i = 0; i < 16; i++){
    
    tone(BUZZER_PIN, notes[i], duration);

    delay(300);
    
    Serial.print(notes[i]);
    Serial.print("     ");
    Serial.println(i);
    
    if(digitalRead(BUTTON_MODE_PIN) == HIGH){
      break;
    }
    
  } 
  
}
/******************LOOPMODE(): IMPLEMENT *********************************
LOOPMODE() randomizes the order of the notes in notes[] and plays them back in this new order
**************************************************************************/
void loopMode(){
  int currentIndex = 15;
  int temporaryValue;

  while (0 != currentIndex) {                     //while there are still indexes to be randomized

    int randomIndex = random(0, currentIndex);    //random number from remaining indexes to be randomized
    currentIndex -= 1;

    temporaryValue = notes[currentIndex];         //saves temp value from current index
    notes[currentIndex] = notes[randomIndex];     //puts contents of random index in current index
    notes[randomIndex] = temporaryValue;          //puts saved contents into random index
  }
 
    for(int i = 0; i < 16; i++){

        tone(BUZZER_PIN, notes[i], duration);        
  
        delay(300);
        
        Serial.print(notes[i]);
        Serial.print("     ");
        Serial.println(i);
      
      if(digitalRead(BUTTON_MODE_PIN) == HIGH){
        break;
      }
        
    }
  
}

/**************************************************************************/

