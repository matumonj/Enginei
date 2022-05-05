#include "BossEnemy.h"
#include"Collision.h"
bool BossEnemy::altAttackflag = false;
 Ray BossEnemy::laserRay;

// Sphere BossEnemy::playersphere;
BossEnemy::BossEnemy()
{
}
BossEnemy* BossEnemy::GetInstance()
{
	static BossEnemy instance;
	return &instance;
}
BossEnemy::~BossEnemy()
{
	delete BossObject, BossModel;
}

void BossEnemy::EnemySearchPlayer(Player* player)
{

}
void BossEnemy::Attack(Player* player)
{
	//私レイキャストをこっちに入れておりません
	playersphere.center = { player->GetPosition().x, player->GetPosition().y, player->GetPosition().z };
	playersphere.radius = 0.5f;
	laserRay.start = { Position.x,Position.y,Position.z };
	laserRay.dir = { -1,0.1,0 };

	//if (HP < HP / 9&&!altAttackflag) {
	if(Input::GetInstance()->TriggerKey(DIK_B)){
		bossAction = AltAttack;
	}
	if (Collision::GetLen(Position, player->GetPosition()) < 10) {
		bossAction = Jump;
	}
	else {
		bossAction = None;
	}
//	if (altAttackflag) {
		if (Collision::CheckRay2Sphere(laserRay, playersphere))
		{
			player->SetScale({ 0,0,0 });
		}
		
	//}
}
//初期化処理
void BossEnemy::Initialize()
{
	//モデルの読込
	BossModel = Model::CreateFromOBJ("sphere");
	//モデル割り当て
	//BossObject = new Object3d();
	BossObject = Object3d::Create();
	BossObject->SetModel(BossModel);

	//パラメータのセット
	Position = { 40,-4,0 };
	
	Boss_Scl = { 0.5,0.5,0.5 };
	Boss_Rot = { 0,180,0 };
	//Position = { 30,-2,0 };
}

//更新処理
void BossEnemy::Update(XMFLOAT3 position)
{
	Old_Pos = Position;
	
	

	BossObject->Update({ 1,1,1,1 });
	//モブ
	BossObject->SetPosition(Position);
	BossObject->SetScale({ 1,1,1 });
	BossObject->SetRotation(Boss_Rot);
	
}

//描画処理
void BossEnemy::Draw()
{
	BossObject->PreDraw();
	BossObject->Draw();
	BossObject->PostDraw();
}

//解放処理
void BossEnemy::Finalize()
{
	delete BossObject, BossModel;
}
void BossEnemy::ColMap(int map[20][200], std::unique_ptr<Object3d>  tst[20][200], float mapx[20][200], float mapy[20][200], const int X, const int Y)
{
	//grav-grav
//time-time
//movespeed-movespeed
	float height;//
	float width;
	XMFLOAT3 Player_Scl = {4,4,4 };
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			if (map[j][i] == 1) {
				mapx[j][i] = tst[j][i]->GetPosition().x;
				mapy[j][i] = tst[j][i]->GetPosition().y;
				height = tst[j][i]->GetScale().y;
				width = tst[j][i]->GetScale().x;

				if ((Position.x + Player_Scl.x > mapx[j][i] - (width - bossmovespeed) && Position.x - Player_Scl.x < mapx[j][i] + (width - bossmovespeed))) {
					if (Old_Pos.y > mapy[j][i] && Position.y - Player_Scl.y < mapy[j][i] + height) {
						Position.y = height + mapy[j][i] + Player_Scl.y;
						//moveSpeed = 0;
						bossgrav = 0.0f;
						bosstime = 0;
						bossjumpflag = false;
						//	Line::GetInstance()->SetBondflag(false);
						break;
					} else if (Old_Pos.y <mapy[j][i] && Position.y + Player_Scl.y>mapy[j][i] - height) {
						Position.y = mapy[j][i] - (Player_Scl.y + height);
						//Line::GetInstance()->SetBondflag(false);
						break;
					}

				} else {
					bossmovespeed = 0.2f;
					bossgrav = 0.03;
				}

				//プレイヤーの左辺
				if ((Position.y - Player_Scl.y < mapy[j][i] + height && mapy[j][i] - height < Position.y + Player_Scl.y)) {
					if (Position.x - Player_Scl.x < mapx[j][i] + width && mapx[j][i] < Old_Pos.x) {

						Position.y = Position.y + 0.001f;
						Position.x = width + mapx[j][i] + Player_Scl.x;
						//Line::GetInstance()->SetBondflag(false);
						break;
					}
					//プレイヤーの右辺
					else if (Position.x + Player_Scl.x > mapx[j][i] - width && mapx[j][i] > Old_Pos.x) {

						Position.x = mapx[j][i] - (Player_Scl.x + width);
						//Line::GetInstance()->SetBondflag(false);
						break;
					}
				} else {
					bossmovespeed = 0.2f;
				}
			}
		}
	}

	bosstime += 0.04f;
	Position.y -= bossgrav * bosstime * bosstime;


}

void BossEnemy::Motion(int time)
{
	switch (bossAction)
	{
	case None:
		break;
	case MoveRight:
		if (movement < 10) {
			Position.x += bossmovespeed;
			movement += 0.5f;
		}
		else if (movement >= 10) {
			movement = 0;
		}
		break;
	case MoveLeft:
		if (movement < 10) {
			Position.x -= bossmovespeed;
			movement += 0.5f;
		}
		else if (movement >= 10) {
			movement = 0;
		}
		break;
	case Jump:
			bossjumpflag = true;
		if (bossjumpflag == true) {
			Position.y += 0.1f;
			bosstime += 0.02f;
		}

		break;
	case AltAttack:
		
		Attackcount++;
		if (Attackcount > 30) {
			altAttackflag = false;
			Attackcount = 0;
			bossAction = NormalAttack;
		}
		else {
			altAttackflag = true;
		}
		break;
	case NormalAttack:

		break;
	default:
		break;
	}
}

void BossEnemy::ColMapb1(int map[15][200], std::unique_ptr<Object3d>  tst[15][200], float mapx[15][200], float mapy[15][200], const int X, const int Y)
{

	//enemy->Setposition(Position);
}