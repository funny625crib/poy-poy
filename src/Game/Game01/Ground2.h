#pragma once
#include <System/Scene.h>

namespace Game01 {
USING_PTR(Ground2);

class Ground2 : public Object
{
public:
    BP_OBJECT_DECL(Ground2, u8"Game01 の Ground");

    bool Init() override;

    void Update() override;
    void Draw() override;

private:
};

}    // namespace Game01
