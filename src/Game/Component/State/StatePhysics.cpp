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
    if(IsStatic == false)
        return;
    if(gravity_on) {
        addForce(float3{0, 1, 0} * 9.8f * mass, Force);
    }
    owner->AddTranslate(velocity * GetDeltaTime());
}

void StatePhysics::GUI()
{
    __super::GUI();
}

void StatePhysics::addForce(float3 force, int mode1 = Force)
{
    float3 acceleration = force / mass;
    switch(mode1) {
    case Force:
        velocity += acceleration * GetDeltaTime();
        break;
    case Impulse:
        velocity += force / mass;
        break;
    case VelocityChange:
        break;
    case Acceleration:
        break;
    default:

        break;
    }
    //return velocity;
}

float3 StatePhysics::SetVelocity()
{
    return velocity;
}

void StatePhysics::SetStatic(bool Static)
{
    IsStatic = Static;
}

CEREAL_REGISTER_TYPE(StatePhysics)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, StatePhysics)
