#include "game.h"

namespace SDG
{
	STATIC_FIELD_DEF(Player*, Player, player, Offsets::_player);
	FIELD_DEF(Equipment*, Player, equipment, Offsets::_equipment);
	FIELD_DEF(SteamChannel*, Player, channel, Offsets::channel);
	GAMEOBJECT_DEF(Player);

	FIELD_DEF(SteamPlayer*, SteamChannel, owner, Offsets::owner);

	FIELD_DEF(Player*, SteamPlayer, player, Offsets::_splayer); //equates to Player* SteamPlayer::player() ...
	FIELD_DEF(bool, SteamPlayer, admin, Offsets::_isAdmin);

	STATIC_FIELD_DEF(bool, Provider, isConnected, Offsets::_isConnected);
	STATIC_FIELD_DEF(Unity::Array<SteamPlayer*>*, Provider, clients, Offsets::_clients);

	FIELD_DEF(Asset*, Equipment, asset, Offsets::_asset);

	FIELD_DEF(float, ItemGunAsset, recoilMin_x, Offsets::recoilMin_x);
	FIELD_DEF(float, ItemGunAsset, recoilMax_x, Offsets::recoilMax_x);
	FIELD_DEF(float, ItemGunAsset, recoilMin_y, Offsets::recoilMin_y);
	FIELD_DEF(float, ItemGunAsset, recoilMax_y, Offsets::recoilMax_y);
	FIELD_DEF(float, ItemGunAsset, baseSpreadAngleRadians, Offsets::baseSpreadAngleRadians);
}