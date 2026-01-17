#pragma once
#include <System/Scene.h>

namespace Game01 {
USING_PTR(Arrow_Betty);

class Arrow_Betty : public Object
{
public:
    BP_OBJECT_DECL(Arrow_Betty, u8"Game01 の Arrow_Betty");

    bool Init() override;

    void Update() override;

    void Draw() override;

    float3 arrow_pos;

private:
    float3 name_pos;
};

}    // namespace Game01
