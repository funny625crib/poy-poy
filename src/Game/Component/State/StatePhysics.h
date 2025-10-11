#pragma once
#include <System/Scene.h>
#include <System/Component/Component.h>

USING_PTR(StatePhysics);

class StatePhysics : public Component
{
public:
    BP_COMPONENT_DECL(StatePhysics, u8"StatePhysics");

    void Init() override;

    void Update() override;

    void GUI() override;

    void   addForce(float3 force, int mode1);
    float3 SetVelocity();
    void   SetStatic(bool Static);
    float3 velocity;
    int    mode;
    float3 speed;
    float  mass = 1.0f;
    float  gravity;
    bool   gravity_on = false;
    bool   IsStatic   = false;
    enum
    {
        Force,
        Impulse,
        VelocityChange,
        Acceleration,
    };

private:
    ComponentWeakPtr left_collision_;
    //--------------------------------------------------------------------
    //! @name Cereal処理
    //--------------------------------------------------------------------
    //@{

    //! @brief セーブ
    // @param arc アーカイバ
    // @param ver バージョン
    CEREAL_SAVELOAD(arc, ver) { arc(cereal::make_nvp("StatePhysics", cereal::base_class<Component>(this))); }
};

CEREAL_CLASS_VERSION(StatePhysics, 1);
