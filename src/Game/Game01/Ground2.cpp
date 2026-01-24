#include "Ground2.h"
#include <System/Component/ComponentModel.h>
#include <System/Component/ComponentCollisionModel.h>
#include <System/Component/ComponentCollision.h>
#include <System/Component/ComponentCollisionCapsule.h>

namespace Game01 {
bool Ground2::Init()
{
    Super::Init();

    // グランド

    auto coll2 = AddComponent<ComponentCollisionCapsule>();
    coll2->SetTranslate({-12, -5, -20});
    coll2->SetHeight(20);
    coll2->SetRadius(10);
    coll2->SetCollisionGroup(ComponentCollision::CollisionGroup::GROUND);
    coll2->SetHitCollisionGroup((u32)ComponentCollision::CollisionGroup::PLAYER | (u32)ComponentCollision::CollisionGroup::ETC);

    auto coll = AddComponent<ComponentCollisionCapsule>();
    coll->SetTranslate({-22, -10, 0});
    coll->SetHeight(50);
    coll->SetRadius(17);
    coll->SetCollisionGroup(ComponentCollision::CollisionGroup::GROUND);
    coll->SetHitCollisionGroup((u32)ComponentCollision::CollisionGroup::PLAYER | (u32)ComponentCollision::CollisionGroup::ETC);
    return true;
}

void Ground2::Update()
{
    Super::Update();
    SetTranslate({-22, -10, 0});
}
void Ground2::Draw()
{
    Super::Draw();
}
}    // namespace Game01
