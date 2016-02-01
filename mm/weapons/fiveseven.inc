Handle FIVESEVEN_timerHandle = INVALID_HANDLE;

public void FIVESEVEN_init() {
	//g_WeaponsInfo[FIVESEVEN][name] = "Health Regeneration";
	Format(g_WeaponsInfo[FIVESEVEN][desc], 63, "FiveSeven");
	Format(g_WeaponsInfo[FIVESEVEN][columnname], 63, "fiveSeven");
	g_WeaponsInfo[FIVESEVEN][maxLevel] = 5;
	g_WeaponsInfo[FIVESEVEN][initialCost] = 1250;
	g_WeaponsInfo[FIVESEVEN][powerPerLevel] = 5;
	//Format(g_WeaponsInfo[FIVESEVEN][prefix], 4, "");
	//Format(g_WeaponsInfo[FIVESEVEN][firstUnit], 4, "");
	Format(g_WeaponsInfo[FIVESEVEN][secondUnit], 4, "%%");

	HookEvent("round_poststart", FIVESEVEN_round_poststart, EventHookMode_Post);
}

public Action FIVESEVEN_round_poststart(Event event, const char[] name, bool dontBroadcast)
{
	ClearTimer(FIVESEVEN_timerHandle);
	FIVESEVEN_timerHandle = CreateTimer(WEAPON_TIME, FIVESEVEN_timerCallback);
}

public Action FIVESEVEN_timerCallback(Handle timer)
{
	int rand, chance;

	for(new i = 1; i <= MaxClients; i++)
	{
		if(!IsClientInGame(i) || !IsPlayerAlive(i))
			continue;

		rand = GetRandomInt(1, 100);
		chance = GetClientWepPower(i, FIVESEVEN);

		if(chance >= rand)
		{
			int weapon = GetPlayerWeaponSlot(i, CS_SLOT_SECONDARY);

			if(weapon != -1)
				AcceptEntityInput(weapon, "Kill");

			weapon = GivePlayerItem(i, "weapon_fiveseven");

			CreateTimer(0.1, FIVESEVEN_setAmmo, weapon);

			PrintToChat(i, "%s\x03 You've got a\x04 fiveseven\x03!", CHAT_PREFIX);
		}
	}

	FIVESEVEN_timerHandle = INVALID_HANDLE;
	return Plugin_Stop;
}

public Action FIVESEVEN_setAmmo(Handle timer, any weapon)
{
	SetEntData(weapon, m_iClip1, 1);
	SetEntProp(weapon, Prop_Send, "m_iPrimaryReserveAmmoCount", 0);
}
