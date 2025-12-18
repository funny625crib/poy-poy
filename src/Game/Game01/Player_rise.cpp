#include "Player_rise.h"
#include "Animal.h"
#include <DxLib.h>
#include <System/Component/ComponentModel.h>
#include <System/Component/ComponentCollisionModel.h>
#include <System/Component/ComponentCollisionCapsule.h>
#include <System/Component/ComponentObjectController.h>
#include <System/Component/ComponentCollisionSphere.h>
#include <Game/Component/ComponentGameCamera.h>
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
int       heal_effect;           //回復
int       run_effect;            //超加速
int       power_up_effect;       //怪力
int       threatening_effect;    //威嚇

bool Player_Rise::Init()
{
    Super::Init();

    // プレイヤー
    SetName("Player Rise");
    SetTranslate({-87.0f, -6.0f, 47.0f});
    auto col = AddComponent<ComponentCollisionCapsule>();
    col->SetRadius(4.53f);
    col->SetHeight(16.81f);
    col->UseGravity();
    col->SetCollisionGroup(ComponentCollision::CollisionGroup::PLAYER);

    auto model      = AddComponent<ComponentModel>("data/Sample/Player/Rise_school/Rise.mv1");
    model->Matrix() = matrix::scale(0.9f);
    model->SetAnimation({
        {       "idle",        "data/Sample/Player/Rise_school/Anim/Idle.mv1", 0, 1.0f},
        {       "walk",     "data/Sample/Player/Rise_school/Anim/Walking.mv1", 0, 1.0f},
        {       "jump",        "data/Sample/Player/Rise_school/Anim/Jump.mv1", 0, 1.0f},
        {        "run",         "data/Sample/Player/Rise_school/Anim/Run.mv1", 0, 1.0f},
        {       "heal",  "data/Sample/Player/Rise_school/Anim/Magic Heal.mv1", 0, 1.0f},
        {     "defend",      "data/Sample/Player/Rise_school/Anim/defend.mv1", 0, 1.0f},
        {"Threatening", "data/Sample/Player/Rise_school/Anim/Threatening.mv1", 0, 1.0f},
        {   "power up",    "data/Sample/Player/Rise_school/Anim/Power Up.mv1", 0, 1.0f},
    });
    //   model->SetScaleAxisXYZ( { 1, 1, 1 } );

    //エフェクトの初期化

    effect = LoadEffekseerEffect("data/effects/00_Version16/Barrior01.efkefc");

    heal_effect = LoadEffekseerEffect("data/effects/01_NextSoft01/Heal.efkefc");

    run_effect = LoadEffekseerEffect("data/effects/01_Pierre01/run.efkefc");

    power_up_effect = LoadEffekseerEffect("data/effects/01_NextSoft01/power up.efkefc");

    AddComponent<ComponentGameCamera>();
    AddComponent<Pickup>();
    AddComponent<StateIdleWalk>();
    AddComponent<StateThorw>();
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

    static int h           = -1;
    static int heal        = -1;    //回復
    static int run         = -1;    //超加速
    static int power_up    = -1;    //怪力
    static int threatening = -1;    //威嚇

    static float3 pos;
    //Zキー：無敵化
    if(Input::IsKeyDown(KEY_INPUT_Z)) {
        h = PlayEffekseer3DEffect(effect);
    }

    pos = GetTranslate();
    SetPosPlayingEffekseer3DEffect(h, pos.x, pos.y + 1.0f, pos.z);
    SetScalePlayingEffekseer3DEffect(h, 2.5f, 4.0f, 2.5f);

    auto mdl = GetComponent<ComponentModel>();

    // Xキー：回復
    if(Input::IsKeyDown(KEY_INPUT_X) && !is_healing_ && heal_frame_ == 0) {
        is_healing_ = true;
        heal_frame_ = 160;

        mdl->PlayAnimationNoSame("heal", false);
    }

    if(is_healing_) {
        if(heal_frame_ > 0) {
            --heal_frame_;
        }

        if(heal_frame_ <= 0) {
            is_healing_ = false;
            heal_frame_ = 0;
            mdl->PlayAnimationNoSame("idle", true);
            //アクション完了後アニメーションを再生する
            heal = PlayEffekseer3DEffect(heal_effect);
            //HPが増える
            auto Hp_get            = Scene::Object::Get<Hp>();
            Hp_get->Hp_count_rise += 1;
        }
    }
    pos = GetTranslate();
    SetPosPlayingEffekseer3DEffect(heal, pos.x, pos.y + 1.0f, pos.z);
    SetScalePlayingEffekseer3DEffect(heal, 3.0f, 3.0f, 3.0f);

    //Cキー：怪力
    if(Input::IsKeyDown(KEY_INPUT_C) && !ispower_up_ && power_up_frame_ == 0) {
        ispower_up_     = true;
        power_up_frame_ = 120;
        mdl->PlayAnimationNoSame("power up", false);
        power_up = PlayEffekseer3DEffect(power_up_effect);
    }
    pos = GetTranslate();
    SetPosPlayingEffekseer3DEffect(power_up, pos.x, pos.y, pos.z);
    SetScalePlayingEffekseer3DEffect(power_up, 6.0f, 6.0f, 6.0f);
    if(ispower_up_) {
        if(power_up_frame_ > 0) {
            --power_up_frame_;
        }

        if(power_up_frame_ <= 0) {
            ispower_up_     = false;
            power_up_frame_ = 0;
            mdl->PlayAnimationNoSame("idle", true);
        }
    }

    //Vキー：威嚇
    if(Input::IsKeyDown(KEY_INPUT_V) && !isthreatening_ && threatening_frame_ == 0) {
        isthreatening_     = true;
        threatening_frame_ = 120;
        mdl->PlayAnimationNoSame("Threatening", false);
    }

    if(isthreatening_) {
        if(threatening_frame_ > 0) {
            --threatening_frame_;
        }

        if(threatening_frame_ <= 0) {
            isthreatening_     = false;
            threatening_frame_ = 0;
            mdl->PlayAnimationNoSame("idle", true);
        }
    }

    //IキーとOキー：超加速
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

    bool using_skill = is_healing_ || ispower_up_ || isthreatening_;

    if(using_skill) {
        StartSkillCamera();
    }
    else {
        EndSkillCamera();
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

//void Player_Rise::OnHit(const ComponentCollision::HitInfo& hit_info)
//{
//    Super::OnHit(hit_info);
//
//    //float max_dir = 10000.0f;    //一番遠くに距離のの初期値を置くを置く
//    //                             //一番近くのオブジェクトの保管
//
//    ////すべて見て行って一番近くのオブジェクトを取得
//    //if(IsKeyOn(KEY_INPUT_Q) && _isholding == IDLE) {
//    //    for(auto obj_ : Scene::Object::GetArray<Animal>()) {
//    //        // ここに来る場合 obj がEnemyクラスということが保証されます。
//    //        // nameは、必ず存在するため、オブジェクトの名前を取得できます。
//    //        //if(Get_obj == nullptr) {
//    //        auto name        = obj_->GetName();
//    //        auto get_obj_pos = obj_->GetTranslate();
//    //        auto get_npc_pos = float3{pos_npc_.x, pos_npc_.y + 18.0f, pos_npc_.z};
//    //        dis              = get_obj_pos - get_npc_pos;
//    //        float dir        = sqrtf(dis.x * dis.x + dis.y * dis.y + dis.z * dis.z);
//    //        if(dir < max_dir) {
//    //            max_dir = dir;
//
//    //            Get_obj = obj_;
//    //        }
//    //    }
//    //    auto get_pickup_com = GetComponent<Pickup>();
//    //    if(get_pickup_com->Check_Pickup() == true) {
//    //        _isholding = HOLDING;
//    //    }
//    //}
//
//    //auto& obj = Get_obj;    //一番近くのオブジェクトを取得
//
//    ////IDLE状態のときPキー押した時HOLDING状態にする
//
//    ////もしnpcの状態がHOLDING状態なら一番近くで当たってるものをHOLDING状態にする
//    //if(_isholding == HOLDING) {
//    //    for(auto obj_ : Scene::Object::GetArray<Animal>()) {
//    //        if(Get_obj == obj_) {
//    //            obj_->Cone_Mode = HOLDING;
//    //            obj_->SetTranslate({pos_npc_.x, pos_npc_.y + 18.0f, pos_npc_.z});
//    //            // ★ 追加: プレイヤーの前方向に動物モデルの向きを一発で合わせる
//    //            if(auto pModel = GetComponent<ComponentModel>()) {
//    //                const auto forward = -pModel->GetWorldMatrix().axisZ();    // 投げ処理と同じ基準
//    //                if(auto aModel = obj_->GetComponent<ComponentModel>()) {
//    //                    aModel->SetRotationToVectorWithLimit(-forward, 999.0f);    // 即時に向きを一致
//    //                }
//    //            }
//    //        }
//    //    }
//    //}
//    ////HOLDING状態のときOキー押した時THROWING状態にする
//    //if(IsKeyOn(KEY_INPUT_E) && _isholding == HOLDING) {
//    //    _isholding = THROWING;
//    //    if(_isholding == THROWING) {
//    //        for(auto obj_ : Scene::Object::GetArray<Animal>()) {
//    //            if(Get_obj == obj_) {
//    //                obj->SetTranslate(GetTranslate() + float3{0, 18.0f, 0});
//    //                auto modelrot = GetComponent<ComponentModel>();
//    //                auto dir      = -modelrot->GetWorldMatrix().axisZ();
//    //                obj->SetDirectior(dir);
//    //                obj_->Cone_Mode    = THROWING;
//    //                obj_->who_throwing = Game01::Animal::RISE;
//    //                obj_->Game01::Animal::Throw();
//    //            }
//    //        }
//    //    }
//    //}
//    ////IDLE状態のときオブジェクトを移動するのをやめさせる
//    //if(obj) {
//    //    if(obj->Cone_Mode == IDLE) {
//    //        _isholding = IDLE;
//    //        Get_obj    = nullptr;
//    //    }
//    //}
//    //// Super::OnHit(hit_info);
//    //auto hit_owner_name = hit_info.hit_collision_->GetOwner()->GetNameDefault();
//
//    //for(auto obj_ : Scene::Object::GetArray<Animal>()) {
//    //    if(obj_->Cone_Mode == THROWING) {
//    //        if(hit_owner_name == "Animal") {
//    //            // printfDx("%s\n", obj_->GetName());
//    //        }
//    //    }
//    //}
//}
void Player_Rise::OnHit(const ComponentCollision::HitInfo& hit_info)
{
    Super::OnHit(hit_info);
    auto hit_owner_name = hit_info.hit_collision_->GetOwner();
    //for(auto obj_ : Scene::Object::GetArray<Animal>()) {
    //    if(obj_->GetName() == hit_owner_name->GetName()) {
    //        if(obj_->Cone_Mode == THROWING) {
    //            if(obj_->who_throwing != Game01::Animal::BETTY) {
    //                //ここに当たったら
    //            }
    //        }
    //    }
    //}

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

void Game01::Player_Rise::StartSkillCamera()
{
    // すでにスキル用カメラになっている場合は何もしない
    if(is_skill_camera_) {
        return;
    }

    auto cam = GetComponent<ComponentGameCamera>();
    auto mdl = GetComponent<ComponentModel>();
    if(!cam || !mdl) {
        return;
    }

    // スキルカメラ中フラグ ON
    is_skill_camera_ = true;

    // スキル開始前のカメラ位置と注視点を保存しておく
    skill_cam_old_pos_    = cam->GetPosition();
    skill_cam_old_target_ = cam->GetTarget();

    // -----------------------------
    // プレイヤーの正面から見るカメラにする
    // -----------------------------
    // プレイヤーの現在位置（ワールド座標）
    float3 player_pos = GetTranslate();

    // モデルのワールド行列から「前方向ベクトル」を取得
    auto mat = mdl->GetWorldMatrix();
    // この forward が「プレイヤーの前方向」
    // もしカメラが後ろ側に来てしまう場合は、
    // 下の - を消して = mat.axisZ(); にして試してみてください。
    float3 forward = -mat.axisZ();

    // カメラの距離・高さ・注視点の高さ
    const float cam_dist       = 30.0f;    // プレイヤーからどれくらい離すか
    const float cam_height     = 15.0f;    // カメラをどれくらい上に上げるか
    const float look_at_height = 8.5f;     // どの高さを注視するか（顔あたり）

    // カメラ位置：プレイヤーの前方向に cam_dist 離して、少し上にオフセット
    float3 cam_pos = {
        player_pos.x + forward.x * cam_dist,
        player_pos.y + forward.y * cam_dist + cam_height,
        player_pos.z + forward.z * cam_dist,
    };

    // 注視点：プレイヤーの少し上（顔のあたり）を見る
    float3 look_at  = player_pos;
    look_at.y      += look_at_height;

    cam->SetPositionAndTarget(cam_pos, look_at);
}

void Game01::Player_Rise::EndSkillCamera()
{
    // スキル用カメラでない場合は何もしない
    if(!is_skill_camera_) {
        return;
    }

    auto cam = GetComponent<ComponentGameCamera>();
    if(cam) {
        // 保存しておいた位置と注視点に戻す
        cam->SetPositionAndTarget(skill_cam_old_pos_, skill_cam_old_target_);
    }

    // 通常カメラに戻ったのでフラグ OFF
    is_skill_camera_ = false;
}
