Handle HPREGEN_timers[MAXPLAYERS + 1];

public void HPREGEN_init() {
    Format(g_AbilitiesInfo[HPREGEN][desc], 63, "Health Regeneration");
    g_AbilitiesInfo[HPREGEN][maxLevel] = 10;
    g_AbilitiesInfo[HPREGEN][initialCost] = 50;
    g_AbilitiesInfo[HPREGEN][powerPerLevel] = 1;
    //Format(g_AbilitiesInfo[HPREGEN][prefix], 4, "");
    Format(g_AbilitiesInfo[HPREGEN][firstUnit], 4, "hp");
    Format(g_AbilitiesInfo[HPREGEN][secondUnit], 4, "s");

    HookEvent("player_spawn", HPREGEN_EventPlayerSpawned, EventHookMode_Post);
}

public Action HPREGEN_EventPlayerSpawned(Event event, const char[] name, bool dontBroadcast)
{
    int client = event.GetInt("userid");

    ClearTimer(HPREGEN_timers[client]);
    HPREGEN_timers[client] = CreateTimer(10.0, HPREGEN_regen, client, TIMER_REPEAT);
}

public Action HPREGEN_regen(Handle timer, any userid)
{
    int client = GetClientOfUserId(userid);

    if(!IsClientInGame(client) || !IsPlayerAlive(client))
        return Plugin_Stop;

    int maxhp = 100, hp = GetClientHealth(client);
    int add = g_Abilities[client][HPREGEN] * g_AbilitiesInfo[HPREGEN][powerPerLevel];

    SetEntityHealth(client, Math_Min(maxhp, hp + add));

    return Plugin_Continue;
}
