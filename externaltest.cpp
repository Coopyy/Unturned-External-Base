#include "external/types/game.h"
using namespace std;

int main()
{
	Memory::init();
	Classes::init(); // classes before offsets
	Offsets::init();

	if (!SDG::Provider::isConnected())
	{
		Log("It seems like you're not in a server yet, run again when you are");
		system("pause");
		return 0;
	}


	// get local player
	auto localPlayer = SDG::Player::player();
	if (!localPlayer)
	{
		Log("Couldn't find local player");
		system("pause");
		return 0;
	}
	Log("Local Player: %p %s", localPlayer, localPlayer->gameObject()->transform()->localPosition().ToString().c_str());
	printf("\n");


	// iterate players
	auto clients = SDG::Provider::clients();
	auto count = clients->Count();
	Log("Connected players: %d", count);
	for (uint32_t i = 0; i < count; i++)
	{
		auto steamPlayer = clients->Get(i);
		auto player = steamPlayer->player();
		Log("Player %d: %p %s", i, player, player->gameObject()->transform()->localPosition().ToString().c_str());
	}
	printf("\n");


	// admin stuff
	auto owner = localPlayer->channel()->owner();
	owner->admin_set(1); //write
	if (owner->admin()) // read
		Log("Use keys Shift + F1 & F7 for freecam & esp");


	// gun mods
	auto gun = (SDG::ItemGunAsset*)(localPlayer->equipment()->asset());
	if (gun)
	{
		gun->recoilMax_x_set(0);
		gun->recoilMax_y_set(0);
		gun->recoilMin_x_set(0);
		gun->recoilMin_y_set(0);
		gun->baseSpreadAngleRadians_set(0);
		Log("Set current weapon recoil and spread to 0");
	} else
		Log("Couldn't find current weapon");

	system("pause");
}