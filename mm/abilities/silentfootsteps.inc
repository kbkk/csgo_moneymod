public void SILENTFOOTSTEPS_init() {
    //g_AbilitiesInfo[SILENTFOOTSTEPS][name] = "Health Regeneration";
    Format(g_AbilitiesInfo[SILENTFOOTSTEPS][desc], 63, "Silent Footsteps");
    g_AbilitiesInfo[SILENTFOOTSTEPS][maxLevel] = 1;
    g_AbilitiesInfo[SILENTFOOTSTEPS][initialCost] = 30000;
    g_AbilitiesInfo[SILENTFOOTSTEPS][powerPerLevel] = 1;
    Format(g_AbilitiesInfo[SILENTFOOTSTEPS][prefix], 4, "");
    //Format(g_AbilitiesInfo[SILENTFOOTSTEPS][firstUnit], 4, "");
    Format(g_AbilitiesInfo[SILENTFOOTSTEPS][secondUnit], 4, "");

}
