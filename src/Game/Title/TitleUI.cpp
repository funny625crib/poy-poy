#include "TitleUI.h"

namespace Title {

bool UI::Init()
{
    __super::Init();
    //Bg_image = LoadGraph("data/Game/Title/TitleBg.png");
    //GetGraphSize(Bg_image, &Bg_x, &Bg_y);
    //タイトルUIのオブジェクト
    SetName("UI");
    this->SetTranslate({0.0f, 0.0f, 0.0f});
    return true;
}
void UI::Update()
{
    Super::Update();
    timer += GetDeltaTime() * blinking_speed;
    //sinカーブの計算の値を０～２５５にする
    text_alpha = (sinf(timer) + 1) * 127.5f;
}
void UI::Draw()
{
    Super::Draw();
    SetFontSize(font_size);
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, text_alpha);
    DrawString(text_x, text_y, "PRESS ANY BUTTON", GetColor(255, 255, 255));
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    //DrawExtendGraph(0, 0, Bg_x, Bg_y, Bg_image, TRUE);
}
}    // namespace Title
