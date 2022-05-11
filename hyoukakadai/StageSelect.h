#pragma once
#include"Model.h"
#include"Object3d.h"
#include"BaseScene.h"
#include"Input.h"
#include"DirectXCommon.h"
#include"DebugCamera.h"
#include"LightGroup.h"
class StageSelect:public BaseScene
{
public:
	StageSelect(SceneManager* sceneManager);
private: // エイリアス
	 // Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

private:
	Object3d* SelectStageObj;
	Model* SelectStageModel;
private:
	enum Stage {
		TutorialStage,
		Stage1_1,
		Stage1_2,
		Stage2_1,
		Stage2_2,
	};
	Stage selectStage[5] = { TutorialStage,
		Stage1_1,
		Stage1_2,
		Stage2_1,
		Stage2_2, };
	int SelectNum = 0;
	float time = 0.0f;
	float Rotnext;
	float RotNow;
	Stage NowSelectStage = TutorialStage;
	bool SelectEnd = false;
	bool Selectflag = false;
public:
	void SelectMove();

	void Select();
	private:
		DebugCamera* camera;
	private:
		XMFLOAT3 obj_Pos;
		XMFLOAT3 obj_Scl = { 1,1,1};
		XMFLOAT3 obj_Rot;
		//float botttomy = 0;
	private://点光源
		LightGroup* lightGroup = nullptr;
		float ambientColor0[3] = { 1,1,1 };

		float lightDir0[3] = { 0,0,1 };
		float lightColor0[3] = { 1,0,0 };

		float lightDir1[3] = { 0,1,0 };
		float lightColor1[3] = { 0,1,0 };

		float lightDir2[3] = { 1,0,0 };
		float lightColor2[3] = { 0,0,1 };

		float pointLightPos[3] = { 0,0,-50 };
		float pointLightColor[3] = { 1,1,1 };
		float pointLightAtten[3] = { 0.05f,0.05f,0.05f };

		int SpotLightflag = false;
	private://スポットライト
		float spotLightDir[3] = { 0,-1,0 };
		float spotLightpos[3] = { 0.0f,24.11f,-16.4f };
		float spotLightColor[3] = { 1,1,1 };
		float spotLightAtten[3] = { 0.0f,0.0f,0.0f };
		float spotLightFactorAngle[2] = { 20.0f,30.0f };

	public:
		void SpriteCreate();
		void ModelCreate();
		void MyGameDraw(DirectXCommon* dxcomn);
	public:
		XMFLOAT3 texpo = { 0,0,0 };
		void Initialize(DirectXCommon* dxCommon)override;
		void Update(DirectXCommon* dxCommon)override;
		void Draw(DirectXCommon* dxcomn)override;
		void ImGuiDraw();
		void Finalize()override;

		
	};