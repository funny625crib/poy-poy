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

    //回復のアニメーションが再生しているかどうか
    bool IsHealing() const { return is_healing_; }
    //怪力のアニメーションが再生しているかどうか
    bool IsPower_up() const { return ispower_up_; }
    //威嚇のアニメーションが再生しているかどうか
    bool IsThreatening() const { return isthreatening_; }

private:
    bool is_healing_ = false;
    int  heal_frame_ = 0;

    bool ispower_up_     = false;
    int  power_up_frame_ = 0;

    bool isthreatening_     = false;
    int  threatening_frame_ = 0;
};

}    // namespace Game01
