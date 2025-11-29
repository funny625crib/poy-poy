#pragma once
#include <System/Component/ComponentModel.h>
#include <Game/Component/State/StateIdleWalk.h>
#include <Game/Game01/Skills/Acceleration.h>
#include <Game/Game01/Skills/Ramming.h>
#include <Game/Game01/Animal.h>
#include <Game/Game01/Skills/Avoidance.h>
#include <System/Component/ComponentSpringArm.h>
#include "StateJump.h"
#include "StateRun.h"
#include <Game/Game01/Player_rise.h>

void StateIdleWalk::Init()
{
    __super::Init();
}

void StateIdleWalk::Update()
{
    __super::Update();

    // オーナー(自分がAddComponentされたObject)を取得します
    // 処理されるときは必ずOwnerは存在しますので基本的にnullptrチェックは必要ありません
    auto owner = GetOwner();

    auto player  = Scene::Object::Get<Game01::Player_Rise>();
    bool healing = (player && player->IsHealing());

    // 移動方向
    float3 dir{0, 0, 0};
    if(IsKey(key_up_))
        dir += {0, 0, -1};

    if(IsKey(key_down_))
        dir += {0, 0, 1};

    if(IsKey(key_right_))
        dir += {-1, 0, 0};

    if(IsKey(key_left_))
        dir += {1, 0, 0};

    // 移動キーが押されているか?
    if((float)length(dir) > 0.0f) {
        // 斜めが押されていることを考慮し、
        // その方向の移動スピードを1とし、スピードを掛け合わせる
        dir              = normalize(dir);
        float base_speed = 0.5f;
        if(owner->GetComponent<Game01::Acceleration>() && Input::IsKeyRepeat(KEY_INPUT_P)) {
            base_speed = 1.5f;
        }

        // キャラのローカル方向で移動をさせる
        owner->AddTranslate(dir * base_speed, true);
        for(auto obj_ : Scene::Object::GetArray<Game01::Animal>()) {
            if(obj_->Cone_Mode == obj_->HOLDING) {
                auto Get_positon = owner->GetTranslate();
                obj_->SetTranslate({Get_positon.x, Get_positon.y + 18.0f, Get_positon.z});
            }
        }

        // モデルを移動の方向に向けます
        if(auto mdl = owner->GetComponent<ComponentModel>()) {
            auto rot = quaternion::rotation_axis({0, 1, 0}, front_rot_ * DegToRad);    //< Y軸1度回転

            mdl->SetRotationToVectorWithLimit(mul(dir, rot), rot_speed_);
            mdl->PlayAnimationNoSame("walk", true);
        }
    }
    else {
        if(!healing) {
            // モデルを移動の方向に向けます
            auto mdl = owner->GetComponent<ComponentModel>();
            mdl->PlayAnimationNoSame("idle", true);
        }
    }

    if(Input::IsKeyDown(KEY_INPUT_SPACE))    //ジャンプ
    {
        owner->RemoveComponent(shared_from_this());
        owner->AddComponent<StateJump>();
    }

    if(Input::IsKeyRepeat(KEY_INPUT_LSHIFT) || Input::IsKeyRepeat(KEY_INPUT_RSHIFT))    //走る
    {
        if(Input::IsKeyRepeat(KEY_INPUT_W) || Input::IsKeyRepeat(KEY_INPUT_A) || Input::IsKeyRepeat(KEY_INPUT_S) ||
           Input::IsKeyRepeat(KEY_INPUT_D))    //移動キー押している時だけ
        {
            owner->RemoveComponent(shared_from_this());
            owner->AddComponent<StateRun>();
        }
    }
    else if(Input::IsKeyOn(KEY_INPUT_O))    //走る
    {
        owner->RemoveComponent(shared_from_this());
        owner->AddComponent<Game01::Ramming>();
    }
    else if(Input::IsKeyOn(KEY_INPUT_I))    //走る
    {
        owner->RemoveComponent(shared_from_this());
        owner->AddComponent<Game01::Ramming>();
    }
    if(Input::IsKeyDown(KEY_INPUT_P))    //Pを押したら超加速
    {
        owner->RemoveComponent(shared_from_this());
        owner->AddComponent<Game01::Acceleration>();
    }
}

StateIdleWalkPtr StateIdleWalk::SetMoveSpeed(const float speed)
{
    move_speed_ = speed;
    return std::dynamic_pointer_cast<StateIdleWalk>(shared_from_this());
}
StateIdleWalkPtr StateIdleWalk::SetRotateSpeed(const float speed)
{
    rot_speed_ = speed;
    return std::dynamic_pointer_cast<StateIdleWalk>(shared_from_this());
}

const float StateIdleWalk::GetMoveSpeed() const
{
    return move_speed_;
}

const float StateIdleWalk::GetRotateSpeed() const
{
    return rot_speed_;
}

StateIdleWalkPtr StateIdleWalk::SetKeys(int up, int down, int left, int right)
{
    // 移動キーの設定
    key_up_    = up;
    key_down_  = down;
    key_left_  = left;
    key_right_ = right;
    return std::dynamic_pointer_cast<StateIdleWalk>(shared_from_this());
}

void StateIdleWalk::GUI()
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

CEREAL_REGISTER_TYPE(StateIdleWalk)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, StateIdleWalk)
