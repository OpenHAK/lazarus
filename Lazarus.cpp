/* Lazarus.h - Library for onBLE functions to break INFINITE waits in loop()
   written by Thomas Olson Consulting
   20140806.01
   20140808.01 modified for lower power by using pulldown instead of pullup.
*/

#include "Arduino.h"
//#include "RFduinoBLE.h"
#include "SimbleeBLE.h"
#include "Lazarus.h"

Lazarus::Lazarus()
{
  _lazarus = 31;

  pinMode(_lazarus, INPUT_PULLDOWN);
  NRF_GPIO->PIN_CNF[_lazarus] =
      (GPIO_PIN_CNF_PULL_Pulldown << GPIO_PIN_CNF_PULL_Pos); // use pulldown
  // RFduino_pinWake(_lazarus,HIGH);
  // RFduino_resetPinWake(_lazarus); // +++ <-- timb103 added this line
   Simblee_pinWake(_lazarus,HIGH);
    Simblee_resetPinWake(_lazarus); // +++ <-- timb103 added this line

}

void Lazarus::ariseLazarus()
{
  // need to bring internal pin high somehow.. so..
  NRF_GPIO->PIN_CNF[_lazarus] =
      (GPIO_PIN_CNF_PULL_Pullup<<GPIO_PIN_CNF_PULL_Pos);
  //RFduino_pinWake(_lazarus,HIGH);
  Simblee_pinWake(_lazarus,HIGH);
  // need to bring internal pin low again.. so..
  NRF_GPIO->PIN_CNF[_lazarus] =
      (GPIO_PIN_CNF_PULL_Pulldown<<GPIO_PIN_CNF_PULL_Pos);
}

bool Lazarus::lazarusArising()
{
  // if(RFduino_pinWoke(_lazarus)){
  //   RFduino_resetPinWake(_lazarus);
  //   return HIGH; // return high/true if woke
  // }
  if(Simblee_pinWoke(_lazarus)){
    Simblee_resetPinWake(_lazarus);
    return HIGH; // return high/true if woke
  }
  return LOW; // return low/false if not woke
}
