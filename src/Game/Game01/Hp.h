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

    void LateDraw() override;

    void Exit() override;
    int  Hp_count_abigail;
    int  Hp_count_sol;
    int  Hp_count_rise;
    int  Hp_count_betty;
    //abigailがやられたかどうかの変数
    bool abigail_death_flag;
    //solがやられたかどうかの変数
    bool sol_death_flag;
    //riseがやられたかどうかの変数
    bool rise_death_flag;
    //bettyがやられたかどうかの変数
    bool betty_death_flag;
    //やられた人数をカウントする変数
    int Hp_death_count;

private:
    int Hp_image;

    int Hp_x;
    int Hp_y;
    int Hp_imgx;
    int Hp_imgy;

    int Hp_image2;
    int Hp_x2;
    int Hp_y2;
    int Hp_imgx2;
    int Hp_imgy2;

    int Hp_image3;
    int Hp_x3;
    int Hp_y3;
    int Hp_imgx3;
    int Hp_imgy3;

    int Hp_image4;
    int Hp_x4;
    int Hp_y4;
    int Hp_imgx4;
    int Hp_imgy4;
};

}    // namespace Game01
