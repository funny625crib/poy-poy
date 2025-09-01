#include <System/Component/ComponentFilterFade.h>
#include "SceneFade.h"
void Fade::FadeIn()
{
    Scene::Object::Create<Object>()              // フェード用オブジェクト
        ->SetName("FadeIn")                      // 名前設定
        ->AddComponent<ComponentFilterFade>()    // フェードコンポーネント
        ->StartFadeIn();                         // フェードインスタート
}

bool Fade::WaitFadeIn()
{
    if(auto obj = Scene::Object::Get<Object>("FadeIn")) {
        auto fade = obj->GetComponent<ComponentFilterFade>();
        if(fade->IsFadeIn()) {
            if(!fade->IsFinishFade())
                return true;

            Scene::Object::Release("FadeIn");
            return false;
        }
    }

    return false;
}

void Fade::FadeOut()
{
    Scene::Object::Create<Object>()              // フェード用オブジェクト
        ->SetName("FadeOut")                     // 名前設定
        ->AddComponent<ComponentFilterFade>()    // フェードコンポーネント
        ->StartFadeOut();                        // フェードインスタート
}

bool Fade::WaitFadeOut()
{
    if(auto obj = Scene::Object::Get<Object>("FadeOut")) {
        auto fade = obj->GetComponent<ComponentFilterFade>();
        if(fade->IsFadeOut()) {
            if(!fade->IsFinishFade()) {
                return true;
            }
            Scene::Object::Release("FadeOut");
            return false;
        }
    }

    return true;
}
