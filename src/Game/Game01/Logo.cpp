#include "Logo.h"

namespace Game01 {
bool Logo::Init()
{
    __super::Init();

    Logo_abigail_image = LoadGraph("data/Game/Logo/img_abigail.png");
    //  ロゴの座標
    Logo_abigail.x = 0;
    Logo_abigail.y = 590;
    //  プレイヤーかＮＰＣかを見分ける用のものの座標
    name_abigail_pos.x = 15;
    name_abigail_pos.y = 560;

    Logo_betty_image = LoadGraph("data/Game/Logo/img_betty.png");
    Logo_betty.x     = 960;
    Logo_betty.y     = 590;
    name_betty_pos.x = 975;
    name_betty_pos.y = 560;

    Logo_rise_image = LoadGraph("data/Game/Logo/img_rise.png");
    Logo_rise.x     = 640;
    Logo_rise.y     = 590;
    name_rise_pos.x = 635;
    name_rise_pos.y = 560;

    Logo_sol_image = LoadGraph("data/Game/Logo/img_sol.png");
    Logo_sol.x     = 320;
    Logo_sol.y     = 590;
    name_sol_pos.x = 330;
    name_sol_pos.y = 560;

    return true;
}

void Logo::Update()
{
}

void Logo::Draw()
{
    Super::Draw();
    //  ロゴの描画
    DrawGraph(Logo_abigail.x, Logo_abigail.y, Logo_abigail_image, TRUE);
    DrawGraph(Logo_betty.x, Logo_betty.y, Logo_betty_image, TRUE);
    DrawGraph(Logo_rise.x, Logo_rise.y, Logo_rise_image, TRUE);
    DrawGraph(Logo_sol.x, Logo_sol.y, Logo_sol_image, TRUE);

    DrawStringF(name_abigail_pos.x, name_abigail_pos.y, "NPC2", GetColor(0, 0, 255));
    DrawStringF(name_betty_pos.x, name_betty_pos.y, "NPC1", GetColor(0, 0, 255));
    DrawStringF(name_sol_pos.x, name_sol_pos.y, "NPC3", GetColor(0, 0, 255));
    DrawStringF(name_rise_pos.x, name_rise_pos.y, "PLAYER", GetColor(255, 0, 0));
}

void Logo::Exit()
{
    DeleteGraph(Logo_abigail_image);
}

}    // namespace Game01
