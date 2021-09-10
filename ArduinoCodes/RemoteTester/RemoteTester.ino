/*
 * This is the remote control test file.
 * After you made connections of the IR, you can upload this code to Arduino and run
 * While Arduino running, you open the Serial Monitor under Tools menu to see codes of the buttons your pressed on the remote
 */

#include <IRremote.h>
#define RECV_PIN 3

IRrecv irrecv(RECV_PIN);

void setup() {
  Serial.begin(9600); // begin serial communication with a baud rate of 9600
  irrecv.enableIRIn(); // enable the receiver
}

void loop() {
  if (irrecv.decode()) {      
    Serial.println(irrecv.decodedIRData.command);
    delay(100);
    irrecv.resume(); // Receive the next value
  }
}
