#include <System/Scene.h>
#include <Game/Game01/Game01.h>
#include <Game/Title/Title.h>
#include <Game/SceneFade/SceneFade.h>
#include "Operate.h"
#include "OperateBg.h"

namespace Operate {
Fade fadeout;    //	シーンフェイドクラス関数を使うための宣言

bool Operate::Init()
{
    //__super::Init();
    Scene::Object::Create<Obg>();
    return true;
}

//
void Operate::Update()
{
    if(Input::IsKeyDown(KEY_INPUT_T)) {
        //	次のシーンへの移動準備を行います
        fadeout.FadeOut();    //	Game01シーンにフェイドアウト
    }

    //	フェードアウトを実行していい状態なら
    if(!fadeout.WaitFadeOut()) {
        //	シーンの切り替えを行います
        Scene::Change(Scene::GetScene<Title::Title>());
    }
}
}    // namespace Operate
