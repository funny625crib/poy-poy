#pragma once
#include <System/Scene.h>

namespace Game01 {
USING_PTR(Animal);

class Animal : public Object
{
public:
    BP_OBJECT_DECL(Animal, u8"Game01 の Animal");

    bool Init() override;

    void Update() override;
    void OnHit(const ComponentCollision::HitInfo& hit_info) override;
    void SetDirectior(float3 dir);
    void SetMoveDirectior(float3 dir);
    void UpdateAnimation();

    int Cone_Mode;
    enum
    {
        IDLE,
        HOLDING,
        THROWING,
    };
    float3 direction_;
    float3 mode_direction_;

private:
    float speed_ = 1.0f;
};

}    // namespace Game01
