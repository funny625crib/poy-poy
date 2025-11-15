#pragma once
#include <System/Scene.h>

#include <System/Component/Component.h>

namespace Game01 {
USING_PTR(Acceleration);

class Acceleration : public Component
{
public:
    BP_COMPONENT_DECL(Acceleration, u8"Game01 の Acceleration");
    void Init() override;
    void Update() override;

private:
    float move_speed_    = 1.0f;     //移動速度
    float target_speed_  = 1.0f;     //目標速度
    float rot_speed_     = 20.0f;    //回転速度
    float current_speed_ = 0.0f;     //現在の速度
    float front_rot_     = 0.0f;     //オブジェクト オフセット回転
    float stall_time_    = 0.0f;     //加速時間
};
}    // namespace Game01
