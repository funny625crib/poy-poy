#pragma once
#include "StateThorw.h"

#include "StateIdleWalk.h"
#include <System/Component/ComponentModel.h>
#include <System/Component/ComponentCollisionSphere.h>
#include <DxLib.h>
#include <Game/Game01/Animal.h>
#include <Game/Game01/Animal_pickup.h>
#include <Game/Game01/time_bomb.h>
Game01::AnimalPtr    Get_obj  = nullptr;
Game01::Time_bombPtr Get_obj2 = nullptr;

void StateThorw::Init()
{
    __super::Init();

    auto owner = GetOwner();

    auto col = owner->AddComponent<ComponentCollisionSphere>();
    col->AttachToModel("mixamorig:LeftLeg");
    col->SetName("PlayerJump");

    left_collision_ = col;

    if(auto model = owner->GetComponent<ComponentModel>()) {
        model->PlayAnimation("jump");
    }
}

void StateThorw::Update()
{
    //__super::Update();
    auto   owner    = GetOwner();
    float3 pos_npc_ = owner->GetTranslate();
    float  max_dir  = 10000.0f;    //一番遠くに距離のの初期値を置くを置く
                                   //一番近くのオブジェクトの保管
    auto get_pickup_com = owner->GetComponent<Game01::Pickup>();

    //すべて見て行って一番近くのオブジェクトを取得
    if(IsKeyOn(KEY_INPUT_Q) && owner->_isholding == IDLE) {
        for(auto obj_boms_ : Scene::Object::GetArray<Game01::Time_bomb>()) {
            for(auto obj_ : Scene::Object::GetArray<Game01::Animal>()) {
                // ここに来る場合 obj がEnemyクラスということが保証されます。
                // nameは、必ず存在するため、オブジェクトの名前を取得できます。
                //if(Get_obj == nullptr) {
                auto get_bom_pos      = obj_boms_->GetTranslate();
                auto get_obj_pos      = obj_->GetTranslate();
                auto get_npc_pos      = float3{pos_npc_.x, pos_npc_.y + 18.0f, pos_npc_.z};
                dis_character_animal_ = get_obj_pos - get_npc_pos;
                dis_character_Boms_   = get_bom_pos - get_npc_pos;
                float dir             = sqrtf(dis_character_animal_.x * dis_character_animal_.x + dis_character_animal_.y * dis_character_animal_.y +
                                  dis_character_animal_.z * dis_character_animal_.z);
                float dir2            = sqrtf(dis_character_Boms_.x * dis_character_Boms_.x + dis_character_Boms_.y * dis_character_Boms_.y +
                                   dis_character_Boms_.z * dis_character_Boms_.z);

                if(dir < max_dir) {
                    max_dir  = dir;
                    Get_obj  = obj_;
                    Get_obj2 = nullptr;
                }
                if(dir2 < max_dir) {
                    max_dir  = dir2;
                    Get_obj  = nullptr;
                    Get_obj2 = obj_boms_;
                }
            }
        }

        if(get_pickup_com->Check_Pickup() == true) {
            owner->_isholding = HOLDING;
        }
    }

    auto& obj     = Get_obj;     //一番近くのオブジェクトを取得
    auto& obj_bom = Get_obj2;    //一番近くのオブジェクトを取得
    //IDLE状態のときPキー押した時HOLDING状態にする

    //もしnpcの状態がHOLDING状態なら一番近くで当たってるものをHOLDING状態にする
    if(owner->_isholding == HOLDING) {
        for(auto obj_ : Scene::Object::GetArray<Game01::Animal>()) {
            if(Get_obj == obj_ && get_pickup_com->set_obj_ == Game01::Pickup::ANIMAL) {
                obj_->Cone_Mode = HOLDING;
                obj_->SetTranslate({pos_npc_.x, pos_npc_.y + 18.0f, pos_npc_.z});
                // ★ 追加: プレイヤーの前方向に動物モデルの向きを一発で合わせる
                if(auto pModel = owner->GetComponent<ComponentModel>()) {
                    const auto forward = -pModel->GetWorldMatrix().axisZ();    // 投げ処理と同じ基準
                    if(auto aModel = obj_->GetComponent<ComponentModel>()) {
                        aModel->SetRotationToVectorWithLimit(-forward, 999.0f);    // 即時に向きを一致
                    }
                }
            }
        }
        for(auto obj_boms_ : Scene::Object::GetArray<Game01::Time_bomb>()) {
            if(Get_obj2 == obj_boms_ && get_pickup_com->set_obj_ == Game01::Pickup::BOMS) {
                obj_boms_->Boms_Mode = HOLDING;
                obj_boms_->SetTranslate({pos_npc_.x, pos_npc_.y + 25.0f, pos_npc_.z});
                // ★ 追加: プレイヤーの前方向に動物モデルの向きを一発で合わせる
                if(auto pModel = owner->GetComponent<ComponentModel>()) {
                    const auto forward = -pModel->GetWorldMatrix().axisZ();    // 投げ処理と同じ基準
                    if(auto aModel = obj_boms_->GetComponent<ComponentModel>()) {
                        aModel->SetRotationToVectorWithLimit(-forward, 999.0f);    // 即時に向きを一致
                    }
                }
            }
        }
    }
    //HOLDING状態のときOキー押した時THROWING状態にする
    if(IsKeyOn(KEY_INPUT_E) && owner->_isholding == HOLDING) {
        owner->_isholding = THROWING;
        if(owner->_isholding == THROWING) {
            for(auto obj_ : Scene::Object::GetArray<Game01::Animal>()) {
                if(Get_obj == obj_) {
                    obj->SetTranslate(owner->GetTranslate() + float3{0, 18.0f, 0});
                    auto modelrot = owner->GetComponent<ComponentModel>();
                    auto dir      = -modelrot->GetWorldMatrix().axisZ();
                    obj->SetDirectior(dir);
                    obj_->Cone_Mode    = THROWING;
                    obj_->who_throwing = Game01::Animal::RISE;
                    obj_->Game01::Animal::Throw();
                }
            }
            for(auto obj_boms_ : Scene::Object::GetArray<Game01::Time_bomb>()) {
                if(Get_obj2 == obj_boms_) {
                    obj_bom->SetTranslate(owner->GetTranslate() + float3{0, 18.0f, 0});
                    auto modelrot = owner->GetComponent<ComponentModel>();
                    auto dir      = -modelrot->GetWorldMatrix().axisZ();
                    obj_bom->SetDirectior(dir);
                    obj_boms_->Boms_Mode    = THROWING;
                    obj_boms_->who_throwing = Game01::Animal::RISE;
                    obj_boms_->Game01::Time_bomb::Throw();
                }
            }
        }
    }
    //IDLE状態のときオブジェクトを移動するのをやめさせる
    if(obj) {
        if(obj->Cone_Mode == IDLE || obj->Cone_Mode == Game01::Animal::DEATH) {
            owner->_isholding = IDLE;
            Get_obj           = nullptr;
        }
    }
    if(obj_bom) {
        if(obj_bom->Boms_Mode == IDLE || obj_bom->Boms_Mode == Game01::Animal::DEATH) {
            owner->_isholding = IDLE;
            Get_obj2          = nullptr;
        }
    }
    // Super::OnHit(hit_info);
}

void StateThorw::GUI()
{
    __super::GUI();

    // GUI内に出現させる
    ImGui::Begin(GetOwner()->GetName().data());
    {
        ImGui::Separator();
        if(ImGui::TreeNode(u8"State Jump")) {
            ImGui::TreePop();
        }
    }
    ImGui::End();
}

CEREAL_REGISTER_TYPE(StateThorw)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, StateThorw)
