#include "MobEnemy.h"
#include<math.h>
#include"Line.h"
/// <summary>
/// コンストラクタ
/// </summary>
MobEnemy::MobEnemy()
{
}

/// <summary>
/// デストラクタ
/// </summary>
MobEnemy::~MobEnemy()
{
	delete MobObject, MobModel;
}

//初期化処理
void MobEnemy::Initialize()
{
	//モデルの読込
	MobModel = Model::CreateFromOBJ("bossenemy");
	//モデル割り当て
	//MobObject = new Object3d();
	MobObject = Object3d::Create();
	MobObject->SetModel(MobModel);
	//MobObject->Initialize();
	//パラメータのセット
	Mob_Scl = { 2,2,2 };
	Mob_Rot = { 0,180,0 };
	Mob_Pos = { -10,-2,0 };
	Position = { 20,0,0 };
	HP = 10;

}

//更新処理
void MobEnemy::Update(XMFLOAT3 position)
{
	//float lx = Line::GetInstance()->getpos().x;
	//float ly= Line::GetInstance()->getpos().y;
	////パラメータのセット
	//float dis;
	//
	//	dis = sqrtf((lx-Position.x) * (lx - Position.x) +
	//		(ly - Position.y) * (ly - Position.y));

	//	if (dis <= 2 &&Line::GetInstance()->Gettriggerflag()) {
	//		Line::GetInstance()->Setelf(true);
	//	}

	//	if (Line::GetInstance()->Getelf()) {
	//		Line::GetInstance()->Setpos(Position.x,Position.y);
	//	}
	//モブ
	//MobObject->SetPosition(Position);
	if (HP < 0) {
		enemyState = State::DEAD;
	} else {
	//	enemyState = State::ALIVE;
	}
	MobObject->SetScale({ 0.5,0.5,0.5 });
	MobObject->SetRotation({ 0,180,0 });

	//Follow(position);
	MobObject->Update({ 1,1,1,1 });
	MobObject->SetPosition(Position);

}

//描画処理
void MobEnemy::Draw()
{
	MobObject->PreDraw();
	MobObject->Draw();
	MobObject->PostDraw();
}

//解放処理
void MobEnemy::Finalize()
{
	delete MobObject, MobModel;
}
void MobEnemy::EnemySearchPlayer(XMFLOAT3 player)
{
	Follow(player);
}

void MobEnemy::Follow(XMFLOAT3 player)
{
	float angleX, angleZ, angleR;
	float centerSpeed = 0.1f;
	angleX = (player.x - Position.x);
	angleZ = (player.y - Position.y);
	angleR = sqrtf((Position.x - player.x) * (Position.x - player.x)
		+ (Position.y - player.y) * (Position.y - player.y));
	Position.x += (angleX / angleR) * centerSpeed;
	Position.y += (angleZ / angleR) * centerSpeed;
	//Position.x =player.x;
	//Position.y =player.y;
	//MobObject->SetPosition(Position);
	//MobObject->SetPosition(Position);
}

void MobEnemy::Motion(int timer)
{
	switch (enemyState)
	{
	case State::ALIVE:

		break;

	case State::DEAD:

		break;
	}

}