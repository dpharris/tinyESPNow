#include "tinyESPNow.h"
static tinyESPNow tEN;

#define BUFSIZE (64)            // The size of the buffer you want to send and receive (MAX 249 Byte)

struct Complex {
  char c[20];
  long l;
  float f;
} comp;

enum Type { COUNT=0xFF };
void dataUpdate() {
  uint8_t *buf = tEN.get();     // Get a pointer to the library buffer
  buf[0] = COUNT;
  Serial.printf("%02X=>", buf[1]);
  buf[1] = (buf[1] + 1) % 256;  // Add One to the received data
  Serial.printf("%02X\n", buf[1]);
  //tEN.put(buf, 2);              // Update the buffer
  //tEN.send();                   // Send the buffer
  tEN.send(buf, 2);               // Send the msg
}

void setup() {
  uint8_t myId = 0xFF;          // Register your number
  Serial.begin( 115200 ); while (!Serial);
  tEN.begin(myId, BUFSIZE);
  dataUpdate();
}

void loop() {
  if (tEN.isRecv()) {           // Did the data arrive?
    dataUpdate();
  }
  tEN.send('C', (uint8_t*)&comp, sizeof(comp));
  String s = "Hello there";
  tEN.send('T', (uint8_t (uint8_t*)s, lengthof(s));
  tEN.update();                 // Update class
  delay(10);
}
