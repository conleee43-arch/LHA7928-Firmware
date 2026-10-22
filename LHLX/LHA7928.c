
#include "LHA7928.h"
#include "spi.h"


/**
 * @brief ADC initiate
 */
void lha7928_Init(void)
{    
    // Config: Continous, AIN0-AIN1, PGA 2.048V, 100SPS
    uint16_t config = CFG_MUX_DIFF_0_1  |
                      CFG_PGA_2_048V    |
                      CFG_DR_100SPS     |
                      CFG_MODE_CONTUS   |
	                    CFG_ADC_MODE      |
                      CFG_PULLUP_EN     |
	                    CFG_NOP;
    
    lha7928_WriteConfig(config);
}

/**
 * @brief Write ADC config register
 * @param value: 16 bit reg value
 */
uint16_t lha7928_WriteConfig(uint16_t config)
{
    uint8_t tx_buf[6] = {0};
    uint8_t rx_buf[6] = {0};
    
		tx_buf[0] = 0x0;
    tx_buf[1] = (config >> 8) & 0xFF;
    tx_buf[2] = config & 0xFF;
    
    CSN_LOW;
    HAL_SPI_TransmitReceive(&hspi1, tx_buf, rx_buf, 6, HAL_MAX_DELAY);
    CSN_HIGH;
    
    return ((uint16_t)rx_buf[4] << 8) | rx_buf[5];
}

/**
 * @brief Read ADC conversion data
 * @retval 24 bit ADC data
 */
uint32_t lha7928_ReadData(void)
{
    uint8_t tx_buf[3] = {0};
    uint8_t rx_buf[3] = {0};
		uint32_t adc_data = 0;
    
    CSN_LOW;
    HAL_SPI_TransmitReceive(&hspi1, tx_buf, rx_buf, 3, HAL_MAX_DELAY);
    CSN_HIGH;
		
		adc_data = rx_buf[0] << 16 | rx_buf[1] << 8 | rx_buf[2];
    
    return adc_data;
}

/**
 * @brief Translate ADC code to volt
 * @param adc_value: ADC code
 * @param pga_config: PGA config
 * @retval volt: mV
 */
float lha7928_Code2Volt_mV(uint32_t adc_value, uint16_t pga_config) {
    float fullScaleRange = 0.0f;
		float volt = 0.0f;
	
		/* sign extend data */
   if (adc_value & 0x800000)
      adc_value |= 0xff000000;

    switch (pga_config & 0x0E00) { // Bits 11:9
        case CFG_PGA_6_144V: fullScaleRange = 6144.0f; break;
        case CFG_PGA_4_096V: fullScaleRange = 4096.0f; break;
        case CFG_PGA_2_048V: fullScaleRange = 2048.0f; break;
        case CFG_PGA_1_024V: fullScaleRange = 1024.0f; break;
        case CFG_PGA_0_512V: fullScaleRange =  512.0f; break;
        case CFG_PGA_0_256V: fullScaleRange =  256.0f; break;
        default:             fullScaleRange = 2048.0f; break;
    }

    volt = ((float)(int32_t)adc_value / 8388608.0f) * fullScaleRange;
		
		return volt;
}

/**
 * @brief Temp Sensor initiate
 */
void lha7928_TS_Init(void)
{    
    // Config: Continous, AIN0-AIN1, PGA 2.048V, 100SPS
    uint16_t config = CFG_DR_100SPS     |
                      CFG_MODE_CONTUS   |
	                    CFG_TS_MODE       |
                      CFG_PULLUP_EN     |
	                    CFG_NOP;
    
    lha7928_WriteConfig(config);
}

/**
 * @brief Read temperature sensor data
 * @retval 16 bit TS data
 */
uint16_t TS_ReadData(void)
{
    uint8_t tx_buf[2] = {0};
    uint8_t rx_buf[2] = {0};
		uint16_t ts_data = 0;
    
    CSN_LOW;
    HAL_SPI_TransmitReceive(&hspi1, tx_buf, rx_buf, 2, HAL_MAX_DELAY);
    CSN_HIGH;
		
		ts_data = rx_buf[0] << 8 | rx_buf[1];
    
    return ts_data;
}

/**
 * @brief Translate temperature sensor code to temperature
 * @param ts_value: TS code
 * @retval Temperature: C
 */
float TS_Code2Temp_C(uint16_t ts_value) {
    float fullScaleRange = 0.0f;
		float temp = 0.0f;

    temp = ((float)(int16_t)ts_value) * 0.0078125f;
		
		return temp;
}
