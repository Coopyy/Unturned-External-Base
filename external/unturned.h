#pragma once
#include "mono.h"

namespace unturned
{
	namespace classes
	{
		static mono_class_t* provider;
		static mono_class_t* player;
		static mono_class_t* channel;
		static mono_class_t* steamplayer;

		static mono_class_t* equipment;
		static mono_class_t* asset;
		static mono_class_t* gun_asset;

		inline void init()
		{
			provider = mono::find_class("Assembly-CSharp", "SDG.Unturned.Provider");

			player = mono::find_class("Assembly-CSharp", "SDG.Unturned.Player");
			channel = mono::find_class("Assembly-CSharp", "SDG.Unturned.SteamChannel");
			steamplayer = mono::find_class("Assembly-CSharp", "SDG.Unturned.SteamPlayer");

			equipment = mono::find_class("Assembly-CSharp", "SDG.Unturned.PlayerEquipment");
			asset = mono::find_class("Assembly-CSharp", "SDG.Unturned.ItemAsset");
			gun_asset = mono::find_class("Assembly-CSharp", "SDG.Unturned.ItemGunAsset");
		}
	}

	namespace offsets
	{
		static uintptr_t is_connected;
		static uintptr_t is_loading;

		static uintptr_t player;
		static uintptr_t channel;
		static uintptr_t owner;
		static uintptr_t admin;

		static uintptr_t equipment;
		static uintptr_t asset;

		static uintptr_t rec_min_x;
		static uintptr_t rec_max_x;
		static uintptr_t rec_min_y;
		static uintptr_t rec_max_y;


		inline void init()
		{
			player = classes::player->find_field("_player")->offset();
			is_connected = classes::provider->find_field("_isConnected")->offset();
			is_loading = classes::provider->find_field("isLoadingUGC")->offset();
			channel = classes::player->find_field("_channel")->offset();
			owner = classes::channel->find_field("owner")->offset();
			admin = classes::steamplayer->find_field("_isAdmin")->offset();
			equipment = classes::player->find_field("_equipment")->offset();
			asset = classes::equipment->find_field("_asset")->offset();

			rec_min_x = classes::gun_asset->find_field("recoilMin_x")->offset();
			rec_max_x = classes::gun_asset->find_field("recoilMax_x")->offset();
			rec_min_y = classes::gun_asset->find_field("recoilMin_y")->offset();
			rec_max_y = classes::gun_asset->find_field("recoilMax_y")->offset();
		}
	}

	inline uintptr_t get_static_provider() // Provider
	{
		static auto inst = classes::provider->get_vtable(mono::get_root_domain())->get_static_field_data();
		return inst;
	}

	inline uintptr_t get_static_player() // Player
	{
		static auto inst = classes::player->get_vtable(mono::get_root_domain())->get_static_field_data();
		return inst;
	}

	inline uintptr_t get_local_steamplayer() // (SteamPlayer) Player.player.channel.owner
	{
		auto splr = get_static_player(); // Player
		auto plr = read<uintptr_t>(splr + offsets::player); // Player.player
		auto chnl = read<uintptr_t>(plr + offsets::channel); // Player.player.channel
		auto owner = read<uintptr_t>(chnl + offsets::owner); // Player.player.channel.owner

		return owner;
	}

	inline uintptr_t get_held_gun_asset()
	{
		auto plr = read<uintptr_t>(get_static_player() + offsets::player); // Player.player
		auto eq = read<uintptr_t>(plr + offsets::equipment); // Player.player.equipment
		auto asset = read<uintptr_t>(eq + offsets::asset); // Player.player.equipment.asset
		return asset;
	}
}
