#pragma once
#include <System/Scene.h>
#include <System/Component/Component.h>

USING_PTR(AnimalStateIdleWalk);

class AnimalStateIdleWalk : public Component
{
public:
    BP_COMPONENT_DECL(AnimalStateIdleWalk, u8"State 移動・停止");

    void Init() override;

    void Update() override;

    AnimalStateIdleWalkPtr SetMoveSpeed(const float speed);

    AnimalStateIdleWalkPtr SetRotateSpeed(const float speed);

    AnimalStateIdleWalkPtr SetKeys(int up, int down, int left, int right);

    const float GetMoveSpeed() const;
    const float GetRotateSpeed() const;

    inline const void  SetFrontRotate(float rotate) { front_rot_ = rotate; }
    inline const float GetFrontRotate() const { return front_rot_; }

    void GUI() override;

private:
    float move_speed_ = 0.5f;
    float rot_speed_  = 20.0f;

    float front_rot_ = 0.0f;    //!<前方ベクトルの回転角度(0-360度)

    //--------------------------------------------------------------------
    //! @name Cereal処理
    //--------------------------------------------------------------------
    //@{

    //! @brief セーブ
    // @param arc アーカイバ
    // @param ver バージョン
    CEREAL_SAVELOAD(arc, ver)
    {
        arc(CEREAL_NVP(move_speed_),
            CEREAL_NVP(rot_speed_),

            CEREAL_NVP(front_rot_));

        arc(cereal::make_nvp("Component", cereal::base_class<Component>(this)));
    }
};

CEREAL_CLASS_VERSION(AnimalStateIdleWalk, 1);
