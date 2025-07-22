#pragma once
#include "main.h"
using float32_t = float;

enum class ADC_Channel : uint8_t {
    VHS = 0,
    VLS = 1,
    IS = 2
};
class SamplerTypeDef {
public:
    static constexpr uint8_t ADC_ReferenceSampleTime{40};
    static constexpr uint8_t ADC_OffsetSampleTime{5};
    static constexpr uint16_t FULL_SCALE{4095};
    static constexpr float32_t ADC_VREF{3.3f};
    static constexpr uint8_t BUFFER_SIZE{24};
    static constexpr float32_t filter_rate{0.66f};
    uint8_t counter{0};
    float32_t vhs{0.0f};
    float32_t vls{0.0f};
    float32_t is{0.0f};


    void ADC_ReferenceGet();
    void ADC_Init();
    float32_t ADC_Decode(uint8_t offset);

private:
    float32_t current_offset{0.0f};
    uint16_t buffer[BUFFER_SIZE]{};
    float32_t adc_ratio{0.0f};
    uint16_t vrefint_cal{*(__IO uint16_t *)(0x1FFFF7BA)};

    
};

extern SamplerTypeDef sampler;
