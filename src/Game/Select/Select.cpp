#include <System/Scene.h>
#include <Game/Game01/Game01.h>
#include <Game/SceneFade/SceneFade.h>
#include <fstream>
#include <sstream>
#include <string>
#include "Select.h"

namespace Select {
Fade fadeout;    //シーンフェイドクラスの関数を使うため宣言
//タイトル用変数の初期化処理
bool Select::Init()
{
    std::ifstream ifs("data/Game/Select/SkillData.csv");
    if(!ifs.is_open()) {
        return false;
    };
    // 1行ずつ読み込む
    std::string line;
    while(std::getline(ifs, line)) {
        std::stringstream ss(line);
        std::string       item;
        // カンマ区切りで分割
        while(std::getline(ss, item, ',')) {
            // item に1つのデータが入る
            // ここで必要な処理を行う
        }
    }
    ifs.close();
    return true;
}
//タイトルの更新処理
void Select::Update()
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
}    // namespace Select
