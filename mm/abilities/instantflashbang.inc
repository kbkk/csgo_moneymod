public void INSTANTFLASHBANG_init() {
    //g_AbilitiesInfo[INSTANTFLASHBANG][name] = "Health Regeneration";
    Format(g_AbilitiesInfo[INSTANTFLASHBANG][desc], 63, "Instant Flashbang");
    Format(g_AbilitiesInfo[INSTANTFLASHBANG][columnname], 63, "instantfb");
    g_AbilitiesInfo[INSTANTFLASHBANG][maxLevel] = 1;
    g_AbilitiesInfo[INSTANTFLASHBANG][initialCost] = 100000;
    g_AbilitiesInfo[INSTANTFLASHBANG][powerPerLevel] = 1;
    Format(g_AbilitiesInfo[INSTANTFLASHBANG][prefix], 4, "");
    //Format(g_AbilitiesInfo[INSTANTFLASHBANG][firstUnit], 4, "");
    Format(g_AbilitiesInfo[INSTANTFLASHBANG][secondUnit], 4, "");

}
