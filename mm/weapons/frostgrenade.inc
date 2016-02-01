Handle FROSTGRENADE_timerHandle = INVALID_HANDLE;

public void FROSTGRENADE_init() {
	//g_WeaponsInfo[FROSTGRENADE][name] = "Health Regeneration";
	Format(g_WeaponsInfo[FROSTGRENADE][desc], 63, "Frost Grenade");
	Format(g_WeaponsInfo[FROSTGRENADE][columnname], 63, "frostgrenade");
	g_WeaponsInfo[FROSTGRENADE][maxLevel] = 5;
	g_WeaponsInfo[FROSTGRENADE][initialCost] = 600;
	g_WeaponsInfo[FROSTGRENADE][powerPerLevel] = 10;
	//Format(g_WeaponsInfo[FROSTGRENADE][prefix], 4, "");
	//Format(g_WeaponsInfo[FROSTGRENADE][firstUnit], 4, "");
	Format(g_WeaponsInfo[FROSTGRENADE][secondUnit], 4, "%%");

	HookEvent("round_poststart", FROSTGRENADE_round_poststart, EventHookMode_Post);
}

public Action FROSTGRENADE_round_poststart(Event event, const char[] name, bool dontBroadcast)
{
	ClearTimer(FROSTGRENADE_timerHandle);
	FROSTGRENADE_timerHandle = CreateTimer(WEAPON_TIME, FROSTGRENADE_timerCallback);
}

public Action FROSTGRENADE_timerCallback(Handle timer)
{
	int rand, chance;

	for(new i = 1; i <= MaxClients; i++)
	{
		if(!IsClientInGame(i) || !IsPlayerAlive(i) || GetClientTeam(i) != CS_TEAM_T)
			continue;

		rand = GetRandomInt(1, 100);
		chance = GetClientWepPower(i, FROSTGRENADE);

		if(chance >= rand)
		{
			GivePlayerItem(i, "weapon_smokegrenade");
			PrintToChat(i, "%s\x03 You've got a\x04 frost grenade\x03!", CHAT_PREFIX);
		}
	}

	FROSTGRENADE_timerHandle = INVALID_HANDLE;
	return Plugin_Stop;
}
