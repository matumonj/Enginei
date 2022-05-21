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
	MobModel = Model::CreateFromOBJ("enemy2");
	//モデル割り当て
	//MobObject = new Object3d();
	MobObject = Object3d::Create();
	MobObject->SetModel(MobModel);
	//MobObject->Initialize();
	//パラメータのセット
	Mob_Scl = { 2,2,2 };
	Mob_Rot = { 0,180,0 };
	//Mob_Pos = { -10,-2,0 };
	//Position = { 24,10,0 };
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
		//enemyState = State::DEAD;
	} else {
	//	enemyState = State::ALIVE;
	}
	SetHP(HP);
	MobObject->SetScale({0.5,0.5,0.5 });
	MobObject->SetRotation(Mob_Rot);

	//Follow(position);
	MobObject->SetColor({ 1,1,1,1 });
	MobObject->Update({ 1,1,1,1 });
	MobObject->SetPosition(Position);

}

//描画処理
void MobEnemy::Draw(DirectXCommon* dxcomn)
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
void MobEnemy::EnemySearchPlayer(Player* player)
{
	
	//Follow(player);
}

void MobEnemy::Follow(Player*player)
{
	float angleX, angleZ, angleR;
	float centerSpeed = 0.1f;
	angleX = (player->GetPosition().x - Position.x);
	angleZ = (player->GetPosition().y - Position.y);
	angleR = sqrtf((Position.x - player->GetPosition().x) * (Position.x - player->GetPosition().x)
		+ (Position.y - player->GetPosition().y) * (Position.y - player->GetPosition().y));
	if (angleR>2) {
		Position.x += (angleX / angleR) * movespeed;
		//Position.y += (angleZ / angleR) * centerSpeed;
	}
	//Position.x =player.x;
	//Position.y =player.y;
	//MobObject->SetPosition(Position);
	//MobObject->SetPosition(Position);
	float dis;
	dis = sqrtf((player->GetPosition().x - Position.x) * (player->GetPosition().x - Position.x) +
		(player->GetPosition().y - Position.y) * (player->GetPosition().y - Position.y));
	if (dis <= 2) {
		player->SetHp(player->getHp() - 1);
		//Attack(player);
	}
	if (player->GetPosition().x >= Position.x) {
		if (Mob_Rot.y <= 90) {
			Mob_Rot.y += 10;
		}
	}
	else
	{
		if (Mob_Rot.y >= -90) {
			Mob_Rot.y -= 10;
		}
	}
}

void MobEnemy::Motion(Player* player)
{
	switch (enemyState)
	{
	case State::ALIVE:

		break;

	case State::DEAD:

		break;
	}

}
void MobEnemy::Attack(Player*player)
{
	float dis;
	dis = sqrtf((player->GetPosition().x - Position.x) * (player->GetPosition().x - Position.x) +
		(player->GetPosition().y - Position.y) * (player->GetPosition().y - Position.y));
	if (dis <= 5) {
		followf = true;
		//Attack(player);
	}
	if (followf) {
		Follow(player);
	}
		//player->SetHp(player->getHp() - AttackDamage);
}
void MobEnemy::ColMap(int map[20][200], std::unique_ptr<Object3d>  tst[20][200] , float mapx[20][200], float mapy[20][200], const int X, const int Y)
{
	//grav-grav
	Old_Pos = Position;
//time-time
//movespeed-movespeed
	float height;//
	float width;
	XMFLOAT3 Player_Scl = { 1,1,1 };
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			if (map[j][i] == 1) {
				mapx[j][i] = tst[j][i]->GetPosition().x;
				mapy[j][i] = tst[j][i]->GetPosition().y;
				height = tst[j][i]->GetScale().y;
				width = tst[j][i]->GetScale().x;

				if ((Position.x + Player_Scl.x > mapx[j][i] - (width - movespeed) && Position.x - Player_Scl.x < mapx[j][i] + (width - movespeed))) {
					if (Old_Pos.y > mapy[j][i] && Position.y - Player_Scl.y < mapy[j][i] + height) {
						Position.y = height + mapy[j][i] + Player_Scl.y;
						//moveSpeed = 0;
						grav = 0.0f;
						time = 0;
						//jumpflag = false;
						//	Line::GetInstance()->SetBondflag(false);
						break;
					} else if (Old_Pos.y <mapy[j][i] && Position.y + Player_Scl.y>mapy[j][i] - height) {
						Position.y = mapy[j][i] - (Player_Scl.y + height);
						//Line::GetInstance()->SetBondflag(false);
						break;
					}

				} else {
					movespeed = 0.1f;
					grav = 0.03;
				}

				//プレイヤーの左辺
				if ((Position.y - Player_Scl.y < mapy[j][i] + height && mapy[j][i] - height < Position.y + Player_Scl.y)) {
					if (Position.x - Player_Scl.x < mapx[j][i] + width && mapx[j][i] < Old_Pos.x) {
						//bossjumpflag = true;
						Position.y = Position.y + 0.001f;
						Position.x = width + mapx[j][i] + Player_Scl.x;

						//Line::GetInstance()->SetBondflag(false);
						break;
					}
					//プレイヤーの右辺
					else if (Position.x + Player_Scl.x > mapx[j][i] - width && mapx[j][i] > Old_Pos.x) {
						//bossjumpflag = true;
						
						Position.x = mapx[j][i] - (Player_Scl.x + width);
						//Line::GetInstance()->SetBondflag(false);
						break;
					}
				} else {
					movespeed = 0.1f;
				}
			}
		}
	}

	time += 0.04f;
	Position.y -= grav * time * time;
}
void MobEnemy::ColMap1(int map[130][20], std::unique_ptr<Object3d>  tst[130][20], float mapx[130][20], float mapy[130][20], const int X, const int Y)
{
	//grav-grav
	Old_Pos = Position;
	//time-time
	//movespeed-movespeed
	float height;
	float width;
	XMFLOAT3 Player_Scl = { 1,1,1 };
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			if (map[j][i] == 1|| map[j][i] == 2) {
				mapx[j][i] = tst[j][i]->GetPosition().x;
				mapy[j][i] = tst[j][i]->GetPosition().y;
				height = tst[j][i]->GetScale().y;
				width = tst[j][i]->GetScale().x;

				if ((Position.x + Player_Scl.x > mapx[j][i] - (width - movespeed) && Position.x - Player_Scl.x < mapx[j][i] + (width - movespeed))) {
					if (Old_Pos.y > mapy[j][i] && Position.y - Player_Scl.y < mapy[j][i] + height) {
						Position.y = height + mapy[j][i] + Player_Scl.y;
						//moveSpeed = 0;
						grav = 0.0f;
						time = 0;
						//jumpflag = false;
						//	Line::GetInstance()->SetBondflag(false);
						break;
					} else if (Old_Pos.y <mapy[j][i] && Position.y + Player_Scl.y>mapy[j][i] - height) {
						Position.y = mapy[j][i] - (Player_Scl.y + height);
						//Line::GetInstance()->SetBondflag(false);
						break;
					}

				} else {
					movespeed = 0.1f;
					grav = 0.03;
				}

				//プレイヤーの左辺
				if ((Position.y - Player_Scl.y < mapy[j][i] + height && mapy[j][i] - height < Position.y + Player_Scl.y)) {
					if (Position.x - Player_Scl.x < mapx[j][i] + width && mapx[j][i] < Old_Pos.x) {
						//bossjumpflag = true;
						Position.y = Position.y + 0.001f;
						Position.x = width + mapx[j][i] + Player_Scl.x;

						//Line::GetInstance()->SetBondflag(false);
						break;
					}
					//プレイヤーの右辺
					else if (Position.x + Player_Scl.x > mapx[j][i] - width && mapx[j][i] > Old_Pos.x) {
						//bossjumpflag = true;

						Position.x = mapx[j][i] - (Player_Scl.x + width);
						//Line::GetInstance()->SetBondflag(false);
						break;
					}
				} else {
					movespeed = 0.1f;
				}
			}
		}
	}

	time += 0.04f;
	Position.y -= grav;// *time* time;
}

void MobEnemy::enemyappearance(TyutorialSprite* sprite)
{
	if (sprite->GetPhase_Attack() == true) {
		if (Position.y >= -2) {
			Position.y -= 0.5f;
		}
	}
}
void MobEnemy::SearchAction(XMMATRIX matview, XMMATRIX matprojection, XMFLOAT3 position) {

}