#include <Adafruit_TinyUSB.h>
#include  "Keypad.h"

const uint8_t Keypad::_desc_hid_report[] = {
    TUD_HID_REPORT_DESC_KEYBOARD()
};

Keypad::Keypad(void){

}
void Keypad::hid_report_callback(uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize) {
	(void) report_id;
	(void) bufsize;

	// LED indicator is output report with only 1 byte length
	if (report_type != HID_REPORT_TYPE_OUTPUT) return;

	// The LED bit map is as follows: (also defined by KEYBOARD_LED_* )
	// Kana (4) | Compose (3) | ScrollLock (2) | CapsLock (1) | Numlock (0)
	uint8_t ledIndicator = buffer[0];

	#ifdef LED_BUILTIN
	// turn on LED if capslock is set
	digitalWrite(LED_BUILTIN, ledIndicator & KEYBOARD_LED_CAPSLOCK);
	#endif
}

void Keypad::begin(void)
{
    if (!TinyUSBDevice.isInitialized()) {
        TinyUSBDevice.begin(0);
    }

    // Setup HID
    _usb_hid.setBootProtocol(HID_ITF_PROTOCOL_KEYBOARD);
    _usb_hid.setPollInterval(polling_interval_ms);
    _usb_hid.setReportDescriptor(_desc_hid_report, sizeof(_desc_hid_report));
    _usb_hid.setStringDescriptor("TinyUSB Keyboard");

    // Set up output report (on control endpoint) for Capslock indicator
    _usb_hid.setReportCallback(NULL, Keypad::hid_report_callback);

    _usb_hid.begin();

    // If already enumerated, additional class driverr begin() e.g msc, hid, midi won't take effect until re-enumeration
    if (TinyUSBDevice.mounted()) {
        TinyUSBDevice.detach();
        delay(_press_delay);
        TinyUSBDevice.attach();
    }
}

void Keypad::end(void)
{
}
  
size_t Keypad::press(char c) 
{
  	_usb_hid.keyboardPress(0, c);
    delay(_press_delay);

    return 1;
}

void Keypad::releaseAll(void)
{
    uint8_t none[6] = {0,0,0,0,0,0};
    _usb_hid.keyboardReport(0, 0, none);
    delay(_press_delay);

}

size_t Keypad::write(uint8_t keycode)
{
	if (TinyUSBDevice.suspended()) {
    	// Wake up host if we are in suspend mode
    	// and REMOTE_WAKEUP feature is enabled by host
		TinyUSBDevice.remoteWakeup();
	}

    // keyboardReport expects an array of up to 6 keycodes
    uint8_t keys[6] = {0,0,0,0,0,0};
    keys[0] = keycode;

    // report_id = 0, modifier = 0
    _usb_hid.keyboardReport(0, 0, keys);

    // short hold, then release
    delay(_press_delay);
	releaseAll();
    return 1;
}

size_t Keypad::write_with_modifier(uint8_t modifier, uint8_t keycode) {

	if (TinyUSBDevice.suspended()) {
    	// Wake up host if we are in suspend mode
    	// and REMOTE_WAKEUP feature is enabled by host
		TinyUSBDevice.remoteWakeup();
	}

    // keyboardReport expects an array of up to 6 keycodes
    uint8_t keys[6] = {0,0,0,0,0,0};
    keys[0] = keycode;

    // report_id = 0, modifier = 0
    _usb_hid.keyboardReport(0, modifier, keys);

    // short hold, then release
    delay(_press_delay);
	releaseAll();
    return 1;
}
  
// helper: map ASCII char to HID keycode and modifier (modifier passed back by reference)
static uint8_t ascii_to_hid(char c, uint8_t &modifier)
{
    modifier = 0;

    if (c >= 'a' && c <= 'z') {
        return HID_KEY_A + (c - 'a');
    }
    if (c >= 'A' && c <= 'Z') {
        modifier = HID_MODIFIER_SHIFT_LEFT;
        return HID_KEY_A + (c - 'A');
    }
    if (c >= '1' && c <= '9') {
        return HID_KEY_1 + (c - '1');
    }
    if (c == '0') return HID_KEY_0;
    if (c == ' ') return HID_KEY_SPACE;
    if (c == '\n' || c == '\r') return HID_KEY_ENTER;
    if (c == '.') return HID_KEY_PERIOD;
    if (c == ',') return HID_KEY_COMMA;
    if (c == '-') return HID_KEY_MINUS;
    if (c == '_') { modifier = HID_MODIFIER_SHIFT_LEFT; return HID_KEY_MINUS; }
    if (c == '!') { modifier = HID_MODIFIER_SHIFT_LEFT; return HID_KEY_1; }
    if (c == '?') { modifier = HID_MODIFIER_SHIFT_LEFT; return HID_KEY_SLASH; }
    if (c == ';') return HID_KEY_SEMICOLON;
    if (c == ':') { modifier = HID_MODIFIER_SHIFT_LEFT; return HID_KEY_SEMICOLON; }
    // add more mappings as needed

    return 0; // unsupported
}

void Keypad::write_string(const char* str)
{
    if (!str) return;

    for (const char *p = str; *p != '\0'; ++p) {
        uint8_t mod = 0;
        uint8_t key = ascii_to_hid(*p, mod);
        if (!key) {
            // unsupported char -> short pause and continue
        }

        if (mod) {
            write_with_modifier(mod, key);
        } else {
            write(key);
        }
    }

    // ensure all keys released
    releaseAll();
}
// Output report callback for LED indicator such as Caplocks
