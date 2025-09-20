#pragma once
#include <System/Scene.h>

namespace Select {
USING_PTR(Select);

class Select : public Scene::Base
{
public:
    BP_CLASS_DECL(Select, u8"Game02 の Selectのシーン!!!");

    bool Init() override;

    void Update() override;

private:
    int file_count_;
    int vertical_count_;
};

}    // namespace Select
