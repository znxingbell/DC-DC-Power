#include "hrtim_manager.hpp"
#include "hrtim.h"

void HRTIM_Init() {
    HAL_HRTIM_WaveformCounterStart(&hhrtim1, HRTIM_TIMERID_MASTER);
    HAL_HRTIM_WaveformCounterStart(&hhrtim1, HRTIM_TIMERID_TIMER_A); 
    HAL_HRTIM_WaveformOutputStart(&hhrtim1, HRTIM_OUTPUT_TA1 | HRTIM_OUTPUT_TA2); 
    __HAL_HRTIM_MASTER_ENABLE_IT(&hhrtim1, HRTIM_MASTER_IT_MREP);
}

void SetCmp(){
    hhrtim1.Instance->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_A].CMP1xR = 11504;//通过修改比较值CMP，从而修改占空比
}