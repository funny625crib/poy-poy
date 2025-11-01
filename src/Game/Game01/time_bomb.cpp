#include "time_bomb.h"
#include "Animal.h"
#include <DxLib.h>
#include <System/Component/ComponentModel.h>
#include <System/Component/ComponentCollisionModel.h>
#include <System/Component/ComponentCollisionCapsule.h>
#include <System/Component/ComponentObjectController.h>
#include <System/Component/ComponentCollisionSphere.h>
#include <Game/Component/ComponentGameCamera.h>
#include <Game/Game01/Skills/Acceleration.h>

namespace Game01 {

bool Time_bomb::Init()
{
    Super::Init();

    // プレイヤー
    SetName("Time bomb");
    SetTranslate({-87.0f, -6.0f, 47.0f});
    AddComponent<Acceleration>();
    auto col = AddComponent<ComponentCollisionCapsule>();    //
    col->SetRadius(5.53f);
    col->SetHeight(5.81f);
    col->UseGravity();
    col->SetCollisionGroup(ComponentCollision::CollisionGroup::ITEM);

    auto model      = AddComponent<ComponentModel>("data/Sample/time bomb/Bomb.mv1");
    model->Matrix() = matrix::scale(0.05f);

    //model->UseShader(false);

    //AddComponent<ComponentGameCamera>();

    return true;
}

void Time_bomb::Update()
{
    Super::Update();
}
}    // namespace Game01
