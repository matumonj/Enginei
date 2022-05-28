#include "ThronEnemy.h"
#include<math.h>
#include"Line.h"
/// <summary>
/// コンストラクタ
/// </summary>
ThronEnemy::ThronEnemy()
{
}

/// <summary>
/// デストラクタ
/// </summary>
ThronEnemy::~ThronEnemy()
{
	delete ThronObject, ThronModel;
}

//初期化処理
void ThronEnemy::Initialize()
{
	//モデルの読込
	ThronModel = Model::CreateFromOBJ("enemy2");
	//モデル割り当て
	//ThronObject = new Object3d();
	ThronObject = Object3d::Create();
	ThronObject->SetModel(ThronModel);
	//ThronObject->Initialize();
	//パラメータのセット
	HP = 10;
	
}

//更新処理
void ThronEnemy::Update(XMFLOAT3 position)
{

	if (jumpflag == true) {
			Position.y += 0.5f;
		time += 0.02f;
	} 
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
	//ThronObject->SetPosition(Position);
	if (HP < 0) {
		enemyState = State::DEAD;
	} else {
		//	enemyState = State::ALIVE;
	}
	ThronObject->SetScale({ 0.5,0.5,0.5 });
	ThronObject->SetRotation({ 0,180,0 });

	
	ThronObject->Update({ 1,1,1,1 });
	ThronObject->SetPosition(Position);

}

//描画処理
void ThronEnemy::Draw(DirectXCommon* dxcomn)
{
	ThronObject->PreDraw();
	ThronObject->Draw();
	ThronObject->PostDraw();
}

//解放処理
void ThronEnemy::Finalize()
{
	delete ThronObject, ThronModel;
}
void ThronEnemy::EnemySearchPlayer(Player* player)
{
	//Follow(player);
}

void ThronEnemy::Follow(Player* player)
{
	frame++;

	float angleX, angleY, angleR;
	float centerSpeed = 0.1f;
	angleX = (player->GetPosition().x - Position.x);
	angleY = (player->GetPosition().y - Position.y);
	angleR = sqrtf((Position.x - player->GetPosition().x) * (Position.x - player->GetPosition().x)+
		(Position.y - player->GetPosition().y) * (Position.y - player->GetPosition().y));
	if (angleR < 2) {
		
		followf =true;
		//Position.x += (angleX / angleR) * movespeed;
		//Position.y += (angleZ / angleR) * centerSpeed;
	}
	if (followf) {
		Position.x += (angleX / angleR) * movespeed/2;
		Position.y += (angleY / angleR) * movespeed/2;
	}
	//Position.x =player.x;
	//Position.y =player.y;
	//ThronObject->SetPosition(Position);
	//ThronObject->SetPosition(Position);
	float dis;
	dis = sqrtf((player->GetPosition().x - Position.x) * (player->GetPosition().x - Position.x) +
		(player->GetPosition().y - Position.y) * (player->GetPosition().y - Position.y));
	if (dis <= 2) {
		//servDamage = true;
		if (servDamage) {
			player->SetHp(player->getHp() - 1);
			servDamage = false;
			stayflg = true;
			//Attack(player);
		}
	}
	if (stayflg) {
		redamageCount++;
		if (redamageCount > 30) {
			servDamage = true;
			redamageCount = 0;
			stayflg = false;
		}
	}
}

void ThronEnemy::Motion(Player* player)
{
	Follow(player);
	if (!followf) {
		jumpcount++;
		if (jumpcount % 50 == 0) {
			//jumpflag = true;
			jumpcount = 0;
		}
	}
}
void ThronEnemy::Attack(Player* player)
{
	//player->SetHp(player->getHp() - AttackDamage);
}
void ThronEnemy::ColMap(int map[20][200], std::unique_ptr<Object3d>  tst[20][200], float mapx[20][200], float mapy[20][200], const int X, const int Y)
{
	
}

void ThronEnemy::enemyappearance(TyutorialSprite* sprite)
{
	
}
void ThronEnemy::SearchAction(XMMATRIX matview, XMMATRIX matprojection, XMFLOAT3 position)
{
}
void ThronEnemy::ColMap1(int map[130][20], std::unique_ptr<Object3d>  tst[130][20], float mapx[130][20], float mapy[130][20], const int X, const int Y)
{}