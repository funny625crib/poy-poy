#include "SelectStage.h"
#include <System/Component/ComponentModel.h>
#include <System/Component/ComponentCollisionModel.h>

namespace Game01 {
bool SelectStage::Init()
{
    Super::Init();
    // ステージ
    SetName("SelectStage");
    //AddComponent<ComponentModel>("data/Sample/SwordBout/Stage/fantasy-village-market.mv1.mv1");
    AddComponent<ComponentModel>("data/Sample/SwordBout/Stage/village.mv1");

    AddComponent<ComponentCollisionModel>()    //
        ->AttachToModel();

    return true;
}

void SelectStage::Update()
{
    Super::Update();
}
}    // namespace Game01
