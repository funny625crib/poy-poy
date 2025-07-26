#pragma once
#include <System/Scene.h>

namespace Game01
{
	USING_PTR( Player_Rise );

	class Player_Rise : public Object
	{
	public:
		BP_OBJECT_DECL( Player_Rise, u8"Game01 の Player Rise" );

		bool Init() override;

		void Update() override;

	private:
	};

}	 // namespace Game01
