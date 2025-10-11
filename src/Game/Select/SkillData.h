#pragma once
#include <System/Scene.h>

namespace Select {
USING_PTR(SkillData);

class SkillData : public Object
{
public:
    BP_OBJECT_DECL(SkillData, u8"Select の SkillData");

    bool Init() override;

    void Update() override;

private:
    int file_count_;
    int vertical_count_;
};

}    // namespace Select
