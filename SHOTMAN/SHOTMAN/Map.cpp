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
	// Platinumデータ読み込み
	m_loader.Load("image/map/SHOTMANmap.fmf");

	// マップ画像読み込み
	m_graphHandle = LoadGraph("image/map/Assets_City.png");
	// マップデータ読み込み
	for (int wIndex = 0; wIndex < kMapWidth; wIndex++)
	{
		for (int hIndex = 0; hIndex < kMapHeight; hIndex++)
		{
			MapChip mapChip = m_mapChips[wIndex][hIndex];
			mapChip.SetMapChipW(kMapChipSize);
			mapChip.SetMapChipH(kMapChipSize);

			// Platinumからのデータを入れる
			//mapChip.chipNo = ;
			mapChip.SetChipNo(m_loader.GetChipSpriteNo(LayerType::BackGround, wIndex, hIndex));

			// ポジションの基準を左上に
			mapChip.SetPos(m_vec2.VGet(wIndex * mapChip.GetMapChipW(), hIndex * mapChip.GetMapChipH()));

			// 画像内での描画開始座標（左上）
			// MapGraphSize=512 MapChipSize=32 512*512の画像
			// 512 / 32 = 16なので、１行16個×16列の画像が並ぶ
			// 左上から順番に1ずつ番号をつけていく
			// 0   1  2  .... 15
			// 16 17 18  .... 31
			// .................
			// 240 ..........255
			// と番号が付くので、その番号×MapChipSize(32)が画像内の座標
			int chipSideNum = MapGraphSize / kMapChipSize;  // 一片のマップチップ個数
			int inGraphXIdxX = (mapChip.GetChipNo() % chipSideNum); // 画像内の横インデックス
			int inGraphYIdxY = (mapChip.GetChipNo() / chipSideNum); // 画像内の縦インデックス
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
			//1は当たり判定チップを表しているので1のところだけ描画
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
