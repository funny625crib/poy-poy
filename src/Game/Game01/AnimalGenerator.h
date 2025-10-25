#pragma once
#include <System/Scene.h>

namespace Game01 {
USING_PTR(Generator);

class Generator : public Object
{
public:
    BP_OBJECT_DECL(Generator, u8"Game01 の Generator");

    bool Init() override;
    void Update() override;

private:
    float generation_time_ = 0.0f;
    float speed_           = 1.0f;
};

}    // namespace Game01
