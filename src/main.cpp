#include <Arduino.h>
#include "IRremote.h"

int RECV_PIN = 3;
IRrecv irrecv(RECV_PIN);
decode_results results;



void setup() {
  Serial.begin(9600);
  Serial.print("----- Program Start -------\n");
  
  Serial.println("Enabling IR Rx");
  irrecv.enableIRIn();
  // put your setup code here, to run once:
}

void loop() {

  char rc = Serial.read();
  if(rc == 'q')
  {
    Serial.flush();
  }


  if(irrecv.decode(&results))
  {
    Serial.println(results.value, HEX);
    Serial.println(results.decode_type);
    irrecv.resume();
  }
}
