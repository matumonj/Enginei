#pragma once
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include"DirectXCommon.h"
#include"Player.h"
#include"Texture.h"
#include"Object3d.h"
#include"Model.h"
#include"Enemy.h"
class Line
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::‚ðÈ—ª
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

	static Texture* Twine;
	static Model* NeedleModel;
	static Object3d* NeedleObj;
private:
	static float FollowangleX, FollowangleZ, FollowangleR;
	static float FollowSpeed ;
	static bool trigger ;
	static bool boundflag ;
	static bool returnflag ;
	static 	float tempx, tempy;
	static float linex, linex2, liney, liney2;
	static float lineangle ;
	static float subradius ;
	static float Startsubradius ;
	static float olddistance ;
	static const float LengThenSpeed ;
	static const float MaxLen;
	static const float MinLen ;
	static float LimitGauge;
	static bool lengthserchf ;
	static bool colf ;
	static float grav ;
	static int index;
	static float MoveSpeed;
	static int L_Cflag;
	static XMFLOAT3 po;
	static XMFLOAT3 needlepos;
	static int f;
	static bool elf;
	static float oldlinex, oldliney;
public:
	static Line* GetInstance();
	static void Initialize();
	static void Update(XMMATRIX matview, XMMATRIX matprojection,Object3d*player[],XMFLOAT3&Player_Pos,bool& colf);
	static void Draw(DirectXCommon* dxcomn);
	static void CollisionBlock(int** map, float** mapxy[2],float maphalf[2], const int MapX, const int MapY);
	static void CollisionEnemy(Enemy*Position[]);
public:
	float GetLength() { return subradius; }
	bool GetColf() { return colf; }
	void Setpos(float lx,float ly) { linex2=lx;  liney2 = ly;
	}
	void SetColf(bool colf) { this->colf = colf; }
	float Getolddistance() { return olddistance; }
	float GetlineAngle() { return lineangle; }
	bool Getboundflag() { return boundflag; }
	bool Getreturnflag() { return returnflag; }
	bool Gettriggerflag() { return trigger; }
	XMFLOAT3 getpos() { return {linex2,liney2,needlepos.z}; }
	bool Getelf() { return elf; }
	void Setelf(bool flag) { elf = flag; }
};

