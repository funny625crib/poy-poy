#include "Animal.h"
#include <DxLib.h>
#include <Game/Component/State/StatePhysics.h>
#include <System/Component/ComponentModel.h>
#include <System/Component/ComponentCollisionModel.h>
#include <System/Component/ComponentCollisionCapsule.h>
#include <System/Component/ComponentObjectController.h>
#include <Game/Component/ComponentGameCamera.h>
#include <Game/Component/State/AnimalStateIdleWalk.h>

const char* Animal_name[] = {
    "data/Sample/Animal/Pig.mv1",
    "data/Sample/Animal/lion.mv1",
    "data/Sample/Animal/Bear.mv1",
    "data/Sample/Animal/Sheep.mv1",
    "data/Sample/Animal/Duck.mv1",
    "data/Sample/Animal/Antelope.mv1",
    "data/Sample/Animal/Buffalo.mv1",
    "data/Sample/Animal/Chick.mv1",
    "data/Sample/Animal/Koala.mv1",
    "data/Sample/Animal/Turkey.mv1",
};

namespace Game01 {
bool Animal::Init()
{
    Super::Init();

    //動物の初期座標
    float pos_x = GetRand(170.0f) - 140.0f;
    float pos_z = GetRand(200.0f) - 100.0f;

    // 動物
    SetName("Animal");
    SetTranslate({pos_x, 5.0f, pos_z});
    SetRotationAxisXYZ({0.0f, 180.0f, 0.0f});

    int         num = GetRand(9);
    const char* str = Animal_name[num];

    //当たり判定の円の大きさ
    float radius = 0;
    float height = 0;

    //動物に対して大きさ
    float size = 0.0f;
    switch(num) {
    case 0:    //Pig
        size   = 0.15f;
        radius = 5.0f;
        height = 11.0f;
        break;
    case 1:    //Lion
        size   = 0.08f;
        radius = 6.0f;
        height = 15.0f;
        break;
    case 2:    //Bear
        size   = 0.07f;
        radius = 7.0f;
        height = 17.0f;
        break;
    case 3:    //Sheep
        size   = 0.15f;
        radius = 6.0f;
        height = 11.0f;
        break;
    case 4:    //Duck
        size   = 0.15f;
        radius = 6.0f;
        height = 11.0f;
        break;
    case 5:    //Antelope
        size   = 0.07f;
        radius = 7.0f;
        height = 17.0f;
        break;
    case 6:    //Buffalo
        size   = 0.15f;
        radius = 7.0f;
        height = 12.0f;
        break;
    case 7:    //Chick
        size   = 0.15f;
        radius = 6.0f;
        height = 11.0f;
        break;
    case 8:    //Koala
        size   = 0.07f;
        radius = 6.0f;
        height = 11.0f;
        break;
    case 9:    //Turkey
        size   = 0.07f;
        radius = 6.0f;
        height = 11.0f;
        break;
    }

    auto col = AddComponent<ComponentCollisionCapsule>();
    col->SetRadius(radius);
    col->SetHeight(height);
    col->UseGravity();

    auto model      = AddComponent<ComponentModel>(str);
    model->Matrix() = matrix::scale(size);
    model->SetAnimation({
        {"idle", Animal_name[num],  8, 1.0f},
        {"walk", Animal_name[num], 17, 1.0f},
    });

    model->PlayAnimation("idle", true);
    AddComponent<StatePhysics>();
    AddComponent<ComponentGameCamera>();

    //auto state = AddComponent<AnimalStateIdleWalk>();
    // state->SetMoveSpeed(0.3f)->SetRotateSpeed(20.0f);

    return true;
}

void Animal::Update()
{
    Super::Update();
    //float V0     = 0.5f;    //初速度
    //direction_.y = -0.5f * 0.25f * throw_time * throw_time + V0 * throw_time * 1.1;

    auto col = GetComponent<ComponentCollisionCapsule>();
    // col->UseGravity(true);
    bool T_OR_F  = true;
    throw_time  += 0.4f;
    if(Cone_Mode == HOLDING) {
        T_OR_F     = false;
        throw_time = 0.0f;
        // col->RemoveThisComponent();
    }
    else if(Cone_Mode == THROWING) {
        T_OR_F = false;
    }
    else {
        throw_time = 0.0f;
    }
    if(col)
        col->UseGravity(T_OR_F);

    /* direction_.x *= 1.08f;
    direction_.z *= 1.08f;*/
    AddTranslate(direction_ * 1.0f);
    // ジャンプしていて、アニメーションが一定数値以上ならば、慣性の法則にしたがって上に移動させる
}
void Animal::OnHit(const ComponentCollision::HitInfo& hit_info)
{
    AnimalPtr Get_obj        = nullptr;
    auto      hit_owner_name = hit_info.hit_collision_->GetOwner()->GetNameDefault();
    auto      col            = GetComponent<ComponentCollisionCapsule>();

    if(hit_owner_name == "Ground") {
        direction_ = 0;
        //地面に当たっているobjをIDLE状態にする
        Cone_Mode = IDLE;
    }
    __super::OnHit(hit_info);
}
void Animal::SetDirectior(float3 dir)
{
    direction_ = dir;
}
void Animal::SetDirectior2(float3 dir)
{
}
void Animal::SetMoveDirectior(float3 dir)
{
    mode_direction_ = dir;
    AddTranslate(mode_direction_);
}
}    // namespace Game01
