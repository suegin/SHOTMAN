﻿#include "DxLib.h"
#include <vector>
#include "PlatinumLoader.h"
#include <string>
#include <cassert>

void PlatinumLoader::Load(const TCHAR* filePath)
{
	//FMFヘッダー(Platinumのドキュメントに書いてある)
	struct Header {
		int8_t id[4];			//識別子(FMF_)			1*4バイト
		uint32_t size;			//データサイズ　		4バイト
		uint32_t mapWidth;		//マップの幅			4バイト
		uint32_t mapHeight;		//マップの高さ　		4バイト
		uint8_t chiphWidth;		//チップ(セル一個)の幅					1バイト
		uint8_t chpHeight;		//チップ(セル一個)の高さ				1バイト
		uint8_t layerCount;		//レイヤーの数							1バイト
		uint8_t bitCount;		//１セル当たりのビット数(÷8でバイト数)	1バイト
	};//20バイト

	Header header;
	int handle =  FileRead_open(filePath);
	FileRead_read(&header,sizeof(header), handle);

	std::string strId;
	strId.resize(4);
	std::copy_n(header.id, 4, strId.begin());

	if (strId != "FMF_") {
		assert(0);
	}

	mapWidth_ = header.mapWidth;
	mapHeight_ = header.mapHeight;
	int layerCount = header.layerCount;
	//レイヤー1個当たりのサイズを計算する
	//マップの幅＊マップの高さ*(チップ1個当たりのバイト数)
	int layerDataSize = header.mapWidth * header.mapHeight * (header.bitCount / 8);

	mapData_.resize(layerCount);
	for (auto& layer : mapData_) {
		layer.resize(layerDataSize);
		FileRead_read(layer.data(), layerDataSize, handle);
	}

	for (auto& map : mapData_)
	{
		for (auto& data : map)
		{
			if (data != 0)
			{
				printfDx("あ");
			}
		}
	}

	FileRead_close(handle);
}

const MapData_t& PlatinumLoader::GetMapData() const
{
	return mapData_;
}

const int PlatinumLoader::GetChipSpriteNo(LayerType layerType, int chipX, int chipY) const
{
	assert(chipX < mapWidth_);
	assert(chipY < mapHeight_);
	auto index = chipX + chipY * mapWidth_;
	return mapData_[(int)layerType][index];
}

void PlatinumLoader::GetMapSize(int& width, int& height)
{
	width = mapWidth_;
	height = mapHeight_;
}
