#pragma once
#include <System/Scene.h>

namespace Game01 {
USING_PTR(Arrow);

class Arrow : public Object
{
public:
    BP_OBJECT_DECL(Arrow, u8"Game01 の Arrow");

    bool Init() override;

    void   Update() override;
    float3 arrow_pos;

private:
};

}    // namespace Game01
