#ifndef GAME_H
#define GAME_H

#include "../unturned.h"
#include "unity.h"

namespace SDG
{
	class SteamPlayer;
	class SteamChannel;
	class Player;
	class Provider;
	class Equipment;
	class Asset;
	class ItemGunAsset;

	class SteamPlayer
	{
	public:
		FIELD_DEC(Player*, player);
		FIELD_DEC(bool, admin);
	};

	class SteamChannel
	{
	public:
		FIELD_DEC(SteamPlayer*, owner);
	};

	class Player
	{
		INSTANCE_DEF(Classes::Player);
	public:
		FIELD_DEC(SteamChannel*, channel);
		FIELD_DEC(Equipment*, equipment);
		STATIC_FIELD_DEC(Player*, player);
		Unity::GameObject* gameObject();
	};

	class Provider
	{
		INSTANCE_DEF(Classes::Provider);
	public:
		STATIC_FIELD_DEC(bool, isConnected);
		STATIC_FIELD_DEC(Unity::Array<SteamPlayer*>*, clients);
	};

	class Equipment
	{
	public:
		FIELD_DEC(Asset*, asset);
	};

	class Asset
	{
	public:
	};

	class ItemGunAsset
	{
	public:
		FIELD_DEC(float, recoilMin_x);
		FIELD_DEC(float, recoilMax_x);
		FIELD_DEC(float, recoilMin_y);
		FIELD_DEC(float, recoilMax_y);
		FIELD_DEC(float, baseSpreadAngleRadians);
	};
}

#endif