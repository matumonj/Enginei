#include "ThrowEnemy.h"
#include"Line.h"
ThrowEnemy::ThrowEnemy()
{
}

/// <summary>
/// デストラクタ
/// </summary>
ThrowEnemy::~ThrowEnemy()
{
	delete EnemyObj, EnemyModel;
	delete ThrowObj, ThrowModel;
}
void ThrowEnemy::Initialize()
{

	//モデルの読込
	EnemyModel = Model::CreateFromOBJ("subenemy");
	//モデル割り当て
	//MobObject = new Object3d();
	EnemyObj = Object3d::Create();
	EnemyObj->SetModel(EnemyModel);

	//モデルの読込
	ThrowModel = Model::CreateFromOBJ("sphere");
	//モデル割り当て
	//MobObject = new Object3d();
	ThrowObj = Object3d::Create();
	ThrowObj->SetModel(ThrowModel);
	//MobObject->Initialize();
	//パラメータのセット
	scale = { 1,1,1 };
	rotation = { 0,180,0 };
	position = { -10,20,0 };
	Position = { 20,20,0 };
	HP = 10;
	thposition = position;
}

void ThrowEnemy::Update(XMFLOAT3 position)
{
	if (HP <= 0) {
		enemyState = State::Dead;
	}

	switch (enemyState)
	{
	case State::SearchPlayer:

		break;
	case State::Attack:
		float dis;
		dis = sqrtf((position.x - Position.x) * (position.x - Position.x) + (position.y - Position.y) * (position.y - Position.y));
		if (dis <= 3) {
			//Attack();
		}
		break;
	case State::None:

		break;
	case State::Dead:
		SetDead(true);
		break;
	default:
		break;
	}
	
	ThrowObj->SetPosition(thposition);
	EnemyObj->SetPosition(this->position);
	EnemyObj->Update({1,1,1,1});
	ThrowObj->Update({1,1,1,1});
}

void ThrowEnemy::Attack(Player* player)
{
	float dis;
	dis = sqrtf((EnemyObj->GetPosition().x - player->GetPosition().x) * (EnemyObj->GetPosition().x - player->GetPosition().x) +
		(EnemyObj->GetPosition().y - player->GetPosition().y) * (EnemyObj->GetPosition().y - player->GetPosition().y));
	if (dis <= 2) {
		player->SetHp(player->getHp() - Damage);
		ThrowObj->SetPosition(Position);
	}

}

void ThrowEnemy::Draw()
{
	EnemyObj->PreDraw();
	EnemyObj->Draw();
	EnemyObj->PostDraw();

	ThrowObj->PreDraw();
	ThrowObj->Draw();
	ThrowObj->PostDraw();
}
void ThrowEnemy::Motion(int time)
{

}
void ThrowEnemy::EnemySearchPlayer(Player* time)
{

}