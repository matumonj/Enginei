#pragma once
#pragma once
#include"Object3d.h"
#include"Model.h"
#include"DebugCamera.h"
#include "Enemy.h"
#include"OBBCollision.h"
#include"CollisionPrimitive.h"
class ForestBoss :
    public Enemy
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ForestBoss();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~ForestBoss();

private:
    OBB pobb;
    OBB earmobb_right;// = nullptr;
    OBB earmobb_left;// = nullptr;
    OBBCollision* pobbcolright = nullptr;
    OBBCollision* pobbcolleft = nullptr;
    //オブジェクトのインスタンス
    Object3d* BossObject = nullptr;
    //モデルのインスタンス
    Model* BossModel = nullptr;
    Model* NuclearModel;
    Object3d* NuclearObj;
    static XMFLOAT3 Nuclear_Pos;
    float Rot_Nuclear;
    bool NuclearDeayh;
    int NuclearHP=10;
    XMFLOAT4 nuclearcolor;
    Object3d* BossArmObj[2] = { nullptr };
    Object3d* BarrelObj = nullptr;
    Model* BarrelModel;
    XMFLOAT3 Barrel_Rot;
    XMFLOAT3 Barrel_Scl;
    //モデルのインスタンス
    Model* BossArmModel = nullptr;
    XMFLOAT3 Arm_Pos[2];
    XMFLOAT3 Arm_Rot[2];
    XMFLOAT3 Arm_Scl[2];
    bool ArmAttackflag;
    //オブジェクトのインスタンス
    Object3d* SkewersObject[3] = { nullptr };
    //モデルのインスタンス
    Model* SkewersBossModel = nullptr;

    //オブジェクトのインスタンス
    Object3d* ShotObj[3] = { nullptr };
    //モデルのインスタンス
    Model* ShotModel = nullptr;

private:
    bool ChangeAttack;
    float r = 1;
    float g = 1;
    float b = 1;
    int BefHP;
    //パラメータ
    XMFLOAT3 Shot_Pos[3];
    bool shotf[3];
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
    float BarrelRotFollow=0;
    bool BarrelReverse;
    float BarrelsclTime;
private:

    XMFLOAT3 Boss_Pos;
    XMFLOAT3 Boss_Rot;
    XMFLOAT3 Boss_Scl = { 9,9,9 };
    static const int max = 3;
    static XMFLOAT3 Skewers_Scl[max];
    
    float bossmovespeed = 0.1f;
    float bossgrav = 0.03f;
    float bosstime = 0;
    int Attackcount = 0;

    const int MaxHP = 20;//体力の初期値

    static bool bossjumpflag;
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
    static float startcount;
public:
    static ForestBoss* GetInstance();

    bool GetJumpFlag() { return bossjumpflag; }

    float GetMoveSpeed() { return bossmovespeed; }

    float GetGrav() { return bossgrav; }

    float GetTtime() { return bosstime; }

    XMFLOAT3 GetOldPosition() { return Old_Pos; }

    XMFLOAT3 GetRotation() { return Boss_Rot; }

    XMFLOAT3 GetScale() { return Boss_Scl; }

public:
    void  appearance(float& camerapos,float position);

    void SetJumpFlag(bool f) { bossjumpflag = f; }

    void SetMoveSpeed(float s) { bossmovespeed = s; }

    void SetGrav(float g) { bossgrav = g; }

    void SetTtime(float t) { bosstime = t; }
    void ColMap1(int map[130][20], std::unique_ptr<Object3d>  tst[130][20], float mapx[130][20], float mapy[130][20], const int X, const int Y)override;

public:
    void Initialize()override;

    void Update(XMFLOAT3 position)override;

    void Draw(DirectXCommon* dxcomn)override;

    void Finalize()override;
    void SearchAction(XMMATRIX matview, XMMATRIX matprojection, XMFLOAT3 position)override;
public:
    //埋め込み回避用
    void MoveBlockJump();
    //いらん
    static void SkewersAttack(int map[130][20], std::unique_ptr<Object3d> tst[130][20]);
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
    void collisionArm(Player* player);
    void ArmAytack(Player* player);
    void ArmAttack_Left(Player* player);
    void GetDamage();
    void UpDownMove(XMFLOAT3 position);
    void DeathMotion();
private:
    int countUpDownMove;
    float lene;
    float ArmMaxlen;
    bool armreturn;
    XMFLOAT3 OldArm_Scl[2];
    float armattacktime;
    float armattacktime2;
    int AttackNum = 0;
    bool Sec_ArmAttackflag;
    bool Sec_armreturn;
    float Sec_armattacktime;
    float Sec_armattacktime2;
    int ArmAttackCount;
    static XMFLOAT3 wpos[max];
    static bool woodatkflag;
    static float woodatkCount;
    static float woodatkCount2;
    static float woodatkCount3;
    private:
    static int StayCount;
    bool damageRec = false;
    static int attacktime;
    bool phase;
    float cameratime = 0;
    const int NormalDmage = 1;
    float oshake, oshakex, oshakey;
    float shake, shakex, shakey;
    int shaketime = 100;
    XMFLOAT2 DamageArea;
    XMFLOAT2 DamageAreaStart;
    float rotfollow;
    float Sec_rotfollow;
private:
    static XMFLOAT3 startPos;
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
        StartBattle
    };
    bool hitcol[3];
    DirectX::XMVECTOR oldrot;
    DirectX::XMVECTOR positionB;
    float rt[3];
    enum Phase {
        StartFloor,
        SecondFloor,
        FinalFloor,
    };
    Phase Bossphase = StartFloor;
    BossAction bossAction = StartBattle;
    static bool stayflag;
    int deathcount;
public:
    bool GetAltStay() { return stayflag; }
    bool GetNucclear() { return NuclearDeayh; }
};

