public void ShowMainMenu(int client)
{
	Menu menu = new Menu(HandleMainMenu);

	menu.SetTitle("%s Main Menu\nYour money: $%i\n  ", MENU_PREFIX, g_Players[client][Money]);

	menu.AddItem("info", "Info");
	menu.AddItem("weapons", "Weapons\n ");

	char buffer[128], itemname[12];
	int maxlvl;

	#define INFO[%0] g_AbilitiesInfo[i][%0]
	#define ABI g_Abilities[client][i]

	for(int i = 0; i < view_as<int>(e_Abilities); i++)
	{
		Format(itemname, sizeof(itemname), "%i", i);

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
				INFO[initialCost] << (ABI));


		menu.AddItem(itemname, buffer, maxlvl ? ITEMDRAW_DISABLED : ITEMDRAW_DEFAULT);
	}

	#undef INFO
	#undef ABI

	menu.Display(client, MENU_TIME_FOREVER);
}

public int HandleMainMenu(Menu menu, MenuAction action, int client, int param2) {

	if (action == MenuAction_End)
	{
		delete menu;
	}
	else if(action == MenuAction_Select)
	{
		char info[32];
		GetMenuItem(menu, param2, info, sizeof(info));

		//ability was chosen - try to buy it!
		if(IsCharNumeric(info[0])) {
			int abi = StringToInt(info);
			BuyAbility(client, abi);
		}
		else if(StrEqual(info, "weapons")) {
			ShowWeaponsMenu(client);
			return;
		}
		//redisplay menu
		ShowMainMenu(client);
	}

	return;
}

public bool BuyAbility(client, ability)
{
	int cost = g_AbilitiesInfo[ability][initialCost] << (g_Abilities[client][ability]);

	if(cost > g_Players[client][Money])
	{
		PrintToChat(client, "%s You can't afford this ability :( $\x07%i\x01 to go!",
			CHAT_PREFIX, cost - g_Players[client][Money]);
		return false;
	}

	if(g_Abilities[client][ability] >= g_AbilitiesInfo[ability][maxLevel])
	{
		PrintToChat(client, "%s You have reached the max level of this ability!", CHAT_PREFIX);
		return false;
	}

	g_Players[client][Money] -= cost;
	g_Abilities[client][ability]++;

	PrintToChat(client, "%s\x07 %s\x01 upgraded to level\x07 %i\x01!",
		CHAT_PREFIX, g_AbilitiesInfo[ability][desc], g_Abilities[client][ability]);

	return true;
}
