#include "RankingBg.h"

namespace Ranking {

bool Rbg::Init()
{
    __super::Init();
    Rbg_image = LoadGraph("data/Game/Ranking/RankingBg.png");
    GetGraphSize(Rbg_image, &Rbg_x, &Rbg_y);
    //	ランキング背景のオブジェクト
    SetName("Rbg");
    this->SetTranslate({0.0f, 0.0f, 0.0f});
    return true;
}

void Rbg::Update()
{
    Super::Update();
}

void Rbg::Draw()
{
    Super::Draw();
    DrawExtendGraph(0, 0, Rbg_x, Rbg_y, Rbg_image, TRUE);
}
}    //  namespace Ranking
