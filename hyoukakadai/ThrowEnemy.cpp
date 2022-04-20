#include "ThrowEnemy.h"
#include"Line.h"
#include"imgui.h"
ThrowEnemy::ThrowEnemy()
{
}

/// <summary>
/// デストラクタ
/// </summary>
ThrowEnemy::~ThrowEnemy()
{
	delete EnemyObj, EnemyModel;
	delete *ThrowObj, *ThrowModel;
}
void ThrowEnemy::Initialize()
{

	//モデルの読込
	EnemyModel = Model::CreateFromOBJ("subenemy");
	//モデル割り当て
	//MobObject = new Object3d();
	EnemyObj = Object3d::Create();
	EnemyObj->SetModel(EnemyModel);
	scale = { 0.5f,0.5f,0.5 };
	rotation = { 0,180,0 };
	//position = { 0,20,0 };
	HP = 10;

	//モデルの読込
	for (int i = 0; i < _countof(ThrowModel); i++) {
		ThrowModel[i] = Model::CreateFromOBJ("sphere");
		//モデル割り当て
		//MobObject = new Object3d();
		ThrowObj[i] = Object3d::Create();
		ThrowObj[i]->SetModel(ThrowModel[i]);
		thposition[i] = Position;
	}
	//MobObject->Initialize();
	//パラメータのセット

}

void ThrowEnemy::Update(XMFLOAT3 position)
{
	if (HP <= 0) {
		enemyState = State::Dead;
	}

	float dis;
	dis = sqrtf((position.x - Position.x) * (position.x - Position.x) + (position.y - Position.y) * (position.y - Position.y));
	if (dis <= 20) {
		//Attack();
		enemyState = State::Attack;
	}
	switch (enemyState)
	{
	case State::SearchPlayer:

		break;
	case State::Attack:
		ProjectileMotion();
		break;
	case State::None:

		break;
	case State::Dead:
		SetDead(true);
		break;
	default:
		break;
	}
	if (enemyState != State::Dead) {
		for (int i = 0; i < _countof(ThrowModel); i++) {
			ThrowObj[i]->SetPosition(thposition[i]);
			ThrowObj[i]->Update({ 1,1,1,1 });
		}
		EnemyObj->SetPosition(Position);
		EnemyObj->SetScale(scale);
		EnemyObj->Update({ 1,1,1,1 });
	}
}

void ThrowEnemy::Attack(Player* player)
{
	float dis;
	for (int i = 0; i < _countof(ThrowModel); i++) {
		dis = sqrtf((thposition[i].x - player->GetPosition().x) * (thposition[i].x - player->GetPosition().x) +
			(thposition[i].y - player->GetPosition().y) * (thposition[i].y - player->GetPosition().y));
		if (dis <= 2) {
		//	player->SetHp(player->getHp() - Damage);
		}
	}
}

void ThrowEnemy::Draw()
{
	EnemyObj->PreDraw();
	EnemyObj->Draw();
	EnemyObj->PostDraw();

	if (enemyState != State::Dead) {
		for (int i = 0; i < _countof(ThrowModel); i++) {
			ThrowObj[i]->PreDraw();
			ThrowObj[i]->Draw();
			ThrowObj[i]->PostDraw();
		}
	}

	ImGui::Begin("the");
	if (ImGui::SliderFloat("x", &Position.x, 100, -100));
	if (ImGui::SliderFloat("y", &Position.y, 100, -100));
	ImGui::End();
}
void ThrowEnemy::Motion(int time)
{

}
void ThrowEnemy::EnemySearchPlayer(Player* time)
{

}

void ThrowEnemy::ProjectileMotion()
{
	for (int i = 0; i < 3; i++) {
		if (throwparam[i].flag == true) {
			throwparam[i].time++;
			throwparam[i].movex=(throwparam[i].initialvec_x* throwparam[i].time)/800;
			throwparam[i].movey=(throwparam[i].initialvec_y * throwparam[i].time+
				0.5f * throwparam[i].grav * throwparam[i].time * throwparam[i].time) / 800;
			thposition[i].x -= throwparam[i].movex*2;
			thposition[i].y += throwparam[i].movey*2;

		}
		else if (throwparam[i].flag == false) {
			throwparam[i].flag = true;
			thposition[i] = Position;
			throwparam[i].time = 0;
			throwparam[i].movex = 0;
			throwparam[i].movey = 0;
			break;
		}
	}
}