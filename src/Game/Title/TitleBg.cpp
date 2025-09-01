#include "TitleBg.h"

namespace Title {

bool Bg::Init()
{
    __super::Init();
    Bg_image = LoadGraph("data/Game/Title/TitleBg.png");
    GetGraphSize(Bg_image, &Bg_x, &Bg_y);
    //タイトル背景のオブジェクト
    SetName("Bg");
    this->SetTranslate({0.0f, 0.0f, 0.0f});
    return true;
}
void Bg::Update()
{
    Super::Update();
}

void Bg::Draw()
{
    Super::Draw();
    DrawExtendGraph(0, 0, Bg_x, Bg_y, Bg_image, TRUE);
}
}    // namespace Title
