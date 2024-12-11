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
	// Platinumデータ読み込み
	m_loader.Load("data/stage1.fmf");

	// マップ画像読み込み
	m_graphHandle = LoadGraph("data/map.png");
	// マップデータ読み込み
	for (int wIndex = 0; wIndex < kMapWidth; wIndex++)
	{
		for (int hIndex = 0; hIndex < kMapHeight; hIndex++)
		{
			MapChip& mapChip = m_mapChips[wIndex][hIndex];
		    mapChip.m_w = kMapChipSize;
			mapChip.h = kMapChipSize;

			// Platinumからのデータを入れる
			//mapChip.chipNo = ;
			mapChip.chipNo = map.loader.GetChipSpriteNo(LayerType::BackGround, wIndex, hIndex);

			// ポジションの基準を左上に
			mapChip.pos = VGet(wIndex * mapChip.w, hIndex * mapChip.h, 0);

			// 画像内での描画開始座標（左上）
			// MapGraphSize=512 MapChipSize=32 512*512の画像
			// 512 / 32 = 16なので、１行16個×16列の画像が並ぶ
			// 左上から順番に1ずつ番号をつけていく
			// 0   1  2  .... 15
			// 16 17 18  .... 31
			// .................
			// 240 ..........255
			// と番号が付くので、その番号×MapChipSize(32)が画像内の座標
			int chipSideNum = MapGraphSize / MapChipSize;  // 一片のマップチップ個数
			int inGraphXIdx = (mapChip.chipNo % chipSideNum); // 画像内の横インデックス
			int inGraphYIdx = (mapChip.chipNo / chipSideNum); // 画像内の縦インデックス
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
