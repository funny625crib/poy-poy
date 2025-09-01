#pragma once
#include <Game/Component/State/SolStateIdleWalk.h>
#include <System/Component/ComponentSpringArm.h>
#include <System/Component/ComponentModel.h>
#include "StateJump.h"
#include "StateRun.h"

void SolStateIdleWalk::Init()
{
    __super::Init();
}

void SolStateIdleWalk::Update()
{
    __super::Update();

    // オーナー(自分がAddComponentされたObject)を取得します
    // 処理されるときは必ずOwnerは存在しますので基本的にnullptrチェックは必要ありません
    auto owner = GetOwner();

    // 移動方向がランダムする
    static int sol_dir = 2;    //移動方向

    static int sol_wait_frame;    //移動方向を変わる前に待つ時間

    sol_wait_frame++;
    if(sol_wait_frame >= 180) {
        sol_dir        = GetRand(3);
        sol_wait_frame = 0;
    }

    float3 dir{0, 0, 0};

    switch(sol_dir) {
    case 0:    //up
        dir += {0, 0, -1};
        break;
    case 1:    //down
        dir += {0, 0, 1};
        break;
    case 2:    //right
        dir += {-1, 0, 0};
        break;
    case 3:    //left
        dir += {1, 0, 0};
        break;
    }

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
            mdl->PlayAnimationNoSame("walk", true);
        }
    }
    else {
        // モデルを移動の方向に向けます
        if(auto mdl = owner->GetComponent<ComponentModel>())
            mdl->PlayAnimationNoSame("idle", true);
    }
}

SolStateIdleWalkPtr SolStateIdleWalk::SetMoveSpeed(const float speed)
{
    move_speed_ = speed;
    return std::dynamic_pointer_cast<SolStateIdleWalk>(shared_from_this());
}
SolStateIdleWalkPtr SolStateIdleWalk::SetRotateSpeed(const float speed)
{
    rot_speed_ = speed;
    return std::dynamic_pointer_cast<SolStateIdleWalk>(shared_from_this());
}

const float SolStateIdleWalk::GetMoveSpeed() const
{
    return move_speed_;
}

const float SolStateIdleWalk::GetRotateSpeed() const
{
    return rot_speed_;
}

void SolStateIdleWalk::GUI()
{
    __super::GUI();

    // GUI内に出現させる
    ImGui::Begin(GetOwner()->GetName().data());
    {
        ImGui::Separator();
        if(ImGui::TreeNode(u8"State 移動・停止")) {
            if(ImGui::Button(u8"削除"))
                GetOwner()->RemoveComponent(shared_from_this());

            // 移動の基本情報
            ImGui::DragFloat(u8"移動速度", &move_speed_, 0.1f);
            ImGui::DragFloat(u8"移動回転角度", &rot_speed_, 1.0f);

            // 移動の基本情報
            ImGui::DragFloat(u8"オブジェクト オフセット回転", &front_rot_, 1.0f);

            ImGui::TreePop();
        }
    }
    ImGui::End();
}

CEREAL_REGISTER_TYPE(SolStateIdleWalk)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, SolStateIdleWalk)
