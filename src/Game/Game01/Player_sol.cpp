#include "Player_sol.h"

#include <DxLib.h>
#include <System/Component/ComponentModel.h>
#include <System/Component/ComponentCollisionModel.h>
#include <System/Component/ComponentCollisionCapsule.h>
#include <System/Component/ComponentObjectController.h>

#include <Game/Component/ComponentGameCamera.h>
#include <Game/Component/State/StateIdleWalk.h>
#include <Game/Component/State/StateJump.h>

namespace Game01 {
bool Player_Sol::Init()
{
    Super::Init();

    // プレイヤー
    SetName("Player Sol");
    SetTranslate({-90.0f, 5.0f, -50.0f});
    SetRotationAxisXYZ({0.0f, 180.0f, 0.0f});

    auto col = AddComponent<ComponentCollisionCapsule>();    //
    col->SetRadius(4.53f);
    col->SetHeight(16.81f);
    col->UseGravity();
    col->SetCollisionGroup(ComponentCollision::CollisionGroup::PLAYER);

    auto model      = AddComponent<ComponentModel>("data/Sample/Player/sol/sol.mv1");
    model->Matrix() = matrix::scale(0.8f);
    model->SetAnimation({
        {"idle",    "data/Sample/Player/sol/Anim/Idle.mv1", 0, 1.0f},
        {"walk", "data/Sample/Player/sol/Anim/Walking.mv1", 0, 1.0f},
        {"jump",    "data/Sample/Player/sol/Anim/Jump.mv1", 0, 1.0f},
        { "run",     "data/Sample/Player/sol/Anim/Run.mv1", 0, 1.0f},
    });
    //model->SetScaleAxisXYZ( { 1, 1, 1 } );
    model->PlayAnimation("idle", true);

    AddComponent<ComponentGameCamera>();

    return true;
}

void Player_Sol::Update()
{
    Super::Update();

    // ジャンプしていて、アニメーションが一定数値以上ならば、慣性の法則にしたがって上に移動させる
}
}    // namespace Game01
