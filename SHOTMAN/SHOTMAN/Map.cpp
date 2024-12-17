#include "Map.h"
#include "DxLib.h"
#include "game.h"


Map::Map()
{
}

Map::~Map()
{
}

void Map::Init()
{
	// Platinum�f�[�^�ǂݍ���
	m_loader.Load("image/map/SHOTMANmap.fmf");

	// �}�b�v�摜�ǂݍ���
	m_graphHandle = LoadGraph("image/map/Assets_City.png");
	// �}�b�v�f�[�^�ǂݍ���
	for (int wIndex = 0; wIndex < kMapWidth; wIndex++)
	{
		for (int hIndex = 0; hIndex < kMapHeight; hIndex++)
		{
			MapChip mapChip = m_mapChips[wIndex][hIndex];
			mapChip.SetMapChipW(kMapChipSize);
			mapChip.SetMapChipH(kMapChipSize);

			// Platinum����̃f�[�^������
			//mapChip.chipNo = ;
			mapChip.SetChipNo(m_loader.GetChipSpriteNo(LayerType::BackGround, wIndex, hIndex));

			// �|�W�V�����̊�������
			mapChip.SetPos(m_vec2.VGet(wIndex * mapChip.GetMapChipW(), hIndex * mapChip.GetMapChipH()));

			// �摜���ł̕`��J�n���W�i����j
			// MapGraphSize=512 MapChipSize=32 512*512�̉摜
			// 512 / 32 = 16�Ȃ̂ŁA�P�s16�~16��̉摜������
			// ���ォ�珇�Ԃ�1���ԍ������Ă���
			// 0   1  2  .... 15
			// 16 17 18  .... 31
			// .................
			// 240 ..........255
			// �Ɣԍ����t���̂ŁA���̔ԍ��~MapChipSize(32)���摜���̍��W
			int chipSideNum = MapGraphSize / kMapChipSize;  // ��Ђ̃}�b�v�`�b�v��
			int inGraphXIdxX = (mapChip.GetChipNo() % chipSideNum); // �摜���̉��C���f�b�N�X
			int inGraphYIdxY = (mapChip.GetChipNo() / chipSideNum); // �摜���̏c�C���f�b�N�X
			mapChip.SetPosInGraphX(inGraphXIdxX * kMapChipSize);
			mapChip.SetPosInGraphY(inGraphYIdxY * kMapChipSize);

			m_mapChips[wIndex][hIndex] = mapChip;
		}
	}
}

void Map::Update()
{
}

void Map::Draw()
{
	for (int wIndex = 0; wIndex < kMapWidth; wIndex++)
	{
		for (int hIndex = 0; hIndex < kMapHeight; hIndex++)
		{
			//1�͓����蔻��`�b�v��\���Ă���̂�1�̂Ƃ��낾���`��
			MapChip mapChip = m_mapChips[wIndex][hIndex];
			if (mapChip.GetChipNo() > 0)
			{
				auto leftTopX = static_cast<int>(mapChip.GetPos().X);
				auto leftTopY = static_cast<int>(mapChip.GetPos().Y) - kMapChipSize * kMapHeight + Game::kScreenHeight;
				DrawRectGraph(leftTopX, leftTopY,
					mapChip.GetPosInGraphX(), mapChip.GetPosInGraphY(),
					kMapChipSize, kMapChipSize,
					m_graphHandle, true);


			}
		}
	}
}
