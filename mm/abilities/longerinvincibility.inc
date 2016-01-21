public void LONGERINVINCIBILITY_init() {
    //g_AbilitiesInfo[LONGERINVINCIBILITY][name] = "Health Regeneration";
    Format(g_AbilitiesInfo[LONGERINVINCIBILITY][desc], 63, "Longer Invincibility");
    Format(g_AbilitiesInfo[LONGERINVINCIBILITY][columnname], 63, "longerinvincibility");
    g_AbilitiesInfo[LONGERINVINCIBILITY][maxLevel] = 5;
    g_AbilitiesInfo[LONGERINVINCIBILITY][initialCost] = 4000;
    g_AbilitiesInfo[LONGERINVINCIBILITY][powerPerLevel] = 1;
    Format(g_AbilitiesInfo[LONGERINVINCIBILITY][prefix], 4, "+");
    //Format(g_AbilitiesInfo[LONGERINVINCIBILITY][firstUnit], 4, "");
    Format(g_AbilitiesInfo[LONGERINVINCIBILITY][secondUnit], 4, "s");

}
