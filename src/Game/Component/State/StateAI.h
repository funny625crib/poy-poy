#pragma once
#include <System/Scene.h>
#include <System/Component/Component.h>
#include <Game/Game01/Animal.h>
#include <Game/Game01/time_bomb.h>
USING_PTR(StateAI);

class StateAI : public Component
{
public:
    BP_COMPONENT_DECL(StateAI, u8"State_Thorw");

    void Init() override;

    void          Update() override;
    ObjectWeakPtr hold_obj;
    //ObjectPtr            hold_obj;
    void                 GUI() override;
    Game01::AnimalPtr    Get_obj_A = nullptr;
    Game01::Time_bombPtr Get_obj_B = nullptr;
    int                  mode;
    bool                 thowe_chack = false;
    int                  thowe_time  = 0;
    int                  lock_on_time;
    float3               pos2;
    enum
    {
        Searchobj,
        Movetoobj,
        SearchPlayer,
        MovetoPlayer,
    };
    enum
    {
        NOBODY,
        RISE,
        BETTY,
        ABIGAIL,
        SOL,
    };
    enum
    {
        NOOBJ,
        ANIMAL,
        BOMS,
    };
    enum
    {
        IDLE,
        HOLDING,
        THROWING,
    };
    int set_obj_ = 0;

private:
    ComponentWeakPtr left_collision_;
    int              count_pickup_cooldown = 400;
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

CEREAL_CLASS_VERSION(StateAI, 1);
