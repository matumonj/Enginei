#include "Cllision.h"//collision

bool Cllision::ChenkSphere2Sphere(XMFLOAT3 object1, XMFLOAT3& object2,float r)
{
	//‰~“–‚½‚è”»’è
		float a = object1.x - object2.x;
		float b = object1.y - object2.y;
		float c = object1.z - object2.z;
		float distance = sqrtf(a * a + b * b + c * c);
		//int radius = R1;
		return distance<=r;
}

bool Cllision::CheckBox2Box(XMFLOAT3 object1, XMFLOAT3& object2, XMFLOAT3 r, XMFLOAT3 r2)
{
	BoxVertex Object1;
	BoxVertex Object2;

	//object1‚Ì‰E’¸“_
	Object1.Right = object1.x + r.x * 2;
	//object1‚Ì¶’¸“_
	Object1.Left = object1.x;
	//object1‚Ìã’¸“_
	Object1.Up = object1.y + r.y;
	//object1‚Ì‰º’¸“_
	Object1.Down = object1.y - r.y;

	//object1‚Ì‰E’¸“_
	Object2.Right = object2.x + r.x * 2;
	//object1‚Ì¶’¸“_
	Object2.Left = Object2.Right;
	//object1‚Ì‰º’¸“_
	Object2.Down = object2.y - r2.y;
	//object1‚Ìã’¸“_
	Object2.Up = object2.y + r2.y;

	//¨‚P‚Æ¶‚Q@¨‚Q‚Æ¶‚P@ã‚P‚Æ‰º‚Q@ã‚Q‚Æ‰º‚P
	return Object1.Right >= Object2.Left && Object2.Right >= Object1.Left && Object1.Up >= Object2.Down && Object2.Up >= Object1.Down;

}
