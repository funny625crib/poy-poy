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
    auto owner = GetOwner();    //スキルを使うオブジェクトを取得

    //left_collision_ = col;

    if(auto model = owner->GetComponent<ComponentModel>()) {
        model->PlayAnimation("run");
    }

    //初期速度
    current_speed_ = 2.0f;
    //目標速度
    target_speed = 3.0f;
}

void Acceleration::Update()
{
    __super::Update();
    auto owner = GetOwner();    //スキルを使うオブジェクトを取得

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
    float lerp_factor = 0.1f;    //補間係数(値を大きくすると早く切り替えられる)
    if(stall_time_ <= 0.0f)      //加速フェーズ
    {
        //Lerpで徐々に速度を変化させる
        current_speed_ = current_speed_ + (target_speed - current_speed_) * lerp_factor;
        //現在の移動速度を設定
        move_speed_ = current_speed_;
    }

    target_speed = 1.0f;    //減速目標速度
    //Lerpで徐々に速度を変化させる
    current_speed_ = current_speed_ + (target_speed - current_speed_) * lerp_factor;
    //現在の移動速度を設定
    move_speed_ = current_speed_;
    //回転速度を設定
    rot_speed_ = 30.0f;

    //動く速度がターゲットスピードに到達したら
    if(move_speed_ >= 4.0f) {
        stall_time_ += 1.0f;    //減速するために時間をカウント
    }
    if(stall_time_ >= 30.0f) {
        stall_time_ = 0.0f;    //カウントリセット
    }
}
}    // namespace Game01
