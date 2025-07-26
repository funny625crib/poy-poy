#pragma once
#include <System/Scene.h>
#include <System/Component/ComponentCamera.h>
#include <System/Component/ComponentModel.h>
#include <System/Component/ComponentObjectController.h>
#include <System/Component/ComponentCollisionModel.h>
#include <System/Component/ComponentCollisionCapsule.h>

namespace Game01 {

class Game01 : public Scene::Base
{
public:
    BP_CLASS_DECL(Game01, u8"Game02::Game01のシーン!!!");

    bool Init() override;

    void Update() override;

private:
};

}    // namespace Game01
