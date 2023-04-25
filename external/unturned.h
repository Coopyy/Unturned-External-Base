#ifndef UNTURNED_H
#define UNTURNED_H

#include "mono.h"

#define thisptr reinterpret_cast<uintptr_t>(this)

#define addfield(return_type, klass, name, offset) Field<return_type>* klass::name() { static auto field = new Field<return_type>(thisptr, offset); return field; }
#define addref(return_type, klass, name, offset) return_type klass::name() { return (return_type)read<uintptr_t>(thisptr + offset); }
#define addstaticref(return_type, klass, name, offset) return_type klass::name() { return (return_type)read<uintptr_t>(instance() + offset); }
#define addstaticfield(return_type, klass, name, offset) Field<return_type>* klass::name() { static auto field = new Field<return_type>(instance(), offset); return field; }
#define addgoref(klass) Unity::GameObject* klass::gameObject() { return (Unity::GameObject*)read<uintptr_t>(read<uintptr_t>(thisptr + 0x10) + 0x30);  }

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