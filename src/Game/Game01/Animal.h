#pragma once
#include <System/Scene.h>

namespace Game01 {
USING_PTR(Animal);

class Animal : public Object
{
public:
    BP_OBJECT_DECL(Animal, u8"Game01 の Animal");

    bool Init() override;

    void Update() override;

private:
};

}    // namespace Game01
