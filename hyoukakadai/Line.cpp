#include "Line.h"
#include"Input.h"
#include"GameUI.h"
#define PI 3.14159
using namespace DirectX;

Texture* Line::Twine = nullptr;
float Line::FollowangleX, Line::FollowangleZ, Line::FollowangleR;
float Line::FollowSpeed = 1.0f;
bool Line::trigger = false;
int Line::f;
bool Line::boundflag = false;
bool Line::stopflag = true;
bool Line::returnflag = false;
bool Line::notdoubletuch = true;
float Line::tempx, Line::tempy;
float Line::linex, Line::linex2, Line::liney, Line::liney2;
float Line::lineangle = 0;
float Line::subradius = 0;
float Line::Startsubradius = 2.0f;
float Line::olddistance = 0;
const float Line::LengThenSpeed = 1.0f;
const float Line::MaxLen = 30.0f;
const float Line::MinLen = 0.0f;
float Line::LimitGauge,Line::necolor=1,Line::twcolor=1;
bool Line::lengthserchf = false;
bool Line::goflag = false;
bool Line::colf = false,Line::colfsub=false;
float Line::grav = 0.05f;
float Line::MoveSpeed = 0;
Object3d* Line::NeedleObj = nullptr;
Model* Line::NeedleModel = nullptr;
int Line::L_Cflag = 0;
XMFLOAT3 Line::po = { 0,0,0 }, Line::needlepos, Line::needlerot;
bool Line::elf = false;
float Line::oldlinex, Line::oldliney;
int Line::index = -1;
int Line::index2 = -1;
bool Line::mapcol = false;
Line* Line::GetInstance()
{
	static Line instance;
	return &instance;
}


void Line::Initialize()
{
	Texture::LoadTexture(13, L"Resources/gomi.png");
	Twine = Texture::Create(13, { 0,-50,50 }, { 1,1,1 }, { 1,1,1,1 });

	NeedleModel = Model::CreateFromOBJ("hari");
	NeedleObj = Object3d::Create();
	NeedleObj->SetModel(NeedleModel);

	//各種初期化
	subradius = 0;
	lineangle = 0;
	boundflag = false;
	returnflag = false;

	trigger = false;
	mapcol = false;
	elf = false;
	colf = false;
	lengthserchf = false;
	needlerot.z = 0;
	stopflag = true;
	goflag = false;
}

void Line::Update(XMMATRIX matview, XMMATRIX matprojection, Player* player, XMFLOAT3& Player_Pos, bool& mapcolf, float& moveSpeed)
{
	float sdistance;
	sdistance = sqrtf(((player->GetPosition().x - linex2) * (player->GetPosition().x - linex2)) +
		((player->GetPosition().y - liney2) * (player->GetPosition().y - liney2))
	);
	//UI部分の外枠ゲージが０なったら紐出せなくなる
	LimitGauge = GameUI::GetInstance()->Getsclx();
	if (LimitGauge < 0) {
		//trigger = false;//紐出せないように
		//subradius = 0;//伸ばせる紐の長さを０に強制
		//boundflag = false;
		//returnflag = false;
	}

	//やけくそコード,汚いよ
	linex = player->GetPosition().x;//線の始点をプレイヤー位置に
	liney = player->GetPosition().y;

	if (stopflag == true) {
		if (Input::GetInstance()->Pushkey(DIK_1)&& !boundflag) {
			lineangle += 5.0f;//移動方向の指定
			subradius = Startsubradius;//飛ぶ方向の矢印みたいなの長さの初期値設定(後で置き換え.どうせ別のオブジェするでしょ)
			needlerot.z += 5;
		}
	}

	//コントローラー
	LONG u_r = 32768;
	LONG a = 30000;
	LONG b = 15000;

	if (!elf && !mapcol) {
		if (stopflag == true) {
			if (Input::GetInstance()->GetCMove().lRx < u_r - a)
			{
				// 左に傾けた
				lineangle = +180;
				needlerot.z = +180;
			} else if (Input::GetInstance()->GetCMove().lRx > u_r + a)
			{
				// 右に傾けた
				lineangle = 0;
				needlerot.z = 0;
			}
			if (Input::GetInstance()->GetCMove().lRy < u_r - a)
			{
				// 傾けた
				lineangle = +90;
				needlerot.z = +90;

			} else if (Input::GetInstance()->GetCMove().lRy > u_r + a)
			{
				// 傾けた
				lineangle = +270;
				needlerot.z = +270;
			}

			// 右上に傾けた
			if (Input::GetInstance()->GetCMove().lRx > u_r + b && Input::GetInstance()->GetCMove().lRy < u_r - b)
			{
				lineangle = +45;
				needlerot.z = +45;
			}
			// 左上に傾けた
			if (Input::GetInstance()->GetCMove().lRx < u_r - b && Input::GetInstance()->GetCMove().lRy < u_r - b)
			{
				lineangle = +135;
				needlerot.z = +135;
			}
			// 左下に傾けた
			if (Input::GetInstance()->GetCMove().lRx < u_r - b && Input::GetInstance()->GetCMove().lRy > u_r + b)
			{
				lineangle = +225;
				needlerot.z = +225;
			}
			// 右下に傾けた
			if (Input::GetInstance()->GetCMove().lRx > u_r + b && Input::GetInstance()->GetCMove().lRy > u_r + b)
			{
				lineangle = +315;
				needlerot.z = +315;
			}
		}
	}
	if (!elf) {
		linex2 = tempx + cosf((lineangle)*PI / 180.0f) * subradius;
		liney2 = tempy + sinf((lineangle)*PI / 180.0f) * subradius + 0.5f;
	}
	//////////中心点//////飛ばす角度///////////////////半径(距離)
	if (notdoubletuch == true) {
		if (Input::GetInstance()->TriggerButtonRB() || Input::GetInstance()->TriggerKey(DIK_SPACE)) {
			//Line::GetInstance()->SetTrigger(true);
			trigger = true;//線を伸ばすフラグね
			elf = false;
			stopflag = false;
			notdoubletuch = false;

			//Line = 1;
		}
	}

	if (trigger) {//trigger:線伸ばすフラグ
		subradius += LengThenSpeed;//線を伸ばす
		if (subradius > MaxLen || elf) {//一定以上行ったら+ブロックに針あたったら
			lengthserchf = true;
			goflag = true;
			trigger = false;
		}
		if (subradius > MaxLen && !elf) {//一定以上行って何も当たらなかったら
			lengthserchf = true;
			returnflag = true;
			trigger = false;
		}

	} else if (!trigger && subradius > 0) {//フラグ切られて線の長さがまだある時
		
		if (goflag == true && elf) {
			boundflag = true;//線の終点へ吸い付くフラグ
		}

		//線の終点とプレイヤーとの距離求める
		float distance;
		distance = sqrtf(((player->GetPosition().x - linex2) * (player->GetPosition().x - linex2)) +
			((player->GetPosition().y - liney2) * (player->GetPosition().y - liney2))
		);
		//プレイヤーと紐の距離が一定以内に縮まったら
		if (distance <= 2.0f) {
			colf = true;//UIゲージ減らす処理gameui.cppの方

			//elf = false;
			boundflag = false;
			subradius = 0;//線の長さを0に
			stopflag = true;
			notdoubletuch = true;
		} 

	}
	//先の長さが最大超えた、またはブロックあたったらその時点のプレイヤーと線の距離を求める（その距離分ゲージ減らす）
	if (lengthserchf) {
		olddistance = sdistance;//ui.scaleX-sdistance*4
		lengthserchf = false;
	}

	//吸い付く処理
	if (boundflag) {
		FollowangleX = (linex2 - player->GetPosition().x);
		FollowangleZ = (liney2 - player->GetPosition().y);//これZじゃなくてYです
		FollowangleR = sqrtf((player->GetPosition().x - linex2) * (player->GetPosition().x - linex2)
			+ (player->GetPosition().y - liney2) * (player->GetPosition().y - liney2));
		moveSpeed = 0.5f;
		Player_Pos.x += (FollowangleX / FollowangleR) * moveSpeed;
		Player_Pos.y += (FollowangleZ / FollowangleR) * moveSpeed;
		//stopflag = true;
		//notdoubletuch = true;
	} else {

		//吸い付くフラグがFALSEんときだけ中心点をプレイヤーの方に
		/*メモ:ずっと中心点を現時点のプレイヤーの座標に設定してるとプレイヤーが動いた分だけ
　　　　　線の終点も動いてしまうから(subradiusの部分が中心点依存)*/
		tempx = Player_Pos.x;
		tempy = Player_Pos.y;
	}
	//線が戻ってくる処理
	if (returnflag) {
		subradius -= 1.5f;

		if (subradius <= 0.5f) {//先の長さが０なったら切る
			returnflag = false;
			//mapcolf = false;
			colf = true;
			stopflag = true;
			notdoubletuch = true;
			goflag = false;
		}
	}

	max(subradius, MinLen);
	min(subradius, MaxLen);
	Twine->CreateLineTexture(linex, linex2, liney, liney2);
	Twine->SetPosition(po);
	Twine->Update(matview, matprojection);
	

	NeedleObj->SetPosition({ linex2,liney2,Player_Pos.z });
	//needlerot = player->GetRotation();
	needlepos = NeedleObj->GetPosition();
	NeedleObj->SetScale({ 1.4f,1.4f,1.5f });
	NeedleObj->SetRotation({ needlerot });
	NeedleObj->Update({ 1,1,1,necolor });
}

void Line::Draw(DirectXCommon* dxcomn)
{
	Texture::PreDraw(dxcomn->GetCmdList());
	Twine->Draw();
	Texture::PostDraw();

	Object3d::PreDraw();
	NeedleObj->Draw();
	Object3d::PostDraw();
}


void Line::CollisionEnemys(std::unique_ptr<Enemy>position[])
{
	//int index;
	if (elf) {
		Twine->SetColor({ 1,0,0,twcolor });
	} else {
		Twine->SetColor({ 1,1,1,twcolor });
	}
	//int in = -1;
	float dis[10];
	for (int i = 0; i < 10; i++) {
		if (position[i] != nullptr) {
			dis[i] = sqrtf((position[i]->GetPosition().x - needlepos.x) * (position[i]->GetPosition().x - needlepos.x) +
				(position[i]->GetPosition().y - needlepos.y) * (position[i]->GetPosition().y - needlepos.y));

			if (dis[i] <= 2 && trigger && !elf) {
				elf = true;
				index = i;//あたった敵の要素番号を割り当て
			}
		}

		//衝突時
		if (elf && !mapcol) {
			if (position[index] != nullptr) {
				linex2 = position[index]->GetPosition().x;
				liney2 = position[index]->GetPosition().y;
			}
			else {
				if (index2 == -1) {
					returnflag = true;
				}
			}
		}
	}
	if (mapcol) {
		oldlinex = linex2;
		oldliney = liney2;
		if (elf) {
			linex2 = oldlinex;
			liney2 = oldliney;
		}
	}

	if ( colf) {
		elf = false;
		mapcol = false;
	}
}
//

void Line::CollisionEnemys2group(std::unique_ptr<Enemy>position[])
{
	if (elf) {
		Twine->SetColor({ 1,0,0,twcolor });
	} else {
		Twine->SetColor({ 1,1,1,twcolor });
	}
	//int in = -1;
	float dis[10];
	for (int i = 0; i < 10; i++) {
		if (position[i] != nullptr) {
			dis[i] = sqrtf((position[i]->GetPosition().x - needlepos.x) * (position[i]->GetPosition().x - needlepos.x) +
				(position[i]->GetPosition().y - needlepos.y) * (position[i]->GetPosition().y - needlepos.y));

			if (dis[i] <= 2 && trigger && !elf) {
				elf = true;
				index2 = i;//あたった敵の要素番号を割り当て
			}
		}

		//衝突時
		if (elf && !mapcol) {
			if (position[index2] != nullptr) {
				linex2 = position[index2]->GetPosition().x;
				liney2 = position[index2]->GetPosition().y;
			} else {
				if (index == -1) {
					returnflag = true;
				}
				}
		}
	}
	if (mapcol) {
		oldlinex = linex2;
		oldliney = liney2;
		if (elf) {
			linex2 = oldlinex;
			liney2 = oldliney;
		}
	}

	if (colf) {
		elf = false;
		mapcol = false;
	}
}


void Line::CollisionEnemy(Enemy* position)
{
	if (elf) {
		Twine->SetColor({ 1,0,0,twcolor });
	} else {
		Twine->SetColor({ 1,1,1,twcolor });
	}
	//int in = -1;
	float dis;
	if (position != nullptr) {
		dis = sqrtf((position->GetPosition().x - needlepos.x) * (position->GetPosition().x - needlepos.x) +
			(position->GetPosition().y - needlepos.y) * (position->GetPosition().y - needlepos.y));

		if (dis <= 2 && trigger && !elf) {
			elf = true;
			//	index = i;//あたった敵の要素番号を割り当て
		}
	}

	//衝突時
	if (elf && !mapcol) {
		if (position != nullptr) {
			linex2 = position->GetPosition().x;
			liney2 = position->GetPosition().y;
		} 
		else {
			returnflag = true;
		}
	}
	if (mapcol) {
		oldlinex = linex2;
		oldliney = liney2;
		
		if (elf) {
			linex2 = oldlinex;
			liney2 = oldliney;
			
		}
	}

	if ( colf) {
		elf = false;
		//boundflag = false;
		mapcol = false;
	}
}
//フラグ説明
/*
boundflag:紐の終点へプレイヤーが吸い付くフラグ
returnflag:紐の終点(subradius)がプレイヤーの方へ
colf:紐の残量が減るフラグ
elf:紐とマップブロック&&敵の当たり判定
lenserchf:紐ゲージの減る量を決めるフラグ
*/
void Line::Finalize()
{
	delete Twine;
	delete  NeedleModel;
	delete NeedleObj;

}