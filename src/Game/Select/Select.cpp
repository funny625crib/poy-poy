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
    //ファイルが開かなかったらfalseを返す
    if(!ifs.is_open()) {
        return false;
    };
    // 1行ずつ読み込む
    std::string line;
    //getline関数でifsの中身を一文づつ読み込み
    while(std::getline(ifs, line)) {
        std::stringstream ss(line);    //ssに切り取った一文を入れる
        std::string       type;
        std::string       name;
        std::string       description;
        std::string       iconPath;
        std::string       colum;
        // カンマ区切りで分割
        while(std::getline(ss, colum, ',')) {
            // item に1つのデータが入る
            // ここで必要な処理を行う
            file_count_++;
            if(file_count_ == 1) {
                type = colum;
            }
            else if(file_count_ == 2) {
                name = colum;
            }
            else if(file_count_ == 3) {
                description = colum;
            }
            else if(file_count_ == 4) {
                iconPath = colum;
            }
            if(file_count_ >= 4) {
                file_count_ = 0;
            }
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
