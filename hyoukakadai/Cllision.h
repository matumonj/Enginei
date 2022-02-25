#pragma once

#include<DirectXMath.h>
using namespace DirectX;
class Cllision
{
public:
	struct BoxVertex
	{
		float Up;
		float Down;
		float Left;
		float Right;
	};
public:
	static bool ChenkSphere2Sphere(XMFLOAT3 object1, XMFLOAT3& object2, float r);
	static bool CheckBox2Box(XMFLOAT3 object1, XMFLOAT3& object2, XMFLOAT3 r, XMFLOAT3 r2);
	
};

