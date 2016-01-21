Handle SECONDFLASH_timerHandle = INVALID_HANDLE;

public void SECONDFLASH_init() {
	//g_WeaponsInfo[SECONDFLASH][name] = "Health Regeneration";
	Format(g_WeaponsInfo[SECONDFLASH][desc], 63, "Second Flashbang");
	Format(g_WeaponsInfo[SECONDFLASH][columnname], 63, "secondflashbang");
	g_WeaponsInfo[SECONDFLASH][maxLevel] = 5;
	g_WeaponsInfo[SECONDFLASH][initialCost] = 400;
	g_WeaponsInfo[SECONDFLASH][powerPerLevel] = 10;
	//Format(g_WeaponsInfo[SECONDFLASH][prefix], 4, "");
	//Format(g_WeaponsInfo[SECONDFLASH][firstUnit], 4, "");
	Format(g_WeaponsInfo[SECONDFLASH][secondUnit], 4, "%%");

	HookEvent("round_poststart", SECONDFLASH_round_poststart, EventHookMode_Post);
}

public Action SECONDFLASH_round_poststart(Event event, const char[] name, bool dontBroadcast)
{
	ClearTimer(SECONDFLASH_timerHandle);
	SECONDFLASH_timerHandle = CreateTimer(5.0, SECONDFLASH_timerCallback);
}

public Action SECONDFLASH_timerCallback(Handle timer)
{
	int rand, chance;

	for(new i = 1; i <= MaxClients; i++)
	{
		if(!IsClientInGame(i) || !IsPlayerAlive(i))
			continue;

		rand = GetRandomInt(1, 100);
		chance = GetClientWepPower(i, SECONDFLASH);

		if(chance >= rand)
		{
			GivePlayerItem(i, "weapon_flashbang");
			PrintToChat(i, "%s\x03 You've got a\x04 flashbang\x03!", CHAT_PREFIX);
		}
	}

	SECONDFLASH_timerHandle = INVALID_HANDLE;
	return Plugin_Stop;
}
