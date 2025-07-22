#include "main.h"
#include "hrtim_manager.hpp"
#include "adc_manager.hpp"
#include "controller.hpp"
#include "oled.hpp"
#include "tim.h"

/**
 * @brief      系统初始化函数
 * @param      NULL
 * @retval     NULL
 */
extern "C" void UserInit(){ 

    OLED_Init();
    sampler.ADC_Init();
    controller.controller_init();
    HRTIM_Init();
    HAL_TIM_Base_Start_IT(&htim2);
}

/**
 * @brief      系统主循环
 * @param      NULL
 * @retval     NULL
 */
extern "C" void UserLoop(){

}