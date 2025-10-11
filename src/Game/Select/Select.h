#pragma once
#include <System/Scene.h>
#include <string>
using namespace std;
namespace Select {
USING_PTR(Select);

class Select : public Scene::Base
{
public:
    BP_CLASS_DECL(Select, u8"Game02 の Selectのシーン!!!");

    bool Init() override;

    void Update() override;

    void Draw() override;

    string GetSelectedSkill();

    static const int SkillTypeCount = 7;

    string SkillTypeNames[SkillTypeCount];
    // enum SkillType
    // {
    //     Acceleration,    //超加速
    //     Charge,          //突進
    //     Strength,        //怪力
    //     Avoidance,       //回避
    //     Infiltration,    //潜伏
    //     Intimidation,    //威嚇
    //     Shield,          //シールド
    //     SkillTypeCount
    // };

private:
    int    text_x_         = 500;
    int    text_y_         = 200;
    int    mouse_x_        = 0;     //マウスが押されたときにマウスのX座標を取得する変数
    int    mouse_y_        = 0;     //マウスが押されたときにマウスのY座標を取得する変数
    int    selected_index_ = -1;    // 選択されたスキルタイプのインデックス
    string selected_skill_;         //選択されたスキルタイプの名前
};
}    // namespace Select
