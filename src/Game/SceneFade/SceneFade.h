#pragma once

USING_PTR(Fade);

class Fade : public Object
{
public:
    BP_OBJECT_DECL(Fade, u8"シーンのフェイド");
    void FadeIn();
    bool WaitFadeIn();
    void FadeOut();
    bool WaitFadeOut();

private:
};
