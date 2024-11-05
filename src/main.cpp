#include <Arduino.h>
#include "IRremote.h"
#include "ir_cmds.h"

#define SW1 2
#define SW2 4
#define SW3 7

int RECV_PIN = 3;
IRrecv irrecv(RECV_PIN);
decode_results results;

IRsend sender;
int IRSEND_PIN = 9;


void _event_enable_fan();
void _event_fan_speed();
void _event_enable_oscillation();

bool _poll_pin_state(uint8_t pin, bool prevState);

bool _sw1_state = LOW;
bool _sw2_state = LOW;
bool _sw3_state = LOW;

void setup() {
  Serial.begin(9600);
  Serial.print("----- Program Start -------\n");
  
  Serial.println("Enabling IR Rx");
  irrecv.enableIRIn();

  Serial.println("Initializing interrupts");
  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  pinMode(SW3, INPUT);

  Serial.println("Initializing send");
  pinMode(IRSEND_PIN, OUTPUT);

}

void loop() {

  bool sw1state = digitalRead(SW1);
  if(_poll_pin_state(sw1state, _sw1_state))
  {
    Serial.println("Interrupt 1");
    _event_enable_fan();
  }
  _sw1_state = sw1state;

  bool sw2state = digitalRead(SW2);
  if(_poll_pin_state(sw2state, _sw2_state))
  {
    Serial.println("Interrupt 2");
    _event_fan_speed();
  }
  _sw2_state = sw2state;

  bool sw3state = digitalRead(SW3);
  if(_poll_pin_state(sw3state, _sw3_state))
  {
    Serial.println("Interrupt 3");
    _event_enable_oscillation();
  }
  _sw3_state = sw3state;

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
  delay(50);
}

bool _poll_pin_state(uint8_t pin, bool prevState)
{
  return (pin == HIGH && prevState == LOW) ? true : false;
}

void _event_enable_fan()
{
  Serial.println("Sending enable fan code");
  sender.sendNEC(0x371A3C86, 32);
  delay(2000);
}

void _event_fan_speed()
{
  Serial.println("_event_fan_speed");
}

void _event_enable_oscillation()
{
  Serial.println("_event_enable_oscillation");
}