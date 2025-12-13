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
#include <Game/Component/State/StateThorw.h>
#include "Hp.h"

namespace Game01 {
//float3    dir{0, 0, 0};
//AnimalPtr Get_obj2 = nullptr;    //一番近くのオブジェクトの保管
AnimalPtr Get_obj = nullptr;
int       effect;
int       heal_effect;    //回復
int       run_effect;     //超加速

bool Player_Rise::Init()
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
    player_name = RISE;

    //エフェクトの初期化

    effect = LoadEffekseerEffect("data/effects/00_Version16/Barrior01.efkefc");

    heal_effect = LoadEffekseerEffect("data/effects/01_NextSoft01/Heal.efkefc");

    run_effect = LoadEffekseerEffect("data/effects/01_Pierre01/run.efkefc");

    AddComponent<ComponentGameCamera>();
    //AddComponent<Pickup>();
    AddComponent<StateIdleWalk>();

    return true;
}

void Player_Rise::Update()
{
    Super::Update();
    // StateThorw::ThorwUpdate(_isholding);

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

    static int h    = -1;
    static int heal = -1;    //回復
    static int run  = -1;    //超加速

    static float3 pos;

    //Zキー：無敵化
    if(Input::IsKeyDown(KEY_INPUT_Z)) {
        h = PlayEffekseer3DEffect(effect);
    }

    pos = GetTranslate();
    SetPosPlayingEffekseer3DEffect(h, pos.x, pos.y + 1.0f, pos.z);
    SetScalePlayingEffekseer3DEffect(h, 2.5f, 4.0f, 2.5f);

    //Xキー：回復
    if(Input::IsKeyDown(KEY_INPUT_X)) {
        heal = PlayEffekseer3DEffect(heal_effect);
    }
    pos = GetTranslate();
    SetPosPlayingEffekseer3DEffect(heal, pos.x, pos.y + 1.0f, pos.z);
    SetScalePlayingEffekseer3DEffect(heal, 3.0f, 3.0f, 3.0f);

    //Xキー：回復
    static int run_frame;
    if(Input::IsKeyDown(KEY_INPUT_I) && run_frame == 0 || Input::IsKeyDown(KEY_INPUT_O) && run_frame == 0) {
        run       = PlayEffekseer3DEffect(run_effect);
        run_frame = 60;
    }
    run_frame--;
    run_frame = max(0, run_frame);
    if(run_frame == 0) {
        StopEffekseer3DEffect(run);
    }
    pos = GetTranslate();
    SetPosPlayingEffekseer3DEffect(run, pos.x, pos.y + 1.0f, pos.z);
    SetScalePlayingEffekseer3DEffect(run, 3.0f, 3.0f, 3.0f);

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
}

void Player_Rise::OnHit(const ComponentCollision::HitInfo& hit_info)
{
    Super::OnHit(hit_info);
    auto hit_owner_name = hit_info.hit_collision_->GetOwner();
    for(auto obj_ : Scene::Object::GetArray<Animal>()) {
        if(obj_->GetName() == hit_owner_name->GetName()) {
            if(obj_->Cone_Mode == THROWING) {
                if(obj_->who_throwing != Game01::Animal::RISE && obj_->who_throwing != Game01::Animal::NOBODY) {
                    obj_->Cone_Mode        = Game01::Animal::DEATH;
                    auto Hp_get            = Scene::Object::Get<Hp>();
                    Hp_get->Hp_count_rise -= 1;
                }
            }
        }
    }
}

}    // namespace Game01
