#include "Player_betty.h"
#include "Animal.h"

#include <DxLib.h>
#include <System/Component/ComponentModel.h>
#include <System/Component/ComponentCollisionModel.h>
#include <System/Component/ComponentCollisionCapsule.h>
#include <System/Component/ComponentObjectController.h>
#include <System/Component/ComponentCollisionSphere.h>
#include <Game/Component/ComponentGameCamera.h>
#include <Game/Component/State/StateIdleWalk.h>
#include <Game/Component/State/StateJump.h>
#include <Game/Component/State/BettyStateIdleWalk.h>
#include "Hp.h"
#include <Game/Component/State/StateAI.h>
#include "Animal_pickup.h"
extern int hit_effect;

namespace Game01 {

bool Player_Betty::Init()
{
    Super::Init();

    // プレイヤー
    SetName("Player Betty");
    SetTranslate({0.0f, 5.0f, -50.0f});
    SetRotationAxisXYZ({0.0f, 180.0f, 0.0f});

    auto col = AddComponent<ComponentCollisionCapsule>();    //
    col->SetRadius(4.53f);
    col->SetHeight(16.81f);
    col->UseGravity();
    col->SetCollisionGroup(ComponentCollision::CollisionGroup::PLAYER);

    auto model      = AddComponent<ComponentModel>("data/Sample/Player/Betty/Betty.mv1");
    model->Matrix() = matrix::scale(0.8f);
    model->SetAnimation({
        {"idle",    "data/Sample/Player/Betty/Anim/Idle.mv1", 0, 1.0f},
        {"walk", "data/Sample/Player/Betty/Anim/Walking.mv1", 0, 1.0f},
        {"jump",    "data/Sample/Player/Betty/Anim/Jump.mv1", 0, 1.0f},
        { "run",     "data/Sample/Player/Betty/Anim/Run.mv1", 0, 1.0f},
    });
    //model->SetScaleAxisXYZ( { 1, 1, 1 } );
    model->PlayAnimation("idle", true);
    player_name = BETTY;
    //当たるエフェクトの初期化
    hit_effect = LoadEffekseerEffect("data/effects/01_AndrewFM01/hit.efkefc");
    AddComponent<Game01::Pickup>();

    AddComponent<ComponentGameCamera>();
    AddComponent<StateAI>();
    //  AddComponent<BettyStateIdleWalk>();

    return true;
}

void Player_Betty::Update()
{
    Super::Update();
    pos_npc_ = GetTranslate();

    // ジャンプしていて、アニメーションが一定数値以上ならば、慣性の法則にしたがって上に移動させる
}
void Player_Betty::OnHit(const ComponentCollision::HitInfo& hit_info)
{
    Super::OnHit(hit_info);
    auto hit_owner_name = hit_info.hit_collision_->GetOwner();
    //for(auto obj_ : Scene::Object::GetArray<Animal>()) {
    //    if(obj_->GetName() == hit_owner_name->GetName()) {
    //        if(obj_->Cone_Mode == THROWING) {
    //            if(obj_->who_throwing != Game01::Animal::BETTY) {
    //                //ここに当たったら
    //            }
    //        }
    //    }
    //}

    for(auto obj_ : Scene::Object::GetArray<Animal>()) {
        if(obj_->GetName() == hit_owner_name->GetName()) {
            if(obj_->Cone_Mode == THROWING) {
                if(obj_->who_throwing != Game01::Animal::BETTY && obj_->who_throwing != Game01::Animal::NOBODY) {
                    obj_->Cone_Mode         = Game01::Animal::DEATH;
                    auto Hp_get             = Scene::Object::Get<Hp>();
                    Hp_get->Hp_count_betty -= 1;

                    //エフェクトが出る
                    int h = PlayEffekseer3DEffect(hit_effect);

                    float3 pos = GetTranslate();
                    SetPosPlayingEffekseer3DEffect(h, pos.x, pos.y + 5.0f, pos.z);
                    SetScalePlayingEffekseer3DEffect(h, 4.0f, 4.0f, 4.0f);
                }
            }
        }
    }
}
}    // namespace Game01
