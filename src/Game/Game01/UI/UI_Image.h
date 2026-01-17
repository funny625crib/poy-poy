#pragma once
#include <System/Scene.h>

namespace Game01 {
USING_PTR(UI_Image);

class UI_Image : public Object
{
public:
    BP_OBJECT_DECL(UI_Image, u8"Game01 の UI Rise");

    bool Init() override;
    void Update() override;
    void Draw() override;
    void Exit() override;

private:
    float2 pos2d_abigail_ = {10.0f + 110.0f, 610.0f + 2.0f};
    float2 pos2d_sol_     = {340.0f + 110.0f, 610.0f + 2.0f};
    float2 pos2d_rise_    = {640.0f + 110.0f, 610.0f + 2.0f};
    float2 pos2d_betty_   = {940.0f + 110.0f, 610.0f + 2.0f};
    float2 size2d         = {126.0f, 136.0f};

    int rise_image    = -1;
    int betty_image   = -1;
    int sol_image     = -1;
    int abigail_image = -1;
};

}    // namespace Game01
