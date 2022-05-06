#include "BoundEnemy.h"
#include<math.h>
#include"Line.h"

void BoundEnemy::Initialize()
{
	//モデルの読込
	EnemyModel = Model::CreateFromOBJ("bossenemy");
	//モデル割り当て
	//MobObject = new Object3d();
	EnemyObj = Object3d::Create();
	EnemyObj->SetModel(EnemyModel);
	//MobObject->Initialize();
	//パラメータのセット
	Ene_Scl = { 2,2,2 };
	Ene_Rot = { 0,180,0 };
	//Mob_Pos = { -10,-2,0 };
	//Position = { 24,10,0 };
	HP = 10;
}

void BoundEnemy::Update(XMFLOAT3 position)
{
	if (HP < 0) {
		enemyState = State::DEAD;
	}
	
	EnemyObj->SetScale({ 0.5f,0.5f,0.5f });
	EnemyObj->SetRotation({ 0,180,0 });

	EnemyObj->Update({ 1,1,1,1 });
	EnemyObj->SetPosition(Position);
}

void BoundEnemy::Draw()
{
	EnemyObj->PreDraw();
	EnemyObj->Draw();
	EnemyObj->PostDraw();
}

void BoundEnemy::BoundMove()
{
	Ene_Pos.x += moveSpeed;
	Ene_Pos.y += moveSpeed;
}

void BoundEnemy::Finalize()
{
	delete EnemyModel, EnemyObj;
}

void BoundEnemy::Motion(int time)
{
	switch (enemyState)
	{
	case State::ALIVE:
		break;
	case State::DEAD:
		break;
	}
}
