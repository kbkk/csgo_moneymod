public void LIFESTEAL_init() {
    Format(g_AbilitiesInfo[LIFESTEAL][desc], 63, "Life Steal");
    Format(g_AbilitiesInfo[LIFESTEAL][columnname], 63, "lifesteal");
    g_AbilitiesInfo[LIFESTEAL][maxLevel] = 5;
    g_AbilitiesInfo[LIFESTEAL][initialCost] = 1000;
    g_AbilitiesInfo[LIFESTEAL][powerPerLevel] = 20;
    Format(g_AbilitiesInfo[LIFESTEAL][prefix], 4, "+");
    //Format(g_AbilitiesInfo[LIFESTEAL][firstUnit], 4, "");
    Format(g_AbilitiesInfo[LIFESTEAL][secondUnit], 4, "%%");

    //SDKHook(client, SDKHook_OnTakeDamage, LIFESTEAL_OnTakeDamage);
}

public Action:LIFESTEAL_OnTakeDamage(victim, &attacker, &inflictor, &Float:damage, &damagetype)
{
    if(!Client_IsIngame(attacker)
    || !g_Abilities[attacker][LIFESTEAL]
    || victim == attacker)
        return Plugin_Continue;

    int maxhp = 100;
    float add = damage * (GetClientAbiPower(attacker, LIFESTEAL) / 100.0);
    int hp = GetClientHealth(attacker);

    SetEntityHealth(attacker, Math_Min(maxhp, hp + RoundFloat(add)));

    return Plugin_Continue;
}
