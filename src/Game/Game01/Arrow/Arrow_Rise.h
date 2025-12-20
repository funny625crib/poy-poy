#pragma once
#include <System/Scene.h>

namespace Game01 {
USING_PTR(Arrow_Rise);

class Arrow_Rise : public Object
{
public:
    BP_OBJECT_DECL(Arrow_Rise, u8"Game01 の Arrow_Rise");

    bool Init() override;

    void Update() override;

    void   Draw() override;
    float3 arrow_pos;

private:
    float3 name_pos;
};

}    // namespace Game01
