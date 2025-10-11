#include <System/Scene.h>
#include <Game/Game01/Game01.h>
#include <Game/SceneFade/SceneFade.h>
#include "Select.h"

namespace Select {
Fade fadeout;    //シーンフェイドクラスの関数を使うため宣言
//タイトル用変数の初期化処理
bool Select::Init()
{
    SkillTypeNames[0] = "超加速";
    SkillTypeNames[1] = "突進";
    SkillTypeNames[2] = "怪力";
    SkillTypeNames[3] = "回避";
    SkillTypeNames[4] = "潜伏";
    SkillTypeNames[5] = "威嚇";
    SkillTypeNames[6] = "シールド";
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

    //マウスの位置を取得
    GetMousePoint(&mouse_x_, &mouse_y_);
    //マウスがクリックされたら
    if(MOUSE_INPUT_LEFT) {
        for(int i = 0; i < SkillTypeCount; i++) {
            int y      = text_y_ + (i * 50);
            int width  = 200;    // 文字列の幅（適宜調整）
            int height = 40;     // 文字列の高さ（適宜調整）
            //マウスの位置が文字列の範囲内にあるかをチェック
            if(mouse_x_ >= text_x_ && mouse_x_ <= text_x_ + width && mouse_y_ >= y && mouse_y_ <= y + height) {
                selected_index_ = i;
                // 選択したスキルをインゲームに渡すために変数に格納
                selected_skill_ = SkillTypeNames[i];
                // シーンを切り替えます
                Scene::Change(Scene::GetScene<Game01::Game01>());
            }
        }
    }
}
void Select::Draw()
{
    //スキルタイプの名前を表示
    for(int i = 0; i < SkillTypeCount; i++) {
        DrawString(text_x_, text_y_ + (i * 50), SkillTypeNames[i].c_str(), GetColor(255, 255, 255));
    }
}
//ユーザーが選択したスキルを返す関数
string Select::GetSelectedSkill()
{
    return SkillTypeNames[selected_index_];
}
}    // namespace Select
