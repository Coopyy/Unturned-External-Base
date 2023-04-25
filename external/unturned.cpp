#include "unturned.h"

namespace Classes
{
	mono_class_t* Provider;
	mono_class_t* Player;
	mono_class_t* SteamChannel;
	mono_class_t* SteamPlayer;

	mono_class_t* PlayerEquipment;
	mono_class_t* ItemAsset;
	mono_class_t* ItemGunAsset;


	void init()
	{
		Provider = mono::find_class("Assembly-CSharp", "SDG.Unturned.Provider");

		Player = mono::find_class("Assembly-CSharp", "SDG.Unturned.Player");
		SteamChannel = mono::find_class("Assembly-CSharp", "SDG.Unturned.SteamChannel");
		SteamPlayer = mono::find_class("Assembly-CSharp", "SDG.Unturned.SteamPlayer");

		PlayerEquipment = mono::find_class("Assembly-CSharp", "SDG.Unturned.PlayerEquipment");
		ItemAsset = mono::find_class("Assembly-CSharp", "SDG.Unturned.ItemAsset");
		ItemGunAsset = mono::find_class("Assembly-CSharp", "SDG.Unturned.ItemGunAsset");
	}
}

namespace Offsets
{
	uintptr_t _player;

	uintptr_t _isConnected;
	uintptr_t isLoadingUGC;

	uintptr_t channel;
	uintptr_t owner;
	uintptr_t _isAdmin;

	uintptr_t _equipment;
	uintptr_t _asset;
	uintptr_t _joined;

	uintptr_t recoilMin_x;
	uintptr_t recoilMax_x;
	uintptr_t recoilMin_y;
	uintptr_t recoilMax_y;

	uintptr_t baseSpreadAngleRadians;

	void init()
	{
		_player = Classes::Player->find_field("_player")->offset();
		channel = Classes::Player->find_field("_channel")->offset();
		_equipment = Classes::Player->find_field("_equipment")->offset();

		_isConnected = Classes::Provider->find_field("_isConnected")->offset();
		isLoadingUGC = Classes::Provider->find_field("isLoadingUGC")->offset();

		_isAdmin = Classes::SteamPlayer->find_field("_isAdmin")->offset();
		_joined = Classes::SteamPlayer->find_field("_joined")->offset();

		owner = Classes::SteamChannel->find_field("owner")->offset();

		_asset = Classes::PlayerEquipment->find_field("_asset")->offset();;

		recoilMin_x = Classes::ItemGunAsset->find_field("recoilMin_x")->offset();
		recoilMax_x = Classes::ItemGunAsset->find_field("recoilMax_x")->offset();
		recoilMin_y = Classes::ItemGunAsset->find_field("recoilMin_y")->offset();
		recoilMax_y = Classes::ItemGunAsset->find_field("recoilMax_y")->offset();

		baseSpreadAngleRadians = Classes::ItemGunAsset->find_field("<baseSpreadAngleRadians>k__BackingField")->offset();
	}
}