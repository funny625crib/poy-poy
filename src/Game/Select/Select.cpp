#include <System/Scene.h>
#include <Game/Game01/Game01.h>
#include <Game/Game01/Camera.h>
#include <System/Component/ComponentModel.h>
#include <Game/Game01/Player_rise.h>
#include <Game/Game01/Player_sol.h>
#include <Game/Game01/Player_abigail.h>
#include <Game/Game01/Player_betty.h>
#include <Game/Component/State/BettyStateIdleWalk.h>
#include <Game/Component/State/StateIdleWalk.h>
#include <Game/SceneFade/SceneFade.h>
#include "Select.h"
#include "SelectStage.h"

namespace Select {
Fade fadeout;    //シーンフェイドクラスの関数を使うため宣言
//タイトル用変数の初期化処理
bool Select::Init()
{
    //ステージを作成
    Scene::Object::Create<Game01::SelectStage>(u8"Game01のSelectStage");
    //シーン上にカメラオブジェクトを作成して設置
    auto camObj = Scene::Object::Create<Object>(u8"SelectCamera");
    if(camObj) {
        // カメラコンポーネントを追加して位置と注視点を設定
        auto cam = camObj->AddComponent<ComponentCamera>();
        // カメラをカレントに設定
        cam->SetPositionAndTarget({0.0f, 30.0f, -120.0f}, {0.0f, 30.0f, 0.0f})->SetCurrentCamera();
    }
    // プレイヤー
    // 各キャラクターのStateIdleWalkコンポーネントを削除
    auto rise = Scene::Object::Create<Game01::Player_Rise>();
    if(rise)
        rise->RemoveComponent<StateIdleWalk>();

    auto betty = Scene::Object::Create<Game01::Player_Betty>();
    if(betty) {
        // コンポーネントを確実に全て削除（同種コンポーネントが複数ある可能性をカバー）
        while(betty->GetComponent<StateIdleWalk>() != nullptr) {
            betty->RemoveComponent<StateIdleWalk>();
        }
        while(betty->GetComponent<BettyStateIdleWalk>() != nullptr) {
            betty->RemoveComponent<BettyStateIdleWalk>();
        }

        // アニメーションを強制的に idle（ループ）にするか、停止する
        if(auto model = betty->GetComponent<ComponentModel>()) {
            // 常に idle のループ再生にする（歩きアニメが再設定されても優先される）
            model->PlayAnimation("idle", true);
        }
    }
    auto abigail = Scene::Object::Create<Game01::Player_Abigail>();
    if(abigail)
        abigail->RemoveComponent<StateIdleWalk>();

    auto sol = Scene::Object::Create<Game01::Player_Sol>();
    if(sol)
        sol->RemoveComponent<StateIdleWalk>();

    //SkillTypeNames[0] = "超加速";
    //SkillTypeNames[1] = "突進";
    //SkillTypeNames[2] = "怪力";
    //SkillTypeNames[3] = "回避";
    //SkillTypeNames[4] = "潜伏";
    //SkillTypeNames[5] = "威嚇";
    //SkillTypeNames[6] = "シールド";
    return true;
}
//タイトルの更新処理
void Select::Update()
{
    //if(Input::IsKeyDown(KEY_INPUT_SPACE)) {
    //    // 次のシーンに移動準備します
    //    fadeout.FadeOut();    //Game01シーンにフェイドアウト
    //}

    // フェードアウトを実行していい状態なら
    //if(!fadeout.WaitFadeOut()) {
    //    // シーンを切り替えます
    //    Scene::Change(Scene::GetScene<Game01::Game01>());
    //}
    //
    ////マウスの位置を取得
    //GetMousePoint(&mouse_x_, &mouse_y_);
    ////マウスがクリックされたら
    //if(GetMouseInput() & MOUSE_INPUT_LEFT) {
    //    for(int i = 0; i < SkillTypeCount; i++) {
    //        int y      = text_y_ + (i * 50);
    //        int width  = 200;    // 文字列の幅（適宜調整）
    //        int height = 40;     // 文字列の高さ（適宜調整）
    //        //マウスの位置が文字列の範囲内にあるかをチェック
    //        if(mouse_x_ >= text_x_ && mouse_x_ <= text_x_ + width && mouse_y_ >= y && mouse_y_ <= y + height) {
    //            selected_index_ = i;
    //            // 選択したスキルをインゲームに渡すために変数に格納
    //            selected_skill_ = SkillTypeNames[i];
    //            // シーンを切り替えます
    //            Scene::Change(Scene::GetScene<Game01::Game01>());
    //        }
    //    }
    //}
}
void Select::Draw()
{
    ////スキルタイプの名前を表示
    //for(int i = 0; i < SkillTypeCount; i++) {
    //    DrawString(text_x_, text_y_ + (i * 50), SkillTypeNames[i].c_str(), GetColor(255, 255, 255));
    //}
}
//ユーザーが選択したスキルを返す関数
string Select::GetSelectedSkill()
{
    return SkillTypeNames[selected_index_];
}
}    // namespace Select
