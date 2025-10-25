#include "AnimalGenerator.h"
#include "Animal.h"
#include <Game/Component/State/StatePhysics.h>
bool Game01::Generator::Init()
{
    SetName("Generator");
    SetTranslate({112.0f, 50.0f, 55.0f});
    //SetRotationAxisXYZ({0.0f, 180.0f, 0.0f});

    return false;
}

void Game01::Generator::Update()
{
    generation_time_++;
    if(generation_time_ >= 300.0f) {
        auto obj = Scene::Object::Create<Animal>();
        obj->SetTranslate({112.0f, 50.0f, 55.0f});
        auto physics = obj->GetComponent<StatePhysics>();
        physics->SetStatic(true);
        obj->Game01::Animal::Throw();
        generation_time_ = 0.0f;
    }
}
