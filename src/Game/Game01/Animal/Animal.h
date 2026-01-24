#pragma once
#include <System/Scene.h>

namespace Game01 {
USING_PTR(Animal);

class Animal : public Object
{
public:
    BP_OBJECT_DECL(Animal, u8"Game01 の Animal");

    bool  Init() override;
    float throw_time;
    void  Update() override;
    void  OnHit(const ComponentCollision::HitInfo& hit_info) override;
    void  SetDirectior(float3 dir);
    void  Throw();
    int   Cone_Mode;
    int   Size_Reward;
    enum
    {
        ON,
        OFF,
    };
    int Invisible_ = ON;
    int memory_num;
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
        Force,
        Impulse,
        VelocityChange,
        Acceleration,
    };
    enum
    {
        NOBODY,
        RISE,
        BETTY,
        ABIGAIL,
        SOL,
    };
    int    who_throwing = 0;
    int    who_holding  = NOBODY;
    float3 direction_;
    float  dir_xyz_ = 1.00f;
    float3 mode_direction_;

private:
    float speed_ = 1.0f;
};

}    // namespace Game01
