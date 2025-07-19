#pragma once
#include "main.h"
using float32_t = float;

class SamplerTypeDef {
public:
    static constexpr uint8_t ADC_ReferenceSampleTime{20};
    static constexpr uint16_t FULL_SCALE{4095};
    static constexpr float32_t ADC_VREF{3.3f};
    static constexpr uint8_t BUFFER_SIZE{24};

    void ADC_ReferenceGet();
    void ADC_Init();
    float32_t ADC_Decode(uint8_t offset);

private:
    uint16_t buffer[BUFFER_SIZE]{};
    float32_t adc_ratio{0.0f};
    uint16_t vrefint_cal{*(__IO uint16_t *)(0x1FFFF7BA)};
    
};

extern SamplerTypeDef sampler;
