#include "controller.hpp"
#include "oled.hpp"
#include "hrtim_manager.hpp"

void Controller::controller_init() {
    // 初始化PID控制器
    PID_Config Ipid_config{0.01f, 0.004f, 0.0f, 0.9f, 0.10f, 1e3f, -1e3f};
    Ipid = new PID_TypeDef(Ipid_config);
    PID_Config Vpid_config{0.02f, 0.002f, 0.0f, 3.0f, -3.0f, 1e3f, -1e3f};
    Vpid = new PID_TypeDef(Vpid_config);
    // 初始化控制模式
    mode = ControllerMode::CURRENT;
    OLED_ShowString(1, 1, "Mode: Current");
    OLED_ShowString(2, 1, "SetI:+1.0A");
    OLED_ShowString(3, 1, "vi");
    OLED_ShowString(3, 9, "vo");
    OLED_ShowString(4, 1, "ih");
    // 初始化设定点
    current_setpoint = 1.0f;  // 初始电流设定点
    voltage_setpoint = 30.0f; // 初始电压设定点
}

void Controller::implement_control(float32_t vhs, float32_t vls, float32_t is) {
    
    // 根据当前控制模式进行控制
     
    // 电压控制逻辑(50分频)
    if (mode == ControllerMode::VOLTAGE && counter%50 == 0) {
        current_setpoint = -Vpid->PID_Calculate(voltage_setpoint, vhs);
    }

    // 电流控制逻辑      
    duty_ratio = Ipid->PID_Calculate(current_setpoint, is);
    SetCompareValue(HALF_TOTAL_COUNTER * (1 - duty_ratio), HALF_TOTAL_COUNTER * (1 + duty_ratio));
    

    counter++;

}

void Controller::ToggleMode() {
    //if (mode == ControllerMode::CURRENT) {
        mode = ControllerMode::VOLTAGE;
        OLED_ShowString(1, 7, "Voltage");
        OLED_ShowFloat(2, 7, voltage_setpoint, 2);
        OLED_ShowChar(2, 4, 'V');

    //} else {
    //     mode = ControllerMode::CURRENT;
    //     current_setpoint = 0.5f;
    //     OLED_ShowString(1, 7, "Current");
    //     OLED_ShowFloat(2, 7, current_setpoint, 1);
    //     OLED_ShowChar(2, 4, 'I');

    // }
}

void Controller::AddCureent(){
    current_setpoint += 0.1f;
    OLED_ShowFloat(2, 6, current_setpoint, 1);
}

void Controller::MinusCurrent(){
    current_setpoint -= 0.1f;
    OLED_ShowFloat(2, 6, current_setpoint, 1);
}



Controller controller;

