#include "Animal_Pickup.h"
#include "Animal.h"
#include <Game/Game01/time_bomb.h>
namespace Game01 {
float3 dir{0, 0, 0};

float3 pos_npc_;

float3 pos_XZ;
float  r     = 35.0f;
int    color = GetColor(255, 255, 255);
void   Pickup::Init()
{
    __super::Init();

    // カメラオブジェクト
    //auto camera = Scene::Object::Create<Object>();
}

void Pickup::Update()
{
    __super::Update();
    auto         owner          = GetOwner();
    AnimalPtr    Get_obj_animal = nullptr;
    Time_bombPtr Get_obj_boms   = nullptr;

    set_obj_       = NOOBJ;
    float3 Get_pos = owner->GetTranslate();
    float  max_dir = 10000.0f;    //一番遠くに距離のの初期値を置くを置く
    for(auto obj_ : Scene::Object::GetArray<Animal>()) {
        // ここに来る場合 obj がEnemyクラスということが保証されます。
        // nameは、必ず存在するため、オブジェクトの名前を取得できます。
        auto   name        = obj_->GetName();
        auto   get_obj_pos = obj_->GetTranslate();
        auto   get_npc_pos = float3{Get_pos.x, Get_pos.y + 18.0f, Get_pos.z};
        float3 dis         = get_obj_pos - get_npc_pos;
        float  dir         = sqrtf(dis.x * dis.x + dis.y * dis.y + dis.z * dis.z);
        if(dir < max_dir) {
            max_dir        = dir;
            set_obj_       = ANIMAL;
            Get_obj_animal = obj_;
        }
    }
    for(auto obj_boms_ : Scene::Object::GetArray<Game01::Time_bomb>()) {
        // ここに来る場合 obj がEnemyクラスということが保証されます。
        // nameは、必ず存在するため、オブジェクトの名前を取得できます。
        auto   name        = obj_boms_->GetName();
        auto   get_obj_pos = obj_boms_->GetTranslate();
        auto   get_npc_pos = float3{Get_pos.x, Get_pos.y + 18.0f, Get_pos.z};
        float3 dis         = get_obj_pos - get_npc_pos;
        float  dir         = sqrtf(dis.x * dis.x + dis.y * dis.y + dis.z * dis.z);
        if(dir < max_dir) {
            max_dir      = dir;
            set_obj_     = BOMS;
            Get_obj_boms = obj_boms_;
        }
    }

    //for(auto obj_boms_ : Scene::Object::GetArray<Game01::Time_bomb>()) {
    //    for(auto obj_ : Scene::Object::GetArray<Game01::Animal>()) {
    //        // ここに来る場合 obj がEnemyクラスということが保証されます。
    //        // nameは、必ず存在するため、オブジェクトの名前を取得できます。
    //        //if(Get_obj == nullptr) {
    //        auto   get_bom_pos           = obj_boms_->GetTranslate();
    //        auto   get_obj_pos           = obj_->GetTranslate();
    //        auto   get_npc_pos           = float3{pos_npc_.x, pos_npc_.y + 18.0f, pos_npc_.z};
    //        float3 dis_character_animal_ = get_obj_pos - get_npc_pos;
    //        float3 dis_character_Boms_   = get_bom_pos - get_npc_pos;
    //        float  dir                   = sqrtf(dis_character_animal_.x * dis_character_animal_.x + dis_character_animal_.y * dis_character_animal_.y +
    //                          dis_character_animal_.z * dis_character_animal_.z);
    //        float  dir2                  = sqrtf(dis_character_Boms_.x * dis_character_Boms_.x + dis_character_Boms_.y * dis_character_Boms_.y +
    //                           dis_character_Boms_.z * dis_character_Boms_.z);
    //        if(dir2 < max_dir) {
    //            max_dir        = dir2;
    //            Get_obj_animal = nullptr;
    //            Get_obj_boms   = obj_boms_;
    //        }
    //        if(dir < max_dir) {
    //            max_dir        = dir;
    //            Get_obj_animal = obj_;
    //            Get_obj_boms   = nullptr;
    //        }
    //
    //    }
    //}
    if(IsKey(KEY_INPUT_W))
        dir = {0, 180, -90};

    if(IsKey(KEY_INPUT_S))
        dir = {0, 0, 90};

    if(IsKey(KEY_INPUT_D))
        dir = {-90, 270, 0};

    if(IsKey(KEY_INPUT_A))
        dir = {90, 90, 0};

    pos_XZ = {Get_pos.x, 0.0f, Get_pos.z};

    float3 pos1 = Get_pos;
    float3 pos2;
    if(Get_obj_animal != nullptr && set_obj_ == ANIMAL)
        pos2 = Get_obj_animal->GetTranslate();
    float3 pos3;
    if(Get_obj_boms != nullptr && set_obj_ == BOMS)
        pos3 = Get_obj_boms->GetTranslate();

    pos1.y = 0.0f;
    pos2.y = 0.0f;
    pos3.y = 0.0f;

    float x = pos1.x - pos2.x;
    float y = pos1.y - pos2.y;
    float z = pos1.z - pos2.z;

    float x_bom = pos1.x - pos3.x;
    float y_bom = pos1.y - pos3.y;
    float z_bom = pos1.z - pos3.z;

    float distance  = sqrtf(x * x + y * y + z * z);
    float distance2 = sqrtf(x_bom * x_bom + y_bom * y_bom + z_bom * z_bom);

    float radius = 40.0f + 7.0f;

    //	１：２つのベクトルを用意
    //	プレイヤーの前方向のベクトル（内積から角度を求めたいので長さを 1.0 に）
    float3 front;
    front.x = 1.0f * sinf((dir.y * 3.14159265f / 180.0f));
    front.z = 1.0f * cosf((dir.y * 3.14159265f / 180.0f));

    //	プレイヤーから見てＮＰＣがどの方向にいるかのベクトル
    float3 target     = pos2 - pos1;
    float3 target_bom = pos3 - pos1;

    //	ベクトルの正規化（ベクトルの長さを 1.0 に）

    float length     = sqrtf(target.x * target.x + target.z * target.z);
    float length_bom = sqrtf(target_bom.x * target_bom.x + target_bom.z * target_bom.z);

    if(length > 0.0f) {
        target.x = target.x / length;
        target.z = target.z / length;
    }
    if(length_bom > 0.0f) {
        target_bom.x = target_bom.x / length_bom;
        target_bom.z = target_bom.z / length_bom;
    }
    //	２：２つのベクトルの内積を取得
    float front_dot     = front.x * target.x + front.z * target.z;
    float front_dot_bom = front.x * target_bom.x + front.z * target_bom.z;

    /*  GetFloat2Dot(front, target);*/

    //	３：求めた内積の値から角度を求める
    //	この内積の値（ front_dot ）を acos 関数に渡すことで角度を取得できます
    //	acosf：アークコサイン関数（ cos 関数の逆関数）← ラジアン角が返ってきます
    float radian     = acosf(front_dot);
    float radian_bom = acosf(front_dot_bom);
    //	ラジアン角を角度の「度」にします
    float degree     = radian * 180.0f / 3.14159265f;
    float degree_bom = radian_bom * 180.0f / 3.14159265f;

    if(set_obj_ == BOMS && distance2 <= radius && degree_bom < r) {
        color = GetColor(0, 255, 0);
        check = true;
    }
    else if(distance <= radius && set_obj_ == ANIMAL && degree < r) {
        color = GetColor(0, 255, 255);
        check = true;
    }
    else {
        check = false;
        color = GetColor(255, 255, 255);
    }
}
void Pickup::Draw()
{
    float3 line1;
    line1.x = pos_XZ.x + 40.0f * sinf((dir.y + r) * 3.141592f / 180.0f);
    line1.z = pos_XZ.z + 40.0f * cosf((dir.y + r) * 3.141592f / 180.0f);
    DrawLine3D(cast(pos_XZ), cast(line1), color);
    float3 line2;
    line2.x = pos_XZ.x + 40.0f * sinf((dir.y - r) * 3.141592f / 180.0f);
    line2.z = pos_XZ.z + 40.0f * cosf((dir.y - r) * 3.141592f / 180.0f);
    DrawLine3D(cast(pos_XZ), cast(line2), color);
}
bool Pickup::Check_Pickup()
{
    return check;
}
}    // namespace Game01
