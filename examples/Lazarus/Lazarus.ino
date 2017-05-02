/* Lazarus Test
   by Thomas Olson 20140807.02
   
   This is an example of how to wake an RFduino loop() from
   INFINITE sleep mode from a BLE event instead of an RFduino
   Pin Change.
*/
#include <RFduinoBLE.h>
#include <Lazarus.h>
Lazarus Lazarus;

void setup() {
  Serial.begin(9600);
  RFduinoBLE.advertisementData = "Lazarus Test";
  RFduinoBLE.begin();
}

void loop() {

  Serial.println("RFduino LOOP going to sleep forever");
  RFduinoBLE_ULPDelay(INFINITE);
  if(Lazarus.lazarusArising()){
    Serial.println("Lazarus has awakened!");
    Serial.println("");
  }
  
  // Do whatever you need to do in the LOOP while alive again!
  delay(100); // just waste some time for this test

}

// I want to wake up main loop() from INFINITE sleep
// when BLE_onConnect occurs
void RFduinoBLE_onConnect() {
  Serial.println("Connected");
  Lazarus.ariseLazarus(); // Tell Lazarus to arise.
}

// In this example I don't do anything with onDisconnect
void RFduinoBLE_onDisconnect() {
  Serial.println("Disconnected");
}

