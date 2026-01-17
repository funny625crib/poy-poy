#include "Game01.h"
#include "Ground.h"
#include "Camera.h"

#include "Animal/Animal.h"
#include "Arrow/Arrow_Rise.h"
#include "Arrow/Arrow_Abigail.h"
#include "Arrow/Arrow_Sol.h"
#include "Arrow/Arrow_Betty.h"
#include "TIme_bomb.h"
#include "Animal/AnimalGenerator.h"
#include "Player/Player_rise.h"
#include "Player/Player_sol.h"
#include "Player/Player_betty.h"
#include "Player/Player_abigail.h"
#include <Game/SceneFade/SceneFade.h>

#include "Hp.h"
#include <Game/Ranking/Ranking.h>
namespace Game01 {
#if 1    // 参考用
class GameObject
{
public:
    int data = 0;

    virtual void Update() { OutputDebugString("Update"); }
};

class GamePlayer : public GameObject
{
public:
    int              player_data = 0;
    /*virtual*/ void Update() override { OutputDebugString("PlayerUpdate\n"); }
};

std::vector<GameObject*> objects;
std::vector<GamePlayer*> players;

void GameUpdate()
{
    GamePlayer* p1 = new GamePlayer();
    GamePlayer* p2 = new GamePlayer();

    players.push_back(p1);
    players.push_back(p2);
    //players.push_back( e1 ); // ERROR

    objects.push_back(p1);
    objects.push_back(p2);

    for(auto p : players) {
        int a = p->data;
        int b = p->player_data;
    }

    for(auto o : objects) {
        int a = o->data;
        //int b = e->player_data; // ERROR
        //int c = e->enemy_data; // ERROR
        o->Update();
    }

    delete p1;
    delete p2;
}

#endif

Fade fade;    //シーンフェイドクラスの関数を使うため宣言
bool Game01::Init()
{
    GameUpdate();

    // グランド
    Scene::Object::Create<Ground>();

    // プレイヤー
    Scene::Object::Create<Player_Rise>();
    Scene::Object::Create<Player_Betty>();
    Scene::Object::Create<Player_Abigail>();
    Scene::Object::Create<Player_Sol>();

    // 動物生成器
    Scene::Object::Create<Generator>();

    //動物
    for(int i = 0; i < 15; ++i) {
        Scene::Object::Create<Animal>();
    }

    // カメラオブジェクト
    Scene::Object::Create<Camera>();

    Scene::Object::Create<Hp>();

    Scene::Object::Create<Time_bomb>();

    Scene::Object::Create<Arrow_Rise>();

    Scene::Object::Create<Arrow_Abigail>();

    Scene::Object::Create<Arrow_Sol>();

    Scene::Object::Create<Arrow_Betty>();

    // -----------------------------------------------------------------------------------------
    // 空オブジェクト(SkyDome)の追加 ④
    // -----------------------------------------------------------------------------------------
    {
        auto obj = Scene::Object::Create<Object>()    //< Object作成
                       ->SetName("Sky");

        // オブジェクトにモデル能力を追加します
        obj->AddComponent<ComponentModel>("data/Sample/SwordBout/Stage/Stage00_sky.mv1");
        obj->SetTranslate({0, -739.0f, 0});
    }

    fade.FadeIn();    //タイトルシーンからのフェイドイン

    return true;
}

void Game01::Update()
{
    // フェードイン中なら待つ
    if(fade.WaitFadeIn())
        return;
    //--------------------------------------------------------------
    // 雲を動かすように空をY軸で少しづつ回転させます　⑤
    //--------------------------------------------------------------
    if(auto sky = Scene::Object::Get<Object>("Sky")) {
        sky->AddRotationAxisXYZ({0, 0.1f, 0});
    }

    auto hp_obj = Scene::Object::Get<Hp>();
    //三人が倒されたらリザルトへ
    if(hp_obj->Hp_death_count >= 3) {
        fade.FadeOut();    //Game01シーンにフェイドアウト
    }
    if(!fade.WaitFadeOut()) {
        Scene::Change(Scene::GetScene<Ranking::Ranking>());
    }
    //--------------------------------------------------------------
}

void Game01::Draw()
{
    printfDx("　　Zキー：無敵化　　Xキー：回復　　Cキー：怪力　　Ⅴキー：威嚇　　");
}

}    // namespace Game01
