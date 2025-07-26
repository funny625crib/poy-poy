#include "Camera.h"
#include <System/Component/ComponentModel.h>
#include <System/Component/ComponentCollisionModel.h>
#include <System/Component/ComponentSpringArm.h>

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
}
}    // namespace Game01
