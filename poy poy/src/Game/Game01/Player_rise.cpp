#include "Player_rise.h"
#include <DxLib.h>
#include <System/Component/ComponentModel.h>
#include <System/Component/ComponentCollisionModel.h>
#include <System/Component/ComponentCollisionCapsule.h>
#include <System/Component/ComponentObjectController.h>
#include <Game/Component/ComponentGameCamera.h>
#include <Game/Component/State/StateIdleWalk.h>
#include <Game/Component/State/StateJump.h>

namespace Game01
{
	bool Player_Rise::Init()
	{
		Super::Init();

		// プレイヤー
		SetName( "Player Rise" );
		SetTranslate( { -87.0f, -6.0f, 47.0f } );

		auto col = AddComponent<ComponentCollisionCapsule>();	 //
		col->SetRadius( 4.53f );
		col->SetHeight( 16.81f );
		col->UseGravity();
		col->SetCollisionGroup( ComponentCollision::CollisionGroup::PLAYER );

		auto model		= AddComponent<ComponentModel>( "data/Sample/Player/Rise_school/Rise.mv1" );
		model->Matrix() = matrix::scale( 0.7f );
		model->SetAnimation( {
			{"idle",	  "data/Sample/Player/Rise_school/Anim/Idle.mv1", 0, 1.0f},
			{"walk", "data/Sample/Player/Rise_school/Anim/Walking.mv1", 0, 1.0f},
			{"jump",	  "data/Sample/Player/Rise_school/Anim/Jump.mv1", 0, 1.0f},
			{ "run",	 "data/Sample/Player/Rise_school/Anim/Run.mv1", 0, 1.0f},
		} );
		//model->SetScaleAxisXYZ( { 1, 1, 1 } );

		AddComponent<ComponentGameCamera>();

		AddComponent<StateIdleWalk>();

		return true;
	}

	void Player_Rise::Update()
	{
		Super::Update();

		enum
		{
			MODE_IDLE,		   //プレイヤーが立っているとき
			MODE_JUMP_WAIT,	   //ジャンプ前に少し待つ
			MODE_JUMP,		   //ジャンプ
		};
		static int player_mode = MODE_IDLE;	   //プレイヤーのモード

		static int ani_time		 = 0;	 //ジャンプの持続時間
		static int ani_wait_time = 0;	 //ジャンプ前の待機時間

		if( Input::IsKeyDown( KEY_INPUT_SPACE ) && player_mode == MODE_IDLE )
		{
			player_mode	  = MODE_JUMP_WAIT;
			ani_wait_time = 30;
		}

		if( player_mode == MODE_JUMP_WAIT )
		{
			ani_wait_time--;
			if( ani_wait_time < 0 )
			{
				ani_time	  = 40;
				player_mode	  = MODE_JUMP;
				ani_wait_time = 0;
			}
		}
		else if( player_mode == MODE_JUMP )
		{
			ani_time--;
			if( ani_time > 0 )
			{
				AddTranslate( { 0, 0.5, 0 } );
			}
			else
			{
				ani_time	= 0;
				player_mode = MODE_IDLE;
			}
		}

		// ジャンプしていて、アニメーションが一定数値以上ならば、慣性の法則にしたがって上に移動させる
	}
}	 // namespace Game01
