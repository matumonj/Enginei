#pragma once
#include "Enemy.h"
#include"Object3d.h"
#include"Model.h"
#include"CollisionPrimitive.h"
class SecondBoss :
    public Enemy
{
    //
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        SecondBoss();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~SecondBoss();

    private:
        //オブジェクトのインスタンス
        Object3d* BossObject = nullptr;
        //モデルのインスタンス
        Model* BossModel = nullptr;

    private:
        //パラメータ
        XMFLOAT3 Boss_Pos;
        XMFLOAT3 Boss_Rot;
        XMFLOAT3 Boss_Scl = { 9,9,9 };
        float bossmovespeed = 0.1f;
        float bossgrav = 0.03f;
        float bosstime = 0;
        int Attackcount = 0;

        const int MaxHP = 20;//体力の初期値

        bool bossjumpflag = false;
        bool bossjumpflag2 = false;
    private:
        XMFLOAT3 Old_Pos;
        static XMFLOAT3 position;
        float oldx, oldy;
        int time = 0;
        int time2 = 0;

    public:
        static SecondBoss* GetInstance();

        bool GetJumpFlag() { return bossjumpflag; }

        float GetMoveSpeed() { return bossmovespeed; }

        float GetGrav() { return bossgrav; }

        float GetTtime() { return bosstime; }

        XMFLOAT3 GetOldPosition() { return Old_Pos; }

        XMFLOAT3 GetRotation() { return Boss_Rot; }

        XMFLOAT3 GetScale() { return Boss_Scl; }

    public:

        void SetJumpFlag(bool f) { bossjumpflag = f; }

        void SetMoveSpeed(float s) { bossmovespeed = s; }

        void SetGrav(float g) { bossgrav = g; }

        void SetTtime(float t) { bosstime = t; }

    public:
        void Initialize()override;

        void Update(XMFLOAT3 position)override;

        void Draw()override;

        void Finalize()override;

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
    private:
        const int NormalDmage = 1;

    private:
        XMFLOAT3 startPos;
        float movement;
        bool Wrap = false;
        enum BossAction {
            None,
            MoveRight,
            MoveLeft,
            Stay,
            NormalAttack,
            SetStartPos
        };

        BossAction bossAction = None;
        static bool stayflag;
    public:
        bool GetAltStay() { return stayflag; }

    };



