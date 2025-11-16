#ifndef KEYPAD_H
#define KEYPAD_H


#include <Arduino.h>
#include <Adafruit_TinyUSB.h>


class Keypad
{
private:
    Adafruit_USBD_HID _usb_hid;
    static const uint8_t _desc_hid_report[];
    static void hid_report_callback(uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize);

public:
    Keypad(void);
    void begin(void);
    void end(void);
    size_t write(uint8_t k);
    size_t write_with_modifier(uint8_t modifier, uint8_t keycode);
    size_t press(uint8_t k);
    size_t release(uint8_t k);
    void releaseAll(void);
};


#define HID_MODIFIER_CONTROL_LEFT   0x01
#define HID_MODIFIER_SHIFT_LEFT     0x02
#define HID_MODIFIER_ALT_LEFT       0x04
#define HID_MODIFIER_GUI_LEFT       0x08
#define HID_MODIFIER_CONTROL_RIGHT  0x10
#define HID_MODIFIER_SHIFT_RIGHT    0x20
#define HID_MODIFIER_ALT_RIGHT      0x40
#define HID_MODIFIER_GUI_RIGHT      0x80

#endif  