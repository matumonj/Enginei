#pragma once
#pragma once
#include"Object3d.h"
#include"Model.h"
#include "Enemy.h"
#include"CollisionPrimitive.h"
class FirstBoss :
    public Enemy
{
    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        FirstBoss();

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        ~FirstBoss();

    private:
        //�I�u�W�F�N�g�̃C���X�^���X
        Object3d* BossObject = nullptr;
        //���f���̃C���X�^���X
        Model* BossModel = nullptr;

    private:
        //�p�����[�^
        XMFLOAT3 Boss_Pos;
        XMFLOAT3 Boss_Rot;
        XMFLOAT3 Boss_Scl = { 9,9,9 };
        float bossmovespeed = 0.1f;
        float bossgrav = 0.03f;
        float bosstime = 0;
        int Attackcount = 0;

        const int MaxHP = 20;//�̗͂̏����l

        bool bossjumpflag = false;
        bool bossjumpflag2 = false;
    private:
        XMFLOAT3 Old_Pos;
        static XMFLOAT3 position;
        float oldx, oldy;
        int time = 0;
        int time2 = 0;

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
        //���ߍ��݉��p
        void MoveBlockJump();
        //�����
        void ColMapb1(int map[15][200], std::unique_ptr<Object3d> tst[15][200], float mapx[15][200], float mapy[15][200], const int X, const int Y);
        //�v���C���[���m
        void EnemySearchPlayer(Player* player)override;
        //����񂩂�
        void Attack(Player* player)override;
        //�}�b�g�̓����蔻��
        void ColMap(int map[20][200], std::unique_ptr<Object3d>  tst[20][200], float mapx[20][200], float mapy[20][200], const int X, const int Y)override;
        //
        void enemyappearance(TyutorialSprite* sprite)override {};
        //�{�X�̃A�N�V����
        void Motion(Player* player)override;
        //�ǐ�
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

