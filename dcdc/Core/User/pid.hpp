#pragma once
#include "main.h"
using float32_t = float;

struct PID_Config {
    float32_t kp;          // 比例系数
    float32_t ki;          // 积分系数
    float32_t kd;          // 微分系数
    float32_t max_out;     // 最大输出
    float32_t min_out;     // 最小输出
    float32_t ki_max_out;  // 积分最大输出
    float32_t ki_min_out;  // 积分最小输出
};

//位置式pid
class PID_TypeDef {
public:
    /**
     * @brief      构造函数
     * @param      config PID配置
     */ 
    explicit PID_TypeDef(const PID_Config& config);
    /**
     * @brief      计算PID输出
     * @param      set 目标值
     * @param      ref 当前值
     * @retval     返回PID计算后的输出值
     */
    float32_t PID_Calculate(float32_t set, float32_t ref);

private:
    PID_Config config;
    float32_t int_error;  // 积分误差
    float32_t pre_error;// 上一次误差

    /**
     * @brief      限制输出值
     * @param      value 需要限制的值
     * @param      min_val 最小值
     * @param      max_val 最大值
     * @retval     返回限制后的值
     */
    inline float32_t clamp(float32_t value, float32_t min_val, float32_t max_val) {
        if (value > max_val) return max_val;
        if (value < min_val) return min_val;
    return value;
}

    
};