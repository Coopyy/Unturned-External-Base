#include "external/types/game.h"
using namespace std;

int main()
{
	mem::init();

	Classes::init();
	Offsets::init();

	if (!SDG::Provider::isConnected()->Read())
	{
		Log("It seems like you're not in a server yet, run again when you are");
		system("pause");
		return 0;
	}

	auto localPlayer = SDG::Player::player();

	Log("Player.player.gameObject -> 0x%p", localPlayer->gameObject());
	Log("Local Position: %s\n", localPlayer->gameObject()->transform()->position()->Read().ToString().c_str());

	auto adminField = localPlayer->channel()->owner()->admin();

	adminField->Write(1); //write

	if (adminField->Read()) // read
		Log("Use keys Shift + F1 & F7 for freecam & esp");

	auto gun = (SDG::ItemGunAsset*)(localPlayer->equipment()->asset());
	if (gun)
	{
		gun->recoilMax_x()->Write(0);
		gun->recoilMax_y()->Write(0);
		gun->recoilMin_x()->Write(0);
		gun->recoilMin_y()->Write(0);
		gun->baseSpreadAngleRadians()->Write(0);
		Log("Set current weapon recoil and spread to 0");
	}

	system("pause");
}