public void SECONDFLASH_init() {
    //g_WeaponsInfo[SECONDFLASH][name] = "Health Regeneration";
    Format(g_WeaponsInfo[SECONDFLASH][desc], 63, "Second Flashbang");
    g_WeaponsInfo[SECONDFLASH][maxLevel] = 5;
    g_WeaponsInfo[SECONDFLASH][initialCost] = 400;
    g_WeaponsInfo[SECONDFLASH][powerPerLevel] = 10;
    //Format(g_WeaponsInfo[SECONDFLASH][prefix], 4, "");
    //Format(g_WeaponsInfo[SECONDFLASH][firstUnit], 4, "");
    Format(g_WeaponsInfo[SECONDFLASH][secondUnit], 4, "%%");

    RegConsoleCmd("sm_flashbang", Command_Fb);
}

public Action Command_Fb(int client, int args) {
	GivePlayerItem(client, "weapon_flashbang");

	return Plugin_Handled;
}
