#include "Ramming.h"
#include <Game/Component/State/StateRun.h>
#include <Game/Component/State/StateIdleWalk.h>
#include <System/Component/ComponentModel.h>
#include <System/Component/ComponentCollisionSphere.h>
#include <Game/Game01/Animal.h>
#include <DxLib.h>
#include <Game/Game01/Player_rise.h>

namespace Game01 {
void Ramming::Init()
{
    __super::Init();
    auto owner = GetOwner();
    auto col   = owner->AddComponent<ComponentCollisionSphere>();
    col->AttachToModel("mixamorig:LeftLeg");
    col->SetName("PlayerRun");

    left_collision_ = col;

    if(auto model = owner->GetComponent<ComponentModel>()) {
        model->PlayAnimation("run");
    }
    // カメラオブジェクト
    //auto camera = Scene::Object::Create<Object>();
}

void Ramming::Update()
{
    __super::Update();
    auto owner = GetOwner();
    // 移動方向

    // 移動キーが押されているか?
    //if((float)length(dir) > 0.0f) {
    // 斜めが押されていることを考慮し、

    // その方向の移動スピードを1とし、スピードを掛け合わせる
    auto pre    = Scene::Object::Get<Game01::Player_Rise>();
    auto model2 = pre->GetComponent<ComponentModel>();
    auto dir    = -model2->GetWorldMatrix().axisZ();
    dir         = normalize(dir);

    // キャラのローカル方向で移動をさせる
    owner->AddTranslate(dir * move_speed_);

    // モデルを移動の方向に向けます
    if(auto mdl = owner->GetComponent<ComponentModel>()) {
        auto rot = quaternion::rotation_axis({0, 1, 0}, front_rot_ * DegToRad);    //< Y軸1度回転

        mdl->SetRotationToVectorWithLimit(mul(dir, rot), rot_speed_);
    }
    //}

    if(auto model = owner->GetComponent<ComponentModel>()) {
        //　モーションが終了しているか?
        if(!model->IsPlaying()) {
            RemoveThisComponent();
            if(auto left_collision = left_collision_.lock())
                owner->RemoveComponent(left_collision);

            owner->AddComponent<StateIdleWalk>();
        }
    }
}
}    // namespace Game01
