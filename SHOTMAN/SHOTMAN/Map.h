#pragma once

using namespace std;

class MapChip;

namespace
{
	constexpr int MapChipSize = 32;						// ��̃`�b�v�̃T�C�Y
	constexpr int MapWidth = 1280 / MapChipSize;  // �}�b�v�̉���
	constexpr int MapHeight = 720 / MapChipSize;		// �}�b�v�̏c��
}

class Map
{
public:
	Map();

private:
	MapChip* m_pMapChips[MapWidth][MapHeight];
};

