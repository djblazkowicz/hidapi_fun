#include "Wire.h"
#include "HID.h"
#if !defined(_USING_HID)
#error "Using legacy HID core (non pluggable)"
#endif

static const uint8_t _hidReportDescriptor[] PROGMEM = {
 0x06, 0x00, 0xff,         // USAGE_PAGE (vendor defined)
    0x09, 0x00,         // USAGE (Undefined)
    0xa1, 0x01,         // COLLECTION (Application)
    0x15, 0x00,         //   LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x00,   //   LOGICAL_MAXIMUM (255)
    0x85, 0x01,         //   REPORT_ID (1)
    0x75, 0x08,         //   REPORT_SIZE (8)
    
    0x95, 0x3f,         //   REPORT_COUNT (63)
    
    0x09, 0x00,         //   USAGE (Undefined)
    0x81, 0x02,         //   INPUT (Data,Var,Abs) - to the host
    0xc0           
};


float quat[4];


void setup() {
  static HIDSubDescriptor node (_hidReportDescriptor, sizeof(_hidReportDescriptor));
  HID().AppendDescriptor(&node);

  
  Wire.begin();
  Wire.setClock(2000000);
  delay(1000);

  quat[0] = 1;
  quat[1] = 2;
  quat[2] = 3;
  quat[3] = 4;

}

void loop() {
  static uint32_t prev_ms = millis();
  if ((millis() - prev_ms) > 16)
  {
    
    HID().SendReport(1,quat,63);
    prev_ms = millis();
  }
}
