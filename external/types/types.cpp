#include "types.h"

namespace SDG
{
	addstaticref(Player*, Player, player, Offsets::_player);
	addref(Equipment*, Player, equipment, Offsets::_equipment);
	addref(SteamChannel*, Player, channel, Offsets::channel);

	addref(SteamPlayer*, SteamChannel, owner, Offsets::owner); //equates to SteamPlayer* SteamChannel::owner() ...

	addfield(bool, SteamPlayer, admin, Offsets::_isAdmin);

	addstaticfield(bool, Provider, isConnected, Offsets::_isConnected);

	addref(Asset*, Equipment, asset, Offsets::_asset);

	addfield(float, ItemGunAsset, recoilMin_x, Offsets::recoilMin_x);
	addfield(float, ItemGunAsset, recoilMax_x, Offsets::recoilMax_x);
	addfield(float, ItemGunAsset, recoilMin_y, Offsets::recoilMin_y);
	addfield(float, ItemGunAsset, recoilMax_y, Offsets::recoilMax_y);
	addfield(float, ItemGunAsset, baseSpreadAngleRadians, Offsets::baseSpreadAngleRadians);
}