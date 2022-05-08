#include "ThrowEnemy.h"
#include"Line.h"
#include"imgui.h"
#include"Collision.h"
ThrowEnemy::ThrowEnemy()
{
}

/// <summary>
/// デストラクタ
/// </summary>
ThrowEnemy::~ThrowEnemy()
{
	delete EnemyObj, EnemyModel;
	for (int i = 0; i < _countof(ThrowModel); i++) {
		delete ThrowObj[i], ThrowModel[i];
	}
}
void ThrowEnemy::Initialize()
{

	//モデルの読込
	EnemyModel = Model::CreateFromOBJ("subenemy");
	//モデル割り当て
	//MobObject = new Object3d();
	EnemyObj = Object3d::Create();
	EnemyObj->SetModel(EnemyModel);
	scale = { 1.5f,1.5f,1.5 };
	rotation = { 0,-90,0 };
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
		ProjectileMotion(position);
		rotation.x++;
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
		EnemyObj->SetRotation(rotation);
		EnemyObj->Update({ 1,1,1,1 });
	}
}

void ThrowEnemy::Attack(Player* player)
{
	float dis;
	if(enemyState==State::Attack){
		for (int i = 0; i < _countof(ThrowModel); i++) {
			dis = sqrtf((thposition[i].x - player->GetPosition().x) * (thposition[i].x - player->GetPosition().x) +
				(thposition[i].y - player->GetPosition().y) * (thposition[i].y - player->GetPosition().y));
			if (dis <= 2&& throwparam[i].flag ==true) {
				player->SetHp(player->getHp() - Damage);
				throwparam[i].flag = false;
			}
		}
	}
	//bi-mu
	
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
	if (ImGui::SliderFloat("x", &Position.x, 200, -200));
	if (ImGui::SliderFloat("y", &Position.y, 200, -200));
	ImGui::End();
}
void ThrowEnemy::Motion(Player* player)
{

}
void ThrowEnemy::EnemySearchPlayer(Player* time)
{

}

void ThrowEnemy::ProjectileMotion(XMFLOAT3 position)
{
	for (int i = 0; i < 10; i++) {
		if (throwparam[i].flag == true) {
			throwparam[i].time++;
			throwparam[i].movex=(throwparam[i].initialvec_x* throwparam[i].time)/600/(i+1);
			throwparam[i].movey=(throwparam[i].initialvec_y * throwparam[i].time+
				0.5f * throwparam[i].grav * throwparam[i].time * throwparam[i].time) / 600/(i+1);
			if (position.x <= Position.x) {
				thposition[i].x -= throwparam[i].movex * 2;
			}
			else {
				thposition[i].x += throwparam[i].movex * 2;
			}
			thposition[i].y += throwparam[i].movey*2;

			if (thposition[i].y < Position.y) {
				//throwparam[i].flag = false;
			}
		}
		if(attackcount%20==0){
			if (throwparam[i].flag == false) {
				throwparam[i].flag = true;
				thposition[i] = Position;
				throwparam[i].time = 0;
				throwparam[i].movex = 0;
				throwparam[i].movey = 0;
				break;
			}
		}

}
	attackcount++;
}

void ThrowEnemy::ColMap(int map[20][200], std::unique_ptr<Object3d>  tst[20][200], float mapx[20][200], float mapy[20][200], const int X, const int Y)
{
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			for (int k = 0; k < 10; k++) {
				if (map[j][i] == 1) {
					if ((thposition[k].x + 0.5f > mapx[j][i] - 0.5f && thposition[k].x - 0.5f < mapx[j][i] + 0.5f) &&
						thposition[k].y + 0.5f > mapy[j][i] && thposition[k].y - 0.5f < mapy[j][i] + 0.5f) {
						throwparam[k].flag = false;
					}
					if (throwparam[k].time > 200) {
						throwparam[k].flag = false;
					}
				}
			}
		}
				}
	
}