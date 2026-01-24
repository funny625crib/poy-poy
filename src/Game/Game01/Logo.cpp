#include "Logo.h"

namespace Game01 {
bool Logo::Init()
{
    __super::Init();

    Logo_abigail_image = LoadGraph("data/Game/Logo/img_abigail.png");
    Logo_abigail.x     = 130;
    Logo_abigail.y     = 600;

    Logo_betty_image = LoadGraph("data/Game/Logo/img_betty.png");
    Logo_betty.x     = 1060;
    Logo_betty.y     = 600;

    Logo_rise_image = LoadGraph("data/Game/Logo/img_rise.png");
    Logo_rise.x     = 760;
    Logo_rise.y     = 600;

    Logo_sol_image = LoadGraph("data/Game/Logo/img_sol.png");
    Logo_sol.x     = 460;
    Logo_sol.y     = 600;

    return true;
}

void Logo::Update()
{
}

void Logo::Draw()
{
    Super::Draw();
    DrawGraph(Logo_abigail.x, Logo_abigail.y, Logo_abigail_image, TRUE);
    DrawGraph(Logo_betty.x, Logo_betty.y, Logo_betty_image, TRUE);
    DrawGraph(Logo_rise.x, Logo_rise.y, Logo_rise_image, TRUE);
    DrawGraph(Logo_sol.x, Logo_sol.y, Logo_sol_image, TRUE);
}

void Logo::Exit()
{
    DeleteGraph(Logo_abigail_image);
}

}    // namespace Game01
