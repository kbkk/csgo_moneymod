public void CRITICALHIT_init() {
    //g_AbilitiesInfo[CRITICALHIT][name] = "Health Regeneration";
    Format(g_AbilitiesInfo[CRITICALHIT][desc], 63, "Critical Hit");
    g_AbilitiesInfo[CRITICALHIT][maxLevel] = 5;
    g_AbilitiesInfo[CRITICALHIT][initialCost] = 750;
    g_AbilitiesInfo[CRITICALHIT][powerPerLevel] = 1;
    //Format(g_AbilitiesInfo[HPREGEN][prefix], 4, "");
    //Format(g_AbilitiesInfo[HPREGEN][firstUnit], 4, "");
    Format(g_AbilitiesInfo[CRITICALHIT][secondUnit], 4, "%%");

    //SDKHook(client, SDKHook_OnTakeDamage, CRITICALHIT_OnTakeDamage);
}

public Action:CRITICALHIT_OnTakeDamage(victim, &attacker, &inflictor, &Float:damage, &damagetype)
{
    //decl String:sWeapon[32];
    //GetEdictClassname(inflictor, sWeapon, sizeof(sWeapon));
    if(!Client_IsIngame(attacker) || !g_Abilities[attacker][CRITICALHIT])
        return Plugin_Continue;

    PrintToChat(victim, "victim: %i, attacker: %i, inflictor: %i, damage: %.1f",
        victim, attacker, inflictor, damage);

    int chance = g_Abilities[attacker][CRITICALHIT] * g_AbilitiesInfo[CRITICALHIT][powerPerLevel];
    int rand = GetRandomInt(1, 100);

    if(rand > chance)
    {
        damage *= 2.0;
        return Plugin_Changed;
    }

    return Plugin_Continue;
}
