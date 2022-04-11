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
 bool Line::returnflag = false;
 float Line::tempx, Line::tempy;
 float Line::linex, Line::linex2, Line::liney, Line::liney2;
 float Line::lineangle = 0;
 float Line::subradius = 0;
 float Line::Startsubradius = 2.0f;
 float Line::olddistance = 0;
 const float Line::LengThenSpeed = 1.0f;
 const float Line::MaxLen = 30.0f;
 const float Line::MinLen = 0.0f;
 float Line::LimitGauge;
 bool Line::lengthserchf = false;
 bool Line::colf = false;
 float Line::grav = 0.05f;
 float Line::MoveSpeed = 0;
 Object3d* Line::NeedleObj=nullptr;
 Model* Line::NeedleModel=nullptr;
 int Line::L_Cflag = 0;
 XMFLOAT3 Line::po = { 0,0,0 },Line::needlepos;
 bool Line::elf = false;
 float Line::oldlinex, Line::oldliney;
 int Line::index = -1;
 Line* Line::GetInstance()
 {
	 static Line instance;
	 return &instance;
}

void Line::Initialize()
{
	Texture::LoadTexture(13, L"Resources/gomi.png");
	Twine = Texture::Create(13, { 0,-50,50 }, { 1,1,1 }, { 1,1,1,1 });
	
	NeedleModel= Model::CreateFromOBJ("sphere");
	NeedleObj = Object3d::Create();
	NeedleObj->SetModel(NeedleModel);
	
}

void Line::Update(XMMATRIX matview,XMMATRIX matprojection,std::unique_ptr<Object3d>player[],XMFLOAT3& Player_Pos,bool& mapcolf)
{
	float sdistance;
	sdistance = sqrtf(((player[0]->GetPosition().x - linex2) * (player[0]->GetPosition().x - linex2)) +
		((player[0]->GetPosition().y - liney2) * (player[0]->GetPosition().y - liney2))
	);
	//UI�����̊O�g�Q�[�W���O�Ȃ�����R�o���Ȃ��Ȃ�
	LimitGauge = GameUI::GetInstance()->Getsclx();
	if (LimitGauge < 0) {
		trigger = false;//�R�o���Ȃ��悤��
		subradius = 0;//�L�΂���R�̒������O�ɋ���
		//boundflag = false;
		//returnflag = false;
	}

	//�₯�����R�[�h,������
	linex = player[0]->GetPosition().x;//���̎n�_���v���C���[�ʒu��
	liney = player[0]->GetPosition().y;
	if (Input::GetInstance()->Pushkey(DIK_1) && (!returnflag && !boundflag)) {
		lineangle += 13.0f;//�ړ������̎w��
		subradius = Startsubradius;//��ԕ����̖��݂����Ȃ̒����̏����l�ݒ�(��Œu������.�ǂ����ʂ̃I�u�W�F����ł���)
	}
	if (!elf) {
		linex2 = tempx + cosf((lineangle)*PI / 180) * subradius;
		liney2 = tempy + sinf((lineangle)*PI / 180) * subradius;
	}
	//////////���S�_//////��΂��p�x///////////////////���a(����)

	if (Input::GetInstance()->TriggerKey(DIK_SPACE) && (!returnflag && !boundflag)) {
		trigger = true;//����L�΂��t���O��
		elf = false;
	}

	if (trigger) {//trigger:���L�΂��t���O
		subradius += LengThenSpeed;//����L�΂�
		if (subradius > MaxLen||elf) {//���ȏ�s������+�u���b�N�ɐj����������
			trigger = false;
			lengthserchf = true;
		}
		if (subradius > MaxLen && !elf) {//���ȏ�s���ĉ���������Ȃ�������
			trigger = false;
			lengthserchf = true;
			returnflag = true;
		}
		
	} else if (!trigger && subradius > 0) {//�t���O�؂��Đ��̒������܂����鎞
		if (Input::GetInstance()->TriggerKey(DIK_F)&&elf) {//�����L�ѐ؂��ĉ����������Ă��Ȃ��Ƃ�
			boundflag = true;//���̏I�_�֋z���t���t���O
		} else if (Input::GetInstance()->TriggerKey(DIK_G)) {
			returnflag = true;//�����v���C���[�̕��֖߂��Ă���t���O,�R�̒�����maxlen�����Đj���u���b�N�Ƃ������Ă��Ȃ������炱��true��
		}
		//���̏I�_�ƃv���C���[�Ƃ̋������߂�
		float distance;
		distance = sqrtf(((player[0]->GetPosition().x - linex2) * (player[0]->GetPosition().x - linex2)) +
			((player[0]->GetPosition().y - liney2) * (player[0]->GetPosition().y - liney2))
		);
		//�v���C���[�ƕR�̋��������ȓ��ɏk�܂�����
		if (distance <= 1.0f) {
			colf = true;//UI�Q�[�W���炷����gameui.cpp�̕�
			//elf = false;
			boundflag = false;
			subradius = 0;//���̒�����0��
		}
	}
	//��̒������ő咴�����A�܂��̓u���b�N���������炻�̎��_�̃v���C���[�Ɛ��̋��������߂�i���̋������Q�[�W���炷�j
	if (lengthserchf) {
		olddistance = sdistance;//ui.scaleX-sdistance*4
		lengthserchf = false;
	}

	//�z���t������
	if (boundflag) {
		FollowangleX = (linex2 - player[0]->GetPosition().x);
		FollowangleZ = (liney2 - player[0]->GetPosition().y);//����Z����Ȃ���Y�ł�
		FollowangleR = sqrtf((player[0]->GetPosition().x - linex2) * (player[0]->GetPosition().x - linex2)
			+ (player[0]->GetPosition().y - liney2) * (player[0]->GetPosition().y - liney2));

		Player_Pos.x += (FollowangleX / FollowangleR) * FollowSpeed;
		Player_Pos.y += (FollowangleZ / FollowangleR) * FollowSpeed;
	} else {
		//�z���t���t���O��FALSE��Ƃ��������S�_���v���C���[�̕���
		/*����:�����ƒ��S�_�������_�̃v���C���[�̍��W�ɐݒ肵�Ă�ƃv���C���[��������������
�@�@�@�@�@���̏I�_�������Ă��܂�����(subradius�̕��������S�_�ˑ�)*/
		tempx = Player_Pos.x;
		tempy = Player_Pos.y;
	}
	//�����߂��Ă��鏈��
	if (returnflag) {
		subradius -= 1.5f;
		if (subradius <= 0) {//��̒������O�Ȃ�����؂�
			returnflag = false;
			//mapcolf = false;
			colf = true;
		}
	}

	max(subradius, MinLen);
	min(subradius, MaxLen);
	Twine->CreateLineTexture(linex, linex2, liney, liney2);
	Twine->SetPosition(po);
	Twine->Update(matview, matprojection);
	
	
	NeedleObj->SetPosition({linex2,liney2,Player_Pos.z});
	needlepos = NeedleObj->GetPosition();
	NeedleObj->SetScale({ 0.8,0.4,0.5 });
	NeedleObj->Update({ 1,1,1,1 });
}

void Line::Draw(DirectXCommon* dxcomn)
{
	Texture::PreDraw(dxcomn->GetCmdList());
	Twine->Draw();
	Texture::PostDraw();
	
	Object3d::PreDraw();
	//NeedleObj->Draw();
	Object3d::PostDraw();
}


void Line::CollisionEnemy(std::unique_ptr<Enemy>position[])
{
	//int in = -1;
	float dis[2];
	for (int i = 0; i < 2; i++) {
		if (position[i] != nullptr) {
			dis[i] = sqrtf((position[i]->GetPosition().x - needlepos.x) * (position[i]->GetPosition().x - needlepos.x) +
				(position[i]->GetPosition().y - needlepos.y) * (position[i]->GetPosition().y - needlepos.y));

			if (dis[i] <= 2 && trigger && !elf) {
				elf = true;
				index = i;//���������G�̗v�f�ԍ������蓖��
			}
		}
		if (elf) {
			linex2 = position[index]->GetPosition().x;
			liney2 = position[index]->GetPosition().y;	
		}
	
		if (returnflag || colf) {
			elf = false;
		}
	}
}
//�t���O����
/*
boundflag:�R�̏I�_�փv���C���[���z���t���t���O
returnflag:�R�̏I�_(subradius)���v���C���[�̕���
colf:�R�̎c�ʂ�����t���O
elf:�R�ƃ}�b�v�u���b�N&&�G�̓����蔻��
lenserchf:�R�Q�[�W�̌���ʂ����߂�t���O
*/