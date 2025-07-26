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

private:
};

}    // namespace Game01
