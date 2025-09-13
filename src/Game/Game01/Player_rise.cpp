#include "Player_rise.h"
#include "Animal.h"
#include <DxLib.h>
#include <System/Component/ComponentModel.h>
#include <System/Component/ComponentCollisionModel.h>
#include <System/Component/ComponentCollisionCapsule.h>
#include <System/Component/ComponentObjectController.h>
#include <System/Component/ComponentCollisionSphere.h>
#include <Game/Component/ComponentGameCamera.h>
#include <Game/Game01/Skills/Acceleration.h>
#include <Game/Component/State/StateIdleWalk.h>
#include <Game/Game01/Animal_pickup.h>
#include <Game/Component/State/StateJump.h>

namespace Game01 {
//float3    dir{0, 0, 0};
//AnimalPtr Get_obj2 = nullptr;    //一番近くのオブジェクトの保管
AnimalPtr Get_obj = nullptr;
bool      Player_Rise::Init()
{
    Super::Init();

    // プレイヤー
    SetName("Player Rise");
    SetTranslate({-87.0f, -6.0f, 47.0f});
    AddComponent<Acceleration>();
    auto col = AddComponent<ComponentCollisionCapsule>();    //
    col->SetRadius(4.53f);
    col->SetHeight(16.81f);
    col->UseGravity();
    col->SetCollisionGroup(ComponentCollision::CollisionGroup::PLAYER);

    auto model      = AddComponent<ComponentModel>("data/Sample/Player/Rise_school/Rise.mv1");
    model->Matrix() = matrix::scale(0.7f);
    model->SetAnimation({
        {"idle",    "data/Sample/Player/Rise_school/Anim/Idle.mv1", 0, 1.0f},
        {"walk", "data/Sample/Player/Rise_school/Anim/Walking.mv1", 0, 1.0f},
        {"jump",    "data/Sample/Player/Rise_school/Anim/Jump.mv1", 0, 1.0f},
        { "run",     "data/Sample/Player/Rise_school/Anim/Run.mv1", 0, 1.0f},
    });
    //   model->SetScaleAxisXYZ( { 1, 1, 1 } );

    AddComponent<ComponentGameCamera>();
    AddComponent<Pickup>();
    AddComponent<StateIdleWalk>();

    return true;
}

void Player_Rise::Update()
{
    Super::Update();
    pos_npc_ = GetTranslate();
    enum
    {
        MODE_IDLE,         //プレイヤーが立っているとき
        MODE_JUMP_WAIT,    //ジャンプ前に少し待つ
        MODE_JUMP,         //ジャンプ
    };
    static int player_mode = MODE_IDLE;    //プレイヤーのモード

    static int ani_time      = 0;    //ジャンプの持続時間
    static int ani_wait_time = 0;    //ジャンプ前の待機時間

    if(Input::IsKeyDown(KEY_INPUT_SPACE) && player_mode == MODE_IDLE) {
        player_mode   = MODE_JUMP_WAIT;
        ani_wait_time = 30;
    }

    if(player_mode == MODE_JUMP_WAIT) {
        ani_wait_time--;
        if(ani_wait_time < 0) {
            ani_time      = 40;
            player_mode   = MODE_JUMP;
            ani_wait_time = 0;
        }
    }
    else if(player_mode == MODE_JUMP) {
        ani_time--;
        if(ani_time > 0) {
            AddTranslate({0, 0.5, 0});
        }
        else {
            ani_time    = 0;
            player_mode = MODE_IDLE;
        }
    }

    //if(IsKey(KEY_INPUT_W))
    //    dir = {0, 180, -90};

    //if(IsKey(KEY_INPUT_S))
    //    dir = {0, 0, 90};

    //if(IsKey(KEY_INPUT_D))
    //    dir = {-90, 270, 0};

    //if(IsKey(KEY_INPUT_A))
    //    dir = {90, 90, 0};
    //float max_dir = 10000.0f;    //一番遠くに距離のの初期値を置くを置く
    //for(auto obj_ : Scene::Object::GetArray<Animal>()) {
    //    // ここに来る場合 obj がEnemyクラスということが保証されます。
    //    // nameは、必ず存在するため、オブジェクトの名前を取得できます。
    //    auto name        = obj_->GetName();
    //    auto get_obj_pos = obj_->GetTranslate();
    //    auto get_npc_pos = float3{pos_npc_.x, pos_npc_.y + 18.0f, pos_npc_.z};
    //    dis              = get_obj_pos - get_npc_pos;
    //    float dir        = sqrtf(dis.x * dis.x + dis.y * dis.y + dis.z * dis.z);
    //    if(dir < max_dir) {
    //        max_dir = dir;

    //        Get_obj2 = obj_;
    //    }
    //}
}
void Player_Rise::Draw()
{
    //float3 Get_pos = GetTranslate();

    //float3 pos_XZ = {Get_pos.x, 0.0f, Get_pos.z};
    //int    color  = GetColor(255, 255, 255);

    //float3 pos1 = Get_pos;
    //float3 pos2 = Get_obj2->GetTranslate();
    //DrawSphere3D(cast(pos1), 5.0f, 100, GetColor(255, 255, 255), GetColor(255, 255, 255), TRUE);
    //DrawSphere3D(cast(pos2), 6.0f, 100, GetColor(255, 255, 255), GetColor(255, 255, 255), TRUE);
    //pos1.y = 0.0f;
    //pos2.y = 0.0f;

    //float x        = pos1.x - pos2.x;
    //float y        = pos1.y - pos2.y;
    //float z        = pos1.z - pos2.z;
    //float distance = sqrtf(x * x + y * y + z * z);
    //float radius   = 35.0f + 7.0f;

    ////	１：２つのベクトルを用意
    ////	プレイヤーの前方向のベクトル（内積から角度を求めたいので長さを 1.0 に）
    //float3 front;
    //front.x = 1.0f * sinf((dir.y * 3.14159265f / 180.0f));
    //front.z = 1.0f * cosf((dir.y * 3.14159265f / 180.0f));

    ////	プレイヤーから見てＮＰＣがどの方向にいるかのベクトル
    //float3 target = pos2 - pos1;
    ////	ベクトルの正規化（ベクトルの長さを 1.0 に）

    //float length = sqrtf(target.x * target.x + target.z * target.z);
    //if(length > 0.0f) {
    //    target.x = target.x / length;
    //    target.z = target.z / length;
    //}
    ////	２：２つのベクトルの内積を取得
    //float front_dot = front.x * target.x + front.z * target.z;
    ///*  GetFloat2Dot(front, target);*/

    ////	３：求めた内積の値から角度を求める
    ////	この内積の値（ front_dot ）を acos 関数に渡すことで角度を取得できます
    ////	acosf：アークコサイン関数（ cos 関数の逆関数）← ラジアン角が返ってきます
    //float radian = acosf(front_dot);
    ////	ラジアン角を角度の「度」にします
    //float degree = radian * 180.0f / 3.14159265f;

    //if(distance <= radius && degree < 25.0f) {
    //    color = GetColor(0, 255, 255);
    //}
    //else {
    //    color = GetColor(255, 255, 255);
    //}
    //float3 line1;
    //line1.x = pos_XZ.x + 40.0f * sinf((dir.y + 25.0f) * 3.141592f / 180.0f);
    //line1.z = pos_XZ.z + 40.0f * cosf((dir.y + 25.0f) * 3.141592f / 180.0f);
    //DrawLine3D(cast(pos_XZ), cast(line1), color);
    //float3 line2;
    //line2.x = pos_XZ.x + 40.0f * sinf((dir.y - 25.0f) * 3.141592f / 180.0f);
    //line2.z = pos_XZ.z + 40.0f * cosf((dir.y - 25.0f) * 3.141592f / 180.0f);
    //DrawLine3D(cast(pos_XZ), cast(line2), color);
}
void Player_Rise::OnHit(const ComponentCollision::HitInfo& hit_info)
{
    Super::OnHit(hit_info);

    float max_dir = 10000.0f;    //一番遠くに距離のの初期値を置くを置く
                                 //一番近くのオブジェクトの保管

    //すべて見て行って一番近くのオブジェクトを取得
    if(IsKeyOn(KEY_INPUT_Q) && _isholding == IDLE) {
        for(auto obj_ : Scene::Object::GetArray<Animal>()) {
            // ここに来る場合 obj がEnemyクラスということが保証されます。
            // nameは、必ず存在するため、オブジェクトの名前を取得できます。
            //if(Get_obj == nullptr) {
            auto name        = obj_->GetName();
            auto get_obj_pos = obj_->GetTranslate();
            auto get_npc_pos = float3{pos_npc_.x, pos_npc_.y + 18.0f, pos_npc_.z};
            dis              = get_obj_pos - get_npc_pos;
            float dir        = sqrtf(dis.x * dis.x + dis.y * dis.y + dis.z * dis.z);
            if(dir < max_dir) {
                max_dir = dir;

                Get_obj = obj_;
            }
            //  }
        }
        auto get_pickup_com = GetComponent<Pickup>();
        if(get_pickup_com->Check_Pickup() == true) {
            _isholding = HOLDING;
        }
    }

    auto& obj = Get_obj;    //一番近くのオブジェクトを取得

    //IDLE状態のときPキー押した時HOLDING状態にする

    //もしnpcの状態がHOLDING状態なら一番近くで当たってるものをHOLDING状態にする
    if(_isholding == HOLDING) {
        for(auto obj_ : Scene::Object::GetArray<Animal>()) {
            if(Get_obj == obj_) {
                obj_->Cone_Mode = HOLDING;
                obj_->SetTranslate({pos_npc_.x, pos_npc_.y + 18.0f, pos_npc_.z});
            }
        }
    }
    //HOLDING状態のときOキー押した時THROWING状態にする
    if(IsKeyOn(KEY_INPUT_E) && _isholding == HOLDING) {
        _isholding = THROWING;
        if(_isholding == THROWING) {
            for(auto obj_ : Scene::Object::GetArray<Animal>()) {
                if(Get_obj == obj_) {
                    obj_->Cone_Mode = THROWING;
                }
            }
        }
    }
    //IDLE状態のときオブジェクトを移動するのをやめさせる
    if(obj) {
        if(obj->Cone_Mode == IDLE) {
            obj->SetDirectior(0 * 15);
        }
    }

    //THROWING状態のとき投げる処理
    if(_isholding == THROWING) {
        if(obj->Cone_Mode == THROWING) {
            obj->SetTranslate(GetTranslate() + float3{0, 18.0f, 0});
            auto modelrot = GetComponent<ComponentModel>();
            auto dir      = -modelrot->GetWorldMatrix().axisZ();
            if(IsKeyOn(KEY_INPUT_E)) {
                auto throw_direction  = dir;
                throw_direction.y    += 3.0f;
                obj->AddTranslate(throw_direction * 3.0f);
            }
            //obj->SetDirectior(dir * 1.0f);
            _isholding = IDLE;
            Get_obj    = nullptr;
        }
    }
}
}    // namespace Game01
