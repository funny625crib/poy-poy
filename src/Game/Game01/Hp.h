#pragma once
namespace Game01 {
USING_PTR(Hp);
class Hp : public Object
{
public:
    BP_OBJECT_DECL(Hp, u8"Game02 の Hp");

    bool Init() override;

    void Update() override;

    void Draw() override;

    void Exit() override;

private:
    int Hp_image;
    int Hp_count;
    int Hp_x;
    int Hp_y;
    int Hp_imgx;
    int Hp_imgy;
};

}    // namespace Game01
