#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>
#include <string>
#include"Input.h"
/// <summary>
/// �G�L�����̊��N���X
/// </summary>
/// 
class Enemy
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Enemy();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~Enemy();

protected:
	//Microosoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

protected:
	XMFLOAT3 Position;
	XMFLOAT3 Rotation;
	XMFLOAT3 Scale;

	enum class State {
		ALIVE,
		DEAD,
	};
	State enemyState = State::ALIVE;
	int HP = 10;
public:

	inline bool GetState_DEAD() {
		if (enemyState == State::DEAD) {
			return true;
		} else {
			return false;
		}
	}

	inline bool GetState_ALIVE() {
		if (enemyState == State::ALIVE) {
			return true;
		} else {
			return false;
		}
	}
	void SetDead(bool f) { if (f) { enemyState = State::DEAD; } }
	void SetHP(int HP) { this->HP = HP; }

	virtual void EnemySearchPlayer(XMFLOAT3 player) = 0;

	/// <summary>
	/// ������
	/// </summary>
	virtual void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	virtual void Update(XMFLOAT3 position);

	/// <summary>
	/// �`�揈��
	/// </summary>
	virtual void Draw();

	virtual void Motion(int timer)=0;
	//virtual float Distance(Player* player);

	/// <summary>
	/// �������
	/// </summary>
	virtual void Finalize();
	void Setposition(XMFLOAT3 position) { Position = position; }
	XMFLOAT3 GetPosition() { return Position; }
};

