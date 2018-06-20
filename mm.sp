/*
	HnS MoneyMod by Sejtn

	Notes:
	- giving grenades works really simple and if the player carries
	  too many of them they might just fall on the ground instead
	  useful cvars: ammo_grenade_limit_flashbang and similar

	- database: sqlite, SM creates a db file if there isn't one.
	  on startup you can check for the version and modify the db structure
*/

#include <sourcemod>
#include <sdktools>
#include <sdkhooks>
#include <cstrike>
#include <smlib>
#include "mm.inc"
#include "mm/stocks"

#define KILL_MONEY 50
#define TT_SURVIVE_MONEY 100
#define VIP_MULTIPLIER 1.2

//will give weapons after this time
#define WEAPON_TIME 12.0

#define MENU_PREFIX "[Sejtn's MoneyMod]"
#define CHAT_PREFIX "\x06[Sejtn's MM]\x01"

Database g_Database;

enum e_Player {
	Money,
	bool:Vip
}

bool g_PlayerInitialized[MAXPLAYERS + 1];
new g_Players[MAXPLAYERS + 1][e_Player];

//this enum is also used for weapons
enum e_Ability {
	String:desc[64],
	String:columnname[64],
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
	LONGERINVINCIBILITY,
	LONGERSTEALTH,
	INSTANTFLASHBANG
};

new g_AbilitiesInfo[e_Abilities][e_Ability];

int g_Abilities[MAXPLAYERS + 1][e_Abilities];

enum e_Weapons {
	SECONDFLASH,
	FROSTGRENADE,
	HEGRENADE,
	FIVESEVEN,
	DEAGLE
}

new g_WeaponsInfo[e_Weapons][e_Ability];

int g_Weapons[MAXPLAYERS + 1][e_Weapons];

new m_iClip1, m_iClip2, m_iAmmo, m_iPrimaryAmmoType;

#include "mm/abi_helpers"
#include "mm/wep_helpers"

#include "mm/abilities/hpregen"
#include "mm/abilities/respawn"
#include "mm/abilities/criticalhit"
#include "mm/abilities/lifesteal"
#include "mm/abilities/weakerfreeze"
//#include "mm/abilities/longerboots"
#include "mm/abilities/longerinvincibility"
#include "mm/abilities/longerstealth"
//#include "mm/abilities/silentfootsteps"
#include "mm/abilities/instantflashbang"

#include "mm/weapons/secondflash"
#include "mm/weapons/frostgrenade"
#include "mm/weapons/hegrenade"
#include "mm/weapons/fiveseven"
#include "mm/weapons/deagle"

#include "mm/mainmenu"
#include "mm/weaponsmenu"

#include "mm/natives"


public Plugin myinfo =
{
	name = "kbck's MoneyMod",
	author = "kbck aka sejtn",
	description = "MoneyMod to use with EasyBlock :)",
	version = "1.0",
	url = "http://kbck.pl"
};

public void OnPluginStart()
{
	HPREGEN_init();
	RESPAWN_init();
	CRITICALHIT_init();
	LIFESTEAL_init();
	WEAKERFREEZE_init();
	//LONGERBOOTS_init();
	LONGERINVINCIBILITY_init();
	LONGERSTEALTH_init();
	//SILENTFOOTSTEPS_init();
	INSTANTFLASHBANG_init();

	SECONDFLASH_init();
	FROSTGRENADE_init();
	HEGRENADE_init();
	FIVESEVEN_init();
	DEAGLE_init();

	m_iClip1 = FindSendPropOffsEx("CBaseCombatWeapon", "m_iClip1");
	m_iClip2 = FindSendPropOffsEx("CBaseCombatWeapon", "m_iClip2");
	m_iAmmo = FindSendPropOffsEx("CBasePlayer", "m_iAmmo");
	m_iPrimaryAmmoType = FindSendPropOffsEx("CBaseCombatWeapon", "m_iPrimaryAmmoType");

	char error[512], table[2048];
	g_Database = SQL_Connect("kbkkmm", true, error, sizeof error);

	if(error[0] != EOS)
		PrintToServer("%s %s", CHAT_PREFIX, error);

	Format(table, sizeof(table), "CREATE TABLE IF NOT EXISTS players \
	(%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s)",
		"id INTEGER PRIMARY KEY ASC",
		"steam_id VARCHAR(50)",
		"money INTEGER",
		"hpregen SMALLINT",
		"respawn SMALLINT",
		"criticalhit SMALLINT",
		"lifesteal SMALLINT",
		"weakerfreeze SMALLINT",
		"longerboots SMALLINT",
		"longerinvincibility SMALLINT",
		"longerstealth SMALLINT",
		"silentfootsteps SMALLINT",

		"secondflashbang SMALLINT",
		"frostgrenade SMALLINT",
		"hegrenade SMALLINT",
		"fiveseven SMALLINT",
		"deagle SMALLINT"
		);

	SQL_FastQuery(g_Database, table, sizeof(table));

	//if the index already exists it will just fail with 'index already exists'
	Format(table, sizeof(table), "CREATE UNIQUE INDEX playerssteam_id ON players(steam_id); ");
	SQL_FastQuery(g_Database, table, sizeof(table));

	RegConsoleCmd("sm_mm", Command_MainMenu);
	RegConsoleCmd("sm_store", Command_MainMenu);
	RegConsoleCmd("sm_money", Command_MainMenu);
	RegConsoleCmd("sm_shop", Command_MainMenu);

	RegConsoleCmd("sm_test", Command_Test);

	HookEvent("player_death", Event_PlayerDeath);
	HookEvent("round_end", OnRoundEnd, EventHookMode_Pre);

	CreateTimer(0.1, Timer_RefreshScoreboardMoney, _, TIMER_REPEAT);

	SetRandomSeed(GetTime());
}

public Action Timer_RefreshScoreboardMoney(Handle timer)
{
	for(int client = 1; client <= MaxClients; client++)
	{
		if(IsClientInGame(client))
		{
			SetEntProp(client, Prop_Send, "m_iAccount", g_Players[client][Money]);
		}
	}
}

public void OnRoundEnd(Event hEvent, const char[] name, bool dontBroadcast)
{
	for (new client = 1; client <= MaxClients; ++client)
    {
		if(!IsClientInGame(client) || !IsPlayerAlive(client))
			continue;

		if(GetClientTeam(client) == CS_TEAM_T)
		{
			int money = AddPlayerMoney(client, TT_SURVIVE_MONEY);
			PrintToChat(client, "%s\x04 +$%i\x03 for surviving!", CHAT_PREFIX, money);
		}
	}
}

public APLRes AskPluginLoad2(Handle myself, bool late, char[] error, int err_max)
{
	CreateNative("mm_GetBootsTime", Native_GetBootsTime);
	CreateNative("mm_GetInvincibilityTime", Native_GetInvincibilityTime);
	CreateNative("mm_GetStealthTime", Native_GetStealthTime);
	CreateNative("mm_GetWeakerFreezePercent", Native_GetWeakerFreezePercent);
	CreateNative("mm_AddMoney", Native_AddMoney);

	return APLRes_Success;
}

public Action Event_PlayerDeath(Event event, const char[] name, bool dontBroadcast)
{
	int victim = GetClientOfUserId(event.GetInt("userid"));
	int attacker = GetClientOfUserId(event.GetInt("attacker"));

	if(victim == attacker || attacker == 0 || !IsClientInGame(attacker))
		return;

	int money = AddPlayerMoney(attacker, KILL_MONEY);
	PrintToChat(attacker, "%s\x04 +$%i\x03 for killing!", CHAT_PREFIX, money);
}

public Action Command_MainMenu(int client, int args) {
	ShowMainMenu(client);

	return Plugin_Handled;
}


public Action Command_Test(int client, int args) {
	//g_Players[client][Money] += 1000000;
	PrintToChat(client, "\x01 1\x02 2\x03 3\x04 4\x05 5\x06 6\x07 7\x08 8");
	//g_PlayerInitialized[client] = true;
	SaveData(client);
	return Plugin_Handled;
}

public void OnClientPostAdminCheck(client)
{
	g_Players[client][Vip] = view_as<bool>((GetUserFlagBits(client) & ADMFLAG_CUSTOM6));

	SDKHook(client, SDKHook_OnTakeDamage, CRITICALHIT_OnTakeDamage);
	SDKHook(client, SDKHook_OnTakeDamage, LIFESTEAL_OnTakeDamage);

	g_PlayerInitialized[client] = false;
	LoadData(client);
}

public void OnClientDisconnect(client)
{
	SaveData(client);
	g_PlayerInitialized[client] = false;
	g_Players[client][Money] = 0;
	g_Players[client][Vip] = false;

	for(int i = 0; i < view_as<int>(e_Abilities); i++)
		g_Abilities[client][i] = 0;

	for(int i = 0; i < view_as<int>(e_Weapons); i++)
		g_Weapons[client][i] = 0;
}

public void OnEntityCreated(ent, const char[] classname)
{
	//flashbang_projectile
}

public T_loadPlayerCallback(Handle owner, Handle hndl, const char[] error, any userid)
{
	int client = GetClientOfUserId(userid);

	if(client == 0)
		return;

	if(!SQL_FetchRow(hndl))
		return; //error

	int field = 3; //field indices are starting from 0

	for(int i = 0; i < view_as<int>(e_Abilities); i++)
	{
		SQL_FieldNameToNum(hndl, g_AbilitiesInfo[i][columnname], field);
		g_Abilities[client][i] = SQL_FetchInt(hndl, field);
		field++;
	}

	for(int i = 0; i < view_as<int>(e_Weapons); i++)
	{
		SQL_FieldNameToNum(hndl, g_WeaponsInfo[i][columnname], field);
		g_Weapons[client][i] = SQL_FetchInt(hndl, field);
		field++;
	}

	g_Players[client][Money] = SQL_FetchInt(hndl, 2);

	g_PlayerInitialized[client] = true;
}

public T_initPlayerCallback(Handle owner, Handle hndl, const char[] error, any userid)
{
	int client = GetClientOfUserId(userid);

	if(client == 0)
		return;

	char auth[64], query[256];
	GetClientAuthId(client, AuthId_SteamID64, auth, sizeof(auth));

	Format(query, sizeof(query), "SELECT * FROM players WHERE steam_id = '%s'", auth);
	SQL_TQuery(g_Database, T_loadPlayerCallback, query, userid);
}

public bool LoadData(client)
{
	int userid = GetClientUserId(client);

	char auth[64], query[256];
	GetClientAuthId(client, AuthId_SteamID64, auth, sizeof(auth));

	Format(query, sizeof(query), "INSERT OR IGNORE INTO players(steam_id) VALUES ('%s')", auth);
	SQL_TQuery(g_Database, T_initPlayerCallback, query, userid);

	return true;
}

public T_emptyCallback(Handle owner, Handle hndl, const char[] error, any userid)
{
	//PrintToServer(error);
}

public bool SaveData(client)
{
	if(!g_PlayerInitialized[client])
		return false;

	char auth[64], query[2048];
	GetClientAuthId(client, AuthId_SteamID64, auth, sizeof(auth));

	Format(query, sizeof(query), "UPDATE players SET");

	for(int i = 0; i < view_as<int>(e_Abilities); i++)
	{
		Format(query, sizeof(query), "%s %s = %i,",
			query, g_AbilitiesInfo[i][columnname], g_Abilities[client][i]);
	}

	for(int i = 0; i < view_as<int>(e_Weapons); i++)
	{
		Format(query, sizeof(query), "%s %s = %i,",
			query, g_WeaponsInfo[i][columnname], g_Weapons[client][i]);
	}

	Format(query, sizeof(query), "%s money = %i WHERE steam_id = '%s'",
		query, g_Players[client][Money], auth);

	SQL_TQuery(g_Database, T_emptyCallback, query);

	return true;
}

int AddPlayerMoney(int client, int money, float vipMultiplier = 1.2)
{
	int ccount = GetClientCount();
	//TODO tell the user why he didn't get any money
	if(ccount <= 3)
		return 0;

	if(ccount <= 7)
		money /= 2;

	if(g_Players[client][Vip])
		money = RoundFloat(money * vipMultiplier);


	g_Players[client][Money] += money;
	SaveData(client);
	return money;
}
