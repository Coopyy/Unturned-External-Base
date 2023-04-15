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

		inline void init()
		{
			provider = mono::find_class("Assembly-CSharp", "SDG.Unturned.Provider");

			player = mono::find_class("Assembly-CSharp", "SDG.Unturned.Player");
			channel = mono::find_class("Assembly-CSharp", "SDG.Unturned.SteamChannel");
			steamplayer = mono::find_class("Assembly-CSharp", "SDG.Unturned.SteamPlayer");
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

		inline void init()
		{
			player = classes::player->find_field("_player")->offset();
			is_connected = classes::provider->find_field("_isConnected")->offset();
			is_loading = classes::provider->find_field("isLoadingUGC")->offset();
			channel = classes::player->find_field("_channel")->offset();
			owner = classes::channel->find_field("owner")->offset();
			admin = classes::steamplayer->find_field("_isAdmin")->offset();
		}
	}

	inline uintptr_t get_static_provider()
	{
		static auto inst = classes::provider->get_vtable(mono::get_root_domain())->get_static_field_data();
		return inst;
	}

	inline uintptr_t get_static_player()
	{
		static auto inst = classes::player->get_vtable(mono::get_root_domain())->get_static_field_data();
		return inst;
	}

	inline uintptr_t get_local_steamplayer()
	{
		auto splr = get_static_player();
		auto plr = read<uintptr_t>(splr + offsets::player);
		auto chnl = read<uintptr_t>(plr + offsets::channel);
		auto owner = read<uintptr_t>(chnl + offsets::owner);

		return owner;
	}
}
