
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
    class SeaBoss :
        public Enemy
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        SeaBoss();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~SeaBoss();

    private:
        f_Model* BossModel = nullptr;
        
        f_Object3d* BossObject = nullptr;

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
        float BarrelRotFollow = 0;
        bool BarrelReverse;
        float BarrelsclTime;
    private:

        XMFLOAT3 Boss_Pos;
        XMFLOAT3 Boss_Rot;
        XMFLOAT3 Boss_Scl = { 9,9,9 };
        static const int max = 3;
        
        float bossmovespeed = 0.1f;
        float bossgrav = 0.03f;
        float bosstime = 0;
        int Attackcount = 0;

        const int MaxHP = 20;//体力の初期値

        bool bossjumpflag2 = false;
        bool aperf;
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
        static SeaBoss* GetInstance();

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

    public:
        void Initialize()override;

        void Update(XMFLOAT3 position)override;

        void Draw(DirectXCommon* dxcomn)override;

        void Finalize()override;
        void SearchAction(XMMATRIX matview, XMMATRIX matprojection, XMFLOAT3 position)override;
    public:
        void EatEnemy(std::unique_ptr<Enemy>enemy[]);
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
    private:
        
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
            StartBattle
        };

        enum Phase {
            StartFloor,
            SecondFloor,
            FinalFloor,
        };
        Phase Bossphase = StartFloor;
        BossAction bossAction = StartBattle;
        static bool stayflag;
        int deathcount;
        int RotMove=1;
        bool deathf;
    public:
        bool Getdeathf() { return deathf; }
        bool GetAltStay() { return stayflag; }
        XMFLOAT3 Getrotation() { return Rotation; }
    };


