#pragma once
#include <System/Scene.h>

#include <System/Component/Component.h>

namespace Game01 {
USING_PTR(Acceleration);

class Acceleration : public Component
{
public:
    BP_COMPONENT_DECL(Acceleration, u8"Game01 の Acceleration");

    void Init() override;

    void Update() override;

private:
};

}    // namespace Game01
