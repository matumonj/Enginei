
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
	EnemyModel = Model::CreateFromOBJ("enemy2");
	//モデル割り当て
	//MobObject = new Object3d();
	EnemyObj = Object3d::Create();
	EnemyObj->SetModel(EnemyModel);
	scale = { 0.5f,0.5f,0.5 };
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
	//SearchActionInit();
	nTexture::LoadTexture(130, L"Resources/Sertch.png");
	searchTexture = nTexture::Create(130, { 0,-50,50 }, { 0.3f,0.3f,0.3f }, { 1,1,1,1 });

	searchTexture->CreateNormalTexture();
}

void ThrowEnemy::Update(XMFLOAT3 position)
{
	if (jumpflag == true) {
	//	Position.y += 0.2f;
		time += 0.02f;
	}
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
			ThrowObj[i]->SetScale({ 0.5,0.5,0.5 });
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
	if (enemyState == State::Attack) {
		for (int i = 0; i < _countof(ThrowModel); i++) {
			dis = sqrtf((thposition[i].x - player->GetPosition().x) * (thposition[i].x - player->GetPosition().x) +
				(thposition[i].y - player->GetPosition().y) * (thposition[i].y - player->GetPosition().y));
			if (dis <= 2 && throwparam[i].flag == true) {
				player->SetHp(player->getHp() - Damage);
				throwparam[i].flag = false;
			}
		}
	}
	//bi-mu
	//Motion(player);
}

void ThrowEnemy::Draw(DirectXCommon* dxcomn)
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
	nTexture::PreDraw(dxcomn->GetCmdList());
	if (searchFlag) {
		searchTexture->Draw();
	}
	nTexture::PostDraw();
	ImGui::Begin("the");
	if (ImGui::SliderFloat("x", &Position.x, 200, -200));
	if (ImGui::SliderFloat("y", &Position.y, 200, -200));
	ImGui::End();
}
void ThrowEnemy::SearchAction(XMMATRIX matview, XMMATRIX matprojection, XMFLOAT3 position) {
	if (Collision::GetLen_X(position.x, Position.x) < 5&& searchCount<=20) {
		searchFlag = true;
	}
	if (searchFlag) {
		searchCount++;
		if (searchCount > 20) {
			searchFlag = false;
			//searchCount = 0;
		}
	}
	searchTexture->SetScale({ 0.3f,0.3f,0.3f });
	searchTexture->SetColor({ 1,1,1,1 });
	searchTexture->SetPosition({ Position.x, Position.y+2, Position.z });
	searchTexture->Update(matview, matprojection);
};
void ThrowEnemy::ColMap1(int map[130][20], std::unique_ptr<Object3d>  tst[130][20], float mapx[130][20], float mapy[130][20], const int X, const int Y)
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
			if (map[j][i] == 1 || map[j][i] == 2) {
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
						jumpflag = false;
						//	Line::GetInstance()->SetBondflag(false);
						break;
					} else if (Old_Pos.y <mapy[j][i] && Position.y + Player_Scl.y>mapy[j][i] - height) {
						Position.y = mapy[j][i] - (Player_Scl.y + height);
						//Line::GetInstance()->SetBondflag(false);
						break;
					}

				} else {
					movespeed = 0.1f;
					grav = 0.03f;
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
	Position.y -= grav; //;* time * time;j
}
void ThrowEnemy::Motion(Player* player)
{
	if (Collision::GetLen(player->GetPosition(), Position) < 10) {
		if (!followf) {
			jumpcount++;
			if (jumpcount % 200 == 0) {
				jumpflag = true;
				jumpcount = 0;
			}
			//movement++;
			if (!jumpflag) {
				Position.x += pmmove * movespeed;
			}
			if (movement > 20|| Collision::GetLen_X(player->GetPosition().x, Position.x) < 3) {
				pmmove = -1;
				movereturn = true;
			}
			if (movereturn) {
				movement--;
				if (movement < -200|| Collision::GetLen_X(player->GetPosition().x, Position.x) < 3) {
					pmmove = 1;
					movereturn = false;
				}
			} else {
				movement++;
				if (movement > 100|| Collision::GetLen_X(player->GetPosition().x, Position.x) < 3) {
					pmmove = -1;
					movereturn = true;
				}
			}
		}
	}
	}
void ThrowEnemy::EnemySearchPlayer(Player* time)
{

}

void ThrowEnemy::ProjectileMotion(XMFLOAT3 position)
{
	for (int i = 0; i < 3; i++) {
		if (throwparam[i].flag == true) {
			throwparam[i].time++;
			throwparam[i].movex = (throwparam[i].initialvec_x * throwparam[i].time) / 600 / (i + 1);
			throwparam[i].movey = (throwparam[i].initialvec_y * throwparam[i].time +
				0.5f * throwparam[i].grav * throwparam[i].time * throwparam[i].time) / 600 / (i + 1);

				thposition[i].x += pm[i]*throwparam[i].movex * 2;
			thposition[i].y += throwparam[i].movey * 2;

			if (thposition[i].y < Position.y) {
				//throwparam[i].flag = false;
			}
		}
		if (attackcount % 20 == 0) {
			if (throwparam[i].flag == false) {
				if (position.x <= Position.x) {
					pm[i] =- 1;
				} else {
					pm[i] = 1;;
				}
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
						jumpflag = false;
						//	Line::GetInstance()->SetBondflag(false);
						break;
					} else if (Old_Pos.y <mapy[j][i] && Position.y + Player_Scl.y>mapy[j][i] - height) {
						Position.y = mapy[j][i] - (Player_Scl.y + height);
						//Line::GetInstance()->SetBondflag(false);
						break;
					}

				} else {
					movespeed = 0.1f;
					grav = 0.03f;
				}

				//プレイヤーの左辺
				if ((Position.y - Player_Scl.y < mapy[j][i] + height && mapy[j][i] - height < Position.y + Player_Scl.y)) {
					if (Position.x - Player_Scl.x < mapx[j][i] + width && mapx[j][i] < Old_Pos.x) {
						//jumpflag = true;
						Position.y = Position.y + 0.001f;
						Position.x = width + mapx[j][i] + Player_Scl.x;

						//Line::GetInstance()->SetBondflag(false);
						break;
					}
					//プレイヤーの右辺
					else if (Position.x + Player_Scl.x > mapx[j][i] - width && mapx[j][i] > Old_Pos.x) {
						//jumpflag = true;

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


	//
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			for (int k = 0; k < 3; k++) {
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