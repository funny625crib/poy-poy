#include "Acceleration.h"
#include <Game/Component/State/StateRun.h>
#include <Game/Component/State/StateIdleWalk.h>
#include <System/Component/ComponentModel.h>
#include <System/Component/ComponentCollisionSphere.h>
#include <Game/Game01/Animal.h>
#include <DxLib.h>

namespace Game01 {
void Acceleration::Init()
{
    __super::Init();
    auto owner = GetOwner();
    // auto col   = owner->AddComponent<ComponentCollisionSphere>();
    // col->AttachToModel("mixamorig:LeftLeg");
    //  col->SetName("PlayerRun");

    //left_collision_ = col;

    if(auto model = owner->GetComponent<ComponentModel>()) {
        model->PlayAnimation("run");
    }
    // カメラオブジェクト
    //auto camera = Scene::Object::Create<Object>();
}

void Acceleration::Update()
{
    __super::Update();
    auto owner = GetOwner();
}
}    // namespace Game01
