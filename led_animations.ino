int pinArray[] = {3, 4, 5, 6, 7, 8};
int count = 0;
const long interval = 50;
const int ledPin =  13;
const int buttonPin = 2;
int buttonState = 0;
unsigned long previousMillis = 0;
unsigned long prevAnimMillis = 0;

int currentLed = 0;
int ledState = HIGH;
int animDirection = 1;
int currentAnimation = 0;

int animStep = 0;
int currentStatus[6]={0,0,0,0,0,0};

const long animInterval = 5000; 

struct status {
   int led;
   int ledStatus;
   int animDirection;
};


void setup(){
 
  for (count=0;count<6;count++) {
    pinMode(pinArray[count], OUTPUT);
  }
  
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(pinArray[currentLed], ledState);
}

void loop() {

  unsigned long currentMillis = millis();
  digitalWrite(ledPin, digitalRead(buttonPin));


  if(currentMillis - prevAnimMillis >= animInterval){
    prevAnimMillis = currentMillis;
    currentAnimation = (currentAnimation + 1) % 2;
    clearLeds();
  }
  
  if(currentAnimation==0){
    updateAnimation(currentMillis);  
  }else{
    updateAnimation2(currentMillis);
  }
  
}
void updateAnimation2(long currentMillis){
  if (currentMillis - previousMillis >= interval*5) {
    previousMillis = currentMillis;
    
    getStatus(animStep, currentStatus);
    animStep = (animStep + 1) % 4;

    for (count=0;count<6;count++) {
      digitalWrite(pinArray[count], currentStatus[count]);  
    }
  }
}

void getStatus (int animStep, int (& arr)[6]){
  for (int i = 0; i < 6; i++){
    arr[i] = 0;
  }

  if(animStep == 0){
    arr[0] = 1;
    arr[5] = 1;
  }
  if(animStep == 1 || animStep == 3){
    arr[1] = 1;
    arr[4] = 1;
  }

  if(animStep == 2){
    arr[2] = 1;
    arr[3] = 1;
  }
}

void clearLeds(){
  for (count=0;count<6;count++) {
      digitalWrite(pinArray[count], LOW);  
    }
}

void updateAnimation(long currentMillis){
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    struct status newStatus = updateStatus(currentLed, ledState, animDirection);
    currentLed = newStatus.led;
    ledState = newStatus.ledStatus;
    animDirection = newStatus.animDirection;
        
    digitalWrite(pinArray[currentLed], ledState);
  }
}

struct status updateStatus(int led, int ledStatus, int animDirection) {
  struct status res;

  res.led = led;
  res.animDirection = animDirection;

  if(ledStatus == LOW){
    res.led = res.led + animDirection;
    res.ledStatus = HIGH;

    if(led == 5 && animDirection == 1){
      res.animDirection = -1;
      res.led = 5;
    }

    if(led == 0 && animDirection == -1){
      res.animDirection = 1;
      res.led = 0;
    }
  }else{
    res.ledStatus = LOW;
  }
  return res;
}