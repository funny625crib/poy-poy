#include "Animal_Pickup.h"
#include "Animal.h"

namespace Game01 {
float3    dir{0, 0, 0};
AnimalPtr Get_obj2 = nullptr;
float3    pos_npc_;

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
    auto owner = GetOwner();
    //  pos_npc_      = GetTranslate();
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
            max_dir = dir;

            Get_obj2 = obj_;
        }
    }
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
    float3 pos2 = Get_obj2->GetTranslate();
    //DrawSphere3D(cast(pos1), 5.0f, 100, GetColor(255, 255, 255), GetColor(255, 255, 255), TRUE);
    //DrawSphere3D(cast(pos2), 6.0f, 100, GetColor(255, 255, 255), GetColor(255, 255, 255), TRUE);
    pos1.y = 0.0f;
    pos2.y = 0.0f;

    float x        = pos1.x - pos2.x;
    float y        = pos1.y - pos2.y;
    float z        = pos1.z - pos2.z;
    float distance = sqrtf(x * x + y * y + z * z);
    float radius   = 40.0f + 7.0f;

    //	１：２つのベクトルを用意
    //	プレイヤーの前方向のベクトル（内積から角度を求めたいので長さを 1.0 に）
    float3 front;
    front.x = 1.0f * sinf((dir.y * 3.14159265f / 180.0f));
    front.z = 1.0f * cosf((dir.y * 3.14159265f / 180.0f));

    //	プレイヤーから見てＮＰＣがどの方向にいるかのベクトル
    float3 target = pos2 - pos1;
    //	ベクトルの正規化（ベクトルの長さを 1.0 に）

    float length = sqrtf(target.x * target.x + target.z * target.z);
    if(length > 0.0f) {
        target.x = target.x / length;
        target.z = target.z / length;
    }
    //	２：２つのベクトルの内積を取得
    float front_dot = front.x * target.x + front.z * target.z;
    /*  GetFloat2Dot(front, target);*/

    //	３：求めた内積の値から角度を求める
    //	この内積の値（ front_dot ）を acos 関数に渡すことで角度を取得できます
    //	acosf：アークコサイン関数（ cos 関数の逆関数）← ラジアン角が返ってきます
    float radian = acosf(front_dot);
    //	ラジアン角を角度の「度」にします
    float degree = radian * 180.0f / 3.14159265f;

    if(distance <= radius && degree < r) {
        check = true;
        color = GetColor(0, 255, 255);
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
