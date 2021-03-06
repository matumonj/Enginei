#include "FishEnemy.h"
#include<math.h>
#include"Line.h"
/// <summary>
/// コンストラクタ
/// </summary>
FishEnemy::FishEnemy()
{
}

/// <summary>
/// デストラクタ
/// </summary>
FishEnemy::~FishEnemy()
{
	delete FishObject, FishModel;
}

//初期化処理
void FishEnemy::Initialize()
{
	//モデルの読込
	FishModel = Model::CreateFromOBJ("enemy_fish1");
	//モデル割り当て
	//FishObject = new Object3d();
	FishObject = Object3d::Create();
	FishObject->SetModel(FishModel);
	//FishObject->Initialize();
	//パラメータのセット
	HP = 10;

}

//更新処理
void FishEnemy::Update(XMFLOAT3 position)
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
	Position.x-=0.1f;
	//FishObject->SetPosition(Position);
	if (HP < 0) {
		enemyState = State::DEAD;
	} else {
		//	enemyState = State::ALIVE;
	}
	FishObject->SetScale({ 0.5,0.5,0.5 });
	FishObject->SetRotation({ 0,-90,0 });


	FishObject->Update({ 1,1,1,1 });
	FishObject->SetPosition(Position);

}

//描画処理
void FishEnemy::Draw(DirectXCommon* dxcomn)
{
	FishObject->PreDraw();
	FishObject->Draw();
	FishObject->PostDraw();
}

//解放処理
void FishEnemy::Finalize()
{
	delete FishObject, FishModel;
}
void FishEnemy::EnemySearchPlayer(Player* player)
{
	//Follow(player);
}

void FishEnemy::Follow(Player* player)
{
	frame++;

	float angleX, angleY, angleR;
	float centerSpeed = 0.1f;
	angleX = (player->GetPosition().x - Position.x);
	angleY = (player->GetPosition().y - Position.y);
	angleR = sqrtf((Position.x - player->GetPosition().x) * (Position.x - player->GetPosition().x));
	if (angleR < 2) {

		followf = true;
		//Position.x += (angleX / angleR) * movespeed;
		//Position.y += (angleZ / angleR) * centerSpeed;
	}
	if (followf) {
	//	Position.x += (angleX / angleR) * movespeed;
		//Position.y += (angleX / angleR) * movespeed;
	}
	//Position.x =player.x;
	//Position.y =player.y;
	//FishObject->SetPosition(Position);
	//FishObject->SetPosition(Position);
	float dis;
	dis = sqrtf((player->GetPosition().x - Position.x) * (player->GetPosition().x - Position.x) +
		(player->GetPosition().y - Position.y) * (player->GetPosition().y - Position.y));
	if (dis <= 2) {
		//Attack(player);
	}
}

void FishEnemy::Motion(Player* player)
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
void FishEnemy::Attack(Player* player)
{
	//player->SetHp(player->getHp() - AttackDamage);
}
void FishEnemy::ColMap(int map[20][200], std::unique_ptr<Object3d>  tst[20][200], float mapx[20][200], float mapy[20][200], const int X, const int Y)
{

}

void FishEnemy::enemyappearance(TyutorialSprite* sprite)
{

}
void FishEnemy::SearchAction(XMMATRIX matview, XMMATRIX matprojection, XMFLOAT3 position)
{
}
void FishEnemy::ColMap1(int map[130][20], std::unique_ptr<Object3d>  tst[130][20], float mapx[130][20], float mapy[130][20], const int X, const int Y)
{}