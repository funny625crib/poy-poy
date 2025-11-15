#pragma once
#include <System/Scene.h>
#include "RankingBg.h"

namespace Ranking {
USING_PTR(Ranking);

class Ranking : public Scene::Base
{
public:
    BP_CLASS_DECL(Ranking, u8"Game02 の Ranking");

    bool Init() override;

    void Update() override;

private:
};
}    // namespace Ranking
