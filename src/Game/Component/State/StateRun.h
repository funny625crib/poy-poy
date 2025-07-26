#pragma once
#include <System/Scene.h>
#include <System/Component/Component.h>

USING_PTR(StateRun);

class StateRun : public Component
{
public:
    BP_COMPONENT_DECL(StateRun, u8"State Run");

    void Init() override;

    void Update() override;

    void GUI() override;

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

    float move_speed_ = 1.0f;
    float rot_speed_  = 20.0f;

    float front_rot_ = 0.0f;    //!<前方ベクトルの回転角度(0-360度)
};

CEREAL_CLASS_VERSION(StateRun, 1);
