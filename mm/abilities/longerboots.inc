public void LONGERBOOTS_init() {
    //g_AbilitiesInfo[LONGERBOOTS][name] = "Health Regeneration";
    Format(g_AbilitiesInfo[LONGERBOOTS][desc], 63, "Longer Boots");
    Format(g_AbilitiesInfo[LONGERBOOTS][columnname], 63, "longerboots");
    g_AbilitiesInfo[LONGERBOOTS][maxLevel] = 5;
    g_AbilitiesInfo[LONGERBOOTS][initialCost] = 3000;
    g_AbilitiesInfo[LONGERBOOTS][powerPerLevel] = 1;
    Format(g_AbilitiesInfo[LONGERBOOTS][prefix], 4, "+");
    //Format(g_AbilitiesInfo[LONGERBOOTS][firstUnit], 4, "");
    Format(g_AbilitiesInfo[LONGERBOOTS][secondUnit], 4, "s");

}
