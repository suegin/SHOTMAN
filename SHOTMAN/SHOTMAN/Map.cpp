//#include "Map.h"
//#include "DxLib.h"
//
//
//Map::Map()
//{
//}
//
//Map::~Map()
//{
//}
//
//void Map::Init()
//{
//	// Platinum�f�[�^�ǂݍ���
//	m_loader.Load("data/stage1.fmf");
//
//	// �}�b�v�摜�ǂݍ���
//	m_graphHandle = LoadGraph("data/map.png");
//	// �}�b�v�f�[�^�ǂݍ���
//	for (int wIndex = 0; wIndex < kMapWidth; wIndex++)
//	{
//		for (int hIndex = 0; hIndex < kMapHeight; hIndex++)
//		{
//			MapChip mapChip = m_mapChips[wIndex][hIndex];
//			mapChip.SetMapChipW(kMapChipSize);
//			mapChip.SetMapChipH(kMapChipSize);
//
//			// Platinum����̃f�[�^������
//			//mapChip.chipNo = ;
//			mapChip.SetChipNo(m_loader.GetChipSpriteNo(LayerType::BackGround, wIndex, hIndex));
//
//			// �|�W�V�����̊�������
//			mapChip.SetPos(m_vec2.VGet(wIndex * mapChip.GetMapChipW(), hIndex * mapChip.GetMapChipH()));
//
//			// �摜���ł̕`��J�n���W�i����j
//			// MapGraphSize=512 MapChipSize=32 512*512�̉摜
//			// 512 / 32 = 16�Ȃ̂ŁA�P�s16�~16��̉摜������
//			// ���ォ�珇�Ԃ�1���ԍ������Ă���
//			// 0   1  2  .... 15
//			// 16 17 18  .... 31
//			// .................
//			// 240 ..........255
//			// �Ɣԍ����t���̂ŁA���̔ԍ��~MapChipSize(32)���摜���̍��W
//			int chipSideNum = MapGraphSize / kMapChipSize;  // ��Ђ̃}�b�v�`�b�v��
//			int inGraphXIdx = (mapChip.GetChipNo() % chipSideNum); // �摜���̉��C���f�b�N�X
//			int inGraphYIdx = (mapChip.GetChipNo() / chipSideNum); // �摜���̏c�C���f�b�N�X
//			mapChip.SetPosInGraphX(inGraphXIdx * kMapChipSize);
//			mapChip.SetPosInGraphY(inGraphYIdx * kMapChipSize);
//		}
//	}
//}
//
//void Map::Update()
//{
//}
//
//void Map::Draw()
//{
//}