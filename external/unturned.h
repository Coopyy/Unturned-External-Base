#ifndef UNTURNED_H
#define UNTURNED_H

#include "mono.h"

namespace Classes
{
	extern mono_class_t* Provider;
	extern mono_class_t* Player;
	extern mono_class_t* SteamChannel;
	extern mono_class_t* SteamPlayer;

	extern mono_class_t* PlayerEquipment;
	extern mono_class_t* ItemAsset;
	extern mono_class_t* ItemGunAsset;


	void init();
}

namespace Offsets
{
	extern uintptr_t _player;

	extern uintptr_t _isConnected;
	extern uintptr_t isLoadingUGC;

	extern uintptr_t channel;
	extern uintptr_t owner;
	extern uintptr_t _isAdmin;

	extern uintptr_t _equipment;
	extern uintptr_t _asset;
	extern uintptr_t _joined;

	extern uintptr_t recoilMin_x;
	extern uintptr_t recoilMax_x;
	extern uintptr_t recoilMin_y;
	extern uintptr_t recoilMax_y;

	extern uintptr_t baseSpreadAngleRadians;

	void init();
}
#endif