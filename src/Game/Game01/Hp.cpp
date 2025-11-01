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
    Hp_count = 10;
    //  ＨＰの増減
    Hp_imgx = Hp_count % 4 * 100;
    Hp_imgy = Hp_count / 4 * 100;

    Hp_image2 = LoadGraph("data/Game/Hp/memorygeeji2-2.jpg");
    Hp_x2     = 320;
    Hp_y2     = 620;
    Hp_count2 = 10;
    Hp_imgx2  = Hp_count % 4 * 100;
    Hp_imgy2  = Hp_count / 4 * 100;

    Hp_image3 = LoadGraph("data/Game/Hp/memorygeeji2-2.jpg");
    Hp_x3     = 640;
    Hp_y3     = 620;
    Hp_count3 = 10;
    Hp_imgx3  = Hp_count % 4 * 100;
    Hp_imgy3  = Hp_count / 4 * 100;

    Hp_image4 = LoadGraph("data/Game/Hp/memorygeeji2-2.jpg");
    Hp_x4     = 960;
    Hp_y4     = 620;
    Hp_count4 = 10;
    Hp_imgx4  = Hp_count % 4 * 100;
    Hp_imgy4  = Hp_count / 4 * 100;

    return true;
}

void Hp::Update()
{
    Super::Update();
    //  いったん左右キーで操作
    //  １番左
    if(Input::IsKeyDown(KEY_INPUT_RIGHT)) {
        Hp_count += 1;
    }
    if(Input::IsKeyDown(KEY_INPUT_LEFT)) {
        Hp_count -= 1;
    }
    Hp_count = max(0, min(Hp_count, 10));
    Hp_imgx  = Hp_count % 4 * 100;
    Hp_imgy  = Hp_count / 4 * 100;
    //  Hp_count = min(Hp_count, 10);

    //  左から２番目
    if(Input::IsKeyDown(KEY_INPUT_M)) {
        if(Hp_count2 < 10) {
            Hp_count2 += 1;
            Hp_imgx2   = Hp_count2 % 4 * 100;
            Hp_imgy2   = Hp_count2 / 4 * 100;
        }
    }
    if(Input::IsKeyDown(KEY_INPUT_N)) {
        if(Hp_count2 > 0) {
            Hp_count2 -= 1;
            Hp_imgx2   = Hp_count2 % 4 * 100;
            Hp_imgy2   = Hp_count2 / 4 * 100;
        }
    }

    //  右から２番目
    if(Input::IsKeyDown(KEY_INPUT_K)) {
        if(Hp_count3 < 10) {
            Hp_count3 += 1;
            Hp_imgx3   = Hp_count3 % 4 * 100;
            Hp_imgy3   = Hp_count3 / 4 * 100;
        }
    }
    if(Input::IsKeyDown(KEY_INPUT_J)) {
        if(Hp_count3 > 0) {
            Hp_count3 -= 1;
            Hp_imgx3   = Hp_count3 % 4 * 100;
            Hp_imgy3   = Hp_count3 / 4 * 100;
        }
    }

    //  １番右
    if(Input::IsKeyDown(KEY_INPUT_I)) {
        if(Hp_count4 < 10) {
            Hp_count4 += 1;
            Hp_imgx4   = Hp_count4 % 4 * 100;
            Hp_imgy4   = Hp_count4 / 4 * 100;
        }
    }
    if(Input::IsKeyDown(KEY_INPUT_U)) {
        if(Hp_count4 > 0) {
            Hp_count4 -= 1;
            Hp_imgx4   = Hp_count4 % 4 * 100;
            Hp_imgy4   = Hp_count4 / 4 * 100;
        }
    }
}

void Hp::Draw()
{
    Super::Draw();
    DrawRectGraph(Hp_x, Hp_y, Hp_imgx, Hp_imgy, 100, 100, Hp_image, TRUE, FALSE);
    DrawFormatString(0, 10, WHITE, "%d", Hp_count);
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
