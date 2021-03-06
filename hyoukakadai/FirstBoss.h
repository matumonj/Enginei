#pragma once
#pragma once
#include"Object3d.h"
#include"Model.h"
#include"DebugCamera.h"
#include "Enemy.h"
#include"CollisionPrimitive.h"
class FirstBoss :
    public Enemy
{
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        FirstBoss();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~FirstBoss();

    private:
        //オブジェクトのインスタンス
        Object3d* BossObject = nullptr;
        //モデルのインスタンス
        Model* BossModel = nullptr;

    private:
        float r = 1;
        float g = 1;
        float b = 1;
        int BefHP;
        //パラメータ
        XMFLOAT3 Boss_Pos;
        XMFLOAT3 Boss_Rot;
        XMFLOAT3 Boss_Scl = { 9,9,9 };
        float bossmovespeed = 0.1f;
        float bossgrav = 0.03f;
        float bosstime = 0;
        int Attackcount = 0;

        const int MaxHP = 20;//体力の初期値

        static bool bossjumpflag;
        bool bossjumpflag2 = false;
    private:
        XMFLOAT3 Old_Pos;
        int OldHP;
        //static XMFLOAT3 position;
        float oldx, oldy;
        int time = 0;
        int time2 = 0;
        float rottime = 0;
      static float startcount;
      int dtime;
    public:
        static FirstBoss* GetInstance();

        bool GetJumpFlag() { return bossjumpflag; }

        float GetMoveSpeed() { return bossmovespeed; }

        float GetGrav() { return bossgrav; }

        float GetTtime() { return bosstime; }

        XMFLOAT3 GetOldPosition() { return Old_Pos; }

        XMFLOAT3 GetRotation() { return Boss_Rot; }

        XMFLOAT3 GetScale() { return Boss_Scl; }

    public:
        void  appearance(float &camerapos);

        void SetJumpFlag(bool f) { bossjumpflag = f; }

        void SetMoveSpeed(float s) { bossmovespeed = s; }

        void SetGrav(float g) { bossgrav = g; }

        void SetTtime(float t) { bosstime = t; }

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
        void ColMapb1(int map[15][200], std::unique_ptr<Object3d> tst[15][200], float mapx[15][200], float mapy[15][200], const int X, const int Y);
        //プレイヤー検知
        void EnemySearchPlayer(Player* player)override;
        //いらんかも
        void Attack(Player* player)override;
        //マットの当たり判定
        void ColMap(int map[20][200], std::unique_ptr<Object3d>  tst[20][200], float mapx[20][200], float mapy[20][200], const int X, const int Y)override;
        //
        void enemyappearance(TyutorialSprite* sprite)override {};
        //ボスのアクション
        void Motion(Player* player)override;
        //追跡
        void Follow(XMFLOAT3 position);
        //
        void SummonEnemy(XMFLOAT3 position);

       void RushAttack(Player* player);

       void RushAttackStay(Player* player);

       void RushAttackStayPrm(Player* player);

       void NormalAttacks(Player* player);

       void GetDamage();
       void ColMap1(int map[130][20], std::unique_ptr<Object3d>  tst[130][20], float mapx[130][20], float mapy[130][20], const int X, const int Y)override;

    private:
        static int StayCount;
        bool damageRec = false;
        static int attacktime ;
        bool phase;
        float cameratime = 0;
        const int NormalDmage = 1;
        float oshake, oshakex, oshakey;
        float shake, shakex, shakey;
        int shaketime = 100;
        XMFLOAT2 DamageArea;
        XMFLOAT2 DamageAreaStart;
    private:
        static XMFLOAT3 startPos;
        float movement;
        bool Wrap = false;
        enum BossAction {
            None,
            MoveRight,
            MoveLeft,
            Stay,
            NormalAttack,
            RushAttacks,
            SetStartPos,
            StartBattle
        };
        struct RushAttack{
            float count;
            float aftermovex;
            bool rushflag;
        }rushAttackPrm;
        
        BossAction bossAction =StartBattle;
        static bool stayflag;
        bool servDamage = true;
        bool stayflg;
        int redamageCount = 0;
    public:
        void GetDamageMove();
        bool GetAltStay() { return stayflag; }
};

