public void CRITICALHIT_init() {
    //g_AbilitiesInfo[CRITICALHIT][name] = "Health Regeneration";
    Format(g_AbilitiesInfo[CRITICALHIT][desc], 63, "Critical Hit");
    g_AbilitiesInfo[CRITICALHIT][maxLevel] = 5;
    g_AbilitiesInfo[CRITICALHIT][initialCost] = 750;
    g_AbilitiesInfo[CRITICALHIT][powerPerLevel] = 1;
    //Format(g_AbilitiesInfo[HPREGEN][prefix], 4, "");
    //Format(g_AbilitiesInfo[HPREGEN][firstUnit], 4, "");
    Format(g_AbilitiesInfo[HPREGEN][secondUnit], 4, "%%");
}
