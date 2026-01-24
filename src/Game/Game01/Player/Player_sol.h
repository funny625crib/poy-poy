#pragma once
#include <System/Scene.h>

namespace Game01 {
USING_PTR(Player_Sol);

class Player_Sol : public Object
{
public:
    BP_OBJECT_DECL(Player_Sol, u8"Game01 の Player Sol");

    bool Init() override;

    void Update() override;
    bool up_obj = false;
    //int    _isholding = 0;
    float3 pos_npc_;
    float3 dis;
    enum
    {
        IDLE,
        HOLDING,
        THROWING,
    };
    enum
    {
        NOBODY,
        RISE,
        BETTY,
        ABIGAIL,
        SOL,
    };
    void OnHit(const ComponentCollision::HitInfo& hit_info) override;

private:
};

}    // namespace Game01
