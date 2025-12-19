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
#include <Game/Game01/Player_betty.h>
#include <Game/Game01/Player_sol.h>
#include <Game/Game01/Player_abigail.h>
void StateAI::Init()
{
    __super::Init();

    auto owner = GetOwner();

    //owner->AddComponent<StateThorw>();

    mode = Searchobj;
}

void StateAI::Update()
{
    __super::Update();
    auto owner = GetOwner();
    // static Game01::AnimalPtr    Get_obj_A = nullptr;
    static Game01::Time_bombPtr Get_obj_B = nullptr;
    //Game01::Time_bombPtr memory_bom     = nullptr;
    float3 Get_pos        = owner->GetTranslate();
    auto   get_pickup_com = owner->GetComponent<Game01::Pickup>();

    if(mode == Searchobj) {
        count_pickup_cooldown = 0;
        float min_dir         = 0.0f;        //一番近くに距離のの初期値を置くを置く
        float max_dir         = 10000.0f;    //一番遠くに距離のの初期値を置くを置く

        for(auto obj_ : Scene::Object::GetArray<Game01::Animal>()) {
            // ここに来る場合 obj がEnemyクラスということが保証されます。
            // nameは、必ず存在するため、オブジェクトの名前を取得できます。
            if(obj_->Cone_Mode == HOLDING)
                continue;
            if(obj_->Invisible_ == Game01::Animal::OFF) {
                continue;
            }
            auto   get_obj_pos = obj_->GetTranslate();
            auto   get_npc_pos = float3{Get_pos.x, Get_pos.y + 18.0f, Get_pos.z};
            float3 dis         = get_obj_pos - get_npc_pos;
            float  dir         = sqrtf(dis.x * dis.x + dis.y * dis.y + dis.z * dis.z);
            if(dir > min_dir) {
                min_dir   = dir;
                set_obj_  = ANIMAL;
                Get_obj_A = obj_;
                hold_obj  = Get_obj_A;
                //Get_obj_B = nullptr;
            }
        }
        // ここに来る場合 obj がEnemyクラスということが保証されます。
        // nameは、必ず存在するため、オブジェクトの名前を取得できます。
        for(auto obj_boms_ : Scene::Object::GetArray<Game01::Time_bomb>()) {
            if(obj_boms_->Boms_Mode == HOLDING)
                continue;
            auto   get_obj_pos2 = obj_boms_->GetTranslate();
            auto   get_npc_pos2 = float3{Get_pos.x, Get_pos.y + 18.0f, Get_pos.z};
            float3 dis2         = get_obj_pos2 - get_npc_pos2;
            float  dir2         = sqrtf(dis2.x * dis2.x + dis2.y * dis2.y + dis2.z * dis2.z);
            if(dir2 > min_dir) {
                min_dir   = dir2;
                set_obj_  = BOMS;
                hold_obj  = Get_obj_B;
                Get_obj_B = obj_boms_;
            }
        }

        mode = Movetoobj;
    }

    if(mode == Movetoobj) {
        lock_on_time++;
        if(lock_on_time > 300) {
            lock_on_time = 0;
            mode         = Searchobj;
        }
        if(Get_obj_A) {
            // Get_obj_A->Invisible_ = Game01::Animal::OFF;
        }
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
        if(hold_obj)
            pos2 = hold_obj->GetTranslate();
        if(Get_obj_A != nullptr && set_obj_ == ANIMAL) {
            if(Get_obj_A == nullptr) {
                //mode = Searchobj;
                return;
            }
            if(Get_obj_A) {
                // pos2 = Get_obj_A->GetTranslate();
            }
        }

        float3 pos3;
        if(Get_obj_B != nullptr && set_obj_ == BOMS) {
            if(Get_obj_B == nullptr) {
                // mode = Searchobj;
                return;
            }
            // pos3 = Get_obj_B->GetTranslate();
        }
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
            if(get_pickup_com->Get == hold_obj) {
                owner->_isholding = HOLDING;
                mode              = SearchPlayer;
            }
        }
    }
    auto player1 = Scene::Object::Get<Game01::Player_Rise>();
    auto player2 = Scene::Object::Get<Game01::Player_Betty>();
    auto player3 = Scene::Object::Get<Game01::Player_Abigail>();
    auto player4 = Scene::Object::Get<Game01::Player_Sol>();
    if(mode == SearchPlayer) {
        if(owner->player_name == RISE) {
            int rand = GetRand(2);
            switch(rand) {
            case 0:
                pos2 = player2->GetTranslate();
                break;
            case 1:
                pos2 = player3->GetTranslate();
                break;
            case 2:
                pos2 = player4->GetTranslate();
                break;
            }
        }
        if(owner->player_name == BETTY) {
            int rand = GetRand(2);
            switch(rand) {
            case 0:
                pos2 = player1->GetTranslate();
                break;
            case 1:
                pos2 = player3->GetTranslate();
                break;
            case 2:
                pos2 = player4->GetTranslate();
                break;
            }
        }
        if(owner->player_name == ABIGAIL) {
            int rand = GetRand(2);
            switch(rand) {
            case 0:
                pos2 = player2->GetTranslate();
                break;
            case 1:
                pos2 = player1->GetTranslate();
                break;
            case 2:
                pos2 = player4->GetTranslate();
                break;
            }
        }
        if(owner->player_name == SOL) {
            int rand = GetRand(2);
            switch(rand) {
            case 0:
                pos2 = player2->GetTranslate();
                break;
            case 1:
                pos2 = player3->GetTranslate();
                break;
            case 2:
                pos2 = player1->GetTranslate();
                break;
            }
        }
        mode = MovetoPlayer;
    }

    if(mode == MovetoPlayer) {
        lock_on_time++;
        if(lock_on_time > 300) {
            lock_on_time = 0;
            mode         = SearchPlayer;
        }
        // Get_obj_A->who_holding = owner->player_name;
        float3 pos1    = Get_pos;
        pos1.y         = 0.0f;
        pos2.y         = 0.0f;
        float x        = pos1.x - pos2.x;
        float y        = pos1.y - pos2.y;
        float z        = pos1.z - pos2.z;
        float distance = sqrtf(x * x + y * y + z * z);
        DrawFormatString(0, 100, WHITE, "%f", distance);
        float radius = 60.0f;
        //	１：２つのベクトルを用意
        //	プレイヤーの前方向のベクトル（内積から角度を求めたいので長さを 1.0 に）
        float3 front;
        float3 rot = owner->GetRotationAxisXYZ() + 180.0f;    // X軸Y軸Z軸に対する回転が取得できます

        get_pickup_com->dir = {0.0f, rot.y, 0.0f};
        front.x             = 1.0f * sinf((get_pickup_com->dir.y * 3.14159265f / 180.0f));
        front.z             = 1.0f * cosf((get_pickup_com->dir.y * 3.14159265f / 180.0f));
        //	プレイヤーから見てＮＰＣがどの方向にいるかのベクトル
        float3 target = pos2 - pos1;

        //	ベクトルの正規化（ベクトルの長さを 1.0 に）

        float length = sqrtf(target.x * target.x + target.z * target.z);
        // float length_bom = sqrtf(target_bom.x * target_bom.x + target_bom.z * target_bom.z);

        if(length > 0.0f) {
            target.x = target.x / length;
            target.z = target.z / length;
        }
        /* if(length_bom > 0.0f) {
                target_bom.x = target_bom.x / length_bom;
                target_bom.z = target_bom.z / length_bom;
            }*/
        //	２：２つのベクトルの内積を取得
        float front_dot = front.x * target.x + front.z * target.z;
        //float front_dot_bom = front.x * target_bom.x + front.z * target_bom.z;

        /*  GetFloat2Dot(front, target);*/

        //	３：求めた内積の値から角度を求める
        //	この内積の値（ front_dot ）を acos 関数に渡すことで角度を取得できます
        //	acosf：アークコサイン関数（ cos 関数の逆関数）← ラジアン角が返ってきます
        float radian = acosf(front_dot);
        //  float radian_bom = acosf(front_dot_bom);
        //	ラジアン角を角度の「度」にします
        float degree = radian * 180.0f / 3.14159265f;
        // float degree_bom = radian_bom * 180.0f / 3.14159265f;

        if(owner->_isholding == HOLDING) {
            for(auto obj_ : Scene::Object::GetArray<Game01::Animal>()) {
                if(Get_obj_A == obj_ && get_pickup_com->set_obj_ == Game01::Pickup::ANIMAL) {
                    if(Get_obj_A) {
                        Get_obj_A->Invisible_ = Game01::Animal::OFF;
                    }
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
            if(distance <= radius && degree < 35.0f) {
                if(owner->_isholding == HOLDING) {
                    owner->_isholding = THROWING;
                    if(owner->_isholding == THROWING) {
                        for(auto obj_ : Scene::Object::GetArray<Game01::Animal>()) {
                            if(Get_obj_A == obj_) {
                                if(Get_obj_A) {
                                    Get_obj_A->Invisible_ = Game01::Animal::ON;
                                }

                                Get_obj_A->SetTranslate(owner->GetTranslate() + float3{0, 18.0f, 0});
                                auto modelrot = owner->GetComponent<ComponentModel>();
                                auto dir      = -modelrot->GetWorldMatrix().axisZ();
                                Get_obj_A->SetDirectior(dir);
                                obj_->Cone_Mode = THROWING;
                                if(owner->player_name == RISE) {
                                    obj_->who_throwing = Game01::Animal::RISE;
                                }
                                if(owner->player_name == BETTY) {
                                    obj_->who_throwing = Game01::Animal::BETTY;
                                }
                                if(owner->player_name == ABIGAIL) {
                                    obj_->who_throwing = Game01::Animal::ABIGAIL;
                                }
                                if(owner->player_name == SOL) {
                                    obj_->who_throwing = Game01::Animal::SOL;
                                }
                                // obj_->who_throwing = Get_obj_A->who_holding;
                                obj_->Game01::Animal::Throw();
                                thowe_chack = true;
                            }
                        }
                        for(auto obj_boms_ : Scene::Object::GetArray<Game01::Time_bomb>()) {
                            if(Get_obj_B == obj_boms_) {
                                Get_obj_B->SetTranslate(owner->GetTranslate() + float3{0, 18.0f, 0});
                                auto modelrot = owner->GetComponent<ComponentModel>();
                                auto dir      = -modelrot->GetWorldMatrix().axisZ();
                                Get_obj_B->SetDirectior(dir);
                                obj_boms_->Boms_Mode = THROWING;
                                if(owner->player_name == RISE) {
                                    obj_boms_->who_throwing = Game01::Animal::RISE;
                                }
                                if(owner->player_name == BETTY) {
                                    obj_boms_->who_throwing = Game01::Animal::BETTY;
                                }
                                if(owner->player_name == ABIGAIL) {
                                    obj_boms_->who_throwing = Game01::Animal::ABIGAIL;
                                }
                                if(owner->player_name == SOL) {
                                    obj_boms_->who_throwing = Game01::Animal::SOL;
                                }
                                obj_boms_->Game01::Time_bomb::Throw();

                                thowe_chack = false;
                            }
                        }
                    }
                }
            }

            {
                owner->SetRotationToPositionWithLimit(pos2, 3.0f);
                owner->AddTranslate({0, 0, -0.3f}, true);
            }
            //IDLE状態のときオブジェクトを移動するのをやめさせる
            if(Get_obj_A) {
                if(Get_obj_A->Cone_Mode == IDLE || Get_obj_A->Cone_Mode == Game01::Animal::DEATH) {
                    owner->_isholding = IDLE;
                    Get_obj_A         = nullptr;
                }
            }
            if(Get_obj_B) {
                if(Get_obj_B->Boms_Mode == IDLE || Get_obj_B->Boms_Mode == Game01::Animal::DEATH) {
                    owner->_isholding = IDLE;
                    Get_obj_B         = nullptr;
                    mode              = Searchobj;
                }
            }
        }
        if(thowe_chack == true) {
            thowe_time++;
        }
        else {
            thowe_time = 0;
        }
        if(thowe_time > 30) {
            thowe_chack = false;
            mode        = Searchobj;
        }
    }
}

void StateAI::GUI()
{
    __super::GUI();
}

CEREAL_REGISTER_TYPE(StateAI)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, StateAI)
