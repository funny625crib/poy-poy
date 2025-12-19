#include "arrow.h"
#include "Player_rise.h"
#include <DxLib.h>
#include <System/Component/ComponentModel.h>
#include <System/Component/ComponentCollisionModel.h>
#include <System/Component/ComponentCollisionCapsule.h>
#include <System/Component/ComponentObjectController.h>
#include <System/Component/ComponentCollisionSphere.h>
#include <Game/Component/ComponentGameCamera.h>

namespace Game01 {

bool Arrow::Init()
{
    Super::Init();

    SetName("Arrow");

    auto model      = AddComponent<ComponentModel>("data/Sample/arrow/arrow.mv1");
    model->Matrix() = matrix::scale(1.0f);

    return true;
}

void Arrow::Update()
{
    Super::Update();

    auto player = Scene::Object::Get<Game01::Player_Rise>();
    if(!player)
        return;

    // プレイヤー座標
    float3 p = player->GetTranslate();

    // 頭上オフセット
    const float head_offset = 50.0f;

    // ふわふわ上下
    static int frame = 0;
    frame++;
    float bob = sinf(frame * 0.10f) * 1.5f;    // 振幅 1.0

    arrow_pos = p + float3{0.0f, head_offset + bob, 0.0f};
    SetTranslate(arrow_pos);

    //プレイヤーの向きに合わせたい場合（前方向ベクトルを渡す）
    if(auto pMdl = player->GetComponent<ComponentModel>()) {
        float3 forward = -pMdl->GetWorldMatrix().axisZ();
        SetRotationToVector(forward);
    }
}

}    // namespace Game01
