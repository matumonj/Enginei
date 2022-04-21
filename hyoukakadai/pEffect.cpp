#include "pEffect.h"
void pEffect::Initialize(DirectXCommon* dxcomn, DebugCamera* camera)
{
	effect = new mEffekseer();
	//effect->Initialize(dxcomn, camera);

	//エフェクトのセット(3引き数に)
	effect->EffekseerSetting(dxcomn, camera, (const EFK_CHAR*)L"Effect/10/weffect2.efk", (const EFK_CHAR*)L"effect/10");

}

void pEffect::Update(DirectXCommon* dxcomn, DebugCamera* camera,XMFLOAT3 position,bool flag)
{
	effect->SetPosition(position.x, position.y, position.z );
	//エフェクトのパラメータセット
	effect->SetRotation(0, 0, 0);
	effect->SetScale(0.5,1,0.1);

	//エフェクトの再生
	if (Input::GetInstance()->TriggerKey(DIK_F)&&!eflag) {
		eflag = true;
		//effect->Load_Effect();
	}
	if (eflag) {
		effect->Load_Effect();
		eflag = false;
	}
	effect->EffekseerUpdate(dxcomn, camera);

}

void pEffect::Draw(DirectXCommon*dxcomn)
{
	//effect->EffekseerDraw(dxcomn->GetCmdList());

}