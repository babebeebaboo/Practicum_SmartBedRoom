/* Pin connection
   PIN_PC0 -> RELAY_LED0
   PIN_PC1 -> RELAY_LED1
   PIN_PC2 -> RELAY_LED2
   PIN_PC3 -> RELAY_AIR
   PIN_PC5 -> DHT11

   PIN_PB1 -> Switch_LED0
   PIN_PB2 -> Switch_LED1
   PIN_PB3 -> Switch_LED2
   PIN_PB4 -> Switch_AIR
*/

/* USB Library */
#include <usbdrv.h>

/* Using DHT Sensor Libraries in Arduino IDE by Adafruit */
#include "DHT.h"

/* Define all pin connection */
#define PIN_RELAY_LED0      PIN_PC0
#define PIN_RELAY_LED1      PIN_PC1
#define PIN_RELAY_LED2      PIN_PC2
#define PIN_RELAY_AIR       PIN_PC3
//#define PIN_LDR             PIN_PC4
#define PIN_DHT11           PIN_PC5

//#define PIN_ENABLE_PIR      PIN_PB0
#define PIN_Switch_LED0     PIN_PB1
#define PIN_Switch_LED1     PIN_PB2
#define PIN_Switch_LED2     PIN_PB3
#define PIN_Switch_AIR      PIN_PB4

/* Define USB Function */
#define RQ_SET_LED      0
#define RQ_GET_TEMP     1
#define RQ_GET_HUMID    2
//#define RQ_GET_LIGHT    3
#define RQ_GET_SWITCH   4

/* define BYTE to use in USB */
#define TEMP_BYTE       2
#define HUMID_BYTE      2

/* Setup DHT and declare dht class */
#define DHTTYPE DHT11
DHT dht(PIN_DHT11, DHTTYPE);

/*Define Global DHT to prevent timeout in python*/
uint16_t humid;
uint16_t temp;
uint8_t Stage_Switch_LED0 = 0;
uint8_t Stage_Switch_LED1 = 0;
uint8_t Stage_Switch_LED2 = 0;
uint8_t Stage_Switch_AIR = 0;
static uint8_t Switch[4] = {0, 0, 0, 0};

/* ------------------------------------------------------------------------- */
/* ----------------------------- USB interface ----------------------------- */
/* ------------------------------------------------------------------------- */
extern "C" usbMsgLen_t usbFunctionSetup(uint8_t data[8])
{
  usbRequest_t *rq = (usbRequest_t*)data;

  /* declared as static so they stay valid when usbFunctionSetup returns */
  static uint8_t switch_state;
  static uint16_t light;

  if (rq->bRequest == RQ_SET_LED)
  {
    uint8_t led_val = rq->wValue.bytes[0];
    uint8_t led_no  = rq->wIndex.bytes[0];
    if (led_val > 1) {
      led_val = 1;
    }
    if (led_val < 0) {
      led_val = 0;
    }
    if (led_no == 0) {
      digitalWrite(PIN_RELAY_LED0, led_val);
    }
    if (led_no == 1) {
      digitalWrite(PIN_RELAY_LED1, led_val);
    }
    if (led_no == 2) {
      digitalWrite(PIN_RELAY_LED2, led_val);
    }
    if (led_no == 3) {
      digitalWrite(PIN_RELAY_AIR, led_val);
    }

//    if (led_no == 4) {
//      digitalWrite(PIN_ENABLE_PIR, led_val);
//    }
    /* return the number of bytes of data to be returned to host */
    return 0;
  }
  if (rq->bRequest == RQ_GET_TEMP) {
    usbMsgPtr = (uint8_t *) &temp;
    /* return the number of bytes of data to be returned to host */
    return TEMP_BYTE;
  }
  if (rq->bRequest == RQ_GET_HUMID) {
    usbMsgPtr = (uint8_t *) &humid;
    /* return the number of bytes of data to be returned to host */
    return HUMID_BYTE;
  }
  
//  if (rq->bRequest == RQ_GET_LIGHT) {
//    light = analogRead(PIN_LDR);
//    usbMsgPtr = (uint8_t*) &light;
//    /* return the number of bytes of data to be returned to host */
//    return 2;
//  }
  
  if (rq->bRequest == RQ_GET_SWITCH) {
    usbMsgPtr = (uint8_t*) Switch;
    /* return the number of bytes of data to be returned to host */
    return 4;
  }

  /* default for not implemented requests: return no data back to host */
  return 0;
}

/* ------------------------------------------------------------------------- */
/* --------------------------- END USB interface --------------------------- */
/* ------------------------------------------------------------------------- */

void setup() {
  /* Setup Pin Mode  */
  pinMode(PIN_RELAY_LED0, OUTPUT);  //RELAY LED0
  pinMode(PIN_RELAY_LED1, OUTPUT);  //RELAY LED1
  pinMode(PIN_RELAY_LED2, OUTPUT);  //RELAY LED2
  pinMode(PIN_RELAY_AIR, OUTPUT);   //RELAY AIR
  //pinMode(PIN_LDR, INPUT);          //LDR
  //pinMode(PIN_ENABLE_PIR, OUTPUT);  //Enable PIR
  pinMode(PIN_Switch_LED0, INPUT);  //Switch LED0 PULL_UP
  digitalWrite(PIN_Switch_LED0, HIGH);
  pinMode(PIN_Switch_LED1, INPUT);  //Switch LED1 PULL_UP
  digitalWrite(PIN_Switch_LED1, HIGH);
  pinMode(PIN_Switch_LED2, INPUT);  //Switch LED2 PULL_UP
  digitalWrite(PIN_Switch_LED2, HIGH);
  pinMode(PIN_Switch_AIR, INPUT);   //Switch AIR PULL_UP
  digitalWrite(PIN_Switch_AIR, HIGH);

  /* SETUP FOR USB */
  usbInit();

  /* enforce re-enumeration, do this while interrupts are disabled! */
  usbDeviceDisconnect();
  _delay_ms(300);
  usbDeviceConnect();

  /* enable global interrupts */
  sei();

  /* Setup DHT11 */
  dht.begin();
}
void loop() {
  /* Pull USB */
  usbPoll();
  temp = dht.readTemperature();
  humid = dht.readHumidity();
  
  if (digitalRead(PIN_Switch_LED0)) {
    Stage_Switch_LED0 = 1;
  }
  if (digitalRead(PIN_Switch_LED1)) {
    Stage_Switch_LED1 = 1;
  }
  if (digitalRead(PIN_Switch_LED2)) {
    Stage_Switch_LED2 = 1;
  }
  if (digitalRead(PIN_Switch_AIR)) {
    Stage_Switch_AIR = 1;
  }
  
  if (!digitalRead(PIN_Switch_LED0) && Stage_Switch_LED0 == 1) {
    if (Switch[0] == 1) {
      Switch[0] = 0;
    }
    else if (Switch[0] == 0) {
      Switch[0] = 1;
    }
    Stage_Switch_LED0 = 0;
  }
  if (!digitalRead(PIN_Switch_LED1) && Stage_Switch_LED1 == 1) {
    if (Switch[1] == 1) {
      Switch[1] = 0;
    }
    else if (Switch[1] == 0) {
      Switch[1] = 1;
    }
    Stage_Switch_LED1 = 0;
  }
  if (!digitalRead(PIN_Switch_LED2) && Stage_Switch_LED2 == 1) {
    if (Switch[2] == 1) {
      Switch[2] = 0;
    }
    else if (Switch[2] == 0) {
      Switch[2] = 1;
    }
    Stage_Switch_LED2 = 0;
  }
  if (!digitalRead(PIN_Switch_AIR) && Stage_Switch_AIR == 1) {
    if (Switch[3] == 1) {
      Switch[3] = 0;
    }
    else if (Switch[3] == 0) {
      Switch[3] = 1;
    }
    Stage_Switch_AIR = 0;
  }
  
}
