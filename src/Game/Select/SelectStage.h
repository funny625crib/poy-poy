#pragma once
#include <System/Scene.h>

namespace Game01 {
USING_PTR(SelectStage);

class SelectStage : public Object
{
public:
    BP_OBJECT_DECL(SelectStage, u8"Game01 の SelectStage");

    bool Init() override;

    void Update() override;

private:
};

}    // namespace Game01
