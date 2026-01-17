#pragma once
#include <System/Scene.h>

namespace Game01 {
USING_PTR(Arrow_Abigail);

class Arrow_Abigail : public Object
{
public:
    BP_OBJECT_DECL(Arrow_Abigail, u8"Game01 の Arrow_Abigail");

    bool Init() override;

    void Update() override;

    void Draw() override;

    float3 arrow_pos;

private:
    float3 name_pos;
};

}    // namespace Game01
