#include <sourcemod>
#include <sdktools>
#include <sdkhooks>
#include <cstrike>
#include <smlib>
#include "mm/stocks"

#define MENU_PREFIX "[Sejtn's MoneyMod]"
#define CHAT_PREFIX "\x06[Sejtn's MM]\x01"

enum e_Player {
	Money
}

new g_Players[MAXPLAYERS + 1][e_Player];

//this enum is also used for weapons
enum e_Ability {
	String:desc[64],
	maxLevel,
	initialCost,
	powerPerLevel,
	String:prefix[5],  //for menus rendering, see mm/mainmenu.inc
	String:firstUnit[5],
	String:secondUnit[5]
}

enum e_Abilities {
	HPREGEN,
	RESPAWN,
	CRITICALHIT,
	LIFESTEAL,
	WEAKERFREEZE,
	LONGERBOOTS,
	LONGERINVINCIBILITY,
	LONGERSTEALTH,
	SILENTFOOTSTEPS
};

new g_AbilitiesInfo[e_Abilities][e_Ability];

int g_Abilities[MAXPLAYERS + 1][e_Abilities];

enum e_Weapons {
	SECONDFLASH
}

new g_WeaponsInfo[e_Weapons][e_Ability];

int g_Weapons[MAXPLAYERS + 1][e_Weapons];

#include "mm/abi_helpers"

#include "mm/abilities/hpregen"
#include "mm/abilities/respawn"
#include "mm/abilities/criticalhit"
#include "mm/abilities/lifesteal"
#include "mm/abilities/weakerfreeze"
#include "mm/abilities/longerboots"
#include "mm/abilities/longerinvincibility"
#include "mm/abilities/longerstealth"
#include "mm/abilities/silentfootsteps"

#include "mm/weapons/secondflash"

#include "mm/mainmenu"
#include "mm/weaponsmenu"


public Plugin myinfo =
{
	name = "Sejnt's MoneyMod",
	author = "Sejtn aka Sejnt",
	description = "MoneyMod to use with EasyBlock :)",
	version = "1.0",
	url = "http://kbkk.pl"
};

public void OnPluginStart()
{
	HPREGEN_init();
	RESPAWN_init();
	CRITICALHIT_init();
	LIFESTEAL_init();
	WEAKERFREEZE_init();
	LONGERBOOTS_init();
	LONGERINVINCIBILITY_init();
	LONGERSTEALTH_init();
	SILENTFOOTSTEPS_init();

	SECONDFLASH_init();

	RegConsoleCmd("sm_mm", Command_MainMenu);
	RegConsoleCmd("sm_test", Command_Test);

}

public Action Command_MainMenu(int client, int args) {
	ShowMainMenu(client);

	return Plugin_Handled;
}


public Action Command_Test(int client, int args) {
	g_Players[client][Money] += 1000000;
	PrintToChat(client, "\x01 1\x02 2\x03 3\x04 4\x05 5\x06 6\x07 7\x08 8");
	return Plugin_Handled;
}

public void OnClientPutInServer(client)
{
	g_Players[client][Money] += 1000000;
	SDKHook(client, SDKHook_OnTakeDamage, CRITICALHIT_OnTakeDamage);
	SDKHook(client, SDKHook_OnTakeDamage, LIFESTEAL_OnTakeDamage);
}

public void OnEntityCreated(ent, const char[] classname)
{
	//flashbang_projectile
}
