#pragma once
#include <System/Scene.h>
#include "TitleBg.h"

namespace Title {
USING_PTR(Title);

class Title : public Scene::Base
{
public:
    BP_CLASS_DECL(Title, u8"Game02 の Titleのシーン!!!");

    bool Init() override;

    void Update() override;

private:
};

}    // namespace Title
