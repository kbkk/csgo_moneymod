public GetClientWepPower(client, weapon)
{
    return  g_WeaponsInfo[weapon][powerPerLevel]
        * g_Weapons[client][weapon];
}
