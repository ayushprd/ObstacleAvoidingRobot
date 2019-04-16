#include <NewPing.h>

#define sonar     1 
#define maxlength 500 // Maximum distance sonar will ping
#define pingtime 250 

unsigned long pingTimer[sonar];
unsigned int cm[sonar];
uint8_t currentSensor = 0;

NewPing sonar[sonar] = {
  NewPing(7, 6, maxlength), 
};

void setup() {

  pingTimer[0] = millis() + 75;
  for (uint8_t i = 1; i < sonar; i++) // Set the start time for each sensor
    pingTimer[i] = pingTimer[i - 1] + pingtime;

  //Setup Channel A & B
  pinMode(12, OUTPUT); //Motor Channel A pin
  pinMode(9, OUTPUT); //Brake Channel A pin
  pinMode(13, OUTPUT); //Motor Channel B pin
  pinMode(8, OUTPUT); //Brake Channel B pin  
}

void loop() {
  for (uint8_t i = 0; i < sonar; i++) { // Loop through all sensors
    if (millis() >= pingTimer[i]) {         // Check each sensor for time to ping
      pingTimer[i] += pingtime * sonar;  // Set time for next ping.
      if (i == 0 && currentSensor == sonar - 1) oneSensorCycle(); 
      sonar[currentSensor].timer_stop();       
      currentSensor = i;
      cm[currentSensor] = maxlength;               
      sonar[currentSensor].ping_timer(echoCheck); 
    }
  }


       if (cm[0] < 20)  // something seen by right US
       {
          turn_right();
       } 
       

       else; // if there's nothing in front of us
       {
          forward(); // drive forward        
       }
  
}

void echoCheck() {
  if (sonar[currentSensor].check_timer())
    cm[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;
}


void forward()
{

  digitalWrite(12, LOW);  //Setting direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, 255);    //Spins the motor on Channel A at full speed
  digitalWrite(13, HIGH); //Setting direction of Channel B 
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  analogWrite(11, 255);   //Spins the motor on Channel B at full speed
}

void turn_right()
{ 

  digitalWrite(12, HIGH); //Setting direction of Channel A 
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, 255);    //Spins the motor on Channel A at full speed
  digitalWrite(13, HIGH); //Setting  direction of Channel B
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  analogWrite(11, 255);   //Spins the motor on Channel B at low speed
  delay(500);
}
