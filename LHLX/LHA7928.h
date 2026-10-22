
#ifndef LHA7928_H
#define LHA7928_H

#include "main.h"

// Configuration register bit definitions
// Single-shot conversion start
#define CFG_OS_SINGLE     (1 << 15)   // Single-shot conversion start

// MUX input channel selection
#define CFG_MUX_DIFF_0_1  (0 << 12)   // AIN0 - AIN1
#define CFG_MUX_DIFF_0_3  (1 << 12)   // AIN0 - AIN3
#define CFG_MUX_DIFF_1_3  (2 << 12)   // AIN1 - AIN3
#define CFG_MUX_DIFF_2_3  (3 << 12)   // AIN2 - AIN3
#define CFG_MUX_SINGLE_0  (4 << 12)   // AIN0 - GND
#define CFG_MUX_SINGLE_1  (5 << 12)   // AIN1 - GND
#define CFG_MUX_SINGLE_2  (6 << 12)   // AIN2 - GND
#define CFG_MUX_SINGLE_3  (7 << 12)   // AIN3 - GND

// PGA gain settings
#define CFG_PGA_6_144V    (0 << 9)    // 6.144V
#define CFG_PGA_4_096V    (1 << 9)    // 4.096V
#define CFG_PGA_2_048V    (2 << 9)    // 2.048V
#define CFG_PGA_1_024V    (3 << 9)    // 1.024V
#define CFG_PGA_0_512V    (4 << 9)    // 0.512V
#define CFG_PGA_0_256V    (5 << 9)    // 0.256V

// Device operating mode
#define CFG_MODE_CONTUS   (0 << 8)    // Continuous-conversion mode
#define CFG_MODE_SINGLE   (1 << 8)    // Single-shot mode or power-down state (default)

// Data rate
#define CFG_DR_5SPS       (0 << 5)
#define CFG_DR_10SPS      (1 << 5)
#define CFG_DR_20SPS      (2 << 5)
#define CFG_DR_50SPS      (3 << 5)
#define CFG_DR_100SPS     (4 << 5)
#define CFG_DR_250SPS     (5 << 5)
#define CFG_DR_500SPS     (6 << 5)
#define CFG_DR_1000SPS    (7 << 5)

// Temperature sensor mode
#define CFG_TS_MODE       (1 << 4)    // Temperature sensor mode
#define CFG_ADC_MODE      (0 << 4)    // ADC mode

// DOUT push-pull / open-drain
#define CFG_PULLUP_EN     (1 << 3)    // Internal pull-up enabled
#define CFG_PULLUP_DIS    (0 << 3)

// No-op (reserved bit) - MUST be set to 1 for successful config write
#define CFG_NOP           (1 << 1)   // Critical: set this bit to 1

// Function prototypes
void lha7928_Init(void);
uint16_t lha7928_WriteConfig(uint16_t config);
uint32_t lha7928_ReadData(void);
int16_t lha7928_ReadTemperature(void);
float lha7928_Code2Volt_mV(uint32_t adc_value, uint16_t pga_config);
void lha7928_TS_Init(void);
uint16_t TS_ReadData(void);
float TS_Code2Temp_C(uint16_t ts_value);

#endif
