#include "external/unturned.h"
using namespace std;
int main()
{
	mem::init();

	unturned::classes::init();
	unturned::offsets::init();

	auto provider = unturned::get_static_provider();

	Log("Provider -> 0x%p", provider);

	bool connected = read<bool>(provider + unturned::offsets::is_connected);
	bool loading = read<bool>(provider + unturned::offsets::is_loading);

	auto lp = unturned::get_local_steamplayer();

	Log("Local SteamPlayer -> 0x%p", lp);

	if (connected && !loading && lp)
	{
		write<int>(1, lp + unturned::offsets::admin);
		Log("Set admin!");
		Log("Use keys Shift + F1 & F7 for freecam & esp");
	}
	else
		Log("It seems like you're not in a server yet, run again when you are");

	system("pause");
}

