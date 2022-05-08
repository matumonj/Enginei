#pragma once
#include "Enemy.h"
#pragma once
#include"mEffekseer.h"
#include"Object3d.h"
#include"Model.h"
#include"TyutorialSprite.h"
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
        //�I�u�W�F�N�g�̃C���X�^���X
        Object3d* ThronObject = nullptr;
        //���f���̃C���X�^���X
        Model* ThronModel = nullptr;
        //
        mEffekseer* effect_dead;
    private:
       
    public:
        void EnemySearchPlayer(Player* player)override;

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
        void Draw()override;

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
    public:
        /// <summary>
        /// �A�N�Z�b�T
        /// </summary>
        /// <returns></returns>
        void ColMap(int map[20][200], std::unique_ptr<Object3d>  tst[20][200], float mapx[20][200], float mapy[15][200], const int X, const int Y);
        void enemyappearance(TyutorialSprite* sprite);
 
};

