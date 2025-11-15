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
    void Update() override;
    void Draw() override;
    bool check    = false;
    int  set_obj_ = NOOBJ;

    bool Check_Pickup();

private:
};

}    // namespace Game01
