Handle DEAGLE_timerHandle = INVALID_HANDLE;

public void DEAGLE_init() {
	//g_WeaponsInfo[DEAGLE][name] = "Health Regeneration";
	Format(g_WeaponsInfo[DEAGLE][desc], 63, "Deagle");
	Format(g_WeaponsInfo[DEAGLE][columnname], 63, "deagle");
	g_WeaponsInfo[DEAGLE][maxLevel] = 5;
	g_WeaponsInfo[DEAGLE][initialCost] = 1500;
	g_WeaponsInfo[DEAGLE][powerPerLevel] = 5;
	//Format(g_WeaponsInfo[DEAGLE][prefix], 4, "");
	//Format(g_WeaponsInfo[DEAGLE][firstUnit], 4, "");
	Format(g_WeaponsInfo[DEAGLE][secondUnit], 4, "%%");

	HookEvent("round_poststart", DEAGLE_round_poststart, EventHookMode_Post);
}

public Action DEAGLE_round_poststart(Event event, const char[] name, bool dontBroadcast)
{
	ClearTimer(DEAGLE_timerHandle);
	DEAGLE_timerHandle = CreateTimer(5.0, DEAGLE_timerCallback);
}

public Action DEAGLE_timerCallback(Handle timer)
{
	int rand, chance;

	for(new i = 1; i <= MaxClients; i++)
	{
		if(!IsClientInGame(i) || !IsPlayerAlive(i))
			continue;

		rand = GetRandomInt(1, 100);
		chance = GetClientWepPower(i, DEAGLE);

		if(chance >= rand)
		{
			int weapon = GetPlayerWeaponSlot(i, CS_SLOT_SECONDARY);

			if(weapon != -1)
				AcceptEntityInput(weapon, "Kill");

			weapon = GivePlayerItem(i, "weapon_deagle");

			CreateTimer(0.1, DEAGLE_setAmmo, weapon);

			PrintToChat(i, "%s\x03 You've got a\x04 deagle\x03!", CHAT_PREFIX);
		}
	}

	DEAGLE_timerHandle = INVALID_HANDLE;
	return Plugin_Stop;
}

public Action DEAGLE_setAmmo(Handle timer, any weapon)
{
	SetEntData(weapon, m_iClip1, 1);
	SetEntProp(weapon, Prop_Send, "m_iPrimaryReserveAmmoCount", 0);
}
