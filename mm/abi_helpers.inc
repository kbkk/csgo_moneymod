public GetClientAbiPower(client, ability)
{
    return  g_AbilitiesInfo[ability][powerPerLevel]
        * g_Abilities[client][ability];
}
