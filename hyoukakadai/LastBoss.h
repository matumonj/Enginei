
#pragma once
#pragma once
#include"Object3d.h"
#include"Model.h"
#include"DebugCamera.h"
#include "Enemy.h"
#include"OBBCollision.h"
#include"CollisionPrimitive.h"
#include"f_Object3d.h"
#include"FbxLoader.h"
#include"Sprite.h"
#include"nTexture.h"
class LastBoss :
    public Enemy
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    LastBoss();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~LastBoss();

private:
    Model* BossModel = nullptr;

    Object3d* BossObject = nullptr;

    Sprite* ZAttention[2];

    Model* BossArmModel ;

    Object3d* BossArmObject[2];
    //オブジェクトのインスタンス
    Object3d* ShotObj[3] = { nullptr };
    //モデルのインスタンス
    Model* ShotModel = nullptr;

    XMFLOAT3 Shot_Pos[3];
    bool shotf[3];
    float rt[3];
private:
    bool ChangeAttack;
    float r = 1;
    float g = 1;
    float b = 1;
    int BefHP;
    //パラメータ
   
    bool returnCamera;
    float returnCameraTime = 0;
    float Xspeed[3];
    float Yspeed[3];
    float BulAngle[3];
    int attackcount;
    int attackcount2;
private:
    bool BarrelFolflag;
    bool BarrelRec;
    float BarrelRotFollow = 0;
    bool BarrelReverse;
    float BarrelsclTime;
private:

    XMFLOAT3 Boss_Pos = {60,-18,0};
    XMFLOAT3 Boss_Rot;
    XMFLOAT3 Boss_Scl = { 9,9,9 };
    static const int max = 3;

    float bossmovespeed = 0.1f;
    float bossgrav = 0.03f;
    float bosstime = 0;
    int Attackcount = 0;

    const int MaxHP = 30;//体力の初期値

    bool bossjumpflag2 = false;
private:
    // bool woodatkflag;
    XMFLOAT3 Old_Pos;
    int OldHP;
    //static XMFLOAT3 position;
    float oldx, oldy;
    int time = 0;
    int time2 = 0;
    float rottime = 0;

public:
    static LastBoss* GetInstance();

    float GetMoveSpeed() { return bossmovespeed; }

    float GetGrav() { return bossgrav; }

    float GetTtime() { return bosstime; }

    XMFLOAT3 GetOldPosition() { return Old_Pos; }

    XMFLOAT3 GetRotation() { return Boss_Rot; }

    XMFLOAT3 GetScale() { return Boss_Scl; }

public:
    void  appearance(float& camerapos, float position);

    void SetMoveSpeed(float s) { bossmovespeed = s; }

    void SetGrav(float g) { bossgrav = g; }

    void SetTtime(float t) { bosstime = t; }
    void ColMap1(int map[130][20], std::unique_ptr<Object3d>  tst[130][20], float mapx[130][20], float mapy[130][20], const int X, const int Y)override;

    void ZAttack(Player*player);
public:
    void Initialize()override;

    void Update(XMFLOAT3 position)override;

    void Draw(DirectXCommon* dxcomn)override;

    void Finalize()override;
    void SearchAction(XMMATRIX matview, XMMATRIX matprojection, XMFLOAT3 position)override;
public:
    //埋め込み回避用
    void MoveBlockJump();
    //プレイヤー検知
    void EnemySearchPlayer(Player* player)override;
    //いらんかも
    void Attack(Player* player)override;
    //マットの当たり判定
    void ColMap(int map[20][200], std::unique_ptr<Object3d>  tst[20][200], float mapx[20][200], float mapy[20][200], const int X, const int Y);
    void enemyappearance(TyutorialSprite* sprite)override {};
    //ボスのアクション
    void Motion(Player* player)override;
    //追跡
    void Follow(XMFLOAT3 position);
    //
    void SummonEnemy(XMFLOAT3 position);

    void NormalAttacks(Player* player);

    //void SkewersAttack();

    void GetDamage();
    void UpDownMove(XMFLOAT3 position);
    void DeathMotion();
    
    XMFLOAT3 Gettexpos() { return texpos[0]; }
    bool GetAtc() { return atcf; }
private:
    static XMFLOAT3 texpos[2];
    static bool atcf;
private:
    int StayCount;
    bool damageRec = false;
    // static int attacktime;
    bool phase;
    float cameratime = 0;
    const int NormalDmage = 1;
    float oshake, oshakex, oshakey;
    float shake, shakex, shakey;
    int shaketime = 100;
    bool syurikenack;
    int syurikentimer;
    XMFLOAT2 DamageArea;
    XMFLOAT2 DamageAreaStart;
    float rotfollow;
    float Sec_rotfollow;
private:
    // static XMFLOAT3 startPos;
    float movement;
    bool Wrap = false;
    enum BossAction {
        KeepPos,
        None,
        MoveRight,
        MoveLeft,
        Stay,
        NormalAttack,
        Skewers,
        SetStartPos,
        ArmAttacks,
        StartBattle,
        altattackk,
        Zattackp,
        syurikenattack
    };
    int gametimer=1;
    enum Phase {
        StartFloor,
        SecondFloor,
        FinalFloor,
    };
    Phase Bossphase = StartFloor;
    BossAction bossAction = StartBattle;
    static bool stayflag;
    int deathcount;

    Object3d* syuriken[2];
    Model* syurikenm;
    XMFLOAT3 syurikenpos[2] = { {25,-10,0},{45,-10,0} };
    XMFLOAT3 syurikenrot[2] = { {0,0,0 },{0,0,0}
};
    XMFLOAT3 syurikenscl[2] = { {0,0,0},{0,0,0} };
    float sclplus[2];
    bool rotack[2];
    OBB pobb;
    OBB syuriken0;// = nullptr;
    OBB syuriken1;// = nullptr;
    OBB syuriken2;// = nullptr;
    OBB syuriken3;// = nullptr;
    OBBCollision* ps0 = nullptr;
    OBBCollision* ps1 = nullptr;
    OBBCollision* ps2 = nullptr;
    OBBCollision* ps3= nullptr;
    nTexture* damagearea[2];
    bool zattack;
    XMFLOAT3 oldplayerpos;
    XMFLOAT3 texscl;
    float konbouscl;
    float zalpha;
    int zatackEndTimer;
    int zatackStartTimer;
    bool rearm;
    bool beamf;
    bool beamf2=false;
    static Ray laserRay;//マップブロックとの当たり判定にも使うからstatic
    Sphere playersphere;
    static bool beamatck;
    static bool staybeam;
    int dtime;
public:
   // void GetDamage();
    bool GetSt() { return stayflag; }
    bool GetStay() { return beamatck; }
    void colsyuri(Player* player);
    bool GetAltStay() { return stayflag; }
    void RotationDamageblock();
   // void ZAttack();
   void ZAttackTex(XMMATRIX matview, XMMATRIX matprojection, Player*player);
   void Drawtex(DirectXCommon* dxcomn);
   void beamAtack(Player* player);
};



