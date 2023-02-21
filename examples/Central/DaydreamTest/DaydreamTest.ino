/*
  Daydream controller test (based on ArduinoBLE SensorTag Button example)

  This example scans for Bluetooth® Low Energy peripherals until a Google daydream controller is discovered.
  It then connects to it, discovers the attributes of the 0xffe0 service,
  subscribes to the Simple Key Characteristic (UUID 0xffe1). When a button is
  pressed on the SensorTag a notification is received and the button state is
  outputted to the Serial Monitor when one is pressed.

  The circuit:
  - Arduino MKR WiFi 1010, Arduino Uno WiFi Rev2 board, Arduino Nano 33 IoT,
    Arduino Nano 33 BLE, or Arduino Nano 33 BLE Sense board.
  - TI SensorTag

  This example code is in the public domain.
*/

#include <ArduinoBLE.h>
#include <DaydreamBLE.h>

DaydreamBLE daydream;
bool acceptOrReject = true;

void setup() {
  Serial.begin(115200);
  //while (!Serial);
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(0,OUTPUT);
  pinMode(1,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(8,OUTPUT);
  analogWriteResolution(12);

  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy module failed!");

    while (1);
  }

  Serial.println("Bluetooth® Low Energy Central - Google daydream");
  Serial.println("Make sure to turn on the device.");

  BLE.setPairable(Pairable::YES);

/*
  // Callback function with confirmation code when new device is pairing.
  BLE.setDisplayCode([](uint32_t confirmCode){
    Serial.println("New device pairing request.");
    Serial.print("Confirm code matches pairing device: ");
    char code[6];
    sprintf(code, "%06d", confirmCode);
    Serial.println(code);
  });

  // Callback to allow accepting or rejecting pairing
  BLE.setBinaryConfirmPairing([&acceptOrReject](){
    Serial.print("Should we confirm pairing? ");
    delay(5000);
    if(acceptOrReject){
      acceptOrReject = false;
      Serial.println("yes");
      return true;
    }else{
      acceptOrReject = true;
      Serial.println("no");
      return false;
    }
  });

  // IRKs are keys that identify the true owner of a random mac address.
  // Add IRKs of devices you are bonded with.
  BLE.setGetIRKs([](uint8_t* nIRKs, uint8_t** BDaddrTypes, uint8_t*** BDAddrs, uint8_t*** IRKs){
    // Set to number of devices
    *nIRKs       = 2;

    *BDAddrs     = new uint8_t*[*nIRKs];
    *IRKs        = new uint8_t*[*nIRKs];
    *BDaddrTypes = new uint8_t[*nIRKs];

    // Set these to the mac and IRK for your bonded devices as printed in the serial console after bonding.
    uint8_t device1Mac[6]    = {0xa8, 0x1e, 0x84, 0x50, 0x71, 0x33};
    uint8_t device1IRK[16]   = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    uint8_t device2Mac[6]    = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    uint8_t device2IRK[16]   = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


    (*BDaddrTypes)[0] = 0; // Type 0 is for pubc address, type 1 is for static random
    (*BDAddrs)[0] = new uint8_t[6]; 
    (*IRKs)[0]    = new uint8_t[16];
    memcpy((*IRKs)[0]   , device1IRK,16);
    memcpy((*BDAddrs)[0], device1Mac, 6);


    (*BDaddrTypes)[1] = 0;
    (*BDAddrs)[1] = new uint8_t[6];
    (*IRKs)[1]    = new uint8_t[16];
    memcpy((*IRKs)[1]   , device2IRK,16);
    memcpy((*BDAddrs)[1], device2Mac, 6);


    return 1;
  });

  // The LTK is the secret key which is used to encrypt bluetooth traffic
  BLE.setGetLTK([](uint8_t* address, uint8_t* LTK){
    // address is input
    Serial.print("Received request for address: ");
    btct.printBytes(address,6);

    // Set these to the MAC and LTK of your devices after bonding.
    uint8_t device1Mac[6]  = {0xa8, 0x1e, 0x84, 0x50, 0x71, 0x33};
    uint8_t device1LTK[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    uint8_t device2Mac[6]  = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    uint8_t device2LTK[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    

    if(memcmp(device1Mac, address, 6) == 0) {
      memcpy(LTK, device1LTK, 16);
      return 1;
    }else if(memcmp(device2Mac, address, 6) == 0) {
      memcpy(LTK, device2LTK, 16);
      return 1;
    }
    return 0;
  });
  
  BLE.setStoreIRK([](uint8_t* address, uint8_t* IRK){
    Serial.print(F("New device with MAC : "));
    btct.printBytes(address,6);
    Serial.print(F("Need to store IRK   : "));
    btct.printBytes(IRK,16);
    return 1;
  });

  BLE.setStoreLTK([](uint8_t* address, uint8_t* LTK){
    Serial.print(F("New device with MAC : "));
    btct.printBytes(address,6);
    Serial.print(F("Need to store LTK   : "));
    btct.printBytes(LTK,16);
    return 1;
  });

*/

  // start scanning for peripheral
  BLE.scan();
}

void loop() {
  // check if a peripheral has been discovered
  BLEDevice peripheral = BLE.available();

  if (peripheral) {
    // discovered a peripheral, print out address, local name, and advertised service
    Serial.print("Found ");
    Serial.print(peripheral.address());
    Serial.print(" '");
    Serial.print(peripheral.localName());
    Serial.print("' ");
    Serial.print(peripheral.advertisedServiceUuid());
    Serial.println();

    // Check if the peripheral is a Daydream controller, the local name will be:
    // "Daydream controller"
    if (peripheral.localName() == "Daydream controller") {
      // stop scanning
      BLE.stopScan();

      monitorDaydream(peripheral);

      // peripheral disconnected, start scanning again
      //BLE.scan();
      while(1);
    }
  }
}

BLECharacteristicEventHandler charHandler(void) {
  Serial.println("test");
}

void monitorDaydream(BLEDevice peripheral) {

  // connect to the peripheral
  Serial.println("Connecting ...");
  if (peripheral.connect()) {
    Serial.println("Connected");
    
  } else {
    Serial.println("Failed to connect!");
    return;
  }

  Serial.print("Initiating pairing with peripheral");
  peripheral.initiatePairing();
  while(!peripheral.paired()){
    BLE.poll();
    delay(100);
  }
  Serial.println("PAIRED");

  peripheral.reConnect();

  // discover peripheral attributes
  Serial.println("Discovering service 0x180a (Device Info) ...");
  if (peripheral.discoverService("180a")) {
    Serial.println("Service discovered");
  } else {
    Serial.println("Attribute discovery failed.");
    peripheral.disconnect();

    while (1);
    return;
  }

  
  BLECharacteristic mfgCharacteristic = peripheral.characteristic("2a29");
  int mfgLength = mfgCharacteristic.valueLength();
  char mfg[mfgLength];
  mfgCharacteristic.readValue(mfg,mfgLength);
  Serial.println("Manufacturer:");
  Serial.println(mfg);

  // discover peripheral attributes
  Serial.println("Discovering service 0xfe55 ...");
  if (peripheral.discoverService("fe55")) {
    Serial.println("Service discovered");
  } else {
    Serial.println("Attribute discovery failed.");
    peripheral.disconnect();

    while (1);
    return;
  }

  // retrieve the simple key characteristic
  BLECharacteristic daydreamCharacteristic = peripheral.characteristic("00000001-1000-1000-8000-00805f9b34fb");

  // subscribe to the simple key characteristic
  Serial.println("Subscribing to daydream controller characteristic ...");
  if (!daydreamCharacteristic) {
    Serial.println("no daydream characteristic found!");
    peripheral.disconnect();
    return;
  } else if (!daydreamCharacteristic.canSubscribe()) {
    Serial.println("daydream characteristic is not subscribable!");
    peripheral.disconnect();
    return;
  } else if (!daydreamCharacteristic.subscribe()) {
    Serial.println("subscription failed!");
    peripheral.disconnect();
    return;
  } else {
    Serial.println("Subscribed");
    Serial.println("Press the buttons on your controller.");
  }

  byte value[20];
  char strHex[2];
  bool wasClickDown = false;
  int lastMil = 0;

  while (peripheral.connected()) {

    // check if the value of the simple key characteristic has been updated
    if (daydreamCharacteristic.valueUpdated()) {

      daydreamCharacteristic.readValue(value,20);
      daydream.update(value);


      if (daydream.state.isClickDown && !wasClickDown) {
          Serial.println("clicker pressed");
          digitalWrite(LED_BUILTIN, (digitalRead(LED_BUILTIN)==HIGH) ? LOW : HIGH);
          if(digitalRead(LED_BUILTIN)==LOW){
             tone(8,220);
          }
          else{
            noTone(8);
          }
      }
      wasClickDown = daydream.state.isClickDown;

      if (daydream.state.isHomeDown) {
        // second bit corresponds to the left button
        Serial.print("(+) pressed -- xOri:");
        Serial.println(daydream.state.xOri);
      }

      if (daydream.state.isAppDown) {
        // second bit corresponds to the left button
        Serial.print("(-) pressed -- yOri:");
        Serial.println(daydream.state.yOri);
      }

      if (daydream.state.isVolPlusDown) {
        // second bit corresponds to the left button
        Serial.print("+ pressed -- zOri:");
        Serial.println(daydream.state.zOri);
        analogWrite(3, daydream.state.zOri);
      }

      if (daydream.state.isVolMinusDown) {
        // second bit corresponds to the left button
        Serial.print("- pressed");
        Serial.println(daydream.state.zGyro);
        
      }

      //analogWrite(0, daydream.state.xTouch);
      //analogWrite(1, 128+daydream.state.xOri*PI/12);
      //analogWrite(2, 128+daydream.state.yOri*PI/12);
      analogWrite(4, 2048-daydream.state.zOri*PI);
      analogWrite(6, 2048-daydream.state.yTouch*5);
      //if(daydream.state.zOri > 31 && daydream.state.zOri < 255){
      //  analogWrite(4, daydream.state.zOri);
      //}
      //tone(8,31+daydream.state.zOri);
    }
  }

  Serial.println("Controller disconnected!");
}

void printData(uint8_t data[], int length) {
  for (int i = 0; i < length; i++) {
    unsigned char b = data[i];

    if (b < 16) {
      Serial.print("0");
    }

    Serial.print(b, HEX);
  }
}


