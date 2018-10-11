#define DEBUG

const int relayPin = 12;
bool builtinStatus = LOW;

unsigned long oldTimer;
unsigned long timer;
unsigned long timer2;



// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  
  pinMode(relayPin, OUTPUT);
  #ifdef DEBUG
  Serial.begin(9600);
  #endif
  oldTimer = millis();
  timer = millis();
  timer2 = millis();
}

class relaySwitch
{
  // Class Member Variables
  // These are initialized at startup
  int relayPin;      // the number of the LED pin

 
  // These maintain the current state
  int relayState;                 // relayState used to set the LED
 
  // Constructor - creates a Flasher 
  // and initializes the member variables and state
  public:
  relaySwitch(int pin)
  {
  relayPin = pin;
  pinMode(relayPin, OUTPUT);     
    
 
  relayState = LOW; 
  }
 
  void Update()
  {
    // check to see if it's time to change the state of the LED
    unsigned long currentMillis = millis();
     
    if(relayState == HIGH)
    {
      relayState = LOW;  // Turn it off
      
      digitalWrite(relayPin, relayState);  // Update the actual LED
    }
    else if (relayState == LOW) 
    {
      relayState = HIGH;  // turn it on
      digitalWrite(relayPin, relayState);   // Update the actual LED
    }
  }
};
 
relaySwitch relay1(11);
 

// the loop function runs over and over again forever
void loop() {

  if (millis() - oldTimer > 1000) {
    debugPrintln(String(millis() - oldTimer));
    oldTimer = millis();
    if (builtinStatus == HIGH) {
      builtinStatus = LOW;
    } else {
      builtinStatus = HIGH;
    }
    digitalWrite(LED_BUILTIN, builtinStatus);
  }
  if (millis() - timer2 > 10000) {
    relay1.Update();
    timer2 = millis();
  }
}

//Debugging / testing stuff goes below here

void debugPrint(String toPrint) {
  #ifdef DEBUG
  Serial.print(toPrint);
  #endif
 
}

void debugPrintln(String toPrint) {
  #ifdef DEBUG
  Serial.println(toPrint);
  #endif
}
