/* Lazarus.h - Library for onBLE functions to break INFINITE waits in loop()
   by Thomas Olson Consulting
   20140806.01
*/

#ifndef Lazarus_h
#define Lazarus_h

//#include "RFduinoBLE.h"
#include "SimbleeBLE.h"
#include "Arduino.h"

class Lazarus
{
  public:
    Lazarus();
    void ariseLazarus();
    bool lazarusArising();
  private:
    int _lazarus;
};

#endif
