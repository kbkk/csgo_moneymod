public void ShowMainMenu(int client)
{
	Menu menu = new Menu(HandleMainMenu);

	menu.SetTitle("%s Main Menu\nYour money: $10\n  ", MENU_PREFIX);

	menu.AddItem("info", "Info");
	menu.AddItem("weapons", "Weapons\n ");

	char buffer[128];
	int maxlvl;

	#define INFO[%0] g_AbilitiesInfo[i][%0]
	#define ABI g_Abilities[client][i]

	for(int i = 0; i < view_as<int>(e_Abilities); i++)
	{
		maxlvl = (ABI >= INFO[maxLevel]);

		if(maxlvl)
			Format(buffer, sizeof(buffer), "%s [%i/%i] (%s%i%s/%i%s)",
				INFO[desc], g_Abilities[client][i], INFO[maxLevel],
				INFO[prefix], ABI * INFO[powerPerLevel], INFO[firstUnit],
				INFO[maxLevel] * INFO[powerPerLevel], INFO[secondUnit]);
		else
			Format(buffer, sizeof(buffer), "%s [%i/%i] (%s%i%s/%i%s) [$%i]",
				INFO[desc], g_Abilities[client][i], INFO[maxLevel],
				INFO[prefix], ABI * INFO[powerPerLevel], INFO[firstUnit],
				INFO[maxLevel] * INFO[powerPerLevel], INFO[secondUnit],
				INFO[initialCost] * (ABI + 1));


		menu.AddItem(INFO[desc], buffer, maxlvl ? ITEMDRAW_DISABLED :  ITEMDRAW_DEFAULT);
	}

	menu.Display(client, MENU_TIME_FOREVER);
}

public int HandleMainMenu(Menu menu, MenuAction action, int param1, int param2) {

	if (action == MenuAction_End)
	{
		delete menu;
	}
}
