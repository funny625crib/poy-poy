#pragma once
#include <System/Scene.h>

namespace Game01 {
USING_PTR(Animal);

class Animal : public Object
{
public:
    BP_OBJECT_DECL(Animal, u8"Game01 の Animal");

    bool Init() override;

    void Update() override;

private:
    float move_speed_ = 0.5f;
    float rot_speed_  = 20.0f;

    float front_rot_ = 0.0f;    //!<前方ベクトルの回転角度(0-360度)
};

}    // namespace Game01
