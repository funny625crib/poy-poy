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

private:
};

}    // namespace Game01
