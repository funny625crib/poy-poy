#pragma once
#include <System/Scene.h>

namespace Game01 {
USING_PTR(Player_Rise);

class Player_Rise : public Object
{
public:
    BP_OBJECT_DECL(Player_Rise, u8"Game01 の Player Rise");

    bool Init() override;

    void Update() override;

    float3 pos_npc_;
    float3 dis;
    enum
    {
        IDLE,
        HOLDING,
        THROWING,
    };

    void OnHit(const ComponentCollision::HitInfo& hit_info) override;

    // ★ 外部用：现在是不是正在播治疗动画
    bool IsHealing() const { return is_healing_; }

private:
    bool is_healing_ = false;    // 是否处于治疗中
    int  heal_frame_ = 0;        // 治疗动画剩余帧数
};

}    // namespace Game01
