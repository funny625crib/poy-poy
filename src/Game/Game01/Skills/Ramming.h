#pragma once
#include <System/Scene.h>

#include <System/Component/Component.h>

namespace Game01 {
USING_PTR(Ramming);

class Ramming : public Component
{
public:
    BP_COMPONENT_DECL(Ramming, u8"Game01 の Ramming");
    ComponentWeakPtr left_collision_;
    void             Init() override;

    void Update() override;

private:
    float move_speed_ = 5.0f;
    float rot_speed_  = 20.0f;

    float front_rot_ = 0.0f;
};

}    // namespace Game01
