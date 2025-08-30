#include "Acceleration.h"
#include <Game/Component/State/StateRun.h>
#include <Game/Component/State/StateIdleWalk.h>
#include <System/Component/ComponentModel.h>
#include <System/Component/ComponentCollisionSphere.h>
#include <DxLib.h>

namespace Game01 {
void Acceleration::Init()
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

void Acceleration::Update()
{
    __super::Update();
    auto owner = GetOwner();
    // 移動方向
    float3 dir{0, 0, 0};
    if(IsKey(KEY_INPUT_W))
        dir += {0, 0, -1};

    if(IsKey(KEY_INPUT_S))
        dir += {0, 0, 1};

    if(IsKey(KEY_INPUT_D))
        dir += {-1, 0, 0};

    if(IsKey(KEY_INPUT_A))
        dir += {1, 0, 0};

    // 移動キーが押されているか?
    if((float)length(dir) > 0.0f) {
        // 斜めが押されていることを考慮し、
        // その方向の移動スピードを1とし、スピードを掛け合わせる
        dir = normalize(dir);

        // キャラのローカル方向で移動をさせる
        owner->AddTranslate(dir * move_speed_, true);

        // モデルを移動の方向に向けます
        if(auto mdl = owner->GetComponent<ComponentModel>()) {
            auto rot = quaternion::rotation_axis({0, 1, 0}, front_rot_ * DegToRad);    //< Y軸1度回転

            mdl->SetRotationToVectorWithLimit(mul(dir, rot), rot_speed_);
        }
    }

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
