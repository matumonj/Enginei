#include "Collision.h"//collision
#include"Line.h"
void Collision::ColMap1(int map[15][200], std::unique_ptr<Object3d>  tst[15][200], float mapx[15][200], float mapy[15][200], const int X, const int Y, float& grav,float& time,float& movespeed,bool &jumpf, XMFLOAT3 &Player_Pos, XMFLOAT3 &Old_Pos)
{
	//grav-grav
	//time-time
	//movespeed-movespeed
	float height;
	float width;
	XMFLOAT3 Player_Scl = { 1,1,1 };
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			if (map[j][i] == 1) {
				mapx[j][i] = tst[j][i]->GetPosition().x;
				mapy[j][i] = tst[j][i]->GetPosition().y;
				height = tst[j][i]->GetScale().y;
				width = tst[j][i]->GetScale().x;

				if ((Player_Pos.x + Player_Scl.x > mapx[j][i] - (width - movespeed) && Player_Pos.x - Player_Scl.x < mapx[j][i] + (width - movespeed))) {
					if (Old_Pos.y > mapy[j][i] && Player_Pos.y - Player_Scl.y < mapy[j][i] + height) {
						Player_Pos.y = height + mapy[j][i] + Player_Scl.y;
						//moveSpeed = 0;
						grav = 0.0f;
						time = 0;
						jumpf = false;
						//Line::GetInstance()->SetBondflag(false);
						break;
					} else if (Old_Pos.y <mapy[j][i] && Player_Pos.y + Player_Scl.y>mapy[j][i] - height) {
						Player_Pos.y = mapy[j][i] - (Player_Scl.y + height);
						//Line::GetInstance()->SetBondflag(false);
						break;
					}

				} else {
					movespeed = 0.2f;
					grav = 0.03;
				}

				//�v���C���[�̍���
				if ((Player_Pos.y - Player_Scl.y < mapy[j][i] + height && mapy[j][i] - height < Player_Pos.y + Player_Scl.y)) {
					if (Player_Pos.x - Player_Scl.x < mapx[j][i] + width && mapx[j][i] < Old_Pos.x) {

						Player_Pos.y = Player_Pos.y + 0.001f;
						Player_Pos.x = width + mapx[j][i] + Player_Scl.x;
						//Line::GetInstance()->SetBondflag(false);
						break;
					}
					//�v���C���[�̉E��
					else if (Player_Pos.x + Player_Scl.x > mapx[j][i] - width && mapx[j][i] > Old_Pos.x) {

						Player_Pos.x = mapx[j][i] - (Player_Scl.x + width);
						//Line::GetInstance()->SetBondflag(false);
						break;
					}
				} else {
					movespeed = 0.2f;
				}
			}
		}
	}

//

for (int i = 0; i < X; i++) {
	for (int j = 0; j < Y; j++) {
		if (map[j][i] == 2 && Line::GetInstance()->Getboundflag() == false && Line::GetInstance()->getcolfsub() == false) {
			mapx[j][i] = tst[j][i]->GetPosition().x;
			mapy[j][i] = tst[j][i]->GetPosition().y;
			height = tst[j][i]->GetScale().y;
			width = tst[j][i]->GetScale().x;

			if ((Player_Pos.x + Player_Scl.x > mapx[j][i] - (width - movespeed) && Player_Pos.x - Player_Scl.x < mapx[j][i] + (width - movespeed))) {
				if (Old_Pos.y > mapy[j][i] && Player_Pos.y - Player_Scl.y < mapy[j][i] + height) {
					Player_Pos.y = height + mapy[j][i] + Player_Scl.y;
					//moveSpeed = 0;
					grav = 0.0f;
					time = 0;
					jumpf = false;
					//Line::GetInstance()->SetBondflag(false);
					break;
				} else if (Old_Pos.y <mapy[j][i] && Player_Pos.y + Player_Scl.y>mapy[j][i] - height) {
					Player_Pos.y = mapy[j][i] - (Player_Scl.y + height);
					//Line::GetInstance()->SetBondflag(false);
					break;
				}

			} else {
				movespeed= 0.2f;
				grav = 0.03;
			}

			//�v���C���[�̍���
			if ((Player_Pos.y - Player_Scl.y < mapy[j][i] + height && mapy[j][i] - height < Player_Pos.y + Player_Scl.y)) {
				if (Player_Pos.x - Player_Scl.x < mapx[j][i] + width && mapx[j][i] < Old_Pos.x) {

					Player_Pos.y = Player_Pos.y + 0.001f;
					Player_Pos.x = width + mapx[j][i] + Player_Scl.x;
					//Line::GetInstance()->SetBondflag(false);
					break;
				}
				//�v���C���[�̉E��
				else if (Player_Pos.x + Player_Scl.x > mapx[j][i] - width && mapx[j][i] > Old_Pos.x) {

					Player_Pos.x = mapx[j][i] - (Player_Scl.x + width);
					//Line::GetInstance()->SetBondflag(false);
					break;
				}
			} else {
			movespeed = 0.2f;
			}
		}
	}
}

/// <summary>
/// 
/// 
/// </summary>
/// <param name="dxCommon"></param>

for (int i = 0; i < X; i++) {
	for (int j = 0; j < Y; j++) {

		if (map[j][i] == 2 && Line::GetInstance()->Getboundflag() == true && Line::GetInstance()->getcolfsub() == true) {
			mapx[j][i] = tst[j][i]->GetPosition().x;
			mapy[j][i] = tst[j][i]->GetPosition().y;
			height = tst[j][i]->GetScale().y + 0.2f;
			width = tst[j][i]->GetScale().x + 0.2f;

			if ((Player_Pos.x + Player_Scl.x > mapx[j][i] - (width - movespeed) && Player_Pos.x - Player_Scl.x < mapx[j][i] + (width - movespeed))) {
				if (Old_Pos.y > mapy[j][i] && Player_Pos.y - Player_Scl.y < mapy[j][i] + height) {
					map[j][i] = 0;
					Line::GetInstance()->setcolfsub(false);
					break;
				} else if (Old_Pos.y <mapy[j][i] && Player_Pos.y + Player_Scl.y>mapy[j][i] - height) {
					map[j][i] = 0;
					Line::GetInstance()->setcolfsub(false);
					break;
				}

			}
			//�v���C���[�̍���
			if ((Player_Pos.y - Player_Scl.y < mapy[j][i] + height && mapy[j][i] - height < Player_Pos.y + Player_Scl.y)) {
				if (Player_Pos.x - Player_Scl.x < mapx[j][i] + width && mapx[j][i] < Old_Pos.x) {
					map[j][i] = 0;
					Line::GetInstance()->setcolfsub(false);
					break;
				}
				//�v���C���[�̉E��
				else if (Player_Pos.x + Player_Scl.x > mapx[j][i] - width && mapx[j][i] > Old_Pos.x) {
					map[j][i] = 0;
					Line::GetInstance()->setcolfsub(false);
					break;
				}
			}
		}
	}
}
}
void Collision::ClosestPtPoint2Triangle(const DirectX::XMVECTOR& point, const Triangle& triangle, DirectX::XMVECTOR* closest)
{
	// point��p0�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
	XMVECTOR p0_p1 = triangle.p1 - triangle.p0;
	XMVECTOR p0_p2 = triangle.p2 - triangle.p0;
	XMVECTOR p0_pt = point - triangle.p0;

	float d1 = XMVector3Dot(p0_p1, p0_pt).m128_f32[0];
	float d2 = XMVector3Dot(p0_p2, p0_pt).m128_f32[0];

	if (d1 <= 0.0f && d2 <= 0.0f)
	{
		// p0���ŋߖT
		*closest = triangle.p0;
		return;
	}

	// point��p1�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
	XMVECTOR p1_pt = point - triangle.p1;

	float d3 = XMVector3Dot(p0_p1, p1_pt).m128_f32[0];
	float d4 = XMVector3Dot(p0_p2, p1_pt).m128_f32[0];

	if (d3 >= 0.0f && d4 <= d3)
	{
		// p1���ŋߖT
		*closest = triangle.p1;
		return;
	}

	// point��p0_p1�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����point��p0_p1��ɑ΂���ˉe��Ԃ�
	float vc = d1 * d4 - d3 * d2;
	if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f)
	{
		float v = d1 / (d1 - d3);
		*closest = triangle.p0 + v * p0_p1;
		return;
	}

	// point��p2�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
	XMVECTOR p2_pt = point - triangle.p2;

	float d5 = XMVector3Dot(p0_p1, p2_pt).m128_f32[0];
	float d6 = XMVector3Dot(p0_p2, p2_pt).m128_f32[0];
	if (d6 >= 0.0f && d5 <= d6)
	{
		*closest = triangle.p2;
		return;
	}

	// point��p0_p2�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����point��p0_p2��ɑ΂���ˉe��Ԃ�
	float vb = d5 * d2 - d1 * d6;
	if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f)
	{
		float w = d2 / (d2 - d6);
		*closest = triangle.p0 + w * p0_p2;
		return;
	}

	// point��p1_p2�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����point��p1_p2��ɑ΂���ˉe��Ԃ�
	float va = d3 * d6 - d5 * d4;
	if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f)
	{
		float w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
		*closest = triangle.p1 + w * (triangle.p2 - triangle.p1);
		return;
	}

	// point�͖ʗ̈�̒��ɂ���Bclosest���d�S���W��p���Čv�Z����
	float denom = 1.0f / (va + vb + vc);
	float v = vb * denom;
	float w = vc * denom;
	*closest = triangle.p0 + p0_p1 * v + p0_p2 * w;
}
bool Collision::CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB, DirectX::XMVECTOR* inter, DirectX::XMVECTOR* reject)
{
	// ���S�_�̋����̂Q�� <= ���a�̘a�̂Q��@�Ȃ����
	float dist = XMVector3LengthSq(sphereA.center - sphereB.center).m128_f32[0];

	float radius2 = sphereA.radius + sphereB.radius;
	radius2 *= radius2;

	if (dist <= radius2) {
		if (inter) {
			// A�̔��a��0�̎����W��B�̒��S�@B�̔��a��0�̎����W��A�̒��S�@�ƂȂ�悤�⊮
			float t = sphereB.radius / (sphereA.radius + sphereB.radius);
			*inter = XMVectorLerp(sphereA.center, sphereB.center, t);
		}
		// �����o���x�N�g�����v�Z
		if (reject) {
			float rejectLen = sphereA.radius + sphereB.radius - sqrtf(dist);
			*reject = XMVector3Normalize(sphereA.center - sphereB.center);
			*reject *= rejectLen;
		}
		return true;
	}

	return false;
}

bool Collision::CheckSphere2Triangle(const Sphere& sphere, const Triangle& triangle, DirectX::XMVECTOR* inter, DirectX::XMVECTOR* reject)
{
	XMVECTOR p;
	// ���̒��S�ɑ΂���ŋߐړ_�ł���O�p�`��ɂ���_p��������
	ClosestPtPoint2Triangle(sphere.center, triangle, &p);
	// �_p�Ƌ��̒��S�̍����x�N�g��
	XMVECTOR v = p - sphere.center;
	// �����̓������߂�
	//�i�����x�N�g�����m�̓��ς͎O�����̒藝�̃��[�g�����̎��ƈ�v����j
	float distanceSquare = XMVector3Dot(v, v).m128_f32[0];
	// ���ƎO�p�`�̋��������a�ȉ��Ȃ瓖�����Ă��Ȃ�
	if (distanceSquare > sphere.radius * sphere.radius)	return false;
	// �[����_���v�Z
	if (inter) {
		// �O�p�`��̍ŋߐړ_p���^����_�Ƃ���
		*inter = p;
	}
	// �����o���x�N�g�����v�Z
	if (reject) {
		float ds = XMVector3Dot(sphere.center, triangle.normal).m128_f32[0];
		float dt = XMVector3Dot(triangle.p0, triangle.normal).m128_f32[0];
		float rejectLen = dt - ds + sphere.radius;
		*reject = triangle.normal * rejectLen;
	}
	return true;
}

bool Collision::Boxcol(XMFLOAT2 a1, XMFLOAT2 a2, XMFLOAT2 b1, XMFLOAT2 b2)
{
	if (b1.x > a2.x) { return false; }
	if (a1.x > b2.x) { return false; }
	if (b1.y > a2.y) { return false; }
	if (a1.y > b2.y) { return false; }
	return true;
}
bool Collision::CheckBox2Box(XMFLOAT3 object1, XMFLOAT3& object2, XMFLOAT3 r, XMFLOAT3 r2)
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
bool Collision::CheckRay2Plane(const Ray& lay, const Plane& plane, float* distance, DirectX::XMVECTOR* inter)
{
	const float epsilon = 1.0e-5f;	// �덷�z���p�̔����Ȓl

	float d1 = XMVector3Dot(plane.normal, lay.dir).m128_f32[0];
	// ���ʂɂ͓�����Ȃ�
	if (d1 > -epsilon) {
		return false;
	}

	float d2 = XMVector3Dot(plane.normal, lay.start).m128_f32[0];
	float t = (plane.distance - d2) / d1;

	if (t < 0) return false;

	// ��������������
	if (distance) {
		*distance = t;
	}

	// ��_���v�Z
	if (inter) {
		*inter = lay.start + t * lay.dir;
	}

	return true;
}

bool Collision::CheckRay2Triangle(const Ray& lay, const Triangle& triangle, float* distance, DirectX::XMVECTOR* inter)
{
	// �O�p�`������Ă��镽�ʂ��Z�o
	Plane plane;
	XMVECTOR interPlane;
	plane.normal = triangle.normal;
	plane.distance = XMVector3Dot(triangle.normal, triangle.p0).m128_f32[0];
	// ���C�ƕ��ʂ��������Ă��Ȃ���΁A�������Ă��Ȃ�	
	if (!CheckRay2Plane(lay, plane, distance, &interPlane)) {
		return false;
	}
	// ���C�ƕ��ʂ��������Ă����̂ŁA�����ƌ�_���������܂ꂽ

	// ���C�ƕ��ʂ̌�_���O�p�`�̓����ɂ��邩����
	const float epsilon = 1.0e-5f;	// �덷�z���p�̔����Ȓl
	XMVECTOR m;
	// ��p0_p1�ɂ���
	XMVECTOR pt_p0 = triangle.p0 - interPlane;
	XMVECTOR p0_p1 = triangle.p1 - triangle.p0;
	m = XMVector3Cross(pt_p0, p0_p1);
	// �ӂ̊O��
	if (XMVector3Dot(m, triangle.normal).m128_f32[0] < -epsilon) {
		return false;
	}

	// ��p1_p2�ɂ���
	XMVECTOR pt_p1 = triangle.p1 - interPlane;
	XMVECTOR p1_p2 = triangle.p2 - triangle.p1;
	m = XMVector3Cross(pt_p1, p1_p2);
	// �ӂ̊O��
	if (XMVector3Dot(m, triangle.normal).m128_f32[0] < -epsilon) {
		return false;
	}

	// ��p2_p0�ɂ���
	XMVECTOR pt_p2 = triangle.p2 - interPlane;
	XMVECTOR p2_p0 = triangle.p0 - triangle.p2;
	m = XMVector3Cross(pt_p2, p2_p0);
	// �ӂ̊O��
	if (XMVector3Dot(m, triangle.normal).m128_f32[0] < -epsilon) {
		return false;
	}

	if (inter) {
		*inter = interPlane;
	}

	// �����Ȃ̂ŁA�������Ă���
	return true;
}

bool Collision::CheckRay2Sphere(const Ray& lay, const Sphere& sphere, float* distance, DirectX::XMVECTOR* inter)
{
	XMVECTOR m = lay.start - sphere.center;
	float b = XMVector3Dot(m, lay.dir).m128_f32[0];
	float c = XMVector3Dot(m, m).m128_f32[0] - sphere.radius * sphere.radius;
	// lay�̎n�_��sphere�̊O���ɂ���(c > 0)�Alay��sphere���痣��Ă���������
	// �����Ă���ꍇ(b > 0)�A������Ȃ�
	if (c > 0.0f && b > 0.0f) {
		return false;
	}

	float discr = b * b - c;
	// ���̔��ʎ��̓��C�������O��Ă��邱�ƂɈ�v
	if (discr < 0.0f) {
		return false;
	}

	// ���C�͋��ƌ������Ă���B
	// ��������ŏ��̒lt���v�Z
	float t = -b - sqrtf(discr);
	// t�����ł���ꍇ�A���C�͋��̓�������J�n���Ă���̂�t���[���ɃN�����v
	if (t < 0) t = 0.0f;

	if (distance) {
		*distance = t;
	}

	if (inter) {
		*inter = lay.start + t * lay.dir;
	}

	return true;
}

float Collision::LinetoBoxCollision(const int Map_X, const int Map_Y, Object3d** map[], Player*player,float radius)
{
	BoxVertex** MapObject;
	BoxVertex PlayerObject;

	PlayerObject.Left = player->GetPosition().x - 1;
	PlayerObject.Right = player->GetPosition().x + 1;
	PlayerObject.Up = player->GetPosition().y+ 1;
	PlayerObject.Down= player->GetPosition().y - 1;
	
	for (int i = 0; i < Map_Y; i++) {
		for (int j = 0; j < Map_X; j++) {
			MapObject[i][j].Right = map[i][j]->GetPosition().x + 1;
			MapObject[i][j].Left = map[i][j]->GetPosition().x - 1;
			MapObject[i][j].Up = map[i][j]->GetPosition().y + 1;
			MapObject[i][j].Down = map[i][j]->GetPosition().y - 1;

		}
	}
	for (int i = 0; i < Map_Y; i++) {
		for (int j = 0; j < Map_X; j++) {
			return MapObject[i][j].Right >= PlayerObject.Left && PlayerObject.Right >= MapObject[i][j].Left && MapObject[i][j].Up >= PlayerObject.Down && PlayerObject.Up >= MapObject[i][j].Down;
		}
	}
	
}

bool Collision::BoxCollision_Down(XMFLOAT3 object1, XMFLOAT3 radius1, XMFLOAT3 object2, XMFLOAT3 radius2) {
	BoxVertex Object1;
	BoxVertex Object2;

	//object1�̉E���_
	Object1.Right = object1.x + radius1.x;
	//object1�̍����_
	Object1.Left = object1.x - radius1.x;
	//object1�̏㒸�_
	Object1.Up = object1.y + radius1.y;
	//object1�̉����_
	Object1.Down = object1.y - radius1.y;

	//object1�̍����_
	Object2.Left = object2.x - radius2.x;
	//object1�̉E���_
	Object2.Right = object2.x + radius2.x;
	//object1�̉����_
	Object2.Down = object2.y - radius2.y;
	//object1�̏㒸�_
	Object2.Up = Object2.Down + 2;
	//���P�ƍ��Q�@���Q�ƍ��P�@��P�Ɖ��Q�@��Q�Ɖ��P
	return Object1.Right > Object2.Left && Object2.Right > Object1.Left && Object1.Up > Object2.Down && Object2.Up > Object1.Down;
}

bool Collision::BoxCollision_Up(XMFLOAT3 object1, XMFLOAT3 radius1, XMFLOAT3 object2, XMFLOAT3 radius2) {
	BoxVertex Object1;
	BoxVertex Object2;

	//object1�̉E���_
	Object1.Right = object1.x + radius1.x;
	//object1�̍����_
	Object1.Left = object1.x - radius1.x;
	//object1�̏㒸�_
	Object1.Up = object1.y + radius1.y;
	//object1�̉����_
	Object1.Down = object1.y - radius1.y;

	//object1�̍����_
	Object2.Left = object2.x - radius2.x;
	//object1�̉E���_
	Object2.Right = object2.x + radius2.x;
	//object1�̉����_
	Object2.Down = object2.y - radius2.y;
	//object1�̏㒸�_
	Object2.Up = Object2.Down - 2;
	//���P�ƍ��Q�@���Q�ƍ��P�@��P�Ɖ��Q�@��Q�Ɖ��P
	return Object1.Right > Object2.Left && Object2.Right > Object1.Left && Object1.Up >= Object2.Down && Object2.Up >= Object1.Down;
}


bool Collision::BoxCollision_Left(XMFLOAT3 object1, XMFLOAT3 radius1, XMFLOAT3 object2, XMFLOAT3 radius2) {
	BoxVertex Object1;
	BoxVertex Object2;

	//object1�̉E���_
	Object1.Right = object1.x + radius1.x;
	//object1�̍����_
	Object1.Left = object1.x;
	//object1�̏㒸�_
	Object1.Up = object1.y + radius1.y;
	//object1�̉����_
	Object1.Down = object1.y - radius1.y;

	//object1�̍����_
	Object2.Left = object2.x - radius2.x;
	//object1�̉E���_
	Object2.Right = Object2.Left+2;
	//object1�̉����_
	Object2.Down = object2.y - radius2.y;
	//object1�̏㒸�_
	Object2.Up = object2.y + radius2.y;
	//���P�ƍ��Q�@���Q�ƍ��P�@��P�Ɖ��Q�@��Q�Ɖ��P
	return Object1.Right >= Object2.Left && Object2.Right >= Object1.Left && Object1.Up >= Object2.Down && Object2.Up >= Object1.Down;
}

bool Collision::BoxCollision_Right(XMFLOAT3 object1, XMFLOAT3 radius1, XMFLOAT3 object2, XMFLOAT3 radius2) {
	BoxVertex Object1;
	BoxVertex Object2;

	//object1�̉E���_
	Object1.Right = object1.x + radius1.x;
	//object1�̍����_
	Object1.Left = object1.x;
	//object1�̏㒸�_
	Object1.Up = object1.y + radius1.y;
	//object1�̉����_
	Object1.Down = object1.y - radius1.y;

	//object1�̉E���_
	Object2.Right = object2.x + radius2.x;
	//object1�̍����_
	Object2.Left = Object2.Right-2;
	//object1�̉����_
	Object2.Down = object2.y - radius2.y;
	//object1�̏㒸�_
	Object2.Up = object2.y + radius2.y;
	//���P�ƍ��Q�@���Q�ƍ��P�@��P�Ɖ��Q�@��Q�Ɖ��P
	return Object1.Right >= Object2.Left && Object2.Right >= Object1.Left && Object1.Up >= Object2.Down && Object2.Up >= Object1.Down;
}