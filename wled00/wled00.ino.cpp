# 1 "C:\\Users\\matt\\AppData\\Local\\Temp\\tmpy_ik98bg"
#include <Arduino.h>
# 1 "C:/Users/matt/Documents/GitHub/WLED/wled00/wled00.ino"
# 13 "C:/Users/matt/Documents/GitHub/WLED/wled00/wled00.ino"
#include "wled.h"
void setup();
void loop();
#line 15 "C:/Users/matt/Documents/GitHub/WLED/wled00/wled00.ino"
void setup() {
  WLED::instance().setup();
}

void loop() {
  WLED::instance().loop();
}