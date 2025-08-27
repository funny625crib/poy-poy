#include "Player_betty.h"
#include "Animal.h"
#include <DxLib.h>
#include <System/Component/ComponentModel.h>
#include <System/Component/ComponentCollisionModel.h>
#include <System/Component/ComponentCollisionCapsule.h>
#include <System/Component/ComponentObjectController.h>
#include <Game/Component/ComponentGameCamera.h>
#include <Game/Component/State/StateIdleWalk.h>
#include <Game/Component/State/StateJump.h>
#include <System/Component/ComponentCollisionSphere.h>
namespace Game01 {
bool Player_Betty::Init()
{
    Super::Init();

    // プレイヤー
    SetName("Player Betty");
    SetTranslate({0.0f, 5.0f, -50.0f});
    SetRotationAxisXYZ({0.0f, 180.0f, 0.0f});

    auto col = AddComponent<ComponentCollisionCapsule>();    //
    col->SetRadius(4.53f);
    col->SetHeight(16.81f);
    col->UseGravity();
    col->SetCollisionGroup(ComponentCollision::CollisionGroup::PLAYER);

    auto model      = AddComponent<ComponentModel>("data/Sample/Player/Betty/Betty.mv1");
    model->Matrix() = matrix::scale(0.8f);
    model->SetAnimation({
        {"idle",    "data/Sample/Player/Betty/Anim/Idle.mv1", 0, 1.0f},
        {"walk", "data/Sample/Player/Betty/Anim/Walking.mv1", 0, 1.0f},
        {"jump",    "data/Sample/Player/Betty/Anim/Jump.mv1", 0, 1.0f},
        { "run",     "data/Sample/Player/Betty/Anim/Run.mv1", 0, 1.0f},
    });
    //model->SetScaleAxisXYZ( { 1, 1, 1 } );
    model->PlayAnimation("idle", true);

    AddComponent<ComponentGameCamera>();
    // AddComponent<StateIdleWalk>();
    return true;
}

void Player_Betty::Update()
{
    Super::Update();
    pos_npc_ = GetTranslate();
    // ジャンプしていて、アニメーションが一定数値以上ならば、慣性の法則にしたがって上に移動させる
}
void Player_Betty::OnHit(const ComponentCollision::HitInfo& hit_info)
{
    Super::OnHit(hit_info);

    float     max_dir = 100.0f;     //一番遠くに距離のの初期値を置くを置く
    AnimalPtr Get_obj = nullptr;    //一番近くのオブジェクトの保管

    //すべて見て行って一番近くのオブジェクトを取得
    for(auto obj_ : Scene::Object::GetArray<Animal>()) {
        // ここに来る場合 obj がEnemyクラスということが保証されます。
        // nameは、必ず存在するため、オブジェクトの名前を取得できます。
        auto name        = obj_->GetName();
        auto get_obj_pos = obj_->GetTranslate();
        auto get_npc_pos = float3{pos_npc_.x, pos_npc_.y + 18.0f, pos_npc_.z};
        dis              = get_obj_pos - get_npc_pos;
        float dir        = sqrtf(dis.x * dis.x + dis.y * dis.y + dis.z * dis.z);
        if(dir < max_dir) {
            max_dir = dir;
            Get_obj = obj_;
        }
    }

    auto& obj     = Get_obj;                                              //一番近くのオブジェクトを取得
    auto  Get_col = Get_obj->GetComponent<ComponentCollisionSphere>();    //重力を帰るために必要
    printfDx("HIT: %s\n", Get_obj->GetName().data());
    auto hit_owner_name2 = hit_info.hit_collision_->GetOwner()->GetNameDefault();    //npcがあたっているものの名前を取得
    //printfDx("HIT: %s\n", hit_info.hit_collision_->GetOwner()->GetName().data());
    //地面に当たっているobjをIDLE状態にする
    if(hit_owner_name2 == "Ground") {
        for(auto obj_ : Scene::Object::GetArray<Animal>()) {
            if(Get_obj != obj_) {
                //obj_->Cone_Mode = IDLE;
            }
        }
    }
    //もしnpcの状態がHOLDING状態なら一番近くで当たってるものをHOLDING状態にする
    if(_isholding == HOLDING) {
        for(auto obj_ : Scene::Object::GetArray<Animal>()) {
            if(Get_obj == obj_) {
                obj_->Cone_Mode = HOLDING;
            }
        }
    }
    //もしnpcの状態がTHROWING状態なら一番近くで当たってるものをTHROWING状態にする
    if(_isholding == THROWING) {
        for(auto obj_ : Scene::Object::GetArray<Animal>()) {
            if(Get_obj == obj_) {
                obj_->Cone_Mode = THROWING;
            }
        }
    }
    //IDLE状態のときPキー押した時HOLDING状態にする
    if(IsKeyOn(KEY_INPUT_P) && _isholding == IDLE) {
        if(hit_owner_name2 == "Animal") {
            _isholding = HOLDING;
        }
    }
    //HOLDING状態のときOキー押した時THROWING状態にする
    if(IsKeyOn(KEY_INPUT_O) && _isholding == HOLDING) {
        _isholding = THROWING;
    }
    //IDLE状態のときオブジェクトを移動するのをやめさせる
    if(obj->Cone_Mode == IDLE) {
        obj->SetDirectior(0 * 15);
    }
    //HOLDING状態のとき重力をなくす
    if(_isholding == HOLDING) {
        if(obj->Cone_Mode == HOLDING) {
            if(Get_col) {
                Get_col->UseGravity(false);
            }
        }
        up_obj = true;
    }
    //THROWING状態のとき投げる処理
    if(_isholding == THROWING) {
        if(obj->Cone_Mode == THROWING) {
            obj->SetTranslate(GetTranslate() + float3{0, 18.0f, 0});
            auto model = GetComponent<ComponentModel>();
            auto dir   = -model->GetWorldMatrix().axisZ();
            obj->SetDirectior(dir * 1.0f);
            if(Get_col) {
                Get_col->UseGravity(true);
            }
            up_obj = false;

            _isholding = IDLE;
        }
    }
    //up_obj==true状態のときnpcの頭上に置く
    if(up_obj == true) {
        for(auto obj_ : Scene::Object::GetArray<Animal>()) {
            if(obj_->Cone_Mode == HOLDING)
                obj_->SetTranslate({pos_npc_.x, pos_npc_.y + 18.0f, pos_npc_.z});
        }
    }
}
}    // namespace Game01
