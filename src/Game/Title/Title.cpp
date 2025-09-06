#include <System/Scene.h>
#include <Game/Game01/Game01.h>
#include <Game/SceneFade/SceneFade.h>
#include "Title.h"
#include "TitleBg.h"
#include "TitleUI.h"

namespace Title {
Fade fadeout;    //シーンフェイドクラスの関数を使うため宣言
//タイトル用変数の初期化処理
bool Title::Init()
{
    Scene::Object::Create<Bg>();
    Scene::Object::Create<UI>();
    return true;
}
//タイトルの更新処理
void Title::Update()
{
    if(Input::IsKeyDown(KEY_INPUT_SPACE)) {
        // 次のシーンに移動準備します
        fadeout.FadeOut();    //Game01シーンにフェイドアウト
    }

    // フェードアウトを実行していい状態なら
    if(!fadeout.WaitFadeOut()) {
        // シーンを切り替えます
        Scene::Change(Scene::GetScene<Game01::Game01>());
    }
    // if(Input::IsKeyDown(KEY_INPUT_SPACE)) {
    //     // シーンを切り替えます
    //     Scene::Change(Scene::GetScene<Game01::Game01>());
    // }
}
}    // namespace Title
