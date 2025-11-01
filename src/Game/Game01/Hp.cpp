//#include <System/Scene.h>
//#include <Game/Game01/Game01.h>
#include "Hp.h"

namespace Game01 {
bool Hp::Init()
{
    __super::Init();
    Hp_image = LoadGraph("data/Game/Hp/memorygeeji2-2.jpg");

    //  画像座標
    Hp_x = 0;
    Hp_y = 620;
    //  プレイヤーとＮＰＣのＨＰ
    Hp_count_abigail = 10;
    //  ＨＰの増減
    Hp_imgx = Hp_count_abigail % 4 * 100;
    Hp_imgy = Hp_count_abigail / 4 * 100;

    Hp_image2    = LoadGraph("data/Game/Hp/memorygeeji2-2.jpg");
    Hp_x2        = 320;
    Hp_y2        = 620;
    Hp_count_sol = 10;
    Hp_imgx2     = Hp_count_sol % 4 * 100;
    Hp_imgy2     = Hp_count_sol / 4 * 100;

    Hp_image3     = LoadGraph("data/Game/Hp/memorygeeji2-2.jpg");
    Hp_x3         = 640;
    Hp_y3         = 620;
    Hp_count_rise = 10;
    Hp_imgx3      = Hp_count_rise % 4 * 100;
    Hp_imgy3      = Hp_count_rise / 4 * 100;

    Hp_image4      = LoadGraph("data/Game/Hp/memorygeeji2-2.jpg");
    Hp_x4          = 960;
    Hp_y4          = 620;
    Hp_count_betty = 10;
    Hp_imgx4       = Hp_count_betty % 4 * 100;
    Hp_imgy4       = Hp_count_betty / 4 * 100;

    return true;
}

void Hp::Update()
{
    Super::Update();
    //  いったん左右キーで操作
    //  １番左
    if(Input::IsKeyDown(KEY_INPUT_RIGHT)) {
        Hp_count_abigail += 1;
    }
    if(Input::IsKeyDown(KEY_INPUT_LEFT)) {
        Hp_count_abigail -= 1;
    }
    Hp_count_abigail = max(0, min(Hp_count_abigail, 10));
    Hp_imgx          = Hp_count_abigail % 4 * 100;
    Hp_imgy          = Hp_count_abigail / 4 * 100;

    //  左から２番目
    if(Input::IsKeyDown(KEY_INPUT_M)) {
        Hp_count_sol += 1;
    }
    if(Input::IsKeyDown(KEY_INPUT_N)) {
        Hp_count_sol -= 1;
    }
    Hp_count_sol = max(0, min(Hp_count_sol, 10));
    Hp_imgx2     = Hp_count_sol % 4 * 100;
    Hp_imgy2     = Hp_count_sol / 4 * 100;
    //  右から２番目
    if(Input::IsKeyDown(KEY_INPUT_K)) {
        Hp_count_rise += 1;
    }
    if(Input::IsKeyDown(KEY_INPUT_J)) {
        Hp_count_rise -= 1;
    }
    Hp_count_rise = max(0, min(Hp_count_rise, 10));
    Hp_imgx3      = Hp_count_rise % 4 * 100;
    Hp_imgy3      = Hp_count_rise / 4 * 100;
    //  １番右
    if(Input::IsKeyDown(KEY_INPUT_I)) {
        Hp_count_betty += 1;
    }
    if(Input::IsKeyDown(KEY_INPUT_U)) {
        Hp_count_betty -= 1;
    }
    Hp_count_betty = max(0, min(Hp_count_betty, 10));
    Hp_imgx4       = Hp_count_betty % 4 * 100;
    Hp_imgy4       = Hp_count_betty / 4 * 100;
}

void Hp::Draw()
{
    Super::Draw();
    DrawRectGraph(Hp_x, Hp_y, Hp_imgx, Hp_imgy, 100, 100, Hp_image, TRUE, FALSE);
    DrawRectGraph(Hp_x2, Hp_y2, Hp_imgx2, Hp_imgy2, 100, 100, Hp_image2, TRUE, FALSE);
    DrawRectGraph(Hp_x3, Hp_y3, Hp_imgx3, Hp_imgy3, 100, 100, Hp_image3, TRUE, FALSE);
    DrawRectGraph(Hp_x4, Hp_y4, Hp_imgx4, Hp_imgy4, 100, 100, Hp_image4, TRUE, FALSE);
    //DrawExtendGraph(0, 0, Hp_x, Hp_y,Hp_image, TRUE);
}

void Hp::Exit()
{
    DeleteGraph(Hp_image);
}
}    // namespace Game01
