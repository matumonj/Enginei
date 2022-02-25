#include "Cllision.h"//collision

bool Cllision::ChenkSphere2Sphere(XMFLOAT3 object1, XMFLOAT3& object2,float r)
{
	//�~�����蔻��
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

	//object1�̉E���_
	Object1.Right = object1.x + r.x * 2;
	//object1�̍����_
	Object1.Left = object1.x;
	//object1�̏㒸�_
	Object1.Up = object1.y + r.y;
	//object1�̉����_
	Object1.Down = object1.y - r.y;

	//object1�̉E���_
	Object2.Right = object2.x + r.x * 2;
	//object1�̍����_
	Object2.Left = Object2.Right;
	//object1�̉����_
	Object2.Down = object2.y - r2.y;
	//object1�̏㒸�_
	Object2.Up = object2.y + r2.y;

	//���P�ƍ��Q�@���Q�ƍ��P�@��P�Ɖ��Q�@��Q�Ɖ��P
	return Object1.Right >= Object2.Left && Object2.Right >= Object1.Left && Object1.Up >= Object2.Down && Object2.Up >= Object1.Down;

}
