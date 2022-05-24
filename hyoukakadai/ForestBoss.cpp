#include "ForestBoss.h"
#include"Collision.h"
#include"MobEnemy.h"
#include"Helper.h"
#include"mHelper.h"
#include<random>
#define PI 3.14
#include"imgui.h"
int ForestBoss::StayCount = 0;
float ForestBoss::startcount = 0;
bool ForestBoss::stayflag;
XMFLOAT3 ForestBoss::startPos;
bool ForestBoss::bossjumpflag = false;
XMFLOAT3 ForestBoss::wpos[max];
int ForestBoss::attacktime = 0;
XMFLOAT3 ForestBoss::Skewers_Scl[max] = { {1,1,1},{1,1,1},{1,1,1} };
bool ForestBoss::woodatkflag = false;
float ForestBoss::woodatkCount = 0;
float ForestBoss::woodatkCount2 = 0;
float ForestBoss::woodatkCount3 = 0;
XMFLOAT3 ForestBoss::Nuclear_Pos;
// Sphere ForestBoss::playersphere;
ForestBoss::ForestBoss()
{
}
ForestBoss* ForestBoss::GetInstance()
{
	static ForestBoss instance;
	return &instance;
}
ForestBoss::~ForestBoss()
{
	delete BossObject, BossModel;
}
void ForestBoss::MoveBlockJump()
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
			//bossjumpflag = true;
			time2 = 0;
		}
	}

}
void ForestBoss::EnemySearchPlayer(Player* player)
{
	collisionArm(player);
}
void ForestBoss::Attack(Player* player)
{

}
//初期化処理
void ForestBoss::Initialize()
{
	NuclearModel= Model::CreateFromOBJ("zako1");
	NuclearObj = Object3d::Create();
	NuclearObj->SetModel(NuclearModel);
	//モデルの読込
	BossModel = Model::CreateFromOBJ("boss1");
	//モデル割り当て
	BossObject = Object3d::Create();
	BossObject->SetModel(BossModel);
	BarrelModel= Model::CreateFromOBJ("arm");
	SkewersBossModel= Model::CreateFromOBJ("arm");
	ShotModel = Model::CreateFromOBJ("sphere");
	BossArmModel = Model::CreateFromOBJ("arm");
	for (int i = 0; i < max; i++) {
		SkewersObject[i] = Object3d::Create();
		SkewersObject[i]->SetModel(SkewersBossModel);
	}
	for (int i = 0; i < 2; i++) {
		BossArmObj[i] = Object3d::Create();
		BossArmObj[i]->SetModel(BossArmModel);
	}
	BarrelObj=Object3d::Create();
	BarrelObj->SetModel(BarrelModel);
	//パラメータのセット

	Position = { 67,-4,0 };
	Boss_Scl = { 2,2,2 };
	Boss_Rot = { 0,-180,0 };
	Rotation = { 0,0,0 };
	//モデルの読込
	//Rotation.z = 0;
	HP = MaxHP;
	startPos = { 40,-18,0 };
	for (int i = 0; i < 2; i++) {
		Arm_Pos[i] = {10,139,0};
		Arm_Rot[i] = { 0,180,90 };
		Arm_Scl[i] = { 1,5,1 };
	}
	for (int i = 0; i < 3; i++) {
		ShotObj[i] = Object3d::Create();
		ShotObj[i]->SetModel(ShotModel);
		Shot_Pos[i] = { Position };

	}
	Barrel_Scl = { 1,5,1 };
	BarrelObj->SetScale({ 1,5,1 });
	BarrelObj->SetPosition(Position);
	Barrel_Rot = { 0,180,90 };
}//

//更新処理
void ForestBoss::Update(XMFLOAT3 position)
{
	if ((int)position.y % 40 == 0) {
		AttackNum++;
	}
	Old_Pos = Position;

	if (bossjumpflag == true) {
		if (bossjumpflag2) {
			Position.y += 0.5f;
		} else {
			Position.y += 0.2f;
		}
		bosstime += 0.02f;
	} else {
		bossjumpflag2 = false;
	}

	if (HP <= 0) {
		enemyState = State::DEAD;
	} else {
		enemyState = State::ALIVE;
	}

	if (Collision::GetLen(position, NuclearObj->GetPosition()) < 10) {
		if (Input::GetInstance()->TriggerButtonA()) {
			
			if (NuclearHP >= 2) {
				NuclearHP--;
			}
		}
	}
	if (NuclearHP == 10) {
		OldHP = NuclearHP - 1;
	}
	if (NuclearHP == OldHP && !damageRec) {
		damageRec = true;
		OldHP--;
	}
	if (damageRec) {
		r = 1.0f; g = 0.2f; b = 0.0f;
		damageRec = false;
	} else {
		if (r > 0.0f)r -= 0.1f;
		if (g < 1.0f)g += 0.1f;
		if (b < 1.0f)b += 0.1f;
	}
	SetHP(NuclearHP);
	Rot_Nuclear++;
	BossObject->Update({ 1,1,1,1 });
	for (int i = 0; i < max; i++) {
		SkewersObject[i]->Update({ 1,1,1,1 });
	}
	NuclearObj->SetPosition(Nuclear_Pos);
	NuclearObj->SetRotation({ 0,Rot_Nuclear,0 });
	NuclearObj->SetScale({ 2,2,2 });
	NuclearObj->Update({ r,g,b,1 });
	Arm_Pos[0] = Position;
	Arm_Pos[1] = Position;
									 //Arm_Rot[1].z = rotfollow  ;//60=角度調整用 180=反転
	
	for (int i = 0; i < 2; i++) {
		BossArmObj[i]->SetPosition(Arm_Pos[i]);
		BossArmObj[i]->SetRotation(Arm_Rot[i]);
		BossArmObj[i]->SetScale(Arm_Scl[i]);
		BossArmObj[i]->Update({1,1,1,1});
	}
	for (int i = 0; i < 3; i++) {
		if (ShotObj[i] != nullptr) {
			ShotObj[i]->SetPosition(Shot_Pos[i]);
			ShotObj[i]->SetRotation({ 0,0,0 });
			ShotObj[i]->SetScale({ 1,1,1 });
			ShotObj[i]->Update({ 1,1,1,1 });
		}
	}
	
	GetDamage();
	//モブ
	Rotation.x = 30;
	Position.x = 20;
	Position.z = 0;
	UpDownMove(position);
	BossObject->SetPosition(Position);
	BossObject->SetScale({ 2,2,2 });
	BossObject->SetRotation(Rotation);
	for (int i = 0; i < max; i++) {
		SkewersObject[i]->SetScale(Skewers_Scl[i]);
		SkewersObject[i]->SetRotation({ 0,0,-90 });
		//BossObject->SetRotation(Boss_Rot);
		SkewersObject[i]->SetPosition(wpos[i]);
	}
	BarrelObj->SetPosition(Position);
	BarrelObj->SetScale(Barrel_Scl);
	BarrelObj->SetRotation(Barrel_Rot);
	//BarrelObj->SetScale({1,5,1});
	BarrelObj->Update({ 1,1,1,1 });
}
void ForestBoss::SkewersAttack(int map[130][20], std::unique_ptr<Object3d> tst[130][20])
{
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j< 130; j++) {
			if (map[j][i] == 3) {
				wpos[0] = { tst[j][i]->GetPosition().x - 5,tst[j][i]->GetPosition().y,tst[j][i]->GetPosition().z };
				if (woodatkflag) {
					map[j][i] = 4;
				}
			}
				if (map[j][i] == 5) {
					wpos[1] = { tst[j][i]->GetPosition().x + 5,tst[j][i]->GetPosition().y,tst[j][i]->GetPosition().z };
					if (woodatkflag) {
						map[j][i] = 4;
					}
				}
				if (map[j][i] == 6) {
					wpos[2] = { tst[j][i]->GetPosition().x + 5,tst[j][i]->GetPosition().y,tst[j][i]->GetPosition().z };
					if (woodatkflag) {
						map[j][i] = 4;
					}
				}
				//break;
				if (map[j][i] == 30) {
					Nuclear_Pos = { tst[j][i]->GetPosition().x - 5,tst[j][i]->GetPosition().y,tst[j][i]->GetPosition().z };
			}
		}
	}
	
	if (woodatkflag) {
		if (Skewers_Scl[0].y <= 8) {
			woodatkCount += 0.05f;
			Skewers_Scl[0].y = Easing::EaseOut(woodatkCount, 0, 8);
		}
		if (Skewers_Scl[1].y >= -8) {
			woodatkCount2 -= 0.05f;
			Skewers_Scl[1].y = Easing::EaseOut(woodatkCount2, 0, -8);
		} 
		if (Skewers_Scl[2].y >= -8) {
			woodatkCount3 -= 0.05f;
			Skewers_Scl[2].y = Easing::EaseOut(woodatkCount3, 0, -8);
		} 
		else {
			woodatkflag = false;
		}
	}
//	wpos ={ 0,0,0 };
	
}
//描画処理
void ForestBoss::Draw(DirectXCommon* dxcomn)
{
	for (int i = 0; i < 2; i++) {
		BossArmObj[i]->PreDraw();
		BossArmObj[i]->Draw();
		BossArmObj[i]->PostDraw();
	}
	
	BossObject->PreDraw();
	BossObject->Draw();
	BossObject->PostDraw();
	for (int i = 0; i < max; i++) {
		SkewersObject[i]->PreDraw();
		SkewersObject[i]->Draw();
		SkewersObject[i]->PostDraw();
	}
	for (int i = 0; i < 3; i++) {
		if (ShotObj[i] != nullptr) {
			ShotObj[i]->PreDraw();
			ShotObj[i]->Draw();
			ShotObj[i]->PostDraw();
		}
	}
	BarrelObj->PreDraw();
	BarrelObj->Draw();
	BarrelObj->PostDraw();

	NuclearObj->PreDraw();
	NuclearObj->Draw();
	NuclearObj->PostDraw();

	ImGui::Begin("scl");
	
	ImGui::SliderFloat("scly",&Arm_Scl[0].y, 20.0f, 20.0f);
	ImGui::SliderFloat("scly", &lene, 20.0f, 20.0f);
	ImGui::End();
}

//解放処理
void ForestBoss::Finalize()
{

}
void ForestBoss::ColMap(int map[20][200], std::unique_ptr<Object3d>  tst[20][200], float mapx[20][200], float mapy[20][200], const int X, const int Y)
{}

void ForestBoss::Motion(Player* player)
{
	NormalAttacks(player);
	lene = Collision::GetLen(Arm_Pos[0], player->GetPosition());

	const float dis = 0.5f;
	if (Position.y > 180) {
		woodatkflag = true;
	}
	if (Position.y > 120) {

	}
	switch (bossAction)
	{
	case KeepPos:
		
		break;
	case SetStartPos://初期位置に戻るや
		
		break;
	
	case None:
		attacktime++;
		if (Input::GetInstance()->TriggerKey(DIK_S)) {
			bossAction = SetStartPos;
		}
		if (HP < MaxHP / 2) {
			bossAction = SetStartPos;//体力が一定以下なったら初期位置に
		}
		if (Collision::GetLen_X(Position.x, player->GetPosition().x) > 5) {
			Follow(player->GetPosition());
			//MoveBlockJump();//ボスの埋まり回避用とブロック飛び越えとか

		} else {
			if (attacktime % 50 == 0) {
				bossAction = NormalAttack;//プレイヤーが上の方逃げたら投擲
				attacktime = 0;
			}
		}

		if (HP != MaxHP && HP != BefHP && HP % 4 == 0) {
			bossAction = SetStartPos;
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
		StayCount++;
		if (StayCount > 150) {
			bossAction = None;
			StayCount = 0;
		}
		break;

	case NormalAttack:
		NormalAttacks(player);
		armreturn = true;
		Sec_armreturn = true;
		break;
	case StartBattle:
		if (startcount > 2.0f) {
			bossAction = None;
			//	phase = true;
		}
		break;
	case ArmAttacks:
		ArmAytack(player);
		ArmAttack_Left(player);
		break;
	default:
		break;
	}

}

void ForestBoss::ColMap1(int map[130][20], std::unique_ptr<Object3d>  tst[130][20], float mapx[130][20], float mapy[130][20], const int X, const int Y)
{

}
void ForestBoss::Follow(XMFLOAT3 position)
{
	float angleX, angleZ, angleR;
	float centerSpeed = 0.1f;
	angleX = (position.x - Position.x);
	angleZ = (position.y - Position.y);
	angleR = sqrtf((Position.x - position.x) * (Position.x - position.x)
		+ (Position.y - position.y) * (Position.y - position.y));

	Position.x += (angleX / angleR) * (bossmovespeed / 2);

}


void ForestBoss::appearance(float& camerapos,float position)
{
	float oldpos=-48;
	if (phase&&!returnCamera) {
		cameratime += 0.002f;
		if (camerapos >= 178) {
			cameratime = 0;
			returnCamera = true;
			phase = false;
		}
		else {
			camerapos = Easing::EaseOut(cameratime, oldpos, 178);
		}
	} else {
		oldpos = camerapos;
		startcount += 0.01f;
	}

	if (returnCamera) {
		returnCameraTime += 0.01f;
		if (camerapos <= -40) {
			returnCameraTime = 0;
			returnCamera = false;
			phase = false;
		}
		else {
			camerapos = Easing::EaseOut(returnCameraTime, 177, -48);
		}

	}
	if (Input::GetInstance()->TriggerKey(DIK_J)) {
		//bossAction = None;
		phase = true;
	}

	if (!returnCamera && !phase) {
		camerapos = position;
	}
}

void ForestBoss::GetDamage()
{

	if (HP == MaxHP) {
		OldHP = HP - 1;
	}
	if (HP == OldHP && !damageRec) {
		damageRec = true;
		OldHP--;
	}
	if (damageRec) {
		r = 1.0f; g = 0.2f; b = 0.0f;
		damageRec = false;
	} else {
		if (r > 0.0f)r -= 0.1f;
		if (g < 1.0f)g += 0.1f;
		if (b < 1.0f)b += 0.1f;
		//BossObject->SetColor({ 1,1.0f,1.0f,1 });
	}
	NuclearObj->SetColor({ r,g,b,1.0f });
	//BossObject->SetColor({ r,g,b,1.0f });
}
void ForestBoss::SearchAction(XMMATRIX matview, XMMATRIX matprojection, XMFLOAT3 position) {

}

void ForestBoss::collisionArm(Player* player)
{
	
	//当たり判定の処理(OBB)後で分けたほうがいい
		//プレイヤーのOBB 回転ベクトル
	pobb.m_NormaDirect[0] = { player->GetMatrot().r[0].m128_f32[0],player->GetMatrot().r[0].m128_f32[1],player->GetMatrot().r[0].m128_f32[2] };
	pobb.m_NormaDirect[1] = { player->GetMatrot().r[1].m128_f32[0],player->GetMatrot().r[1].m128_f32[1],player->GetMatrot().r[1].m128_f32[2] };
	pobb.m_NormaDirect[2] = { player->GetMatrot().r[2].m128_f32[0],player->GetMatrot().r[2].m128_f32[1],player->GetMatrot().r[2].m128_f32[2] };
	pobb.m_fLength[0] = 1;//x方向の長さ
	pobb.m_fLength[1] = 1;//y方向の長さ
	pobb.m_fLength[2] = 1;//z方向の長さ
	//敵のOBB 回転ベクトル
	earmobb_right.m_NormaDirect[0] = { BossArmObj[0]->GetMatrot().r[0].m128_f32[0],BossArmObj[0]->GetMatrot().r[0].m128_f32[1],BossArmObj[0]->GetMatrot().r[0].m128_f32[2] };
	earmobb_right.m_NormaDirect[1] = { BossArmObj[0]->GetMatrot().r[1].m128_f32[0], BossArmObj[0]->GetMatrot().r[1].m128_f32[1], BossArmObj[0]->GetMatrot().r[1].m128_f32[2] };
	earmobb_right.m_NormaDirect[2] = { BossArmObj[0]->GetMatrot().r[2].m128_f32[0], BossArmObj[0]->GetMatrot().r[2].m128_f32[1], BossArmObj[0]->GetMatrot().r[2].m128_f32[2] };
	earmobb_right.m_fLength[0] = Arm_Scl[0].x;//x方向の長さ
	earmobb_right.m_fLength[1] = Arm_Scl[0].y * 2;//y方向の長さ
	earmobb_right.m_fLength[2] = Arm_Scl[0].z;//z方向の長さ
	//OBBの設定位置
	pobb.m_Pos = { player->GetPosition().x,player->GetPosition().y,player->GetPosition().z };
	earmobb_right.m_Pos = { BossArmObj[0]->GetPosition().x,  BossArmObj[0]->GetPosition().y, BossArmObj[0]->GetPosition().z };

	if (pobbcolright->ColOBBs(pobb, earmobb_right)) {
		player->SetHp(player->getHp() - 1);
	} else {
		//obbf = 0;
	}

	//敵のOBB 回転ベクトル
	earmobb_left.m_NormaDirect[0] = { BossArmObj[1]->GetMatrot().r[0].m128_f32[0],BossArmObj[1]->GetMatrot().r[0].m128_f32[1],BossArmObj[1]->GetMatrot().r[0].m128_f32[2] };
	earmobb_left.m_NormaDirect[1] = { BossArmObj[1]->GetMatrot().r[1].m128_f32[0], BossArmObj[1]->GetMatrot().r[1].m128_f32[1], BossArmObj[1]->GetMatrot().r[1].m128_f32[2] };
	earmobb_left.m_NormaDirect[2] = { BossArmObj[1]->GetMatrot().r[2].m128_f32[0], BossArmObj[1]->GetMatrot().r[2].m128_f32[1], BossArmObj[1]->GetMatrot().r[2].m128_f32[2] };
	earmobb_left.m_fLength[0] = Arm_Scl[1].x;//x方向の長さ
	earmobb_left.m_fLength[1] = Arm_Scl[1].y*2;//y方向の長さ
	earmobb_left.m_fLength[2] = Arm_Scl[1].z;//z方向の長さ
	//OBBの設定位置
	pobb.m_Pos = { player->GetPosition().x,player->GetPosition().y,player->GetPosition().z };
	earmobb_left.m_Pos = { BossArmObj[1]->GetPosition().x,  BossArmObj[1]->GetPosition().y, BossArmObj[1]->GetPosition().z };

	if (pobbcolleft->ColOBBs(pobb, earmobb_left)) {
		player->SetHp(player->getHp() - 1);
	} else {
		//obbf = 0;
	}
}

void ForestBoss::ArmAytack(Player*player)
{
	ArmAttackCount++;
	if (ArmAttackCount%300==0) {
		ArmAttackflag = true;
	}
	if (ArmAttackflag) {
		armattacktime += 0.05f;
		Arm_Scl[0].y = Easing::EaseOut(armattacktime, OldArm_Scl[0].y, OldArm_Scl[0].y+5);
		if (Collision::GetLen({ OldArm_Scl[0].x,OldArm_Scl[0].y+10,OldArm_Scl[0].z }, Arm_Scl[0]) < 1) {
			ArmAttackflag = false;
			armreturn=true;
			armattacktime = 0.0f;
		}
	}
	else {
		OldArm_Scl[0] = Arm_Scl[0];
	}
	if (armreturn) {
		armattacktime2 += 0.05f;
		Arm_Scl[0].y = Easing::EaseOut(armattacktime2, Arm_Scl[0].y, 0);
		if (Collision::GetLenY(Arm_Scl[0], { 0,0,0 }) < 1) {
			armreturn = false;
			armattacktime2 = 0;
	}
	}
	if (!ArmAttackflag && !armreturn) {
		XMVECTOR positionA = { player->GetPosition().x,player->GetPosition().y, player->GetPosition().z };
		XMVECTOR positionB = { Arm_Pos[0].x,Arm_Pos[0].y,Arm_Pos[0].z };
		//プレイヤーと敵のベクトルの長さ(差)を求める
		XMVECTOR SubVector = DirectX::XMVectorSubtract(positionB, positionA);// positionA - positionB;
		rotfollow = atan2f(SubVector.m128_f32[0], SubVector.m128_f32[1]);

		Arm_Rot[0].z = rotfollow * 60 + 180;//60=角度調整用 180=反転

	}
}


void ForestBoss::ArmAttack_Left(Player* player)
{
	if (Position.y > 120) {
		attackcount2++;
		if (attackcount2 % 500 == 0) {
			Sec_ArmAttackflag = true;
		}
	}
	if (Input::GetInstance()->TriggerKey(DIK_B)) {
		Sec_ArmAttackflag = true;
	}
	if (Input::GetInstance()->TriggerKey(DIK_C)) {
		Sec_ArmAttackflag = true;
		ArmAttackflag = true;
	}
	if (Sec_ArmAttackflag) {
		Sec_armattacktime += 0.05f;
		Arm_Scl[1].y = Easing::EaseOut(Sec_armattacktime, OldArm_Scl[1].y, OldArm_Scl[1].y + 5);
		if (Collision::GetLen({ OldArm_Scl[1].x,OldArm_Scl[1].y + 10,OldArm_Scl[1].z }, Arm_Scl[1]) < 1) {
			Sec_ArmAttackflag = false;
			Sec_armreturn = true;
			Sec_armattacktime = 0.0f;
		}
	} else {
		OldArm_Scl[1] = Arm_Scl[1];
	}
	if (Sec_armreturn) {
		Sec_armattacktime2 += 0.05f;
		Arm_Scl[1].y = Easing::EaseOut(Sec_armattacktime2, Arm_Scl[1].y, 0);
		if (Collision::GetLenY(Arm_Scl[1], { 0,0,0 }) < 1) {
			Sec_armreturn = false;
			Sec_armattacktime2 = 0;
		}
	}
	if (!Sec_ArmAttackflag && !Sec_armreturn) {
		XMVECTOR positionA = { player->GetPosition().x,player->GetPosition().y, player->GetPosition().z };
		XMVECTOR positionB = { Arm_Pos[1].x,Arm_Pos[1].y,Arm_Pos[1].z };
		//プレイヤーと敵のベクトルの長さ(差)を求める
		XMVECTOR SubVector = DirectX::XMVectorSubtract(positionB, positionA);// positionA - positionB;
		Sec_rotfollow = -1*atan2f(SubVector.m128_f32[0], SubVector.m128_f32[1]);

		Arm_Rot[1].z = Sec_rotfollow * 60 + 180;//60=角度調整用 180=反転

	}
}


void ForestBoss::NormalAttacks(Player* player)
{
	float x[3];
	float y[3];
	if (Input::GetInstance()->TriggerKey(DIK_S)) {
		BarrelRec = true;
	}
	for (int i = 0; i < 3; i++) {
		if (attackcount % 100 == 0) {
			BarrelFolflag = false;
			if (!shotf[i]) {
				//shotf[i] = true;
				//if (Input::GetInstance()->TriggerKey(DIK_S)) {
				if (!ChangeAttack) {
					shotf[i] = true;
					BarrelRec = true;
				}
				else {
					delete ShotObj[i];
					ShotObj[i] = nullptr;
				}
				//}

				Shot_Pos[i] = { Arm_Pos[0].x,Arm_Pos[0].y, Arm_Pos[0].z };
				x[i] = player->GetPosition().x - Shot_Pos[i].x;
				y[i] = player->GetPosition().y - Shot_Pos[i].y;

				BulAngle[i] = sqrtf(x[i] * x[i] + y[i] * y[i]);

				Xspeed[i] = ( 0.1f * x[i] / BulAngle[i]);
				Yspeed[i] = ( 0.1f * y[i] / BulAngle[i]);
				break;
			}

		}
			if (BarrelRec) {
				if (Barrel_Scl.y <= 2) {
					BarrelFolflag = true;
				}
			}
		if(shotf[i]&&ShotObj[i]!=nullptr) {
			Shot_Pos[i].x += Xspeed[i];
			Shot_Pos[i].y += Yspeed[i];
			if (Collision::GetLen(Shot_Pos[i], player->GetPosition()) < 1) {
				player->SetHp(player->getHp() - 1);
				shotf[i] = false;
				break;
			}
			if (Collision::GetLen(Shot_Pos[i], Position) > 100) {
				shotf[i] = false;
				break;
			}
		
		}
		 
		}
	//きったねえ
	attackcount++;
	if (BarrelRec) {
		if (Barrel_Scl.y > 2) {
			Barrel_Scl.y -= 0.08f;
		}
		else {
			BarrelRec = false;
		}
		}
	else {
		if (!ChangeAttack) {
			if (Barrel_Scl.y < 3) {
				Barrel_Scl.y += 0.05f;
			}
		}
	}

	if (player->GetPosition().y > 40) {
		ChangeAttack = true;
	}
	if (ChangeAttack) {
		if (Barrel_Scl.y >= 0) {
			Barrel_Scl.y -= 0.05f;
		}
		else {
			bossAction = ArmAttacks;
		}
	}
	//Barrel_Scl.y -= 0.05f;
	
		XMVECTOR positionA = { player->GetPosition().x,player->GetPosition().y, player->GetPosition().z };
		XMVECTOR positionB = { Position.x,Position.y,Position.z };
		//プレイヤーと敵のベクトルの長さ(差)を求める
		XMVECTOR SubVector = DirectX::XMVectorSubtract(positionB, positionA);// positionA - positionB;
		BarrelRotFollow = atan2f(SubVector.m128_f32[0], SubVector.m128_f32[1]);
		if (BarrelFolflag) {
		
			Barrel_Rot.z = BarrelRotFollow * 60 + 180;//60=角度調整用 180=反転
	}
	}

void ForestBoss::UpDownMove(XMFLOAT3 position)
{
	countUpDownMove++;
	const float moveCycle = 120.0f;
	if (!NuclearDeayh) {
		Position.y = (position.y + 17) + sin(PI * 2 / moveCycle * countUpDownMove) * 2;
		Rotation.y = BarrelRotFollow * 60 + 180;

	}
	if (NuclearHP==1) {
		
		NuclearDeayh = true;
	}
	DeathMotion();
	if (NuclearDeayh&&Position.y<position.y-20) {
		SetHP(0);
		//SetDead(true);
		//enemyState = State::DEAD;
	}
}

void ForestBoss::DeathMotion()
{
	if (Input::GetInstance()->TriggerKey(DIK_D)) {
		NuclearDeayh=true;
	}
	if (NuclearDeayh) {
		
		deathcount++;
		if (deathcount < 200) {
			Rotation.x = 20;
			Rotation.y += 50;
		}
		else if(deathcount>200&&deathcount<230){
			Position.y += 0.3f;
		}
		else if (deathcount > 233) {
			if (Rotation.x < -180) {
				Rotation.x -= 5;
			}
			Position.y -= 0.001f*deathcount*2;
		}
	}
}