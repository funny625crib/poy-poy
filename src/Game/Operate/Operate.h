#pragma once
#include <System/Scene.h>
#include "OperateBg.h"

namespace Operate {
USING_PTR(Operate);

class Operate : public Scene::Base
{
public:
    BP_CLASS_DECL(Operate, u8"Game02 の Operate");

    bool Init() override;

    void Update() override;

private:
};
}    // namespace Operate
