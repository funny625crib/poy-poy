#include "UI_Image.h"
#include <DxLib.h>

namespace Game01 {

bool UI_Image::Init()
{
    Super::Init();
    SetName("UI_Image");

    rise_image = LoadGraph("data/Sample/Player/Rise_school/rise.png");

    betty_image = LoadGraph("data/Sample/Player/Betty/Betty.png");

    sol_image = LoadGraph("data/Sample/Player/Sol/sol.png");

    abigail_image = LoadGraph("data/Sample/Player/Abigail/abigail.png");

    return true;
}

void UI_Image::Exit()
{
    if(rise_image != -1) {
        DeleteGraph(rise_image);
        rise_image = -1;
    }
    if(betty_image != -1) {
        DeleteGraph(betty_image);
        betty_image = -1;
    }
    if(sol_image != -1) {
        DeleteGraph(sol_image);
        sol_image = -1;
    }
    if(abigail_image != -1) {
        DeleteGraph(abigail_image);
        abigail_image = -1;
    }
    Super::Exit();
}

void UI_Image::Update()
{
    Super::Update();
}

void UI_Image::Draw()
{
    Super::Draw();

    const int w = (int)size2d.x;
    const int h = (int)size2d.y;

    DrawExtendGraph((int)pos2d_rise_.x, (int)pos2d_rise_.y, (int)pos2d_rise_.x + w, (int)pos2d_rise_.y + h, rise_image, TRUE);
    DrawExtendGraph((int)pos2d_betty_.x, (int)pos2d_betty_.y, (int)pos2d_betty_.x + w, (int)pos2d_betty_.y + h, betty_image, TRUE);
    DrawExtendGraph((int)pos2d_sol_.x, (int)pos2d_sol_.y, (int)pos2d_sol_.x + w, (int)pos2d_sol_.y + h, sol_image, TRUE);
    DrawExtendGraph((int)pos2d_abigail_.x, (int)pos2d_abigail_.y, (int)pos2d_abigail_.x + w, (int)pos2d_abigail_.y + h, abigail_image, TRUE);
}
}    // namespace Game01

// namespace Game01
