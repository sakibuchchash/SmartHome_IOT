//Insert Network Address Password and control fan and LED with it
#include "Adafruit_APDS9960.h"
#define LED 16            // Led in NodeMCU at pin GPIO16 (D0).
#define FAN 15            // Led in NodeMCU at pin GPIO15 (D0).

Adafruit_APDS9960 apds;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);    // LED pin as output.
  pinMode(FAN, OUTPUT);    // FAN pin as output.
 
  if(!apds.begin()){
    Serial.println("failed to initialize device! Please check your wiring.");
  }
  else Serial.println("Device initialized!");

  //gesture mode will be entered once proximity mode senses something close
  apds.enableProximity(true);
  apds.enableGesture(true);
}

// the loop function runs over and over again forever
void loop() {
  //read a gesture from the device
    uint8_t gesture = apds.readGesture();
    if(gesture == APDS9960_DOWN){ 
      digitalWrite(FAN, HIGH);// turn the LED on.(Note that LOW is the voltage level but actually 
      Serial.println("DOWN");
      delay(1000);            // wait for 1 second.
    }
    if(gesture == APDS9960_UP){ 
      digitalWrite(FAN, LOW); // turn the LED off.
      Serial.println("UP");
      delay(1000); // wait for 1 second.
      
    }
    if(gesture == APDS9960_LEFT){
      digitalWrite(LED, HIGH);// turn the LED on.(Note that LOW is the voltage level but actually 
     
      Serial.println("LEFT");
       delay(1000);            // wait for 1 second.

    }
    if(gesture == APDS9960_RIGHT){
      digitalWrite(LED, LOW); // turn the LED off.
      Serial.println("RIGHT");
      delay(1000); // wait for 1 second.
      
      }
}
