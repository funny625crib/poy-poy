#pragma once
#include <System/Scene.h>
#include <System/Component/Component.h>

USING_PTR(StateThorw);

class StateThorw : public Component
{
public:
    BP_COMPONENT_DECL(StateThorw, u8"State_Thorw");

    void Init() override;

    void Update() override;

    void GUI() override;
    enum
    {
        IDLE,
        HOLDING,
        THROWING,
    };
    float3 dis_character_animal_;
    float3 dis_character_Boms_;

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

    float move_speed_ = 0.5f;
    float rot_speed_  = 20.0f;

    float front_rot_ = 0.0f;    //!<前方ベクトルの回転角度(0-360度)
};

CEREAL_CLASS_VERSION(StateThorw, 1);
