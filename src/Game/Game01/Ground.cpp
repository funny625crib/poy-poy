#include "Ground.h"
#include <System/Component/ComponentModel.h>
#include <System/Component/ComponentCollisionModel.h>
#include <System/Component/ComponentCollision.h>
#include <System/Component/ComponentCollisionCapsule.h>

namespace Game01 {
bool Ground::Init()
{
    Super::Init();

    // グランド
    //auto ground = Scene::Object::Create<Object>();
    SetName("Ground");
    AddComponent<ComponentModel>("data/Sample/SwordBout/Stage/village.mv1");
    //AddComponent<ComponentCollision>();
    auto ground = AddComponent<ComponentCollisionModel>();
    ground->AttachToModel();
    /* auto coll = AddComponent<ComponentCollisionCapsule>();
    coll->SetTranslate({-42, -10, 4});
    coll->SetHeight(60);
    coll->SetRadius(17);
    coll->SetCollisionGroup(ComponentCollision::CollisionGroup::GROUND);
    coll->SetHitCollisionGroup((u32)ComponentCollision::CollisionGroup::PLAYER | (u32)ComponentCollision::CollisionGroup::ETC);*/
    return true;
}

void Ground::Update()
{
    Super::Update();
    // auto ground = GetComponent<ComponentCollisionModel>();
    // SetTranslate({0, 0, 0});
}
void Ground::Draw()
{
    Super::Draw();
}
}    // namespace Game01
