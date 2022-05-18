#pragma once
#include"CollisionPrimitive.h"
#include<DirectXMath.h>
#include"Object3d.h"
#include"Player.h"
using namespace DirectX;
class Collision
{
public:
	struct BoxVertex
	{
		float Up;
		float Down;
		float Left;
		float Right;
	};
public:
	static float GetLen_X(float position, float position2);
	static float GetLen(XMFLOAT3 position, XMFLOAT3 position2);
	static float GetLenX(XMFLOAT3 position, XMFLOAT3 position2);
	static float GetLenY(XMFLOAT3 position, XMFLOAT3 position2);
	static void ColMap1(int map[20][200], std::unique_ptr<Object3d> tst[20][200], float mapx[20][200], float mapy[20][200], const int X, const int Y, float& grav, float& time, float& movespeed, bool& jumpf, XMFLOAT3 &Player_Pos, XMFLOAT3 &Old_Pos);
	static void CollisionMap(int map[20][200], std::unique_ptr<Object3d> tst[20][200], float mapx[20][200], float mapy[20][200], const int X, const int Y, float& grav, float& time, float& movespeed, bool& jumpf, XMFLOAT3& Player_Pos,XMFLOAT3 PLayer_Scl, XMFLOAT3& Old_Pos, int MAP_NUMBER);
	static void ColMapb1(int map[130][20], std::unique_ptr<Object3d> tst[130][20], float mapx[130][20], float mapy[130][20], const int X, const int Y, float& grav, float& time, float& movespeed, bool& jumpf, XMFLOAT3& Player_Pos, XMFLOAT3& Old_Pos);
	//森のBoss用
	static void ColMap2(int map[130][20], std::unique_ptr<Object3d> tst[130][20], float mapx[130][20], float mapy[130][20], const int X, const int Y, float& grav, float& time, float& movespeed, bool& jumpf, XMFLOAT3& Player_Pos, XMFLOAT3& Old_Pos);
	
	
	static bool ColMap3(int map[15][200], float mapx[15][200], float mapy[15][200], const int X, const int Y);

	static bool Boxcol(XMFLOAT2 a1, XMFLOAT2 a2, XMFLOAT2 b1, XMFLOAT2 b2);

	 float LinetoBoxCollision(const int Map_X, const int Map_Y, Object3d** map[],Player*player, float radius);
	/// <summary>
	/// 点と三角形の最近接点を求める
	/// </summary>
	/// <param name="point">点</param>
	/// <param name="triangle">三角形</param>
	/// <param name="closest">最近接点（出力用）</param>
	static void ClosestPtPoint2Triangle(const DirectX::XMVECTOR& point, const Triangle& triangle, DirectX::XMVECTOR* closest);

	/// <summary>
	/// 球と球の当たり判定
	/// </summary>
	/// <param name="sphereA">球A</param>
	/// <param name="sphereB">球B</param>
	/// <param name="inter">交点（出力用）</param>
	/// <param name="reject">排斥ベクトル（出力用）</param>
	/// <returns></returns>
	static bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB, DirectX::XMVECTOR* inter = nullptr, DirectX::XMVECTOR* reject = nullptr);

	//static bool ChenkSphere2Sphere(XMFLOAT3 object1, XMFLOAT3& object2, float r);
	static bool CheckBox2Box(XMFLOAT3 object1, XMFLOAT3& object2, XMFLOAT3 r, XMFLOAT3 r2);
	/// <summary>
	/// レイと平面の当たり判定
	/// </summary>
	/// <param name="lay">レイ</param>
	/// <param name="plane">平面</param>
	/// <param name="inter">距離（出力用）</param>
	/// <param name="inter">交点（出力用）</param>
	/// <returns>交差しているか否か</returns>
	static bool CheckRay2Plane(const Ray& lay, const Plane& plane, float* distance = nullptr, DirectX::XMVECTOR* inter = nullptr);

	/// <summary>
	/// 球と法線付き三角形の当たり判定
	/// </summary>
	/// <param name="sphere">球</param>
	/// <param name="triangle">三角形</param>
	/// <param name="inter">交点（三角形上の最近接点）</param>
	/// <param name="reject">排斥ベクトル（出力用）</param>
	/// <returns>交差しているか否か</returns>
	static bool CheckSphere2Triangle(const Sphere& sphere, const Triangle& triangle, DirectX::XMVECTOR* inter = nullptr, DirectX::XMVECTOR* reject = nullptr);

	/// <summary>
	/// レイと法線付き三角形の当たり判定
	/// </summary>
	/// <param name="lay">レイ</param>
	/// <param name="triangle">三角形</param>
	/// <param name="inter">距離（出力用）</param>
	/// <param name="inter">交点（出力用）</param>
	/// <returns>交差しているか否か</returns>
	static bool CheckRay2Triangle(const Ray& lay, const Triangle& triangle, float* distance = nullptr, DirectX::XMVECTOR* inter = nullptr);

	/// <summary>
	/// レイと球の当たり判定
	/// </summary>
	/// <param name="lay">レイ</param>
	/// <param name="sphere">球</param>
	/// <param name="sphere">距離（出力用）</param>
	/// <param name="inter">交点（出力用）</param>
	/// <returns>交差しているか否か</returns>
	static bool CheckRay2Sphere(const Ray& lay, const Sphere& sphere, float* distance = nullptr, DirectX::XMVECTOR* inter = nullptr);


	bool BoxCollision_Down(XMFLOAT3 object1, XMFLOAT3 radius1, XMFLOAT3 object2, XMFLOAT3 radius2);

	bool BoxCollision_Up(XMFLOAT3 object1, XMFLOAT3 radius1, XMFLOAT3 object2, XMFLOAT3 radius2);

	bool BoxCollision_Left(XMFLOAT3 object1, XMFLOAT3 radius1, XMFLOAT3 object2, XMFLOAT3 radius2);

	bool BoxCollision_Right(XMFLOAT3 object1, XMFLOAT3 radius1, XMFLOAT3 object2, XMFLOAT3 radius2);
};

