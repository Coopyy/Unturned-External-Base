#ifndef UNTURNED_H
#define UNTURNED_H

#include "mono.h"

#define THISPTR reinterpret_cast<uintptr_t>(this)

// this is kinda retarded and unreadable, sorry

#define FIELD_DEF(return_type, klass, name, offset, is_static) \
    return_type klass::name() { \
        return read<return_type>(THISPTR + offset); \
    } \
	void klass::name##_set(return_type val) { \
		return write<return_type>(val, THISPTR + offset); \
	} 

#define FIELD_DEC(return_type, name) \
    return_type name(); \
	void name##_set(return_type val); 

#define STATIC_FIELD_DEF(return_type, klass, name, offset, is_static) \
    return_type klass::name() { \
        return read<return_type>(instance() + offset); \
    } \
	void klass::name##_set(return_type val) { \
		return write<return_type>(val, instance() + offset); \
	} 

#define STATIC_FIELD_DEC(return_type, name) \
    static return_type name(); \
	static void name##_set(return_type val); 

#define INSTANCE_DEF(class_name) \
    static inline uintptr_t instance() { \
        static uintptr_t inst = 0; \
		if (!inst) { \
			inst = class_name->get_vtable(mono::get_root_domain())->get_static_field_data(); \
		} \
        return inst; \
    }

#define GAMEOBJECT_DEF(klass) \
    Unity::GameObject* klass::gameObject() { \
        return (Unity::GameObject*)read<uintptr_t>( \
            read<uintptr_t>(THISPTR + 0x10) + 0x30); \
    }


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
	extern uintptr_t _clients;

	extern uintptr_t channel;
	extern uintptr_t owner;

	extern uintptr_t _isAdmin;
	extern uintptr_t _splayer;

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