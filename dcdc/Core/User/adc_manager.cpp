#include "adc_manager.hpp"
#include "adc.h"

void ADC_ReferenceGet(ADC_ChannelConfTypeDef& sConfig) {
    //uint32_t total_adc = 0;
    HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
    sConfig.Channel = ADC_CHANNEL_VREFINT; 
    sConfig.Rank = ADC_REGULAR_RANK_4;
    sConfig.SamplingTime = ADC_SAMPLETIME_19CYCLES_5;
    sConfig.SingleDiff = ADC_SINGLE_ENDED;

}