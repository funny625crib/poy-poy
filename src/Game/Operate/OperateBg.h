#pragma once
#include <System/Scene.h>
namespace Operate {

USING_PTR(Obg);
class Obg : public Object
{
public:
    BP_OBJECT_DECL(Obg, u8"Ranking の Bg");

    bool Init() override;

    void Update() override;

    void Draw() override;

private:
    int Obg_image;
    int Obg_x;
    int Obg_y;
};
}    // namespace Operate
