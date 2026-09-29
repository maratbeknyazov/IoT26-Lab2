// Exercise 1: LED chase (Knight Rider)
// Cycle RED -> GREEN -> YELLOW -> BLUE -> YELLOW -> GREEN and repeat.
// One LED on at a time for 150 ms; single delay(150) per loop iteration.

#include "Arduino.h"

#define RED_LED_PIN    26
#define GREEN_LED_PIN  27
#define BLUE_LED_PIN   14
#define YELLOW_LED_PIN 12

// Sequence of pins to cycle through (mirrors the README order)
static const uint8_t chasePins[] = {
    RED_LED_PIN,
    GREEN_LED_PIN,
    YELLOW_LED_PIN,
    BLUE_LED_PIN,
    YELLOW_LED_PIN,
    GREEN_LED_PIN,
};
static const uint8_t chaseNames[] = { // matching names for Serial output
    'R', 'G', 'Y', 'B', 'Y', 'G'
};
static const uint8_t chaseLen = sizeof(chasePins) / sizeof(chasePins[0]);

static uint8_t stepIndex = 0; // current position in the chase sequence

/****************************************************/
void setup(void)
{
    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(GREEN_LED_PIN, OUTPUT);
    pinMode(BLUE_LED_PIN, OUTPUT);
    pinMode(YELLOW_LED_PIN, OUTPUT);

    Serial.begin(115200);
}

/****************************************************/
void loop(void)
{
    // Turn everything off, then light exactly one LED
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(chasePins[stepIndex], HIGH);

    // Print the name of the LED that just turned on
    Serial.print("chase=");
    switch (chaseNames[stepIndex]) {
    case 'R': Serial.println("RED");    break;
    case 'G': Serial.println("GREEN");  break;
    case 'Y': Serial.println("YELLOW"); break;
    case 'B': Serial.println("BLUE");   break;
    }

    stepIndex = (stepIndex + 1) % chaseLen; // wrap back to the start

    delay(150); // one delay per loop iteration, as required
}
