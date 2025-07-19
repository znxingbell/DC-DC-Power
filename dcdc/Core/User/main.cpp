#include "main.h"
#include "hrtim_manager.hpp"
#include "adc_manager.hpp"

/**
 * @brief      系统初始化函数
 * @param      NULL
 * @retval     NULL
 */

extern "C" void UserInit(){ 
    sampler.ADC_Init();
    HRTIM_Init();
}

/**
 * @brief      系统主循环
 * @param      NULL
 * @retval     NULL
 */
extern "C" void UserLoop(){

}