#include "controller.hpp"

void Controller::controller_init() {
    // 初始化PID控制器
    PID_Config Ipid_config{1.0f, 0.1f, 0.01f, 100.0f, -100.0f, 50.0f, -50.0f};
    Ipid = new PID_TypeDef(Ipid_config);
    PID_Config Vpid_config{1.0f, 0.1f, 0.01f, 100.0f, -100.0f, 50.0f, -50.0f};
    Vpid = new PID_TypeDef(Vpid_config);
}
