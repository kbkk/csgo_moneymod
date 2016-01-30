public void RESPAWN_init() {
    //g_AbilitiesInfo[RESPAWN][name] = "Health Regeneration";
    Format(g_AbilitiesInfo[RESPAWN][desc], 63, "Respawn");
    Format(g_AbilitiesInfo[RESPAWN][columnname], 63, "respawn");
    g_AbilitiesInfo[RESPAWN][maxLevel] = 10;
    g_AbilitiesInfo[RESPAWN][initialCost] = 75;
    g_AbilitiesInfo[RESPAWN][powerPerLevel] = 2;
    //Format(g_AbilitiesInfo[RESPAWN][prefix], 4, "");
    //Format(g_AbilitiesInfo[RESPAWN][firstUnit], 4, "");
    Format(g_AbilitiesInfo[RESPAWN][secondUnit], 4, "%%");

    HookEvent("player_death", RESPAWN_EventPlayerDeath, EventHookMode_Post);
}

public Action RESPAWN_EventPlayerDeath(Event event, const char[] name, bool dontBroadcast)
{
    int client = event.GetInt("userid");
    CreateTimer(1.0, RESPAWN_RespawnPlayer, client);
}

public Action RESPAWN_RespawnPlayer(Handle timer, any userid)
{
    int client = GetClientOfUserId(userid);

    if(!IsClientInGame(client) || IsPlayerAlive(client))
        return Plugin_Stop;

    /*if(GameRules_GetRoundState() == RoundState_RoundRunning)
    {
        char name[65];
        GetClientName(client, name, sizeof(name));

        CS_RespawnPlayer(client);
        PrintToChatAll("%s Player\x07 %s\x03 has been respawned!", CHAT_PREFIX, name);
    }*/
    int rand = GetRandomInt(1, 100);
    int chance = GetClientAbiPower(client, RESPAWN);

    PrintToServer("%i", chance);

    if(chance >= rand)
    {
        char name[65];
        GetClientName(client, name, sizeof(name));

        CS_RespawnPlayer(client);
        PrintToChatAll("%s Player\x07 %s\x03 has been respawned!", CHAT_PREFIX, name);
    }

    return Plugin_Stop;
}
