#include "SecondBoss.h"
#include"Collision.h"
#include"MobEnemy.h"
#include"Helper.h"
#define PI 3.14

// Sphere SecondBoss::playersphere;
SecondBoss::SecondBoss()
{
}
SecondBoss* SecondBoss::GetInstance()
{
	static SecondBoss instance;
	return &instance;
}
SecondBoss::~SecondBoss()
{
	delete BossObject, BossModel;
}
void SecondBoss::MoveBlockJump()
{
	//ブロック埋まり回避用のジャンプ処理
	//一定時間動かなかったらジャンプ
	time++;
	if (time % 20 == 0) {
		oldx = Position.x;
		//oldy = Position.y;
	}
	if (Collision::GetLenX({ oldx,oldy,0.0f }, Position) <= 0.0f) {
		time2++;
		if (time2 > 10) {
			bossjumpflag = true;
			time2 = 0;
		}
	}

}
void SecondBoss::EnemySearchPlayer(Player* player)
{

}
void SecondBoss::Attack(Player* player)
{

}
//初期化処理
void SecondBoss::Initialize()
{
	//モデルの読込
	BossModel = Model::CreateFromOBJ("sphere");
	//モデル割り当て
	BossObject = Object3d::Create();
	BossObject->SetModel(BossModel);

	//パラメータのセット
	Position = { 40,-4,0 };
	Boss_Scl = { 0.5,0.5,0.5 };
	Boss_Rot = { 0,180,0 };
	//モデルの読込
	HP = MaxHP;
	startPos = { 40,-18,0 };
}
void SecondBoss::SearchAction(XMMATRIX matview, XMMATRIX matprojection, XMFLOAT3 position)
{

}

//更新処理
void SecondBoss::Update(XMFLOAT3 position)
{
	Old_Pos = Position;

	if (HP <= 0) {
		enemyState = State::DEAD;
	} else {
		enemyState = State::ALIVE;
	}
	BossObject->Update({ 1,1,1,1 });
	//モブ
	BossObject->SetPosition(Position);
	BossObject->SetScale({ 1,1,1 });
	BossObject->SetRotation(Boss_Rot);

}

//描画処理
void SecondBoss::Draw(DirectXCommon*dxcomn)
{
	BossObject->PreDraw();
	BossObject->Draw();
	BossObject->PostDraw();
}

//解放処理
void SecondBoss::Finalize()
{

}
void SecondBoss::ColMap(int map[20][200], std::unique_ptr<Object3d>  tst[20][200], float mapx[20][200], float mapy[20][200], const int X, const int Y)
{
	//grav-grav
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

				if ((Position.x + Player_Scl.x > mapx[j][i] - (width - bossmovespeed) && Position.x - Player_Scl.x < mapx[j][i] + (width - bossmovespeed))) {
					if (Old_Pos.y > mapy[j][i] && Position.y - Player_Scl.y < mapy[j][i] + height) {
						Position.y = height + mapy[j][i] + Player_Scl.y;
						bossgrav = 0.0f;
						bosstime = 0;
						bossjumpflag = false;
						break;
					} else if (Old_Pos.y <mapy[j][i] && Position.y + Player_Scl.y>mapy[j][i] - height) {
						Position.y = mapy[j][i] - (Player_Scl.y + height);
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
						break;
					}
					//プレイヤーの右辺
					else if (Position.x + Player_Scl.x > mapx[j][i] - width && mapx[j][i] > Old_Pos.x) {
						Position.x = mapx[j][i] - (Player_Scl.x + width);
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

void SecondBoss::Motion(Player* player)
{

	switch (bossAction)
	{
	case SetStartPos://初期位置に戻るやつ
		Helper::Follow(startPos, Position, 0.1f, bossmovespeed);
		if (Collision::GetLen(Position, startPos) <= 1.0f) {
			bossAction = Stay;//初期位置に戻ったらビームの準備(待機)
		}
		MoveBlockJump();//ここでも戻る途中ブロックとかあったらジャンプ
		break;
	case None:
		Follow(player->GetPosition());

		if (HP < MaxHP / 2) {
			bossAction = SetStartPos;//体力が一定以下なったら初期位置に
		}
		if (Collision::GetLenX(Position, player->GetPosition()) > 5) {
			MoveBlockJump();//ボスの埋まり回避用とブロック飛び越えとか
		} else {
			if (Collision::GetLenY(Position, player->GetPosition()) > 10) {
				bossAction = NormalAttack;//プレイヤーが上の方逃げたら投擲
			}
		}

		break;
	case MoveRight://突進右
		if (movement < 10) {
			Position.x += bossmovespeed;
			movement += 0.5f;
		} else if (movement >= 10) {
			movement = 0;
		}
		break;
	case MoveLeft://突進左
		if (movement < 10) {
			Position.x -= bossmovespeed;
			movement += 0.5f;
		} else if (movement >= 10) {
			movement = 0;
		}
		break;

	case Stay://ビーム前の待機

		break;

	case NormalAttack:

		break;
	default:
		break;
	}

}


void SecondBoss::Follow(XMFLOAT3 position)
{
	float angleX, angleZ, angleR;
	float centerSpeed = 0.1f;
	angleX = (position.x - Position.x);
	angleZ = (position.y - Position.y);
	angleR = sqrtf((Position.x - position.x) * (Position.x - position.x)
		+ (Position.y - position.y) * (Position.y - position.y));
	if (angleR > 5) {
		Position.x += (angleX / angleR) * (bossmovespeed / 2);
	}
}
