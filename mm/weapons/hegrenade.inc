Handle HEGRENADE_timerHandle = INVALID_HANDLE;

public void HEGRENADE_init() {
	//g_WeaponsInfo[HEGRENADE][name] = "Health Regeneration";
	Format(g_WeaponsInfo[HEGRENADE][desc], 63, "HE Grenade");
	Format(g_WeaponsInfo[HEGRENADE][columnname], 63, "hegrenade");
	g_WeaponsInfo[HEGRENADE][maxLevel] = 5;
	g_WeaponsInfo[HEGRENADE][initialCost] = 800;
	g_WeaponsInfo[HEGRENADE][powerPerLevel] = 10;
	//Format(g_WeaponsInfo[HEGRENADE][prefix], 4, "");
	//Format(g_WeaponsInfo[HEGRENADE][firstUnit], 4, "");
	Format(g_WeaponsInfo[HEGRENADE][secondUnit], 4, "%%");

	HookEvent("round_poststart", HEGRENADE_round_poststart, EventHookMode_Post);
}

public Action HEGRENADE_round_poststart(Event event, const char[] name, bool dontBroadcast)
{
	ClearTimer(HEGRENADE_timerHandle);
	HEGRENADE_timerHandle = CreateTimer(5.0, HEGRENADE_timerCallback);
}

public Action HEGRENADE_timerCallback(Handle timer)
{
	int rand, chance;

	for(new i = 1; i <= MaxClients; i++)
	{
		if(!IsClientInGame(i) || !IsPlayerAlive(i))
			continue;

		rand = GetRandomInt(1, 100);
		chance = GetClientWepPower(i, HEGRENADE);

		if(chance >= rand)
		{
			GivePlayerItem(i, "weapon_hegrenade");
			PrintToChat(i, "%s\x03 You've got a\x04 HE grenade\x03!", CHAT_PREFIX);
		}
	}

	HEGRENADE_timerHandle = INVALID_HANDLE;
	return Plugin_Stop;
}
