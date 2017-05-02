/* Lazarus and Buttons Test
   by Thomas Olson 20140808.01
   
   This is an example of how to wake an RFduino loop() from
   INFINITE sleep mode from a BLE event.
   And the two buttons on the RGB shield
*/
#include <RFduinoBLE.h>
#include <Lazarus.h>
Lazarus Lazarus;

char buf[20]; //RFduino currently limited to 20 byte packets.
char BLE_FLAG;

#define buttonPin 5
#define buttonAlt 6

void setup() {
  delay(3000); // for debugging give me plenty of time to start serial monitor 
  Serial.begin(9600);
  RFduinoBLE.advertisementData = "Lazarus Buttons";
  RFduinoBLE.begin();

  // Note if using RGB shield where buttons pullup and resistors pulldown OK. But
  // if you run without the board installed then better have pulldowns on CPU board.
  // Also PinWake will lock up if buttons get stuck on. So make sure input trigger
  // signals always return to normal.  
  pinMode(buttonPin,INPUT_PULLDOWN); // So make sure failsafe.. turn on cpu pulldowns
  RFduino_pinWake(buttonPin,HIGH);
  pinMode(buttonAlt,INPUT_PULLDOWN);
  RFduino_pinWake(buttonAlt,HIGH);
}
 
void loop() {

  Serial.println("RFduino LOOP going to sleep forever");
  RFduinoBLE_ULPDelay(INFINITE);
  if(Lazarus.lazarusArising()){
    Serial.println("Lazarus has awakened!");
    Serial.println("");
    // insert call to function to deal with RADIO initiated demands.
    lazarus_duty();
  }
  if(RFduino_pinWoke(buttonPin)){
    RFduino_resetPinWake(buttonPin);
    // insert call to function to deal with buttonPin activity
    buttonPinActivity();
  }
  
  if(RFduino_pinWoke(buttonAlt)){
    RFduino_resetPinWake(buttonAlt);
    // insert call to routine to deal with buttonAlt activity
    buttonAltActivity();
  }
  
  // Do whatever you need to do in the LOOP while alive again!
  delay(100); // just waste some time for this test

}

void buttonPinActivity(){
  Serial.print("Button Pin: ");
  Serial.print(buttonPin);
  Serial.println(" Pressed!");    
}

void buttonAltActivity(){  
  Serial.print("Button Alt: ");
  Serial.print(buttonAlt);
  Serial.println(" Pressed!");
}

void lazarus_duty(){
  switch(BLE_FLAG){
    case 'C':
      Serial.println("BLE Connected");
      break;
    case 'R':
      Serial.println("BLE Received Buffer");
      Serial.print("buf[0]= ");
      Serial.println(buf[0], HEX);
      break;
    case 'D':
      Serial.println("BLE Disconnected");
    default:
      break;
  }
}

void RFduinoBLE_onConnect() {
  BLE_FLAG = 'C';
  Lazarus.ariseLazarus(); // Tell Lazarus to arise.
}

// In this example I don't do anything with onDisconnect
void RFduinoBLE_onDisconnect() {
  BLE_FLAG = 'D';
  Lazarus.ariseLazarus();
}

void RFduinoBLE_onReceive(char *data, int len) {
  if (len>=1){
    buf[0] = data[0];
  }
  BLE_FLAG = 'R';
  Lazarus.ariseLazarus();
}
