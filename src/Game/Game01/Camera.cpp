#include "Camera.h"
#include <System/Component/ComponentModel.h>
#include <System/Component/ComponentCollisionModel.h>
#include <System/Component/ComponentSpringArm.h>
#include "Player_rise.h"
#include "Player_betty.h"
#include "Player_abigail.h"
#include "Player_sol.h"
#include <array>
#include <algorithm>
#include <cmath>
namespace Game01 {
bool Camera::Init()
{
    __super::Init();

    // カメラオブジェクト
    //auto camera = Scene::Object::Create<Object>();
    SetName("Camera");
    auto cam = AddComponent<ComponentCamera>();
    cam->SetPositionAndTarget({-49.9f, 98.0f, 199.5f}, {-50.3f, -23.0f, -3.30f});

    return true;
}

void Camera::Update()
{
    Super::Update();
    //4人のプレイヤー位置を格納する配列
    std::array<float3, 4> playerPositions{};
    //各プレイヤーの位置を取得して配列に格納
    auto rise          = Scene::Object::Get<Player_Rise>();    //riseのオブジェクトを取得
    playerPositions[0] = rise->GetTranslate();                 //riseの位置を取得

    auto betty         = Scene::Object::Get<Player_Betty>();    //bettyのオブジェクトを取得
    playerPositions[1] = betty->GetTranslate();                 //bettyの位置を取得

    auto abigail       = Scene::Object::Get<Player_Abigail>();    //abigailのオブジェクトを取得
    playerPositions[2] = abigail->GetTranslate();                 //abigailの位置を取得

    auto sol           = Scene::Object::Get<Player_Sol>();    //solのオブジェクトを取得
    playerPositions[3] = sol->GetTranslate();                 //solの位置を取得

    //4人のプレイヤー位置を使ってカメラ更新
    cameraUpdate(playerPositions);
}
void Camera::cameraUpdate(const std::array<float3, 4>& playerPositions)
{
    float3 center{0, 0, 0};
    int    validCount = 0;

    float minX = FLT_MAX, minZ = FLT_MAX;
    float maxX = -FLT_MAX, maxZ = -FLT_MAX;

    for(const auto& p : playerPositions) {
        // 無効（未取得）の判定。ここでは全成分0を無効扱い
        if(p.x == 0.0f && p.y == 0.0f && p.z == 0.0f)
            continue;
        center += p;
        ++validCount;

        minX = min(minX, p.x);
        minZ = min(minZ, p.z);
        maxX = max(maxX, p.x);
        maxZ = max(maxZ, p.z);
    }

    if(validCount == 0) {
        // プレイヤーが一人もいなければ何もしない
        return;
    }

    // 平均位置を計算
    center /= static_cast<float>(validCount);

    // XZ平面での最大スパン（全員を収める目安）
    float spanX   = (maxX > -FLT_MAX && minX < FLT_MAX) ? (maxX - minX) : 0.0f;
    float spanZ   = (maxZ > -FLT_MAX && minZ < FLT_MAX) ? (maxZ - minZ) : 0.0f;
    float maxSpan = std::max(spanX, spanZ);

    // 注視点を中心の「下」にオフセットする（下方向に5.0f）
    const float lookDownOffset = 5.0f;
    float3      desiredTarget  = center - float3{0.0f, lookDownOffset, 0.0f};

    // 自動ズーム（AABBの最大スパンに応じてカメラ後方距離を調整）
    const float baseHeight   = 150.0f;    // カメラの高さ（中心に対する固定オフセットY）
    const float baseDistance = 50.0f;     // 最小距離（全員近いときの距離）
    const float zoomFactor   = 1.25f;     // スパンに対して何倍の距離を取るか
    const float minDistance  = 50.0f;     // 最小クランプ
    const float maxDistance  = 220.0f;    // 最大クランプ

    float desiredZ = baseDistance + maxSpan * zoomFactor;
    desiredZ       = std::clamp(desiredZ, minDistance, maxDistance);

    // カメラ位置は中心からのオフセット（上方かつ後方）
    float3 desiredPosition = center + float3{0.0f, baseHeight, desiredZ};

    // 現在のカメラ（ComponentCamera）を取得してスムーズに移動させる
    if(auto cam = Scene::GetCurrentCamera().lock()) {
        float  lerpFactor    = 0.5f;    // 平滑係数（0:即時、1:滑らかさ最大）
        float3 currentPos    = cam->GetPosition();
        float3 currentTarget = cam->GetTarget();

        float3 newPos    = currentPos + (desiredPosition - currentPos) * lerpFactor;
        float3 newTarget = currentTarget + (desiredTarget - currentTarget) * lerpFactor;

        cam->SetPositionAndTarget(newPos, newTarget);
    }
}
}    // namespace Game01
