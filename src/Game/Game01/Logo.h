#pragma once
namespace Game01 {
USING_PTR(Logo);
class Logo : public Object
{
public:
    BP_OBJECT_DECL(Logo, u8"Game02 の Logo");

    bool Init() override;

    void Update() override;

    void Draw() override;

    void Exit() override;

private:
    int    Logo_abigail_image;
    float2 Logo_abigail;
    //  プレイヤーかＮＰＣかをわかりやすくする
    float2 name_abigail_pos;

    int    Logo_betty_image;
    float2 Logo_betty;
    float2 name_betty_pos;

    int    Logo_rise_image;
    float2 Logo_rise;
    float2 name_rise_pos;

    int    Logo_sol_image;
    float2 Logo_sol;
    float2 name_sol_pos;
};

}    // namespace Game01
