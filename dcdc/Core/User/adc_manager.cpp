#include "adc_manager.hpp"
#include "adc.h"

void SamplerTypeDef::ADC_ReferenceGet() {
    uint32_t total_adc = 0;
    HAL_ADCEx_Calibration_Start(&hadc2, ADC_SINGLE_ENDED);
    HAL_ADC_Start(&hadc2); 
    for(uint8_t i = 0; i < ADC_ReferenceSampleTime; i++) {
        HAL_ADC_PollForConversion(&hadc2, 50);
        total_adc += HAL_ADC_GetValue(&hadc2);
    }
    HAL_ADC_Stop(&hadc2);
    uint32_t vrefint_data = total_adc / ADC_ReferenceSampleTime;
    adc_ratio = (ADC_VREF * vrefint_cal) / (vrefint_data * FULL_SCALE);
}

void SamplerTypeDef::ADC_Init() {
    ADC_ReferenceGet();
    HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
    HAL_ADC_Start_DMA(&hadc1, reinterpret_cast<uint32_t*>(buffer), BUFFER_SIZE);
}

float32_t SamplerTypeDef::ADC_Decode(uint8_t offset) {
    uint16_t temp{0};
    for(uint8_t i = 0; i < 8; i++) {
        temp += buffer[offset + i * 3];
    }
    return static_cast<float32_t>(temp) / 8 * adc_ratio;
}

SamplerTypeDef sampler;
