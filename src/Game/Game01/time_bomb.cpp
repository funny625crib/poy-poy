#include "time_bomb.h"
#include "Animal.h"
#include <DxLib.h>
#include <System/Component/ComponentModel.h>
#include <System/Component/ComponentCollisionModel.h>
#include <System/Component/ComponentCollisionCapsule.h>
#include <System/Component/ComponentObjectController.h>
#include <System/Component/ComponentCollisionSphere.h>
#include <Game/Component/ComponentGameCamera.h>
#include <Game/Game01/Skills/Acceleration.h>

namespace Game01 {

int bomb_effect;

bool Time_bomb::Init()
{
    Super::Init();

    Bomb_Mode = NOTHING;

    // プレイヤー
    SetName("Time bomb");
    SetTranslate({-87.0f, 26.0f, 57.0f});
    auto col = AddComponent<ComponentCollisionCapsule>();    //
    col->SetRadius(5.53f);
    col->SetHeight(5.81f);
    col->UseGravity();
    col->SetCollisionGroup(ComponentCollision::CollisionGroup::ITEM);

    auto model      = AddComponent<ComponentModel>("data/Sample/time bomb/Bomb.mv1");
    model->Matrix() = matrix::scale(0.05f);

    bomb_effect = LoadEffekseerEffect("data/effects/01_AndrewFM01/fire.efkefc");

    return true;
}

void Time_bomb::Update()
{
    Super::Update();
}

void Time_bomb::OnHit(const ComponentCollision::HitInfo& hit_info)
{
    Time_bombPtr Get_obj        = nullptr;
    auto         hit_owner_name = hit_info.hit_collision_->GetOwner()->GetNameDefault();
    auto         col            = GetComponent<ComponentCollisionCapsule>();

    if(hit_owner_name == "Ground" && Bomb_Mode != IDLE) {
        Bomb_Mode = HIT;
    }

    if(Bomb_Mode == HIT) {
        int    h   = PlayEffekseer3DEffect(bomb_effect);
        float3 pos = GetTranslate();
        SetPosPlayingEffekseer3DEffect(h, pos.x, pos.y, pos.z);
        SetScalePlayingEffekseer3DEffect(h, 4.0f, 4.0f, 4.0f);
        Bomb_Mode = IDLE;
    }
    __super::OnHit(hit_info);
}
}    // namespace Game01
