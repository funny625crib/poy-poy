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

    int    Logo_betty_image;
    float2 Logo_betty;

    int    Logo_rise_image;
    float2 Logo_rise;

    int    Logo_sol_image;
    float2 Logo_sol;
};

}    // namespace Game01
