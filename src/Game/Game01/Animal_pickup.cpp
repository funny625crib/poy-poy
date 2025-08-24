#include "Animal_Pickup.h"
#include "Animal.h"

namespace Game01 {
void Pickup::Init()
{
    __super::Init();

    // カメラオブジェクト
    //auto camera = Scene::Object::Create<Object>();
}

void Pickup::Update()
{
    __super::Update();
    auto owner = GetOwner();
}
}    // namespace Game01
