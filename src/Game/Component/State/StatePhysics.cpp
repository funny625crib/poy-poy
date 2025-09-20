#pragma once
#include "StatePhysics.h"
#include "StateIdleWalk.h"
#include <System/Component/ComponentModel.h>
#include <Game/Game01/Animal.h>
#include <System/Component/ComponentCollisionSphere.h>
#include <DxLib.h>

void StatePhysics::Init()
{
    __super::Init();

    auto owner = GetOwner();
}

void StatePhysics::Update()
{
    __super::Update();
    auto owner = GetOwner();
    owner->AddTranslate(velocity * update_delta_time_);
}

void StatePhysics::GUI()
{
    __super::GUI();
}

void StatePhysics::addForce(float3 force, int mode1)
{
    switch(mode1) {
    case 1:
        float3 acceleration  = force / mass;
        velocity            += acceleration * update_delta_time_;
        break;
    case 2:
        velocity += force / mass;
        break;
    default:
        break;
    }
}

float3 StatePhysics::SetVelocity()
{
    return velocity;
}

CEREAL_REGISTER_TYPE(StatePhysics)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, StatePhysics)
