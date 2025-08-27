#include "Animal.h"
#include <DxLib.h>
#include <System/Component/ComponentModel.h>
#include <System/Component/ComponentCollisionModel.h>
#include <System/Component/ComponentCollisionCapsule.h>
#include <System/Component/ComponentObjectController.h>
#include <Game/Component/ComponentGameCamera.h>
#include <Game/Component/State/StateIdleWalk.h>
#include <Game/Component/State/StateJump.h>

const char* Animal_name[] = {
    "data/Sample/Animal/Pig.mv1",
    "data/Sample/Animal/lion.mv1",
    "data/Sample/Animal/Bear.mv1",
    "data/Sample/Animal/Sheep.mv1",
    "data/Sample/Animal/Duck.mv1",
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
    SetTranslate({pos_x, 10.0f, pos_z});
    SetRotationAxisXYZ({0.0f, 180.0f, 0.0f});

    int         num = GetRand(4);
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
        radius = 5.0f;
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
    }

    auto col = AddComponent<ComponentCollisionCapsule>();
    col->SetRadius(radius);
    col->SetHeight(height);
    col->UseGravity();

    auto model      = AddComponent<ComponentModel>(str);
    model->Matrix() = matrix::scale(size);
    model->SetAnimation({
        {"idle", "data/Sample/Animal/abigail/Pig.mv1", 8, 1.0f},
        /*{"walk", "data/Sample/Player/abigail/Anim/Walking.mv1", 0, 1.0f},
			{"jump",	  "data/Sample/Player/abigail/Anim/Jump.mv1", 0, 1.0f},
			{ "run",	 "data/Sample/Player/abigail/Anim/Run.mv1", 0, 1.0f},*/
    });
    //model->SetScaleAxisXYZ( { 1, 1, 1 } );
    model->PlayAnimation("idle", true);

    AddComponent<ComponentGameCamera>();

    return true;
}

void Animal::Update()
{
    Super::Update();
    AddTranslate(direction_ * 1.0f);
    // ジャンプしていて、アニメーションが一定数値以上ならば、慣性の法則にしたがって上に移動させる
}
void Animal::OnHit(const ComponentCollision::HitInfo& hit_info)
{
    AnimalPtr Get_obj        = nullptr;
    auto      hit_owner_name = hit_info.hit_collision_->GetOwner()->GetNameDefault();

    if(hit_owner_name == "Wall") {
        //  direction_ = 0;
    }
    if(hit_owner_name == "Ground") {
        direction_ = 0;
        //地面に当たっているobjをIDLE状態にする
        Cone_Mode = IDLE;
    }
}
void Animal::SetDirectior(float3 dir)
{
    direction_ = dir;
}
}    // namespace Game01
