#include <Arduino.h>
#define CLR_RESET   "\033[0m"
#define CLR_RED     "\033[31m"
#define CLR_GREEN   "\033[32m"
#define CLR_YELLOW  "\033[33m"
#define CLR_BLUE    "\033[34m"
#define CLR_CYAN    "\033[36m"

void serial1PrintColor(const char* color, const char* text)
{
  Serial1.print(color);
  Serial1.print(text);
  Serial1.print(CLR_RESET);
}

void serial1PrintlnColor(const char* color, const char* text)
{
  Serial1.print(color);
  Serial1.println(text);
  Serial1.print(CLR_RESET);
}
// upload_flags = -c set CPUTAPID 0x2ba01477

//////////////////////////////////////////////////////////////
//////////Start UART Test Code Start//////////////////////////
//////////////////////////////////////////////////////////////

// void setup()
// {
//   // put your setup code here, to run once:
//   Serial1.begin(9600);
//   Serial1.print(CLR_RED);
//   Serial1.println("Hello, UART!");
//   pinMode(LED_BUILTIN, OUTPUT_OPEN_DRAIN);
//   digitalWrite(LED_BUILTIN, LOW);
// }

// void loop()
// {
//   Serial1.print(CLR_GREEN);
//   Serial1.println("Here is a test message from STM32 Bluepill UART1.");
//   digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
//   delay(1000);
// }

////////////////////////////////////////////////////////////////
////////////END UART Test Code END//////////////////////////////
////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
////////////Start I2C Scanner Code Start////////////////////////
////////////////////////////////////////////////////////////////
// #include <Wire.h>

// void setup()
// {
//   Serial1.begin(9600);
//   delay(1000);

//   // Wire.setSDA(PB11);
//   // Wire.setSCL(PB10);
//   // Wire.setClock(400000);   // fast mode = 400 kHz
//   Wire.begin(); //connected on

//   serial1PrintlnColor(CLR_YELLOW, "I2C Scanner");
//   serial1PrintlnColor(CLR_YELLOW, "Scanning I2C bus...");

//   int count = 0;
//   for (uint8_t i = 1; i < 127; i++)
//   {
//     Wire.beginTransmission(i);
//     if (Wire.endTransmission() == 0)
//     {
//       serial1PrintColor(CLR_GREEN,"Found device at: 0x");
//       if (i < 16)
//         Serial1.print("0");
//       Serial1.println(i, HEX);
//       count++;
//     }
//   }

//   if (count == 0)
//   {
//     serial1PrintlnColor(CLR_RED, "No I2C devices found!");
//   }
//   else
//   {
//     serial1PrintColor(CLR_GREEN,"Total devices found: ");
//     Serial1.println(count);
//   }
// }

// void loop()
// {
// }

////////////////////////////////////////////////////////////////
////////////END I2C Scanner Code END////////////////////////////
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
////////////Start TCA8418RTWR Matrix Code Start/////////////////
////////////////////////////////////////////////////////////////
//  #include <Adafruit_TCA8418.h>

// Adafruit_TCA8418 keypad;

// void setup()
// {
//   Serial1.begin(9600);
//   while (!Serial1)
//   {
//     delay(10);
//   }
//   Serial1.println("Starting!");
//   Serial1.println(__FILE__);

//   if (!keypad.begin(TCA8418_DEFAULT_ADDR, &Wire))
//   {
//     Serial1.println("keypad not found, check wiring & pullups!");
//     while (1)
//       ;
//   }
//   Serial1.println("keypad found!");

//   // configure the size of the keypad matrix.
//   // all other pins will be inputs
//   keypad.matrix(8, 10);

//   // flush the internal buffer
//   keypad.flush();
// }

// void loop()
// {
//   if (keypad.available() > 0)
//   {
//     //  datasheet page 15 - Table 1
//     int k = keypad.getEvent();
//     if (k & 0x80)
//       Serial1.print("PRESS\tR: ");
//     else
//       Serial1.print("RELEASE\tR: ");
//     k &= 0x7F;
//     k--;
//     Serial1.print(k / 10);
//     Serial1.print("\tC: ");
//     Serial1.print(k % 10);
//     Serial1.println();
//   }
//   // other code here
// }

////////////////////////////////////////////////////////////////
////////////END TCA8418RTWR Matrix Code END ////////////////////
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
////////////Start LEDs Test Code Start//////////////////////////
////////////////////////////////////////////////////////////////
// #include <Wire.h>
// #include <Adafruit_PWMServoDriver.h>
// #include <stdarg.h>
// #include <stdio.h>

// // Use Serial1 for hardware UART, or change to Serial for USB Serial Monitor
// #define DEBUG_SERIAL Serial1

// // Compile-time macro for static colored strings (zero runtime overhead)
// #define COLOR_STR(color, text) (color text CLR_RESET)

// // I2C addresses for the three PCA9685 ICs
// constexpr uint8_t DRIVER_ADDRESSES[]  = {0x40, 0x41, 0x42};
// constexpr size_t NUM_DRIVERS          = sizeof(DRIVER_ADDRESSES) / sizeof(DRIVER_ADDRESSES[0]);
// constexpr uint16_t PWM_FREQUENCY_HZ   = 1000; // Valid PCA9685 range: 24 Hz to 1526 Hz

// Adafruit_PWMServoDriver pwmDrivers[NUM_DRIVERS] = {
//     Adafruit_PWMServoDriver(DRIVER_ADDRESSES[0]),
//     Adafruit_PWMServoDriver(DRIVER_ADDRESSES[1]),
//     Adafruit_PWMServoDriver(DRIVER_ADDRESSES[2])};

// // Printf-style colored output for messages with variables (numbers, hex, etc.)
// void serial1PrintfColor(const char *color, const char *format, ...)
// {
//   char buffer[128];
//   va_list args;
//   va_start(args, format);
//   vsnprintf(buffer, sizeof(buffer), format, args);
//   va_end(args);

//   DEBUG_SERIAL.print(color);
//   DEBUG_SERIAL.print(buffer);
//   DEBUG_SERIAL.print(CLR_RESET);
// }

// // --- PCA9685 Helper Functions ---

// void initDriver(Adafruit_PWMServoDriver &driver, uint8_t address, size_t index)
// {
//   serial1PrintfColor(CLR_CYAN, "Scanning for PCA9685 #%u at 0x%02X...\r\n", index + 1, address);

//   while (true)
//   {
//     Wire.beginTransmission(address);
//     if (Wire.endTransmission() == 0)
//     {
//       serial1PrintfColor(CLR_GREEN, "[OK] PCA9685 #%u found at 0x%02X!\r\n", index + 1, address);
//       break;
//     }
//     serial1PrintfColor(CLR_RED, "[ERR] No PCA9685 at 0x%02X - check wiring! Retrying...\r\n", address);
//     delay(500);
//   }

//   // Initialize ONLY after the chip has responded on the I2C bus
//   driver.begin();
//   driver.setPWMFreq(PWM_FREQUENCY_HZ);

//   serial1PrintfColor(CLR_BLUE, "[INIT] PCA9685 #%u configured at %u Hz.\r\n", index + 1, PWM_FREQUENCY_HZ);
// }

// void setAllOutputs(uint16_t value)
// {
//   for (size_t d = 0; d < NUM_DRIVERS; d++)
//   {
//     for (uint8_t ch = 0; ch < 16; ch++)
//     {
//       pwmDrivers[d].setPin(ch, value);
//     }
//   }
// }

// void setup()
// {
//   DEBUG_SERIAL.begin(9600);
//   while (!DEBUG_SERIAL)
//   {
//     ; // Wait for serial port to connect
//   }
//   delay(1000);

//   serial1PrintlnColor(CLR_CYAN, "=== Starting PCA9685 Multi-Driver System ===");

//   // Initialize I2C bus before scanning
//   Wire.begin();

//   for (size_t i = 0; i < NUM_DRIVERS; i++)
//   {
//     initDriver(pwmDrivers[i], DRIVER_ADDRESSES[i], i);
//   }

//   serial1PrintlnColor(CLR_GREEN, "=== All PCA9685 Drivers Ready! ===");
// }

// void loop()
// {
//   // ALL ON (100% brightness)
//   setAllOutputs(4095);
//   serial1PrintlnColor(CLR_GREEN, "LEDs ON");
//   delay(500);

//   // ALL OFF (0% brightness)
//   setAllOutputs(0);
//   serial1PrintlnColor(CLR_YELLOW, "LEDs OFF");
//   delay(500);
// }
////////////////////////////////////////////////////////////////
////////////END LEDs test Code END /////////////////////////////
////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
////////////Start Buttons Test Code Start///////////////////////
////////////////////////////////////////////////////////////////
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <stdarg.h>
#include <stdio.h>

// Serial1 uses PA10 (RX) and PA9 (TX) per schematic
#define DEBUG_SERIAL Serial1

// ANSI Color Escape Codes
#define CLR_RESET   "\033[0m"
#define CLR_RED     "\033[31m"
#define CLR_GREEN   "\033[32m"
#define CLR_YELLOW  "\033[33m"
#define CLR_BLUE    "\033[34m"
#define CLR_CYAN    "\033[36m"

// --- PCA9685 Configuration ---
constexpr uint8_t DRIVER_ADDRESSES[] = { 0x40, 0x41, 0x42 };
constexpr size_t NUM_DRIVERS = sizeof(DRIVER_ADDRESSES) / sizeof(DRIVER_ADDRESSES[0]);
constexpr uint16_t PWM_FREQUENCY_HZ = 1000;

Adafruit_PWMServoDriver pwmDrivers[NUM_DRIVERS] = {
  Adafruit_PWMServoDriver(DRIVER_ADDRESSES[0]),
  Adafruit_PWMServoDriver(DRIVER_ADDRESSES[1]),
  Adafruit_PWMServoDriver(DRIVER_ADDRESSES[2])
};

// --- Momentary & Toggle Button Structure ---
struct ButtonInput {
  uint32_t pin;
  const char* pinName;
  const char* label;
  const char* category;
  const char* functionName;
  uint8_t idleState;
  uint8_t lastStableState;
  uint8_t lastRawState;
  uint32_t lastDebounceMs;
};

// 20 Buttons & Toggle Switches (Rotary Switch separated below)
ButtonInput buttons[] = {
  // Left Wing Buttons
  { PB13, "PB13", "BTN 1",  "Left Wing",      "CONTRAST_P",    HIGH, HIGH, HIGH, 0 },
  { PB14, "PB14", "BTN 2",  "Left Wing",      "CONTRAST_N",    HIGH, HIGH, HIGH, 0 },
  { PB15, "PB15", "BTN 3",  "Left Wing",      "BRIGHTNESS_P",  HIGH, HIGH, HIGH, 0 },
  { PA8,  "PA8",  "BTN 4",  "Left Wing",      "BRIGHTNESS_N",  HIGH, HIGH, HIGH, 0 },
  { PA11, "PA11", "BTN 5",  "Left Wing",      "EXPOSURE_P",    HIGH, HIGH, HIGH, 0 },
  { PA12, "PA12", "BTN 6",  "Left Wing",      "EXPOSURE_N",    HIGH, HIGH, HIGH, 0 },
  { PA15, "PA15", "BTN 7",  "Left Wing",      "COLOR",         HIGH, HIGH, HIGH, 0 },
  { PB3,  "PB3",  "BTN 8",  "Left Wing",      "AUTO",          HIGH, HIGH, HIGH, 0 },

  // Camera Focus Buttons
  { PB11, "PB11", "BTN 9",  "Camera Focus",   "FOCUS_P",       HIGH, HIGH, HIGH, 0 },
  { PB10, "PB10", "BTN 10", "Camera Focus",   "AUTO_FOCUS",    HIGH, HIGH, HIGH, 0 },
  { PB1,  "PB1",  "BTN 11", "Camera Focus",   "FOCUS_N",       HIGH, HIGH, HIGH, 0 },

  // Battle Range & Lamp Test
  { PA6,  "PA6",  "BTN 12", "General",        "BATTLE_RANGE",  HIGH, HIGH, HIGH, 0 },
  { PA7,  "PA7",  "BTN 13", "General",        "LAMP_TEST",     HIGH, HIGH, HIGH, 0 },

  // Toggle Switches
  { PB0,  "PB0",  "BTN 14", "Toggle 3 Zoom",  "X3_ZOOM",       HIGH, HIGH, HIGH, 0 },
  { PA5,  "PA5",  "BTN 15", "Toggle 2 Therm", "THERMAL_PIN",   HIGH, HIGH, HIGH, 0 },
  { PA4,  "PA4",  "BTN 16", "Toggle 1 LRF",   "LRF_2ND_ECHO",  HIGH, HIGH, HIGH, 0 },
  { PA3,  "PA3",  "BTN 17", "Toggle 1 LRF",   "LRF_OFF",       HIGH, HIGH, HIGH, 0 },
  { PA2,  "PA2",  "BTN 18", "Toggle 3 Zoom",  "X16_ZOOM",      HIGH, HIGH, HIGH, 0 },

  // External Buttons
  { PA1,  "PA1",  "SW_1IN", "External Btn",   "Laser_fire_pin",HIGH, HIGH, HIGH, 0 },
  { PA0,  "PA0",  "SW_2IN", "External Btn",   "Encoder_pin",   HIGH, HIGH, HIGH, 0 }
};

constexpr size_t NUM_BUTTONS = sizeof(buttons) / sizeof(buttons[0]);

// --- 5-Position Rotary Switch Structure ---
struct RotaryPos {
  uint32_t pin;
  const char* pinName;
  const char* label;
  const char* functionName;
};

RotaryPos rotaryPins[] = {
  { PB12, "PB12", "RW 1", "COAXIAL_GUN"   },
  { PB4,  "PB4",  "RW 2", "HEP"           },
  { PB5,  "PB5",  "RW 3", "SABOT"         },
  { PB8,  "PB8",  "RW 4", "HEAT"          },
  { PB9,  "PB9",  "RW 5", "HIGH_EXPOSURE" }
};

constexpr size_t NUM_ROTARY_POS = sizeof(rotaryPins) / sizeof(rotaryPins[0]);

uint8_t rotaryActiveLevel = LOW;     // Automatically detected at startup (LOW if pulled-up, HIGH if pulled-down)
int8_t  currentRotaryIndex = -1;     // Currently confirmed rotary switch index (0..4, or -1 if between detents)
int8_t  candidateRotaryIndex = -1;   // Debounce candidate index
uint32_t rotaryDebounceMs = 0;

constexpr uint32_t DEBOUNCE_MS = 30;

void serial1PrintfColor(const char* color, const char* format, ...) {
  char buffer[160];
  va_list args;
  va_start(args, format);
  vsnprintf(buffer, sizeof(buffer), format, args);
  va_end(args);

  DEBUG_SERIAL.print(color);
  DEBUG_SERIAL.print(buffer);
  DEBUG_SERIAL.print(CLR_RESET);
}

// --- PCA9685 Helper Functions ---

void initDriver(Adafruit_PWMServoDriver &driver, uint8_t address, size_t index) {
  serial1PrintfColor(CLR_CYAN, "Scanning for PCA9685 #%u at 0x%02X...\r\n", index + 1, address);

  while (true) {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0) {
      serial1PrintfColor(CLR_GREEN, "[OK] PCA9685 #%u found at 0x%02X!\r\n", index + 1, address);
      break;
    }
    serial1PrintfColor(CLR_RED, "[ERR] No PCA9685 at 0x%02X - check wiring! Retrying...\r\n", address);
    delay(500);
  }

  driver.begin();
  driver.setPWMFreq(PWM_FREQUENCY_HZ);
  serial1PrintfColor(CLR_BLUE, "[INIT] PCA9685 #%u configured at %u Hz.\r\n", index + 1, PWM_FREQUENCY_HZ);
}

void setAllOutputs(uint16_t value) {
  for (size_t d = 0; d < NUM_DRIVERS; d++) {
    for (uint8_t ch = 0; ch < 16; ch++) {
      pwmDrivers[d].setPin(ch, value);
    }
  }
}

void blinkAllLEDs(uint8_t flashes = 2, uint16_t delayMs = 120) {
  for (uint8_t f = 0; f < flashes; f++) {
    setAllOutputs(4095);
    delay(delayMs);
    setAllOutputs(0);
    delay(delayMs);
  }
}

// --- Read Which Rotary Switch Position Is Currently Active ---
int8_t readActiveRotaryIndex() {
  for (size_t i = 0; i < NUM_ROTARY_POS; i++) {
    if (digitalRead(rotaryPins[i].pin) == rotaryActiveLevel) {
      return (int8_t)i;
    }
  }
  return -1; // No position active (between detents)
}

// --- Initialize & Diagnose Rotary Switch ---
void initAndTestRotarySwitch() {
  serial1PrintlnColor(CLR_CYAN, "\r\n================ ROTARY SWITCH (RW 1 - RW 5) REPORT ================");

  uint8_t highCount = 0;
  uint8_t lowCount  = 0;
  uint8_t floatingCount = 0;

  for (size_t i = 0; i < NUM_ROTARY_POS; i++) {
    pinMode(rotaryPins[i].pin, INPUT_PULLUP);
    delayMicroseconds(200);
    uint8_t pu = digitalRead(rotaryPins[i].pin);

    pinMode(rotaryPins[i].pin, INPUT_PULLDOWN);
    delayMicroseconds(200);
    uint8_t pd = digitalRead(rotaryPins[i].pin);

    pinMode(rotaryPins[i].pin, INPUT);
    delayMicroseconds(500);
    uint8_t raw = digitalRead(rotaryPins[i].pin);

    if (pu != pd) {
      floatingCount++;
    }
    if (raw == HIGH) highCount++;
    else             lowCount++;
  }

  // If the unselected pins are floating (no external resistors), enable internal pull-ups
  if (floatingCount >= 3) {
    for (size_t i = 0; i < NUM_ROTARY_POS; i++) {
      pinMode(rotaryPins[i].pin, INPUT_PULLUP);
    }
    delayMicroseconds(500);
    highCount = 0;
    lowCount = 0;
    for (size_t i = 0; i < NUM_ROTARY_POS; i++) {
      if (digitalRead(rotaryPins[i].pin) == HIGH) highCount++;
      else                                        lowCount++;
    }
    serial1PrintlnColor(CLR_YELLOW, "[NOTE] Rotary pins had no external pull resistors -> Enabled INPUT_PULLUP.");
  }

  // Majority vote: 4 pins are unselected (idle), 1 pin is selected (active)
  uint8_t idleLevel = (highCount >= lowCount) ? HIGH : LOW;
  rotaryActiveLevel = (idleLevel == HIGH) ? LOW : HIGH;

  serial1PrintfColor(
    CLR_BLUE,
    "Rotary Polarity : %s (Unselected pins = %s, Selected pin = %s)\r\n",
    (idleLevel == HIGH) ? "PULLED UP (Active LOW)" : "PULLED DOWN (Active HIGH)",
    (idleLevel == HIGH) ? "HIGH" : "LOW",
    (rotaryActiveLevel == HIGH) ? "HIGH" : "LOW"
  );

  for (size_t i = 0; i < NUM_ROTARY_POS; i++) {
    uint8_t state = digitalRead(rotaryPins[i].pin);
    bool isSelected = (state == rotaryActiveLevel);

    serial1PrintfColor(
      isSelected ? CLR_GREEN : CLR_CYAN,
      "%-5s | %-6s | %-16s | Level: %-4s | %s\r\n",
      rotaryPins[i].pinName,
      rotaryPins[i].label,
      rotaryPins[i].functionName,
      (state == HIGH) ? "HIGH" : "LOW",
      isSelected ? "<-- CURRENTLY SELECTED POSITION" : "Unselected"
    );
  }

  currentRotaryIndex = readActiveRotaryIndex();
  candidateRotaryIndex = currentRotaryIndex;
  rotaryDebounceMs = millis();

  serial1PrintlnColor(CLR_CYAN, "====================================================================");
}

// --- Initialize & Diagnose Pushbuttons and Toggles ---
void initAndTestButtons() {
  // Free PA15, PB3, PB4 from JTAG so they work as standard GPIO inputs on STM32F1
  #if defined(AFIO_MAPR_SWJ_CFG_JTAGDISABLE)
    __HAL_RCC_AFIO_CLK_ENABLE();
    __HAL_AFIO_REMAP_SWJ_NOJTAG();
  #endif

  serial1PrintlnColor(CLR_CYAN, "\r\n================ BUTTON PULL-UP / PULL-DOWN REPORT ================");
  serial1PrintlnColor(CLR_BLUE, "PIN   | LABEL  | FUNCTION         | IDLE STATE & PULL TYPE");
  serial1PrintlnColor(CLR_BLUE, "------+--------+------------------+--------------------------------");

  for (size_t i = 0; i < NUM_BUTTONS; i++) {
    pinMode(buttons[i].pin, INPUT_PULLUP);
    delayMicroseconds(200);
    uint8_t readWithPullUp = digitalRead(buttons[i].pin);

    pinMode(buttons[i].pin, INPUT_PULLDOWN);
    delayMicroseconds(200);
    uint8_t readWithPullDown = digitalRead(buttons[i].pin);

    pinMode(buttons[i].pin, INPUT);
    delayMicroseconds(500);
    uint8_t idle = digitalRead(buttons[i].pin);

    buttons[i].idleState = idle;
    buttons[i].lastStableState = idle;
    buttons[i].lastRawState = idle;
    buttons[i].lastDebounceMs = millis();

    if (readWithPullUp == HIGH && readWithPullDown == HIGH) {
      serial1PrintfColor(
        CLR_GREEN,
        "%-5s | %-6s | %-16s | PULLED UP   (Idle: HIGH -> Active: LOW)\r\n",
        buttons[i].pinName, buttons[i].label, buttons[i].functionName
      );
    } else if (readWithPullUp == LOW && readWithPullDown == LOW) {
      serial1PrintfColor(
        CLR_YELLOW,
        "%-5s | %-6s | %-16s | PULLED DOWN (Idle: LOW  -> Active: HIGH)\r\n",
        buttons[i].pinName, buttons[i].label, buttons[i].functionName
      );
    } else {
      pinMode(buttons[i].pin, INPUT_PULLUP);
      delayMicroseconds(200);
      idle = digitalRead(buttons[i].pin);
      buttons[i].idleState = idle;
      buttons[i].lastStableState = idle;
      buttons[i].lastRawState = idle;

      serial1PrintfColor(
        CLR_RED,
        "%-5s | %-6s | %-16s | FLOATING!   (Input=%s, enabled internal PULLUP)\r\n",
        buttons[i].pinName, buttons[i].label, buttons[i].functionName,
        (idle == HIGH) ? "HIGH" : "LOW"
      );
    }
  }
  serial1PrintlnColor(CLR_CYAN, "===================================================================");
}

void setup() {
  DEBUG_SERIAL.begin(9600);
  Serial1.print("\033[2J\033[H");
  while (!DEBUG_SERIAL) {
    ;
  }
  delay(1000);

  serial1PrintlnColor(CLR_CYAN, "=== Starting PCA9685 + Button & Rotary Diagnostic System ===");

  Wire.begin();

  for (size_t i = 0; i < NUM_DRIVERS; i++) {
    initDriver(pwmDrivers[i], DRIVER_ADDRESSES[i], i);
  }
  setAllOutputs(0);

  initAndTestButtons();
  initAndTestRotarySwitch();

  serial1PrintlnColor(CLR_GREEN, "\r\nReady! Press any button or turn the rotary switch to test...");
}

void loop() {
  uint32_t now = millis();

  // 1. Poll Momentary Pushbuttons & Toggle Switches
  for (size_t i = 0; i < NUM_BUTTONS; i++) {
    uint8_t rawState = digitalRead(buttons[i].pin);

    if (rawState != buttons[i].lastRawState) {
      buttons[i].lastRawState = rawState;
      buttons[i].lastDebounceMs = now;
    }

    if ((now - buttons[i].lastDebounceMs) >= DEBOUNCE_MS) {
      if (rawState != buttons[i].lastStableState) {
        buttons[i].lastStableState = rawState;

        if (rawState != buttons[i].idleState) {
          const char* pullType = (buttons[i].idleState == HIGH) ? "Pulled-UP (Active LOW)" : "Pulled-DOWN (Active HIGH)";

          serial1PrintfColor(
            CLR_GREEN,
            "[PRESSED]  %-6s (%-4s) | %-14s | %-14s | Signal: %s | %s\r\n",
            buttons[i].label,
            buttons[i].pinName,
            buttons[i].category,
            buttons[i].functionName,
            (rawState == HIGH) ? "HIGH (1)" : "LOW  (0)",
            pullType
          );

          serial1PrintlnColor(CLR_CYAN, "  -> Blinking all PCA9685 LEDs!");
          blinkAllLEDs(2, 120);
        } else {
          serial1PrintfColor(
            CLR_YELLOW,
            "[RELEASED] %-6s (%-4s) | %-14s | Returned to Idle (%s)\r\n",
            buttons[i].label,
            buttons[i].pinName,
            buttons[i].functionName,
            (rawState == HIGH) ? "HIGH" : "LOW"
          );
        }
      }
    }
  }

  // 2. Poll 5-Position Rotary Switch (RW 1 - RW 5)
  int8_t rawRotary = readActiveRotaryIndex();

  if (rawRotary != candidateRotaryIndex) {
    candidateRotaryIndex = rawRotary;
    rotaryDebounceMs = now;
  }

  // Only trigger when the rotary switch settles on a valid new position (0..4)
  if ((now - rotaryDebounceMs) >= DEBOUNCE_MS) {
    if (rawRotary != -1 && rawRotary != currentRotaryIndex) {
      currentRotaryIndex = rawRotary;

      serial1PrintfColor(
        CLR_GREEN,
        "[ROTARY]   Selected %-4s (%-4s) | Position #%d | Function: %-14s | Active Level: %s\r\n",
        rotaryPins[currentRotaryIndex].label,
        rotaryPins[currentRotaryIndex].pinName,
        currentRotaryIndex + 1,
        rotaryPins[currentRotaryIndex].functionName,
        (rotaryActiveLevel == HIGH) ? "HIGH (1)" : "LOW  (0)"
      );

      serial1PrintlnColor(CLR_CYAN, "  -> Blinking all PCA9685 LEDs!");
      blinkAllLEDs(2, 120);
    }
  }
}

////////////////////////////////////////////////////////////////
////////////END Button TEST Code END////////////////END/////////
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
////////////START LCD TEST Code START///////////////START///////
////////////////////////////////////////////////////////////////
// #include <Arduino.h>
// #include <LiquidCrystal.h>

// // LCD pins
// const uint8_t LCD_RS = PA2;
// const uint8_t LCD_RW = PA1;
// const uint8_t LCD_EN = PA3;
// const uint8_t LCD_D4 = PA4;
// const uint8_t LCD_D5 = PA5;
// const uint8_t LCD_D6 = PA6;
// const uint8_t LCD_D7 = PA7;

// // Create LCD object
// LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

// void setup()
// {
//   // If RW is connected to the MCU, keep it LOW for write-only operation
//   pinMode(LCD_RW, OUTPUT);
//   digitalWrite(LCD_RW, LOW);

//   lcd.begin(16, 2);

//   lcd.clear();
//   lcd.setCursor(0, 0);
//   lcd.print("STM32 Bluepill");

//   lcd.setCursor(0, 1);
//   lcd.print("LCD Test OK");
// }

// void loop()
// {
//   static uint32_t last = 0;
//   static uint16_t sec = 0;

//   if (millis() - last >= 1000)
//   {
//     last = millis();
//     sec++;

//     lcd.setCursor(0, 1);
//     lcd.print("Seconds:        ");
//     lcd.setCursor(9, 1);
//     lcd.print(sec);
//   }
// }
////////////////////////////////////////////////////////////////
////////////END LCD TEST Code END///////////////////END/////////
////////////////////////////////////////////////////////////////



/*
////////////////////////////////////////////////////////////////
////////////START Data Entry Code START/////////////START///////
////////////////////////////////////////////////////////////////

#include <Wire.h>
#include <Adafruit_TCA8418.h>
#include <Adafruit_PWMServoDriver.h>
#include <LiquidCrystal.h>

#define Key_rows              8
#define Key_cols              5
// LCD pins
#define LCD_RS            PA2
#define LCD_RW            PA1
#define LCD_EN            PA3
#define LCD_D4            PA4
#define LCD_D5            PA5
#define LCD_D6            PA6
#define LCD_D7            PA7

#define LCD_FIRST_ROW     0
#define LCD_SECOND_ROW    1

Adafruit_TCA8418 keypad;
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41);
Adafruit_PWMServoDriver pwm3 = Adafruit_PWMServoDriver(0x42);

// Create LCD object
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

void setLed(uint8_t ch, bool on)
{
  if (on)
  {
    pwm1.setPWM(ch, 0, 4096);
    pwm2.setPWM(ch, 0, 4096);
    pwm3.setPWM(ch, 0, 4096);
  }
  else
  {
    pwm1.setPWM(ch, 4096, 0);
    pwm2.setPWM(ch, 4096, 0);
    pwm3.setPWM(ch, 4096, 0);
  }
}

void setup()
{
  Serial1.begin(9600);
  delay(1000);

  // If RW is connected to the MCU, keep it LOW for write-only operation
  pinMode(LCD_RW, OUTPUT);
  digitalWrite(LCD_RW, LOW);

  lcd.begin(16, 2);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("STM32 Bluepill");

  lcd.setCursor(0, 1);
  lcd.print("LCD Test OK");
  
  Serial1.print(CLR_RED);
  Wire.begin();

  Serial1.println("I2C Scanner");
  Serial1.println("Scanning I2C bus...");

  int count = 0;
  for (uint8_t i = 1; i < 127; i++)
  {
    Wire.beginTransmission(i);
    if (Wire.endTransmission() == 0)
    {
      Serial1.print("Found device at: 0x");
      if (i < 16)
        Serial1.print("0");
      if(i == 0x34)
      {
        Serial1.print(i, HEX);
        Serial1.println(CLR_CYAN "   - TCA8418 Keypad Controller" CLR_RED);
        lcd.clear();
        lcd.setCursor(0, LCD_FIRST_ROW);
        lcd.print("TCA8418 Found");
      }
      else if(i == 0x40 || i == 0x41 || i == 0x42)
      {
        Serial1.print(i, HEX);
        Serial1.println(CLR_CYAN "   - PCA9685 PWM LED Driver" CLR_RED);
        lcd.setCursor(0, LCD_SECOND_ROW);
        static int PCA9685Count = 0;
        PCA9685Count++;
        lcd.print(PCA9685Count);
        lcd.print(" PCA9685 Found");
      }
      else if(i == 0x70)
      {
        Serial1.print(i, HEX);
        Serial1.println(CLR_CYAN "   - I2C address for all ICs of PCA9685 LED Driver" CLR_RED);
      }
      else
      {
        Serial1.print(i, HEX);
        Serial1.println(CLR_CYAN "   - unknown I2C device" CLR_RED);
        lcd.clear();
        lcd.setCursor(0, LCD_FIRST_ROW);
        lcd.print("Error: I2C");
        lcd.setCursor(0, LCD_SECOND_ROW);
        lcd.print("Unknown I2C Found");
      }

      count++;
    }
  }

  if (count == 0)
  {
    Serial1.println("No I2C devices found!");
    lcd.clear();
    lcd.setCursor(0, LCD_FIRST_ROW);
    lcd.print("Error: I2C");
    lcd.setCursor(0, LCD_SECOND_ROW);
    lcd.print("Unknown I2C Found");
  }
  else
  {
    Serial1.print("Total devices found: ");
    Serial1.println(count);
    delay(500);
    lcd.clear();
    lcd.setCursor(0, LCD_FIRST_ROW);
    lcd.print("Total I2C Found");
    lcd.setCursor(0, LCD_SECOND_ROW);
    lcd.print(count);
    delay(2000);
  }

  if (!keypad.begin(TCA8418_DEFAULT_ADDR, &Wire))
  {
    Serial1.println("TCA8418 not found or not responding ⚠️");
    while (1)
      delay(10);
  }

  keypad.matrix(Key_rows, Key_cols);
  keypad.flush();

  pwm1.begin();
  pwm2.begin();
  pwm3.begin();
  pwm1.setPWMFreq(1000);
  pwm2.setPWMFreq(1000);
  pwm3.setPWMFreq(1000);

  for (uint8_t i = 0; i < 16; i++)
  {
    setLed(i, false);
  }

  Serial1.println("Ready");
  Serial1.print(CLR_RESET);
  lcd.setCursor(0, LCD_FIRST_ROW);
  lcd.print("Ready");
  lcd.setCursor(0, LCD_SECOND_ROW);
  lcd.print("NEXT: Loop Function");
}

void loop()
{

  Serial1.print(CLR_GREEN);
  if (keypad.available() > 0)
  {
    int k = keypad.getEvent();
    bool pressed = k & 0x80;
    uint8_t key = k & 0x7F;

    if (key == 0)
    {
      lcd.setCursor(0, LCD_SECOND_ROW);
      lcd.print("                ");
      return;
    }

    key--;

    lcd.setCursor(0, LCD_SECOND_ROW);
    lcd.print("Action Happened!");
    uint8_t row = (key / Key_cols)/2;
    uint8_t col = key % Key_cols;
    uint8_t ledChannel = row * Key_cols + col;

    Serial1.print(pressed ? "PRESS  " : "RELEASE ");
    Serial1.print("R=");
    Serial1.print(row);
    Serial1.print(" C=");
    Serial1.print(col);
    Serial1.print(" CH=");
    Serial1.println(ledChannel);

    lcd.setCursor(0, LCD_FIRST_ROW);
    lcd.print(pressed ? "PRES  " : "RLSE ");
    lcd.print("R=");
    lcd.print(row);
    lcd.print("C=");
    lcd.print(col);

    // if (ledChannel < 16)
    // {
    //   setLed(ledChannel, 1);
    // }
    Serial1.print(CLR_RESET);
  }
}

////////////////////////////////////////////////////////////////
////////////END Data Entry Code END/////////////////END/////////
////////////////////////////////////////////////////////////////
*/