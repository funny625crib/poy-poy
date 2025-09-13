#pragma once
namespace Title {
USING_PTR(Bg);
class Bg : public Object
{
public:
    BP_OBJECT_DECL(Bg, u8"Title の Bg");

    bool Init() override;

    void Update() override;

    void Draw() override;

private:
    int Bg_image;
    int Bg_x;
    int Bg_y;
};

}    // namespace Title
