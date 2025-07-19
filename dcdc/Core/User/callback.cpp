#include "main.h"

extern "C" {
    void HAL_HRTIM_RepetitionEventCallback(HRTIM_HandleTypeDef *hhrtim, uint32_t TimerIdx) {
        if(TimerIdx == HRTIM_TIMERINDEX_MASTER) {
            // 用户自定义代码
        }
    }
};