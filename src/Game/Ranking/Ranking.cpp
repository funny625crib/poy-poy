#include <System/Scene.h>
#include <Game/Game01/Game01.h>
#include <Game/Title/Title.h>
#include <Game/SceneFade/SceneFade.h>
#include "Ranking.h"
#include "RankingBg.h"

namespace Ranking {
Fade fade;    //	シーンフェイドクラス関数を使うための宣言
//	ランキング用変数の初期化処理
bool Ranking::Init()
{
    Scene::Object::Create<Rbg>();
    fade.FadeIn();
    return true;
}

//	ランキングの更新処理
void Ranking::Update()
{
    if(fade.WaitFadeIn())
        return;

    if(Input::IsKeyDown(KEY_INPUT_1)) {
        //	次のシーンへの移動準備を行います
        fade.FadeOut();    //	Game01シーンにフェイドアウト
    }

    //	フェードアウトを実行していい状態なら
    if(!fade.WaitFadeOut()) {
        //	シーンの切り替えを行います
        Scene::Change(Scene::GetScene<Title::Title>());
    }
}
}    // namespace Ranking
