#pragma once
#include "StateAI.h"

#include "StateIdleWalk.h"
#include <System/Component/ComponentModel.h>
#include <System/Component/ComponentCollisionSphere.h>
#include <DxLib.h>
#include <Game/Game01/Animal.h>
#include <Game/Game01/Animal_pickup.h>
#include <Game/Game01/time_bomb.h>
#include "StateThorw.h"
#include <Game/Game01/Player_rise.h>
void StateAI::Init()
{
    __super::Init();

    auto owner = GetOwner();
    owner->AddComponent<Game01::Pickup>();
    //owner->AddComponent<StateThorw>();

    mode = Searchobj;
}

void StateAI::Update()
{
    __super::Update();
    auto owner = GetOwner();
    // static Game01::AnimalPtr    Get_obj_A = nullptr;
    // static Game01::Time_bombPtr Get_obj_B = nullptr;

    //  Game01::AnimalPtr    memory_animal = nullptr;
    //Game01::Time_bombPtr memory_bom     = nullptr;
    float3 Get_pos        = owner->GetTranslate();
    auto   get_pickup_com = owner->GetComponent<Game01::Pickup>();

    if(mode == Searchobj) {
        float max_dir = 10000.0f;    //一番遠くに距離のの初期値を置くを置く
        for(auto obj_ : Scene::Object::GetArray<Game01::Animal>()) {
            // ここに来る場合 obj がEnemyクラスということが保証されます。
            // nameは、必ず存在するため、オブジェクトの名前を取得できます。
            // if(Get_obj_A) {
            if(obj_->Cone_Mode == HOLDING)
                continue;
            // }
            auto   name        = obj_->GetName();
            auto   get_obj_pos = obj_->GetTranslate();
            auto   get_npc_pos = float3{Get_pos.x, Get_pos.y + 18.0f, Get_pos.z};
            float3 dis         = get_obj_pos - get_npc_pos;
            float  dir         = sqrtf(dis.x * dis.x + dis.y * dis.y + dis.z * dis.z);
            if(dir < max_dir) {
                max_dir   = dir;
                set_obj_  = ANIMAL;
                Get_obj_A = obj_;
                //  memory_animal = Get_obj_A;
            }
        }
        for(auto obj_boms_ : Scene::Object::GetArray<Game01::Time_bomb>()) {
            // ここに来る場合 obj がEnemyクラスということが保証されます。
            // nameは、必ず存在するため、オブジェクトの名前を取得できます。
            //if(Get_obj_B) {
            if(obj_boms_->Boms_Mode == HOLDING)
                continue;
            //  }
            auto   name        = obj_boms_->GetName();
            auto   get_obj_pos = obj_boms_->GetTranslate();
            auto   get_npc_pos = float3{Get_pos.x, Get_pos.y + 18.0f, Get_pos.z};
            float3 dis         = get_obj_pos - get_npc_pos;
            float  dir         = sqrtf(dis.x * dis.x + dis.y * dis.y + dis.z * dis.z);
            if(dir < max_dir) {
                max_dir   = dir;
                set_obj_  = BOMS;
                Get_obj_B = obj_boms_;
                // memory_bom = obj_boms_;
            }
        }

        mode = Movetoobj;
    }

    if(mode == Movetoobj) {
        if(Get_obj_A) {
            if(Get_obj_A->Cone_Mode == HOLDING) {
                mode = Searchobj;
            }
        }
        if(Get_obj_B) {
            if(Get_obj_B->Boms_Mode == HOLDING) {
                mode = Searchobj;
            }
        }
        float3 pos1 = Get_pos;
        float3 pos2;
        if(Get_obj_A != nullptr && set_obj_ == ANIMAL)
            pos2 = Get_obj_A->GetTranslate();
        float3 pos3;
        if(Get_obj_B != nullptr && set_obj_ == BOMS)
            pos3 = Get_obj_B->GetTranslate();
        if(set_obj_ == ANIMAL) {
            owner->SetRotationToPositionWithLimit(pos2, 3.0f);
            owner->AddTranslate({0, 0, -0.3f}, true);
        }
        if(set_obj_ == BOMS) {
            owner->SetRotationToPositionWithLimit(pos3, 3.0f);
            owner->AddTranslate({0, 0, -0.3f}, true);
        }
        if(auto mdl = owner->GetComponent<ComponentModel>()) {
            mdl->PlayAnimationNoSame("walk", true);
        }
        if(get_pickup_com->Check_Pickup() == true) {
            owner->_isholding = HOLDING;
            mode              = SearchPlayer;
        }
    }
    if(mode == SearchPlayer) {
        float3 pos1   = Get_pos;
        auto   player = Scene::Object::Get<Game01::Player_Rise>();
        float3 pos2   = player->GetTranslate();
        owner->SetRotationToPositionWithLimit(pos2, 3.0f);
        owner->AddTranslate({0, 0, -0.3f}, true);

        if(owner->_isholding == HOLDING) {
            for(auto obj_ : Scene::Object::GetArray<Game01::Animal>()) {
                if(Get_obj_A == obj_ && get_pickup_com->set_obj_ == Game01::Pickup::ANIMAL) {
                    Get_obj_A->Cone_Mode = HOLDING;
                    Get_obj_A->SetTranslate({Get_pos.x, Get_pos.y + 18.0f, Get_pos.z});
                    // ★ 追加: プレイヤーの前方向に動物モデルの向きを一発で合わせる
                    if(auto pModel = owner->GetComponent<ComponentModel>()) {
                        const auto forward = -pModel->GetWorldMatrix().axisZ();    // 投げ処理と同じ基準
                        if(auto aModel = Get_obj_A->GetComponent<ComponentModel>()) {
                            aModel->SetRotationToVectorWithLimit(-forward, 999.0f);    // 即時に向きを一致
                        }
                    }
                }
            }
            for(auto obj_boms_ : Scene::Object::GetArray<Game01::Time_bomb>()) {
                if(Get_obj_B == obj_boms_ && get_pickup_com->set_obj_ == Game01::Pickup::BOMS) {
                    Get_obj_B->Boms_Mode = HOLDING;
                    Get_obj_B->SetTranslate({Get_pos.x, Get_pos.y + 25.0f, Get_pos.z});
                    // ★ 追加: プレイヤーの前方向に動物モデルの向きを一発で合わせる
                    if(auto pModel = owner->GetComponent<ComponentModel>()) {
                        const auto forward = -pModel->GetWorldMatrix().axisZ();    // 投げ処理と同じ基準
                        if(auto aModel = Get_obj_B->GetComponent<ComponentModel>()) {
                            aModel->SetRotationToVectorWithLimit(-forward, 999.0f);    // 即時に向きを一致
                        }
                    }
                }
            }
        }
    }
}

void StateAI::GUI()
{
    __super::GUI();
}

CEREAL_REGISTER_TYPE(StateAI)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, StateAI)
