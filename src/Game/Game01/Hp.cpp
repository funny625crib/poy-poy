//#include <System/Scene.h>
//#include <Game/Game01/Game01.h>
#include "Hp.h"

namespace Game01 {
bool Hp::Init()
{
    __super::Init();
    Hp_image = LoadGraph("data/Game/Hp/memorygeeji2-2.jpg");

    //  画像座標
    Hp_x = 100;
    Hp_y = 620;
    //  プレイヤーとＮＰＣのＨＰ
    Hp_count = 10;
    //  ＨＰの増減
    Hp_imgx = Hp_count % 4 * 100;
    Hp_imgy = Hp_count / 4 * 100;

    return true;
}

void Hp::Update()
{
    Super::Update();
    //  いったん左右キーで操作
    if(Input::IsKeyDown(KEY_INPUT_RIGHT)) {
        if(Hp_count < 10) {
            Hp_count += 1;
            Hp_imgx   = Hp_count % 4 * 100;
            Hp_imgy   = Hp_count / 4 * 100;
        }
    }
    if(Input::IsKeyDown(KEY_INPUT_LEFT)) {
        if(Hp_count > 0) {
            Hp_count -= 1;
            Hp_imgx   = Hp_count % 4 * 100;
            Hp_imgy   = Hp_count / 4 * 100;
        }
    }
}

void Hp::Draw()
{
    Super::Draw();
    DrawRectGraph(Hp_x, Hp_y, Hp_imgx, Hp_imgy, 100, 100, Hp_image, TRUE, FALSE);
    //DrawExtendGraph(0, 0, Hp_x, Hp_y,Hp_image, TRUE);
}

void Hp::Exit()
{
    DeleteGraph(Hp_image);
}
}    // namespace Game01
