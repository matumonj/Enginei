#include "Helper.h"

void Helper::Follow(XMFLOAT3& position, XMFLOAT3& position2,float dis,float speed)
{
	float angleX, angleZ, angleR;
	angleX = (position.x - position2.x);
	angleZ = (position.y - position2.y);
	angleR = sqrtf((position2.x - position.x) * (position2.x - position.x));
	if (angleR > dis) {
		position2.x += (angleX / angleR) * speed;
		//Position.y += (angleZ / angleR) * bossmovespeed;
	}
}