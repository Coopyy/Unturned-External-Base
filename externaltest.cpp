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

	Log("Local SteamPlayer -> 0x%p\n", lp);

	if (connected && !loading && lp)
	{
		while (true)
		{
			write<int>(1, lp + unturned::offsets::admin);
			
			auto gun = unturned::get_held_gun_asset();
			if (gun)
			{
				write<float>(0, gun + unturned::offsets::rec_min_x);
				write<float>(0, gun + unturned::offsets::rec_max_x);
				write<float>(0, gun + unturned::offsets::rec_min_y);
				write<float>(0, gun + unturned::offsets::rec_max_y);
			}

			static bool hasLogged = false;
			if (!hasLogged)
			{
				Log("Set admin!");
				Log("Use keys Shift + F1 & F7 for freecam & esp");
				Log("Guns that are equipped should now have no recoil");
				hasLogged = true;
			}

			Sleep(1000);
		}
	}
	else
		Log("It seems like you're not in a server yet, run again when you are");

	system("pause");
}

