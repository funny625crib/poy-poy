#pragma once
#include <System/Scene.h>

#include <System/Component/Component.h>

namespace Game01 {
USING_PTR(Pickup);

class Pickup : public Component
{
public:
    BP_COMPONENT_DECL(Pickup, u8"Game01 の Pickup");

    void Init() override;
    enum
    {
        NOOBJ,
        ANIMAL,
        BOMS,
    };
    void   Update() override;
    void   Draw() override;
    bool   check    = false;
    int    set_obj_ = NOOBJ;
    float3 dir{0, 0, 0};

    float3 pos_npc_;

    float3 pos_XZ;
    float  r     = 35.0f;
    int    color = GetColor(255, 255, 255);

    bool Check_Pickup();

private:
};

}    // namespace Game01
