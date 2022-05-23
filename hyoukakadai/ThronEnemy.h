#pragma once
#include "Enemy.h"
#include"mEffekseer.h"
#include"Object3d.h"
#include"Model.h"
#include"TyutorialSprite.h"
#include"nTexture.h"
class ThronEnemy :
    public Enemy
{
    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        ThronEnemy();

        /// <summary>
        /// �f�X�g���N�^
        /// </summary> 
        ~ThronEnemy();

    private:
        float frame;
        nTexture* searchTexture;
        int searchCount = 0;
        bool searchFlag;
        //�I�u�W�F�N�g�̃C���X�^���X
        Object3d* ThronObject = nullptr;
        //���f���̃C���X�^���X
        Model* ThronModel = nullptr;
        //
        mEffekseer* effect_dead;
    private:
       
    public:
        void ColMap1(int map[130][20], std::unique_ptr<Object3d>  tst[130][20], float mapx[130][20], float mapy[130][20], const int X, const int Y)override;

        void EnemySearchPlayer(Player* player)override;
        void SearchAction(XMMATRIX matview, XMMATRIX matprojection, XMFLOAT3 position)override;
        /// <summary>
        /// ������
        /// </summary>
        void Initialize()override;

        /// <summary>
        /// �X�V����
        /// </summary>
        void Update(XMFLOAT3 position)override;

        /// <summary>
        /// �`�揈��
        /// </summary>
        void Draw(DirectXCommon* dxcomn)override;

        /// <summary>
        /// �������
        /// </summary>
        void Finalize()override;
        void Follow(Player* player);
        void Motion(Player* player)override;
        void Attack(Player* player)override;
        float angleXs, angleZs, angleRs;
        float centerSpeed = 0.1f;
        const int AttackDamage = 2;
        bool followf;
        float movespeed = 0.2f;
        float grav = 0.03f;
        float time = 0;
        int Attackcount = 0;
        XMFLOAT3 Old_Pos;
        bool movexrand;
        float movement = 0;
        int jumpcount = 0;
        bool jumpflag = false;
    public:
        /// <summary>
        /// �A�N�Z�b�T
        /// </summary>
        /// <returns></returns>
        void ColMap(int map[20][200], std::unique_ptr<Object3d>  tst[20][200], float mapx[20][200], float mapy[20][200], const int X, const int Y);
        void enemyappearance(TyutorialSprite* sprite);
 
};

