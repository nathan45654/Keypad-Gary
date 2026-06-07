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
    uint8_t _press_delay{ 5 };
    uint8_t polling_interval_ms{ 2 };
public:
    Keypad(void);
    void begin(void);
    void end(void);
    size_t write(uint8_t k);
    size_t write_with_modifier(uint8_t modifier, uint8_t keycode);
    void write_string(const char* str);
    size_t press(char c);
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