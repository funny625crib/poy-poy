#include "OperateBg.h"

namespace Operate {

bool Obg::Init()
{
    __super::Init();
    Obg_image = LoadGraph("data/Game/Operate/WASD_key.png");
    GetGraphSize(Obg_image, &Obg_x, &Obg_y);
    //	操作方法背景のオブジェクト
    SetName("Obg");
    this->SetTranslate({0.0f, 0.0f, 0.0f});
    return true;
}

void Obg::Update()
{
    Super::Update();
}

void Obg::Draw()
{
    Super::Draw();
    DrawExtendGraph(0, 0, Obg_x, Obg_y, Obg_image, TRUE);

    SetFontSize(20);
    DrawString(50, 330, "ＷＡＳＤキーで移動することができる", GetColor(255, 255, 255));
    SetFontSize(16);
}
}    // namespace Operate
