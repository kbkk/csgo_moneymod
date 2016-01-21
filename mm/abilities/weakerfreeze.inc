public void WEAKERFREEZE_init() {
    //g_AbilitiesInfo[WEAKERFREEZE][name] = "Health Regeneration";
    Format(g_AbilitiesInfo[WEAKERFREEZE][desc], 63, "Weaker Freeze");
    Format(g_AbilitiesInfo[WEAKERFREEZE][columnname], 63, "weakerfreeze");
    g_AbilitiesInfo[WEAKERFREEZE][maxLevel] = 5;
    g_AbilitiesInfo[WEAKERFREEZE][initialCost] = 2000;
    g_AbilitiesInfo[WEAKERFREEZE][powerPerLevel] = 10;
    Format(g_AbilitiesInfo[WEAKERFREEZE][prefix], 4, "-");
    //Format(g_AbilitiesInfo[WEAKERFREEZE][firstUnit], 4, "");
    Format(g_AbilitiesInfo[WEAKERFREEZE][secondUnit], 4, "%%");

}
