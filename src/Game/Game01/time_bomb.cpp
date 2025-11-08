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
#include <Game/Component/State/StatePhysics.h>

namespace Game01 {

int bomb_effect;

bool Time_bomb::Init()
{
    Super::Init();

    Boms_Mode = IDLE;

    // プレイヤー
    SetName("Time bomb");
    SetTranslate({-87.0f, 26.0f, 57.0f});
    AddComponent<Acceleration>();
    auto col = AddComponent<ComponentCollisionCapsule>();    //
    col->SetRadius(5.53f);
    col->SetHeight(5.81f);
    col->SetCollisionGroup(ComponentCollision::CollisionGroup::ITEM);
    auto model      = AddComponent<ComponentModel>("data/Sample/time bomb/Bomb.mv1");
    model->Matrix() = matrix::scale(0.05f);
    AddComponent<StatePhysics>();    //投げるために必要

    bomb_effect = LoadEffekseerEffect("data/effects/01_AndrewFM01/fire.efkefc");

    return true;
}

void Time_bomb::Update()
{
    Super::Update();
    if(auto physics = GetComponent<StatePhysics>()) {
        if(Boms_Mode == THROWING || Boms_Mode == IDLE) {
            physics->StatePhysics::gravity_on = true;
        }
        else {
            physics->StatePhysics::gravity_on = false;
        }
    }
    if(Boms_Mode == THROWING) {
        first_thorw = true;
    }
}

void Time_bomb::SetDirectior(float3 dir)
{
    direction_ = dir;
}
void Time_bomb::Throw()
{
    auto physics = GetComponent<StatePhysics>();
    physics->addForce(direction_ * 1.0f, StatePhysics::Impulse);
    physics->SetStatic(false);
}

void Time_bomb::OnHit(const ComponentCollision::HitInfo& hit_info)
{
    Time_bombPtr Get_obj        = nullptr;
    auto         hit_owner_name = hit_info.hit_collision_->GetOwner()->GetNameDefault();
    auto         col            = GetComponent<ComponentCollisionCapsule>();

    if(hit_owner_name == "Ground" && Boms_Mode == THROWING) {
        Boms_Mode = HIT;
    }
    if(hit_owner_name == "Ground") {
        //地面に当たっているobjをIDLE状態にする
        // Boms_Mode    = IDLE;      //こいつの状態
        who_throwing = NOBODY;    //誰が投げてるか
        if(first_thorw == true) {
            //最初に投げた時＆＆地面に当たった時消す
            // Scene::Object::Release(SharedThis());
        }
    }
    if(Boms_Mode == HIT) {
        int    h   = PlayEffekseer3DEffect(bomb_effect);
        float3 pos = GetTranslate();
        SetPosPlayingEffekseer3DEffect(h, pos.x, pos.y, pos.z);
        SetScalePlayingEffekseer3DEffect(h, 4.0f, 4.0f, 4.0f);
        Boms_Mode = IDLE;
    }
    //IDLE時に動かないように
    if(Boms_Mode == IDLE) {
        auto physics = GetComponent<StatePhysics>();
        physics->addForce(float3{0, 0, 0}, StatePhysics::NoMotion);
        who_throwing = NOBODY;
        physics->SetStatic(false);
    }
    __super::OnHit(hit_info);
}
}    // namespace Game01
