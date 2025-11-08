#pragma once
namespace Ranking {

USING_PTR(Rbg);
class Rbg : public Object
{
public:
    BP_OBJECT_DECL(Rbg, u8"Ranking の Bg");

    bool Init() override;

    void Update() override;

    void Draw() override;

private:
    int Rbg_image;
    int Rbg_x;
    int Rbg_y;
};
}    // namespace Ranking
