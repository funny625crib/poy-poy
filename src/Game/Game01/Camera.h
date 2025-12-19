#pragma once
#include <System/Scene.h>

namespace Game01 {
USING_PTR(Camera);

class Camera : public Object
{
public:
    BP_OBJECT_DECL(Camera, u8"Game01 の Camera");

    bool Init() override;

    void Update() override;

private:
    //4人分のプレイヤー位置を受け取る関数
    void cameraUpdate(const std::array<float3, 4>& playerPositions);
};
}    // namespace Game01
