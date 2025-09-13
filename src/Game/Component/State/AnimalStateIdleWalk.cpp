#pragma once
#include <Game/Component/State/AnimalStateIdleWalk.h>
#include <System/Component/ComponentSpringArm.h>
#include <System/Component/ComponentModel.h>
#include <Game/Game01/Animal.h>
#include "StateJump.h"
#include "StateRun.h"

void AnimalStateIdleWalk::Init()
{
    __super::Init();
    wait_frame_ = GetRand(100);
}

void AnimalStateIdleWalk::Update()
{
    __super::Update();

    // オーナー(自分がAddComponentされたObject)を取得します
    // 処理されるときは必ずOwnerは存在しますので基本的にnullptrチェックは必要ありません
    auto owner = GetOwner();

    // 移動方向がランダムする

    if(auto animal = dynamic_cast<Game01::Animal*>(GetOwner())) {
        int mode = animal->Cone_Mode;
        if(mode == Game01::Animal::IDLE) {
            wait_frame_++;
        }
    }
    float3 dir{0, 0, 0};

    switch(dir_) {
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

    //動物が画面外が出られないように

    auto pos = owner->GetTranslate();    // 座標

    pos.x = max(-150.0f, min(pos.x, 55.0f));
    pos.z = max(-100.0f, min(pos.z, 110.0f));

    if(pos.x <= -150.0f || pos.x >= 55.0f || pos.z <= -100.0f || pos.z >= 110.0f) {
        //壁にぶつかると
        dir_ = GetRand(3);
    }

    owner->SetTranslate(pos);
}

AnimalStateIdleWalkPtr AnimalStateIdleWalk::SetMoveSpeed(const float speed)
{
    move_speed_ = speed;
    return std::dynamic_pointer_cast<AnimalStateIdleWalk>(shared_from_this());
}
AnimalStateIdleWalkPtr AnimalStateIdleWalk::SetRotateSpeed(const float speed)
{
    rot_speed_ = speed;
    return std::dynamic_pointer_cast<AnimalStateIdleWalk>(shared_from_this());
}

const float AnimalStateIdleWalk::GetMoveSpeed() const
{
    return move_speed_;
}

const float AnimalStateIdleWalk::GetRotateSpeed() const
{
    return rot_speed_;
}

void AnimalStateIdleWalk::GUI()
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

CEREAL_REGISTER_TYPE(AnimalStateIdleWalk)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, AnimalStateIdleWalk)
