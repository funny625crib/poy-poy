#pragma once
#include <System/Scene.h>

namespace Game01 {
USING_PTR(Generator);

class Generator : public Object
{
public:
    BP_OBJECT_DECL(Generator, u8"Game01 の Generator");

    bool Init() override;
    void Update() override;

private:
    const float3        AREA_CENTER = {(55.0f + -150.0f) / 2.0f, 50.0f, (110.0f + -100.0f) / 2.0f};    //エリアの中心座標
    std::vector<float3> spawn_positions_;                                                              //出現位置リスト
    float               generation_time_     = 0.0f;                                                   //生成までの時間
    float               generarion_interval_ = 300.0f;                                                 //生成間隔
    float               speed_               = 1.0f;
};

}    // namespace Game01
