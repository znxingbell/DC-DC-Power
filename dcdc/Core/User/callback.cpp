#include "main.h"
#include "controller.hpp"
#include "adc_manager.hpp"
#include "oled.hpp"
#include "tim.h"

extern "C" {
    void HAL_HRTIM_RepetitionEventCallback(HRTIM_HandleTypeDef *hhrtim, uint32_t TimerIdx) {
        if(TimerIdx == HRTIM_TIMERINDEX_MASTER && hhrtim->Instance == HRTIM1) {
            sampler.vhs = sampler.ADC_Decode(static_cast<uint8_t>(ADC_Channel::VHS));
            sampler.vls = sampler.ADC_Decode(static_cast<uint8_t>(ADC_Channel::VLS));
            sampler.is = sampler.ADC_Decode(static_cast<uint8_t>(ADC_Channel::IS));
            if(sampler.counter < sampler.ADC_OffsetSampleTime) {
                sampler.counter++;
                return;
            }
            controller.implement_control(sampler.vhs, sampler.vls, sampler.is);
        }
    }

    void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
        switch(GPIO_Pin) {
            case GPIO_PIN_5: // 模式切换按钮
            //controller.ToggleMode();由于硬件故障，禁用该功能
            break;
            case GPIO_PIN_6:
            controller.AddCureent();
            break;
            case GPIO_PIN_7:
            controller.MinusCurrent();
            break;
        }
    }

    void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
        if (htim == &htim2){
            OLED_ShowFloat(3, 3, sampler.vhs, 2);
            OLED_ShowFloat(3, 11, sampler.vls, 2);
            OLED_ShowFloat(4, 3, sampler.is, 2);
        }
    }
};