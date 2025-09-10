#include <stdlib.h>
extern "C" {
 #include "openplc.h"
}
#include "Arduino.h"
#include "../examples/Baremetal/defines.h"
#include <Wire.h>
#include "config.h"
#include "tla2528.h"
#include "TLA2528_C.h"

TLA2528Class tla2528; // Create an instance of the TLA2528 driver (no parameters needed)

//#include "driver/ledc.h"

// OpenPLC HAL for ESP32 boards
// NOTE: PWM channel == pin number

// Create the I/O pin masks (defined within editor GUI when compiling for board)
uint8_t pinMask_DIN[] = {PINMASK_DIN};
uint8_t pinMask_AIN[] = {PINMASK_AIN};
uint8_t pinMask_DOUT[] = {PINMASK_DOUT};
uint8_t pinMask_AOUT[] = {PINMASK_AOUT};

#define PWM_ANALOG_FREQ       4000 // Frequency to use when emulating analog on boards without a DAC
#define PWM_RESOLUTION        12 // 12-bit should allow up to 10kHz
#define PWM_MAX               0xFFF // 12-bit max

bool IN1_isDigital = false; // Flags that define if IN1 should be treated as digital input
bool IN2_isDigital = false; // Flags that define if IN2 should be treated as digital input

//extern "C" uint8_t set_hardware_pwm(uint8_t, float, float); //this call is required for the C-based PWM block on the Editor

//bool pwm_initialized[64] = {false}; // Store which PWM channels have been initialised

void hardwareInit()
{
    for (int i = 0; i < NUM_DISCRETE_INPUT; i++)
    {
        pinMode(pinMask_DIN[i], INPUT);
    }

    for (int i = 0; i < NUM_ANALOG_INPUT; i++)
    {
        pinMode(pinMask_AIN[i], INPUT);
    }

    for (int i = 0; i < NUM_DISCRETE_OUTPUT; i++)
    {
        pinMode(pinMask_DOUT[i], OUTPUT);
    }

    for (int i = 0; i < NUM_ANALOG_OUTPUT; i++)
    {
        pinMode(pinMask_AOUT[i], OUTPUT);
//#if !SOC_DAC_SUPPORTED
//        ledcAttach(pinMask_AOUT[i], PWM_ANALOG_FREQ, PWM_RESOLUTION);
//#endif
    }

    tla2528.begin();

}

/*
uint8_t set_hardware_pwm(uint8_t ch, float freq, float duty)
{
    if (!pwm_initialized[ch])
    {
        if (!ledcAttach(ch, (uint32_t)freq, PWM_RESOLUTION))
        {
            return 0;
        }
        pwm_initialized[ch] = true;
    }

    ledcWrite(ch, (uint32_t)(duty / 100 * PWM_MAX));
    return ledcChangeFrequency(ch, (uint32_t)freq, PWM_RESOLUTION);
}
*/

void updateInputBuffers()
{
    for (int i = 0; i < NUM_DISCRETE_INPUT; i++)
    {
        if (bool_input[i/8][i%8] != NULL)
            *bool_input[i/8][i%8] = digitalRead(pinMask_DIN[i]);
    }

    for (int i = 0; i < NUM_ANALOG_INPUT; i++)
    {
        if (int_input[i] != NULL)
            *int_input[i] = (analogRead(pinMask_AIN[i]) * 64);
    }
    
    // -------------------------------------------------------------------
    // Dynamic mode selection using %MW0 (DigitalState variable in Editor)
    //
    // DigitalState values:
    //   0 → Both IN1 and IN2 are analog
    //   1 → IN1 digital, IN2 analog
    //   2 → IN1 analog, IN2 digital
    //   3 → Both IN1 and IN2 digital
    //
    // Bit0 of %MW0 controls IN1 mode
    // Bit1 of %MW0 controls IN2 mode
    // -------------------------------------------------------------------
    if (int_input[0] != NULL) // %MW0
    {
        int configWord = *int_input[0];
        IN1_isDigital = (configWord & 0x01); // test bit0
        IN2_isDigital = (configWord & 0x02); // test bit1
    }

    // -------------------- IN1 Handling ---------------------
    // %IW4 if analog, %IX0.4 if digital
    // AN1 mapped to %IW4  (int_input[4])
    // -------------------------------------------------------
    if (IN1_isDigital)
    {
        if (bool_input[0][4] != NULL) // Example: %IX0.4
            *bool_input[0][4] = tla2528.digitalReadIO(AN1);
    }
    else
    {
        if (int_input[4] != NULL)     // Example: %IW4
            *int_input[4] = 4095 - int(tla2528.analogReadIO(AN1));
    }

    // -------------------- IN2 Handling ---------------------
    // %IW5 if analog, %IX0.5 if digital
    // AN2 mapped to %IW5  (int_input[5])
    // -------------------------------------------------------
    if (IN2_isDigital)
    {
        if (bool_input[0][5] != NULL) // Example: %IX0.5
            *bool_input[0][5] = tla2528.digitalReadIO(AN2);
    }
    else
    {
        if (int_input[5] != NULL)     // Example: %IW5
            *int_input[5] = 4095 - int(tla2528.analogReadIO(AN2));
    }

}

void updateOutputBuffers()
{
    for (int i = 0; i < NUM_DISCRETE_OUTPUT; i++)
    {
        if (bool_output[i/8][i%8] != NULL)
            digitalWrite(pinMask_DOUT[i], *bool_output[i/8][i%8]);
    }

    for (int i = 0; i < NUM_ANALOG_OUTPUT; i++)
    {
        if (int_output[i] != NULL)
        {
            analogWrite(pinMask_AOUT[i], (*int_output[i] / 64));
#if SOC_DAC_SUPPORTED
            dacWrite(pinMask_AOUT[i], (*int_output[i] / 256));
//#else
//            ledcWrite(pinMask_AOUT[i], (*int_output[i] / 16));
#endif
        }
    }
    // -----------------------------------------
    // REL1 mapped to %QX1.1  (bool_output[1][1])
    // REL2 mapped to %QX1.2  (bool_output[1][2])
    // -----------------------------------------
    if (bool_output[1][1] != NULL)
        tla2528.digitalWriteIO(REL1, *bool_output[1][1]);

    if (bool_output[1][2] != NULL)
        tla2528.digitalWriteIO(REL2, *bool_output[1][2]);

}
