#include "Map.h"
#include "DxLib.h"
#include <memory>

const int MapData[kMapHeight][kMapWidth] =
{
	1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,
	1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
	1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
	1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
	1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,

	1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
	1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
	1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
	1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
	1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,

	1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
	1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
	1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
	1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
	1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,

	1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
	1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
	1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
	1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
	1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,

	1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
	1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,
	1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,
};

void Map::Init()
{
	//�}�b�v�f�[�^�ǂݍ���
	for (int wIndex = 0; wIndex < kMapWidth; ++wIndex)
	{
		for (int hIndex = 0; hIndex < kMapHeight; ++hIndex)
		{
			MapChip& mapChip = m_mapChips[wIndex][hIndex];
			mapChip.SetW(kMapChipSize);
			mapChip.SetH(kMapChipSize);
			mapChip.SetChipKind(MapData[hIndex][wIndex]);

			//�|�W�V�����̊��^�񒆂�
			Vec2 mapChipPos = { 0.0f,0.0f };
			mapChip.SetPos(mapChipPos.VGet(wIndex * mapChip.GetW() + mapChip.GetW() * 0.5f, hIndex * mapChip.GetH() + mapChip.GetW() * 0.5f));
		}
	}
}

void Map::Draw()
{
	for (int wIndex = 0; wIndex < kMapWidth; ++wIndex)
	{
		for (int hIndex = 0; hIndex < kMapHeight; ++hIndex)
		{
			const MapChip& mapChip = m_mapChips[wIndex][hIndex];
			if (mapChip.GetChipKind() == 1)
			{
				auto leftTop = static_cast<int>(mapChip.GetPos().X - mapChip.GetW() * 0.5f);
				auto leftBottom = static_cast<int>(mapChip.GetPos().Y - mapChip.GetH() * 0.5f);
				auto rightTop = static_cast<int>(mapChip.GetPos().X + mapChip.GetW() * 0.5f);
				auto rightBottom = static_cast<int>(mapChip.GetPos().Y + mapChip.GetH() * 0.5f);
				
				DrawBox(leftTop, leftBottom, rightTop, rightBottom, 0x000000, true);
			}
		}
	}
}

bool Map::IsCol(Rect rect, Rect& chipRect)
{
	for (int wIndex = 0; wIndex < kMapWidth; ++wIndex)
	{
		for (int hIndex = 0; hIndex < kMapHeight; ++hIndex)
		{
			//�ǈȊO�Ƃ͓�����Ȃ�
			if (MapData[hIndex][wIndex] == 0) continue;

			int chipLeft = kMapChipSize * wIndex;
			int chipRight = chipLeft + kMapChipSize;
			int chipTop = kMapChipSize * hIndex;
			int chipBottom = chipTop + kMapChipSize;

			//��΂ɓ�����Ȃ��p�^�[�����͂���
			if (chipLeft > rect.right) continue;
			if (chipTop > rect.bottom) continue;
			if (chipRight < rect.left) continue;
			if (chipBottom < rect.top) continue;

			//�Ԃ������}�b�v�`�b�v�̋�`��ݒ肷��
			chipRect.left = chipLeft;
			chipRect.right = chipRight;
			chipRect.top = chipTop;
			chipRect.bottom = chipBottom;

			//�����ꂩ�̃`�b�v�Ɠ������Ă�����I��
			return true;
		}
	}
	//�S�Ẵ`�b�v���`�F�b�N���Ĉ���������Ă��Ȃ���Γ������Ă��Ȃ�
	return false;
}
