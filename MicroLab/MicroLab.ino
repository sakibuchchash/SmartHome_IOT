#include <dht.h>
//#include <Adafruit_APDS9960.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <SparkFun_APDS9960.h>

#define APDS9960_INT    2 // Needs to be an interrupt pin

#define LED 0            // Led in NodeMCU at pin GPIO16 (D3).
#define FANP 14            // FAN in NodeMCU at pin GPIO14 (D5).
#define FANG 12            // FAN in NodeMCU at pin GPIO14 (D6).
#define DHT11_PIN 15

char auth[] = "6TqHFVDYYPU6RL8lJ6xF-rQFst99JJat";
char ssid[] = "EartHTourisT";
char pass[] = "9200,27SunW";



// Global Variables
//Adafruit_APDS9960 apds;
dht DHT;
BlynkTimer timer; 
SparkFun_APDS9960 apds = SparkFun_APDS9960();
int isr_flag = 0;



void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  pinMode(LED, OUTPUT);    // LED pin as output.
  pinMode(FANP, OUTPUT);    // FAN pin as output.
  pinMode(FANG, OUTPUT);    // FAN pin as output.
  pinMode(APDS9960_INT, INPUT);

  // Initialize interrupt service routine
  attachInterrupt(0, interruptRoutine, FALLING);
  
  digitalWrite(LED, 0);
  digitalWrite(FANP, 0);
  digitalWrite(FANG, 0);
 
   if ( apds.init() ) {
    Serial.println(F("APDS-9960 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }

  // Start running the APDS-9960 gesture sensor engine
  if ( apds.enableGestureSensor(true) ) {
    Serial.println(F("Gesture sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during gesture sensor init!"));
  }

  //gesture mode will be entered once proximity mode senses something close
  //apds.enableProximity(true);
  //apds.enableGesture(true);

  //timer.setInterval(500, timerEvent);
  
 }
  
void loop()
{
    Blynk.run(); 
    if( isr_flag == 1 ) {
    detachInterrupt(0);
    timerEvent();
    isr_flag = 0;
    attachInterrupt(0, interruptRoutine, FALLING);
  }
    DHT.read11(DHT11_PIN);
    Blynk.virtualWrite(V3,DHT.temperature);
    Blynk.virtualWrite(V4,DHT.humidity);
   

}

void interruptRoutine() {
  isr_flag = 1;
}

void timerEvent()
{
  if ( apds.isGestureAvailable() ) {
    switch ( apds.readGesture() ) {
      case DIR_UP:
        Serial.println("UP");
        break;
      case DIR_DOWN:
        Serial.println("DOWN");
        break;
      case DIR_LEFT:
        Serial.println("LEFT");
        break;
      case DIR_RIGHT:
        Serial.println("RIGHT");
        break;
      case DIR_NEAR:
        Serial.println("NEAR");
        break;
      case DIR_FAR:
        Serial.println("FAR");
        break;
      default:
        Serial.println("NONE");
    }
  }
  /*
   uint8_t gesture = apds.readGesture();
    if(gesture == APDS9960_DOWN){ 
        digitalWrite(FANP, 1);
        digitalWrite(FANG, 0);
      
      Serial.println("DOWN");
      delay(500);            // wait for 1 second.
    }
    if(gesture == APDS9960_UP){ 
      digitalWrite(FANP, 0);
      digitalWrite(FANG, 0);
      Serial.println("UP");
      delay(500); // wait for 1 second.
      
    }
    if(gesture == APDS9960_LEFT){
      digitalWrite(LED, HIGH);// turn the LED on.(Note that LOW is the voltage level but actually 
     
      Serial.println("LEFT");
       delay(500);            // wait for 1 second.

    }
    if(gesture == APDS9960_RIGHT){
      digitalWrite(LED, LOW); // turn the LED off.
      Serial.println("RIGHT");
      delay(500); // wait for 1 second.
      
      }
      */
}


BLYNK_WRITE(V1)
{
     digitalWrite(FANP, param.asInt());// turn the FAN on.(Note that LOW is the voltage level but actually 
     digitalWrite(FANG, 0);
}
BLYNK_WRITE(V2)
{
    digitalWrite(LED, param.asInt());// turn the LED on.(Note that LOW is the voltage level but actually 
}




