/*
  This file is part of the DaydreamBLE library.
*/

#ifndef _DAYDREAM_BLE_H_
#define _DAYDREAM_BLE_H_

#include <Arduino.h>
//#include "BLEDevice.h"

class DaydreamBLE{    //extend BLEDevice?
public:
DaydreamBLE();
virtual ~DaydreamBLE();

int update(byte value[20]);

struct state_t{

  //https://stackoverflow.com/questions/40730809/use-daydream-controller-on-hololens-or-outside-daydream/40753551#40753551

  bool isClickDown;
  bool isAppDown;
  bool isHomeDown;
  bool isVolPlusDown;
  bool isVolMinusDown;

  uint16_t time;

  uint16_t seq;

  int16_t xOri;
  int16_t yOri;
  int16_t zOri;

  int16_t xAcc;
  int16_t yAcc;
  int16_t zAcc;

  int16_t xGyro;
  int16_t yGyro;
  int16_t zGyro;

  uint8_t xTouch;
  uint8_t yTouch;

} state;
  
protected:

private:

};

#endif
