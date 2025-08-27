#include "Acceleration.h"

namespace Game01 {
void Acceleration::Init()
{
    __super::Init();

    // カメラオブジェクト
    //auto camera = Scene::Object::Create<Object>();
}

void Acceleration::Update()
{
    __super::Update();
    auto owner = GetOwner();
}
}    // namespace Game01
