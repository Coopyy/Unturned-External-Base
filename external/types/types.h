#ifndef TYPES_H
#define TYPES_H

#include "../unturned.h"

#define thisptr reinterpret_cast<uintptr_t>(this)

#define addfield(return_type, klass, name, offset) Field<return_type>* klass::name() { static auto field = new Field<return_type>(thisptr, offset); return field; }
#define addref(return_type, klass, name, offset) return_type klass::name() { return (return_type)read<uintptr_t>(thisptr + offset); }
#define addstaticref(return_type, klass, name, offset) return_type klass::name() { return (return_type)read<uintptr_t>(instance() + offset); }
#define addstaticfield(return_type, klass, name, offset) Field<return_type>* klass::name() { static auto field = new Field<return_type>(instance(), offset); return field; }

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
		Field<bool>* admin();
	};

	class SteamChannel
	{
	public:
		SteamPlayer* owner();
	};
	
	class Player
	{
		static uintptr_t instance()
		{
			static auto inst = Classes::Player->get_vtable(mono::get_root_domain())->get_static_field_data();
			return inst;
		}
	public:
		static Player* player(); // Player.player
		SteamChannel* channel();
		Equipment* equipment();
	};

	class Provider
	{
		static uintptr_t instance()
		{
			static auto inst = Classes::Provider->get_vtable(mono::get_root_domain())->get_static_field_data();
			return inst;
		}
	public:
		static Field<bool>* isConnected();
	};

	

	class Equipment
	{
	public:
		Asset* asset();
	};

	class Asset
	{
	public:
	};

	class ItemGunAsset
	{
	public:
		Field<float>* recoilMin_x();
		Field<float>* recoilMax_x();
		Field<float>* recoilMin_y();
		Field<float>* recoilMax_y();
		Field<float>* baseSpreadAngleRadians();
	};
}

#endif