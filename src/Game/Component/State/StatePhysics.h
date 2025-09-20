#pragma once
#include <System/Scene.h>
#include <System/Component/Component.h>

USING_PTR(StatePhysics);

class StatePhysics : public Component
{
public:
    BP_COMPONENT_DECL(StatePhysics, u8"State Run");

    void Init() override;

    void Update() override;

    void GUI() override;

    void   addForce(float3 force, int mode1);
    float3 SetVelocity();

private:
    ComponentWeakPtr left_collision_;
    //--------------------------------------------------------------------
    //! @name Cereal処理
    //--------------------------------------------------------------------
    //@{

    //! @brief セーブ
    // @param arc アーカイバ
    // @param ver バージョン
    CEREAL_SAVELOAD(arc, ver) { arc(cereal::make_nvp("Component", cereal::base_class<Component>(this))); }
    float3 velocity;
    int    mode;
    float3 speed;
    float  mass;
    float  gravity;
    bool   gravity_on;
    bool   IsStatic = false;
};

CEREAL_CLASS_VERSION(StatePhysics, 1);
