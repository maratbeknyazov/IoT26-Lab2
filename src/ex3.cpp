// Exercise 3: Sensor threshold alert with hysteresis
// Every 300 ms read LIGHT (D33). Raise the alert when the reading rises
// above 3000, clear it when the reading drops below 2500. The gap between
// the two thresholds prevents rapid flickering.
// Print "ALERT=1" only at the moment the alert becomes active and
// "ALERT=0" only at the moment it clears (edge-triggered output).

#include "Arduino.h"

#define LIGHT_SENSOR_PIN 33

#define READ_INTERVAL_MS 300

#define ALERT_ON_THRESHOLD  3000 // activate when reading >  this
#define ALERT_OFF_THRESHOLD 2500 // clear when reading      <  this

static bool alertActive = false;
static uint32_t lastReadMs = 0;

/****************************************************/
void setup(void)
{
    Serial.begin(115200);
    analogReadResolution(12); // 0..4095 like the default ESP32 setup

    lastReadMs = millis();
}

/****************************************************/
void loop(void)
{
    if (millis() - lastReadMs >= READ_INTERVAL_MS) {
        lastReadMs += READ_INTERVAL_MS; // keep a steady 300 ms cadence

        uint16_t reading = analogRead(LIGHT_SENSOR_PIN);

        if (!alertActive && reading > ALERT_ON_THRESHOLD) {
            // Rising above the upper threshold: activate the alert
            alertActive = true;
            Serial.println("ALERT=1");
        }
        else if (alertActive && reading < ALERT_OFF_THRESHOLD) {
            // Dropping below the lower threshold: clear the alert
            alertActive = false;
            Serial.println("ALERT=0");
        }
        // Between 2500 and 3000 nothing changes (hysteresis gap)
    }
}
