#pragma once
#include <System/Scene.h>

namespace Game01
{
	USING_PTR( Player_Abigail );

	class Player_Abigail : public Object
	{
	public:
		BP_OBJECT_DECL( Player_Abigail, u8"Game01 の Player Abigail" );

		bool Init() override;

		void Update() override;

	private:
	};

}	 // namespace Game01
