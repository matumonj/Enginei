#include "TargetMarker.h"
#include"Input.h"
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>

void TargetMarker::Initialize()
{
	Texture::LoadTexture(8, L"Resources/targetcircle.png");
	TargetMakerTexture = Texture::Create(8, { 0,-50,50 }, { 1,1,1 }, { 1,1,1,1 });
	TargetMakerTexture->CreateTexture();

	//MarkerPosition = { -10,2,0 };
}

bool TargetMarker::GetEnemyPosition(Enemy* enemy[], int index, float *x, float *y, float* z)
{
	float tempx, tempy, tempz;
	if (enemy[index] ==NULL/*|敵が死んでいるかどうかのフラグがon|*/) 
		return false;
	
	//指定された添え字の敵座標を取得
	enemy[index]->Getposition(&tempx,&tempy,&tempz);
	*x= tempx;
	*y= tempy;
	*z=tempz;

	return true;
}
int TargetMarker::NearEnemySearch(Enemy* enemy[],Player*player)
{
	int nearindex = -1;
	float nearresult = 0;
	float ex, ey, ez;
	float tx, ty, tz;
	float distance;
	for (int i = 0; i < 3/*enemynum*/; ++i) {
		if (!GetEnemyPosition(enemy, i, &ex, &ey, &ez)) {
			continue;
		}
			tx = ex - player->GetPosition().x;
			ty = ey - player->GetPosition().y;
			tz = ez - player->GetPosition().z;
		
		if (nearindex == -1) {
			nearindex = i;
			nearresult = sqrt(tx * tx + ty * ty + tz * tz);
			continue;
		}
		//比較して小さければそれを最小値に
		if (nearresult > sqrt(tx * tx + ty * ty + tz * tz)) {
			nearindex = i;
			nearresult = sqrt(tx * tx + ty * ty + tz * tz);
		}
		this->nearindex = nearindex;
	//	if(nearresult)
	}
	return nearindex;
}
void TargetMarker::Update(Enemy* enemy[], DebugCamera* camera,Player*player)
{
	int tindex;
	float ex, ey, ez;
	tindex = NearEnemySearch(enemy,player);
	
	GetEnemyPosition(enemy, tindex, &ex, &ey, &ez);//{ enemy[0]->GetPosition().x ,0, enemy[0]->GetPosition().z };

	//マーカー位置をnowTargetに合わせる
	MarkerPosition  = { ex,ey,ez };
	nowTarget = MarkerPosition;

	if (Input::GetInstance()->Pushkey(DIK_L)) {
		MarkerPosition.y+=0.2;
	}
	if (Input::GetInstance()->Pushkey(DIK_K)) {
		MarkerPosition.y-=0.2;
	}
	
	TargetMakerTexture->SetRotation({ rot, 0, 0 });

	TargetMakerTexture->SetPosition(MarkerPosition);
	TargetMakerTexture->Update(camera->GetViewMatrix(), camera->GetProjectionMatrix());
}

void TargetMarker::Draw(DirectXCommon* dxcomn)
{
	//Texture::PreDraw(dxcomn->GetCmdList());
	TargetMakerTexture->Draw();
	//Texture::PostDraw();
}
void TargetMarker::Finalize()
{
	delete TargetMakerTexture;

}