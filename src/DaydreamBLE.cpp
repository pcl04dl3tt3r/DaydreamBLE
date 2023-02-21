/*
  This file is part of the DaydreamBLE library.
*/
/*
#include "utility/ATT.h"
#include "utility/HCI.h"
#include "utility/GAP.h"
#include "utility/GATT.h"
#include "utility/L2CAPSignaling.h"
#include "pins_arduino.h"
#include "WiFi.h"
*/

#include "DaydreamBLE.h"

DaydreamBLE::DaydreamBLE()
{
}


DaydreamBLE::~DaydreamBLE()
{
}

/*
  isClickDown = (value[18) & 0x1) > 0;
  isAppDown = (value[18) & 0x4) > 0;
  isHomeDown = (value[18) & 0x2) > 0;
  isVolPlusDown = (value[18) & 0x10) > 0;
  isVolMinusDown = (value[18) & 0x8) > 0;

  time = ((value[0) & 0xFF) << 1 | (value[1) & 0x80) >> 7);

  seq = (value[1) & 0x7C) >> 2;

  xOri = (value[1) & 0x03) << 11 | (value[2) & 0xFF) << 3 | (value[3) & 0x80) >> 5;
  xOri = (state.xOri << 19) >> 19;
  xOri *= (2 * Math.PI / 4095.0);

  yOri = (value[3) & 0x1F) << 8 | (value[4) & 0xFF);
  yOri = (state.yOri << 19) >> 19;
  yOri *= (2 * Math.PI / 4095.0);

  zOri = (value[5) & 0xFF) << 5 | (value[6) & 0xF8) >> 3;
  zOri = (state.zOri << 19) >> 19;
  zOri *= (2 * Math.PI / 4095.0);

  xAcc = (value[6) & 0x07) << 10 | (value[7) & 0xFF) << 2 | (value[8) & 0xC0) >> 6;
  xAcc = (state.xAcc << 19) >> 19;
  xAcc *= (8 * 9.8 / 4095.0);

  yAcc = (value[8) & 0x3F) << 7 | (value[9) & 0xFE) >>> 1;
  yAcc = (state.yAcc << 19) >> 19;
  yAcc *= (8 * 9.8 / 4095.0);

  zAcc = (value[9) & 0x01) << 12 | (value[10) & 0xFF) << 4 | (value[11) & 0xF0) >> 4;
  zAcc = (state.zAcc << 19) >> 19;
  zAcc *= (8 * 9.8 / 4095.0);

  xGyro = ((value[11) & 0x0F) << 9 | (value[12) & 0xFF) << 1 | (value[13) & 0x80) >> 7);
  xGyro = (state.xGyro << 19) >> 19;
  xGyro *= (2048 / 180 * Math.PI / 4095.0);

  yGyro = ((value[13) & 0x7F) << 6 | (value[14) & 0xFC) >> 2);
  yGyro = (state.yGyro << 19) >> 19;
  yGyro *= (2048 / 180 * Math.PI / 4095.0);

  zGyro = ((value[14) & 0x03) << 11 | (value[15) & 0xFF) << 3 | (value[16) & 0xE0) >> 5);
  zGyro = (state.zGyro << 19) >> 19;
  zGyro *= (2048 / 180 * Math.PI / 4095.0);

  xTouch = ((value[16) & 0x1F) << 3 | (value[17) & 0xE0) >> 5) / 255.0;
  yTouch = ((value[17) & 0x1F) << 3 | (value[18) & 0xE0) >> 5) / 255.0;
*/

int DaydreamBLE::update(byte value[20]){

  // http://stackoverflow.com/questions/40730809/use-daydream-controller-on-hololens-or-outside-daydream/40753551#40753551

  state.isClickDown = (value[18] & 0x0001) > 0;
  state.isAppDown = (value[18] & 0x0004) > 0;
  state.isHomeDown = (value[18] & 0x0002) > 0;
  state.isVolPlusDown = (value[18] & 0x0010) > 0;
  state.isVolMinusDown = (value[18] & 0x0008) > 0;

  state.time = ((value[0] & 0x00FF) << 1 | (value[1] & 0x0080) >> 7);

  state.seq = (value[1] & 0x007C) >> 2;

  state.xOri = (value[1] & 0x0003) << 11 | (value[2] & 0x00FF) << 3 | (value[3] & 0x0080) >> 5;
  state.xOri = (state.xOri << 3);
  state.xOri /= -32;
  //state.xOri *= (2.0 * PI / 4095.0);
 
  state.yOri = (value[3] & 0x001F) << 8 | (value[4] & 0x00FF);
  state.yOri = (state.yOri << 3);
  state.yOri /= -32;
  //state.yOri = (float)state.yOri * (2.0 * PI / 4095.0);

  state.zOri = (value[5] & 0x00FF) << 5 | (value[6] & 0x00F8) >> 3;
  state.zOri = (state.zOri << 3);
  state.zOri /= -32;
  //state.zOri = (float)state.zOri * (2.0 * PI / 4095.0);

  state.xAcc = (value[6] & 0x0007) << 10 | (value[7] & 0x00FF) << 2 | (value[8] & 0x00C0) >> 6;
  state.xAcc = (state.xAcc << 3);
  //state.xAcc *= (8 * 9.8);

  state.yAcc = (value[8] & 0x003F) << 7 | (value[9] & 0x00FE) >> 1;
  state.yAcc = (state.yAcc << 3);
  //state.yAcc *= (8 * 9.8);

  state.zAcc = (value[9] & 0x0001) << 12 | (value[10] & 0x00FF) << 4 | (value[11] & 0x00F0) >> 4;
  state.zAcc = (state.zAcc << 3);
  //state.zAcc *= (8 * 9.8);

  state.xGyro = ((value[11] & 0x000F) << 9 | (value[12] & 0x00FF) << 1 | (value[13] & 0x0080) >> 7);
  state.xGyro = (state.xGyro << 3);
  //state.xGyro *= (2048 / 180 * PI);

  state.yGyro = ((value[13] & 0x007F) << 6 | (value[14] & 0x00FC) >> 2);
  state.yGyro = (state.yGyro << 3);
  //state.yGyro *= (2048 / 180 * PI);

  state.zGyro = ((value[14] & 0x0003) << 11 | (value[15] & 0x00FF) << 3 | (value[16] & 0x00E0) >> 5);
  state.zGyro = (state.zGyro << 3);
  //state.zGyro *= (2048 / 180 * PI);

  //state.xTouch = ((value[16] & 0x1F) << 3 | (value[17] & 0xE0) >> 5) / 255.0;
  //state.yTouch = ((value[17] & 0x1F) << 3 | (value[18] & 0xE0) >> 5) / 255.0;

  state.xTouch = ((value[16] & 0x1F) << 3 | (value[17] & 0xE0) >> 5);
  state.yTouch = ((value[17] & 0x1F) << 3 | (value[18] & 0xE0) >> 5);
}

