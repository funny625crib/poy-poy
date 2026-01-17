#include "AnimalGenerator.h"
#include "Animal.h"
#include <Game/Component/State/AnimalStateIdleWalk.h>
#include <Game/Component/State/StatePhysics.h>
bool Game01::Generator::Init()
{
    SetName("Generator");
    spawn_positions_ = {
        { 112.0f, 50.0f,   55.0f},
        { 112.0f, 50.0f, -100.0f},
        {-240.0f, 90.0f,   88.0f},
        {-170.0f, 70.0f, -125.0f},
    };
    SetTranslate(spawn_positions_[0]);
    return false;
}

void Game01::Generator::Update()
{
    generation_time_++;
    if(generation_time_ >= generarion_interval_) {
        auto obj = Scene::Object::Create<Animal>();
        obj->SetTranslate(spawn_positions_[GetRand(3)]);
        obj->GetComponent<AnimalStateIdleWalk>()->is_just_generated_ = true;
        auto physics                                                 = obj->GetComponent<StatePhysics>();
        physics->SetStatic(true);

        // 投げる方向ベクトルを計算
        float3 throw_dir = normalize(AREA_CENTER - obj->GetTranslate());

        // 投げる方向をセット
        obj->SetDirectior(throw_dir);

        // 投げる処理
        obj->Game01::Animal::Throw();

        generation_time_ = 0.0f;
    }
}
