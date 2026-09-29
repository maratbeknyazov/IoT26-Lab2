// Exercise 2: Serial-only sensor statistics
// Every 1000 ms take 10 back-to-back analogRead() samples of LIGHT (D33)
// (no delay between the samples), compute min / max / average and print
// one line per second: "min=120 max=340 avg=210".

#include "Arduino.h"

#define LIGHT_SENSOR_PIN 33

#define SAMPLE_COUNT 10
#define REPORT_INTERVAL_MS 1000

static uint32_t lastReportMs = 0;

/****************************************************/
void setup(void)
{
    Serial.begin(115200);
    analogReadResolution(12); // 0..4095 like the default ESP32 setup

    lastReportMs = millis();
}

/****************************************************/
void loop(void)
{
    if (millis() - lastReportMs >= REPORT_INTERVAL_MS) {
        lastReportMs += REPORT_INTERVAL_MS; // keep a steady 1 s cadence

        // Take SAMPLE_COUNT back-to-back samples (no delay in between)
        uint16_t samples[SAMPLE_COUNT];
        for (uint8_t i = 0; i < SAMPLE_COUNT; i++) {
            samples[i] = analogRead(LIGHT_SENSOR_PIN);
        }

        // Compute minimum, maximum and average
        uint16_t minValue = samples[0];
        uint16_t maxValue = samples[0];
        uint32_t sum = 0;
        for (uint8_t i = 0; i < SAMPLE_COUNT; i++) {
            if (samples[i] < minValue) minValue = samples[i];
            if (samples[i] > maxValue) maxValue = samples[i];
            sum += samples[i];
        }
        uint16_t avgValue = (uint16_t)(sum / SAMPLE_COUNT);

        // One line per second
        Serial.print("min=");
        Serial.print(minValue);
        Serial.print(" max=");
        Serial.print(maxValue);
        Serial.print(" avg=");
        Serial.println(avgValue);
    }
}
