//author: Ludo Teirlinck, The Things Nerwork

#include <Sodaq_RN2483.h>   //SODAQ Autonom libraries, has the LoRaWAN library inside it

//scrip basic settings 

bool serial = true; //usuage with (true) or without (false) the serial monitor
String message = "<put here your message>"; //message to be send

//pin configuration

#define BUTTON_PIN 4        //button for enabeling and dissabeling the Alarm
#define LED_PIN 13          //difyning the pin of the LED, this LED in embedded into the SODAQ Autonom board it self

//LoRaWAN settings

#define loraSerial Serial1    //serial of the LoRaWAN module

// Change the DevAddr
const uint8_t devAddr[4] = { 0x00, 0x00, 0xAA, 0x01 }; //put here your own device ID

// Public Semtech key
const uint8_t appSKey[16] = { 0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C };

// Public Semtech key
const uint8_t nwkSKey[16] = { 0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C };

void setup() {
  
  //Enable this code if you're connecting the board to your pc, for smooth reading
  if (serial){
       while(!SerialUSB) {
         ;
       }
       delay(1500); 
  }

  // LoRaWAN
  loraSerial.begin(LoRaBee.getDefaultBaudRate());
  //set lora serial port
  LoRaBee.setDiag(SerialUSB);  
  //lora power pin
  pinMode(BEE_VCC, OUTPUT);

 
  // configure Arduino LED for
  pinMode(LED_PIN, OUTPUT);

  // configure Alarm Button
  pinMode(BUTTON_PIN, INPUT);
}

void loop() {
    
    LoRaSet("true");
    
    while (BUTTON_PIN){
        digitalWrite(LED_PIN, HIGH);
        for(int x; x<10; x++){
            delay(500);
            if (x == 8){
                message();
            }
        }
    } else {
        digitalWrite(LED_PIN, LOW);
    }
}

  //this function turns the LoRa module ON/OFF depending on the set integer
void LoRaSet(bool set){
  if (set){
    // Turn the LoRaBee on
    digitalWrite(BEE_VCC, HIGH);
    // Connect the LoRabee
    if (LoRaBee.initABP(loraSerial, devAddr, appSKey, nwkSKey, true))
      SerialUSB.println("Connection to the network was successful.");
    else
      SerialUSB.println("Connection to the network failed!");
  } else {
    digitalWrite(BEE_VCC,LOW);
    SerialUSB.println("Module switched off");
  }
}

//this function sends the message with the LoRaWAN network
void message(){
  SerialUSB.println(message);
      
  uint8_t payload[message.length() + 1];
  message.getBytes(payload, message.length() + 1);

  //Sending the string with LoRaWAN, returns the status of the LoRaWAN module
  switch (LoRaBee.send(1, payload, message.length()))
      {
      case NoError:
        SerialUSB.println("Successful transmission.");
        //i--;
        break;
      case NoResponse:
        SerialUSB.println("There was no response from the device.");
        LoRaSet(false);
        //alarm = false;
        break;
      case Timeout:
        SerialUSB.println("Connection timed-out. Check your serial connection to the device! Sleeping for 20sec.");
        delay(20000);
        break;
      case PayloadSizeError:
        SerialUSB.println("The size of the payload is greater than allowed. Transmission failed!");
        break;
      case InternalError:
        SerialUSB.println("Oh No! This shouldn't happen. Something is really wrong! Try restarting the device!\r\nThe program will now halt.");
        LoRaSet(false);
        //alarm = false;
        break;
      case Busy:
        SerialUSB.println("The device is busy. Sleeping for 10 extra seconds.");
        //sleep + LED blink
          for(int x = 0; x < 20; x++){
            digitalWrite(LED_PIN, HIGH);
            delay(500);
            digitalWrite(LED_PIN, LOW);
            delay(500);
          }
        break;
      case NetworkFatalError:
        SerialUSB.println("There is a non-recoverable error with the network connection. You should re-connect.\r\nThe program will now halt.");
        LoRaSet(false);
        //alarm = false;
        break;
      case NotConnected:
        SerialUSB.println("The device is not connected to the network. Please connect to the network before attempting to send data.\r\nThe program will now halt.");
        LoRaSet(false);
        //alarm = false;
        break;
      case NoAcknowledgment:
        SerialUSB.println("There was no acknowledgment sent back!");
        break;
      default:
        break;
    }
}
