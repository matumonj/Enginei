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
#include<memory>
class Line
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::Çè»ó™
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
	static bool goflag;
	static bool trigger ;
	static bool boundflag ;
	static bool returnflag;
	static bool drawflag;
	static bool stopflag;
	static bool notdoubletuch;
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
	static int index2;
	static float MoveSpeed;
	static int L_Cflag;
	static XMFLOAT3 po;
	static XMFLOAT3 needlepos;
	static XMFLOAT3 needlerot;
	static int f;
	static bool elf;
	static float oldlinex, oldliney;
	static bool mapcol;// = false;
	static bool colfsub;
	static float twcolor;
	static float necolor;
	static float timer;
public:
	void settwcolor(float c) {  twcolor=c; }
	void setnecolor(float c) { necolor=c; }
	static void Finalize();
	static Line* GetInstance();
	static void Initialize();
	static void Update(XMMATRIX matview, XMMATRIX matprojection,Player*player,XMFLOAT3&Player_Pos,bool& colf,float& moveSpeed);
	static void Draw(DirectXCommon* dxcomn);
	static void CollisionBlock(int** map, float** mapxy[2],float maphalf[2], const int MapX, const int MapY);
	static void CollisionEnemys(std::unique_ptr<Enemy> Position[]);
	static void CollisionEnemys2group(std::unique_ptr<Enemy> Position[]);

	static void CollisionEnemy(Enemy*Position);
public:
	void SetSubradius(float len) { subradius = len; }
	bool getcolfsub() { return colfsub; }
	void setcolfsub(bool f) { colfsub = f; }
	void Setmapcol(bool f) { mapcol = f; }
	float GetLength() { return subradius; }
	bool GetColf() { return colf; }
	bool Getreturnflag() { return returnflag; }
	bool GetStop() { return stopflag; }
	void Setpos(float lx,float ly) { linex2=lx;  liney2 = ly;
	}
	void SetColf(bool colf) { this->colf = colf; }
	float Getolddistance() { return olddistance; }
	float GetlineAngle() { return lineangle; }
	bool Getboundflag() { return boundflag; }
	bool Gettriggerflag() { return trigger; }
	XMFLOAT3 getpos() { return {linex2,liney2,needlepos.z}; }
	bool Getelf() { return elf; }
	void Setelf(bool flag) { elf = flag; }
	void SetTrigger(bool flag) { trigger = flag; }
	void SetReturnflag(bool f) { returnflag = f; }
	void SetBondflag(bool f) { boundflag = f; }
	bool getmapcol() {
		if (!mapcol && !elf) { 
			return true; 
		}
		else if (mapcol && elf) {
			return false;
		}
	}
};

