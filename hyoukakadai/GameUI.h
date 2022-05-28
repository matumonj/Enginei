#pragma once
#include"Sprite.h"
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include"DirectXCommon.h"
#include"nTexture.h"
#include"Player.h"
class GameUI
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private:
	//各スプライトのパラメータにはstatic付けといてください
	//playsceneの呼び出しでGameUIのインスタンス何個も必要ないため
	//糸にかかわるUI
	static Sprite* LineLength;
	static Sprite* LineLengthout;
	static Sprite* Attention[3];
	static Sprite* PlayerHP;
	static Sprite* BossHP;
	static Sprite* NowLoad;
	static float LoadAlpha;
	static XMFLOAT2 lpos,loutpos;//座標
	static XMFLOAT2 lscl,loutscl;//スケール
	static float tempx;
	static float lsclMax;
	static float alpha;
	static float walpha;
	static XMFLOAT2 BossHPpos, BossHPscl;
	static nTexture* AllowTexure;
	static XMFLOAT3 Alowpos, Alowscl,Alowrot;//座標
	static nTexture* TargetTexture;
	static XMFLOAT3 Targetpos, Targetscl, Targetrot;//座標
	//static nTexture* EnemySearchTexure;
	static XMFLOAT3 Espos, Esscl, Esrot;//座標
	static XMFLOAT2 playerHPPos, playerHPScl;//座標 
	static float Targetalpha;
	static Sprite* HintSea;
	static Sprite* HintForest;
	static Sprite* HPout;
	static Sprite* lineOutui;
	static float HintSeaAlpha;
	static float HintForestAlpha;
	static float seatimer;
	static float foretimer;
public:
	static void BossUIUpdate(Enemy* enemy);
	float Getsclx() { return loutscl.x; }
	static void UISpriteSet();
	static void UIUpdate(float length,bool flag, bool &boundflag,float movement);
	static void UIDraw(DirectXCommon*dxcomn);
	static void AttentionUI();
	static GameUI* GetInstance();
	void SetlineOutScl(float x) { loutscl.x = x; }
	float GetOutX() { return loutscl.x; }
	static void AllowUISet();
	static void AllowUIUpdate(XMMATRIX matview, XMMATRIX matprojection,XMFLOAT3 position, float rotangle, bool flag);
	static void AllowUIDraw(DirectXCommon*dxcomn);
	static void Finalize();
	static void PlayerUISet();
	static void PlayerUIUpdate(Player* player);
	static void PlayerUIDraw(DirectXCommon* dxcomn);

	static void EnemyUISet();
	static void EnemyUIUpdate(std::unique_ptr<Enemy>enemy);
	static void EnemyUIDraw(DirectXCommon* dxcomn);

	static void TargetUISet();

	static void TargetUIUpdate(XMMATRIX matview, XMMATRIX matprojection, bool flag);

	static void TargetUIDraw(DirectXCommon* dxcomn);

	static void AllDraw(DirectXCommon* dxcomn);
	static void NowLoadSet();

	static void NowLoadUpdate(bool onf);

	static void NowLoadDraw(DirectXCommon* dxcomn);

	static void HintSeaBossSet();

	static void HintSeaBossUpdate(bool onf);

	static void HintSeaBossDraw(DirectXCommon* dxcomn);
	static void HintForeBossSet();

	static void HintForeBossUpdate(bool onf);

	static void HintForeBossDraw(DirectXCommon* dxcomn);
};

