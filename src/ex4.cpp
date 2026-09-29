// Exercise 4: Button press counter with pattern
// Each press of BUTTON (D25) increments a counter that wraps back to 0
// after reaching 4. Exactly that many LEDs are lit simultaneously in the
// fixed order RED -> GREEN -> YELLOW -> BLUE (counter=2 -> RED+GREEN ON).
// Serial prints "count=<n>" every time the counter changes.
// Presses are detected with edge detection: one action per press even
// if the button is held down.

#include "Arduino.h"

#define BUTTON_PIN     25 // active high (pressed = HIGH)
#define RED_LED_PIN    26
#define GREEN_LED_PIN  27
#define BLUE_LED_PIN   14
#define YELLOW_LED_PIN 12

#define COUNTER_MAX 4 // counter wraps back to 0 after reaching this

static uint8_t pressCounter = 0;
static bool buttonWasPressed = false; // previous button state (for edges)
static bool patternDirty = true;      // apply pattern once at boot

/****************************************************/
// Light exactly 'litCount' LEDs in the fixed order
// RED -> GREEN -> YELLOW -> BLUE, the rest stay OFF.
static void applyPattern(uint8_t litCount)
{
    digitalWrite(RED_LED_PIN,    (litCount > 0) ? HIGH : LOW);
    digitalWrite(GREEN_LED_PIN,  (litCount > 1) ? HIGH : LOW);
    digitalWrite(YELLOW_LED_PIN, (litCount > 2) ? HIGH : LOW);
    digitalWrite(BLUE_LED_PIN,   (litCount > 3) ? HIGH : LOW);
}

/****************************************************/
void setup(void)
{
    pinMode(BUTTON_PIN, INPUT);
    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(GREEN_LED_PIN, OUTPUT);
    pinMode(BLUE_LED_PIN, OUTPUT);
    pinMode(YELLOW_LED_PIN, OUTPUT);

    Serial.begin(115200);
}

/****************************************************/
void loop(void)
{
    bool buttonPressed = (digitalRead(BUTTON_PIN) == HIGH);

    // Rising edge = the moment the button goes from released to pressed
    if (buttonPressed && !buttonWasPressed) {
        pressCounter++;
        if (pressCounter > COUNTER_MAX) {
            pressCounter = 0; // wrap back to 0 after reaching 4
        }

        Serial.print("count=");
        Serial.println(pressCounter);

        patternDirty = true;
    }
    buttonWasPressed = buttonPressed;

    // Refresh the LED pattern only when something changed
    if (patternDirty) {
        applyPattern(pressCounter);
        patternDirty = false;
    }
}
