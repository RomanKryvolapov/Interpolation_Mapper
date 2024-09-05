#include <Arduino.h>

// This is a value interpolation algorithm, it is made for Arduino Nano because it supports 5V,
// but you can use any other board. It is important to respect the bit depth of the input and output signal,
// or you need to add a conversion factor to the algorithm if the bit depth does not match.

const uint16_t MIN_VALUE = 178; // set the minimum value at which the action is activated
const uint16_t MAX_VALUE = 818; // set the maximum value that can be used for control

const uint16_t POINT_10_PERCENTS = 90; // the percentage of the input level for the 10 percent curve point
const uint16_t POINT_20_PERCENTS = 88; // the percentage of the input level for the 20 percent curve point
const uint16_t POINT_30_PERCENTS = 86; // the percentage of the input level for the 30 percent curve point
const uint16_t POINT_40_PERCENTS = 88; // the percentage of the input level for the 40 percent curve point
const uint16_t POINT_50_PERCENTS = 90; // the percentage of the input level for the 50 percent curve point
const uint16_t POINT_60_PERCENTS = 92; // the percentage of the input level for the 60 percent curve point
const uint16_t POINT_70_PERCENTS = 94; // the percentage of the input level for the 70 percent curve point
const uint16_t POINT_80_PERCENTS = 96; // the percentage of the input level for the 80 percent curve point
const uint16_t POINT_90_PERCENTS = 98; // the percentage of the input level for the 90 percent curve point

const uint8_t INPUT_PIN = 0;
const uint8_t OUTPUT_PIN = 9;

const uint16_t ONE_HUNDRED_PERCENTS = 100;
const uint16_t STEP = (MAX_VALUE - MIN_VALUE) / 10;
const uint32_t POINT_10_PERCENTS_OUTPUT = MIN_VALUE + STEP;
const uint32_t POINT_20_PERCENTS_OUTPUT = MIN_VALUE + STEP * 2;
const uint32_t POINT_30_PERCENTS_OUTPUT = MIN_VALUE + STEP * 3;
const uint32_t POINT_40_PERCENTS_OUTPUT = MIN_VALUE + STEP * 4;
const uint32_t POINT_50_PERCENTS_OUTPUT = MIN_VALUE + STEP * 5;
const uint32_t POINT_60_PERCENTS_OUTPUT = MIN_VALUE + STEP * 6;
const uint32_t POINT_70_PERCENTS_OUTPUT = MIN_VALUE + STEP * 7;
const uint32_t POINT_80_PERCENTS_OUTPUT = MIN_VALUE + STEP * 8;
const uint32_t POINT_90_PERCENTS_OUTPUT = MIN_VALUE + STEP * 9;
const uint32_t POINT_10_CALCULATED = POINT_10_PERCENTS * POINT_10_PERCENTS_OUTPUT / ONE_HUNDRED_PERCENTS;
const uint32_t POINT_20_CALCULATED = POINT_20_PERCENTS * POINT_20_PERCENTS_OUTPUT / ONE_HUNDRED_PERCENTS;
const uint32_t POINT_30_CALCULATED = POINT_30_PERCENTS * POINT_30_PERCENTS_OUTPUT / ONE_HUNDRED_PERCENTS;
const uint32_t POINT_40_CALCULATED = POINT_40_PERCENTS * POINT_40_PERCENTS_OUTPUT / ONE_HUNDRED_PERCENTS;
const uint32_t POINT_50_CALCULATED = POINT_50_PERCENTS * POINT_50_PERCENTS_OUTPUT / ONE_HUNDRED_PERCENTS;
const uint32_t POINT_60_CALCULATED = POINT_60_PERCENTS * POINT_60_PERCENTS_OUTPUT / ONE_HUNDRED_PERCENTS;
const uint32_t POINT_70_CALCULATED = POINT_70_PERCENTS * POINT_70_PERCENTS_OUTPUT / ONE_HUNDRED_PERCENTS;
const uint32_t POINT_80_CALCULATED = POINT_80_PERCENTS * POINT_80_PERCENTS_OUTPUT / ONE_HUNDRED_PERCENTS;
const uint32_t POINT_90_CALCULATED = POINT_90_PERCENTS * POINT_90_PERCENTS_OUTPUT / ONE_HUNDRED_PERCENTS;

// TODO COMMENT THIS IN analogWrite() arduino library METHOD!!!
//	else if (val == 255)
//	{
//		digitalWrite(pin, HIGH);
//	}

void setValue(uint16_t result) {
    if (result <= MIN_VALUE) {
        analogWrite(OUTPUT_PIN, MIN_VALUE);
        return;
    }
    if (result > MIN_VALUE && result < MAX_VALUE) {
        analogWrite(OUTPUT_PIN, result);
        return;
    }
    if (result >= MAX_VALUE) {
        analogWrite(OUTPUT_PIN, MAX_VALUE);
        return;
    }
}

void calculate() {
    uint16_t input = analogRead(INPUT_PIN);
    if (input <= MIN_VALUE) {
        setValue(MIN_VALUE);
        return;
    }
    if (input <= POINT_10_PERCENTS_OUTPUT) {
        uint16_t result = ((MIN_VALUE * (POINT_10_PERCENTS_OUTPUT - input)
                            + (POINT_10_CALCULATED * (input - MIN_VALUE))) / STEP);
        setValue(result);
        return;
    }
    if (input <= POINT_20_PERCENTS_OUTPUT) {
        uint16_t result = ((POINT_10_CALCULATED * (POINT_20_PERCENTS_OUTPUT - input)
                            + (POINT_20_CALCULATED * (input - POINT_10_PERCENTS_OUTPUT))) / STEP);
        setValue(result);
        return;
    }
    if (input <= POINT_30_PERCENTS_OUTPUT) {
        uint16_t result = ((POINT_20_CALCULATED * (POINT_30_PERCENTS_OUTPUT - input)
                            + (POINT_30_CALCULATED * (input - POINT_20_PERCENTS_OUTPUT))) / STEP);
        setValue(result);
        return;
    }
    if (input <= POINT_40_PERCENTS_OUTPUT) {
        uint16_t result = ((POINT_30_CALCULATED * (POINT_40_PERCENTS_OUTPUT - input)
                            + (POINT_40_CALCULATED * (input - POINT_30_PERCENTS_OUTPUT))) / STEP);
        setValue(result);
        return;
    }
    if (input <= POINT_50_PERCENTS_OUTPUT) {
        uint16_t result = ((POINT_40_CALCULATED * (POINT_50_PERCENTS_OUTPUT - input)
                            + (POINT_50_CALCULATED * (input - POINT_40_PERCENTS_OUTPUT))) / STEP);
        setValue(result);
        return;
    }
    if (input <= POINT_60_PERCENTS_OUTPUT) {
        uint16_t result = ((POINT_50_CALCULATED * (POINT_60_PERCENTS_OUTPUT - input)
                            + (POINT_60_CALCULATED * (input - POINT_50_PERCENTS_OUTPUT))) / STEP);
        setValue(result);
        return;
    }
    if (input <= POINT_70_PERCENTS_OUTPUT) {
        uint16_t result = ((POINT_60_CALCULATED * (POINT_70_PERCENTS_OUTPUT - input)
                            + (POINT_70_CALCULATED * (input - POINT_60_PERCENTS_OUTPUT))) / STEP);
        setValue(result);
        return;
    }
    if (input <= POINT_80_PERCENTS_OUTPUT) {
        uint16_t result = ((POINT_70_CALCULATED * (POINT_80_PERCENTS_OUTPUT - input)
                            + (POINT_80_CALCULATED * (input - POINT_70_PERCENTS_OUTPUT))) / STEP);
        setValue(result);
        return;
    }
    if (input <= POINT_90_PERCENTS_OUTPUT) {
        uint16_t result = ((POINT_80_CALCULATED * (POINT_90_PERCENTS_OUTPUT - input)
                            + (POINT_90_CALCULATED * (input - POINT_80_PERCENTS_OUTPUT))) / STEP);
        setValue(result);
        return;
    }
    if (input < MAX_VALUE) {
        uint16_t result = ((POINT_90_CALCULATED * (MAX_VALUE - input)
                            + (MAX_VALUE * (input - POINT_90_PERCENTS_OUTPUT))) / STEP);
        setValue(result);
        return;
    }
    if (input >= MAX_VALUE) {
        setValue(MAX_VALUE);
        return;
    }
}


void setup() {
    TCCR1A = 0b00000011; // 10bit for Arduino Nano
    TCCR1B = 0b00001001; // x1 fast pwm 15.6khz for Arduino Nano
    analogReference(DEFAULT);
    pinMode(INPUT_PIN, INPUT);
    pinMode(OUTPUT_PIN, OUTPUT);
    delay(1000);
}

void loop() {
    calculate();
}