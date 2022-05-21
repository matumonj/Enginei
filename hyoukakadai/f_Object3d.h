#pragma once

#include "f_Model.h"
#include "Camera.h"

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>
#include <string>
#include"DirectXCommon.h"
#include"DebugCamera.h"
class f_Object3d
{
protected:
	//Microosoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	static void SetDevice(ID3D12Device* device) { f_Object3d::device = device; }
	static void SetCamera(Camera* camera) { f_Object3d::camera = camera; }


	///グラフィックパイプラインの生成
	static void CreateGraphicsPipeline();

private:
	//デバイス
	static ID3D12Device* device;
	//カメラ
	static Camera* camera;
	//ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootsignature;
	//パイプラインステート
	static ComPtr<ID3D12PipelineState> pipelinestate;

public:
	//定数バッファ用データ構造体
	struct ConstBufferDataTransform
	{
		XMMATRIX viewproj;	//ビュープロジェクション行列
		XMMATRIX world;		//ワールド行列
		XMFLOAT3 cameraPos;	//カメラ行列
	};

public:
	/// <summary>
	/// 初期化
	/// </summary>
	bool Initialize(DirectXCommon* dxcomn, DebugCamera* camera);

	/// <summary>
	/// 毎フレーム
	/// </summary>
	void Updata(XMFLOAT4 color, DirectXCommon* dxcomn, DebugCamera* camerabool, bool animeloop);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// モデルのセット
	/// </summary>
	void SetModel(f_Model* model) { this->model = model; }

	/// <summary>
	/// アニメーション
	/// </summary>
	void PlayAnimation();

protected:
	//定数バッファ
	ComPtr<ID3D12Resource> constBuffTransform;
	//スケール
	XMFLOAT3 scale = { 0.01,0.01,0.01 };
	//回転
	XMFLOAT3 rotation = { 0, 0, 0 };
	//座標
	XMFLOAT3 position = { 0, 0, 0 };
	//ワールド変換行列
	XMMATRIX matWorld;
	//モデル
	f_Model* model = nullptr;
	//定数バッファ
	ComPtr<ID3D12Resource> constBuffSkin;
	//1フレーム
	FbxTime frameTime;
	//アニメーション開始時間
	FbxTime startTime=1;
	//アニメーション終了時間
	FbxTime endTime;
	//現在時間
	FbxTime currentTime;
	//アニメーション再生中
	bool isPlay = false;

public:
	void SetPosition(XMFLOAT3 pos) { position = pos; }
	void SetRotation(XMFLOAT3 rot) { rotation = rot; }

	//ボーンの最大数
	static const int MAX_BONES = 50;
	XMFLOAT3 GetPosition() { return position; }
	XMFLOAT3 GetRotation() { return rotation; }
	//定数バッファ用データ構造体（スキニング）
	struct ConstBufferDataSkin
	{
		XMMATRIX bones[MAX_BONES];
	};
};
