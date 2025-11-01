#pragma once
namespace Game01 {
USING_PTR(Hp);
class Hp : public Object
{
public:
    BP_OBJECT_DECL(Hp, u8"Game02 の Hp");
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

    bool Init() override;

    void Update() override;

    void Draw() override;

    void Exit() override;
    int  Hp_count;

private:
    int Hp_image;

    int Hp_x;
    int Hp_y;
    int Hp_imgx;
    int Hp_imgy;

    int Hp_image2;
    int Hp_count2;
    int Hp_x2;
    int Hp_y2;
    int Hp_imgx2;
    int Hp_imgy2;

    int Hp_image3;
    int Hp_count3;
    int Hp_x3;
    int Hp_y3;
    int Hp_imgx3;
    int Hp_imgy3;

    int Hp_image4;
    int Hp_count4;
    int Hp_x4;
    int Hp_y4;
    int Hp_imgx4;
    int Hp_imgy4;
};

}    // namespace Game01
