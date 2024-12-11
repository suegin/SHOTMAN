#include "Map.h"
#include "DxLib.h"
#include "PlatinumLoader.h"
#include "MapChip.h"

Map::Map()
{
}

Map::~Map()
{
}

void Map::Init()
{
	// Platinum�f�[�^�ǂݍ���
	m_loader.Load("data/stage1.fmf");

	// �}�b�v�摜�ǂݍ���
	m_graphHandle = LoadGraph("data/map.png");
	// �}�b�v�f�[�^�ǂݍ���
	for (int wIndex = 0; wIndex < kMapWidth; wIndex++)
	{
		for (int hIndex = 0; hIndex < kMapHeight; hIndex++)
		{
			MapChip& mapChip = m_mapChips[wIndex][hIndex];
		    mapChip.m_w = kMapChipSize;
			mapChip.h = kMapChipSize;

			// Platinum����̃f�[�^������
			//mapChip.chipNo = ;
			mapChip.chipNo = map.loader.GetChipSpriteNo(LayerType::BackGround, wIndex, hIndex);

			// �|�W�V�����̊�������
			mapChip.pos = VGet(wIndex * mapChip.w, hIndex * mapChip.h, 0);

			// �摜���ł̕`��J�n���W�i����j
			// MapGraphSize=512 MapChipSize=32 512*512�̉摜
			// 512 / 32 = 16�Ȃ̂ŁA�P�s16�~16��̉摜������
			// ���ォ�珇�Ԃ�1���ԍ������Ă���
			// 0   1  2  .... 15
			// 16 17 18  .... 31
			// .................
			// 240 ..........255
			// �Ɣԍ����t���̂ŁA���̔ԍ��~MapChipSize(32)���摜���̍��W
			int chipSideNum = MapGraphSize / MapChipSize;  // ��Ђ̃}�b�v�`�b�v��
			int inGraphXIdx = (mapChip.chipNo % chipSideNum); // �摜���̉��C���f�b�N�X
			int inGraphYIdx = (mapChip.chipNo / chipSideNum); // �摜���̏c�C���f�b�N�X
			mapChip.posInGraphX = inGraphXIdx * MapChipSize;
			mapChip.posInGraphY = inGraphYIdx * MapChipSize;
		}
	}
}

void Map::Update()
{
}

void Map::Draw()
{
}
