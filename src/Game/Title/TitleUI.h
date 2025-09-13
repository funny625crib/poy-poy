#pragma once
namespace Title {
USING_PTR(UI);
class UI : public Object
{
public:
    BP_OBJECT_DECL(UI, u8"Title の UI");

    bool Init() override;

    void Update() override;

    void Draw() override;

private:
    int   text_x         = 500;
    int   text_y         = 600;
    int   font_size      = 32;
    int   text_alpha     = 255;
    bool  alpha_flag     = false;
    float blinking_speed = 3.0f;
    float timer          = 0.0f;
};

}    // namespace Title
