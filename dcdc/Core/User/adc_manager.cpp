#include "adc_manager.hpp"
#include "adc.h"
#include "hrtim.h"

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

uint16_t test_point;

float32_t SamplerTypeDef::ADC_Decode(uint8_t offset) {
    float32_t output;
    uint16_t temp{0};
    for(uint8_t i = 0; i < 8; i++) {
        temp += buffer[offset + i * 3];
    }
    switch(offset) {
        case 0:
            output = static_cast<float32_t>(temp) * adc_ratio * 1.653f;
            return output; // VHS
            break;
        case 1:
            output = static_cast<float32_t>(temp) * adc_ratio * 1.649f;
            return output; // VLS
            break;
        case 2:
            if(sampler.counter < ADC_OffsetSampleTime) {
                sampler.current_offset += static_cast<float32_t>(temp);
                if(sampler.counter == ADC_OffsetSampleTime - 1) {
                    sampler.current_offset /= ADC_OffsetSampleTime;
                    HAL_HRTIM_WaveformOutputStart(&hhrtim1, HRTIM_OUTPUT_TA1 | HRTIM_OUTPUT_TA2);
                }
            }
            test_point = temp;
            output = (static_cast<float32_t>(temp)- sampler.current_offset) * adc_ratio * 1.25f;
            return output * (1.0f - filter_rate) + is * filter_rate; // IS
            break;
    }

}

SamplerTypeDef sampler;
