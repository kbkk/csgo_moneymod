public void LONGERSTEALTH_init() {
    //g_AbilitiesInfo[LONGERSTEALTH][name] = "Health Regeneration";
    Format(g_AbilitiesInfo[LONGERSTEALTH][desc], 63, "Longer Stealth");
    Format(g_AbilitiesInfo[LONGERSTEALTH][columnname], 63, "longerstealth");
    g_AbilitiesInfo[LONGERSTEALTH][maxLevel] = 5;
    g_AbilitiesInfo[LONGERSTEALTH][initialCost] = 5000;
    g_AbilitiesInfo[LONGERSTEALTH][powerPerLevel] = 1;
    Format(g_AbilitiesInfo[LONGERSTEALTH][prefix], 4, "+");
    //Format(g_AbilitiesInfo[LONGERSTEALTH][firstUnit], 4, "");
    Format(g_AbilitiesInfo[LONGERSTEALTH][secondUnit], 4, "s");

}
