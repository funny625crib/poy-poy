#pragma once
#include <System/Scene.h>

namespace Game01 {
USING_PTR(Time_bomb);

class Time_bomb : public Object
{
public:
    BP_OBJECT_DECL(Time_bomb, u8"Game01 の Time_bomb");

    bool Init() override;

    void Update() override;
    void OnHit(const ComponentCollision::HitInfo& hit_info) override;
    void SetDirectior(float3 dir);
    void Throw();
    int  Boms_Mode;
    bool first_thorw = false;
    enum
    {
        IDLE,
        HOLDING,
        THROWING,
        DEATH,
        NOTHING,
    };
    enum
    {
        NOBODY,
        RISE,
        BETTY,
        ABIGAIL,
        SOL,
    };
    int who_throwing = 0;

private:
    float3 direction_;
};

}    // namespace Game01
