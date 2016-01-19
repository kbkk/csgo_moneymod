public void ShowWeaponsMenu(int client)
{
	Menu menu = new Menu(HandleWeaponsMenu);

	menu.SetTitle("%s Weapons Menu\nYour money: $%i\n  ", MENU_PREFIX, g_Players[client][Money]);

	char buffer[128], itemname[12];
	int maxlvl;

	#define INFO[%0] g_WeaponsInfo[i][%0]
	#define WEP g_Weapons[client][i]

	for(int i = 0; i < view_as<int>(e_Weapons); i++)
	{
		Format(itemname, sizeof(itemname), "%i", i);

		maxlvl = (WEP >= INFO[maxLevel]);

		if(maxlvl)
			Format(buffer, sizeof(buffer), "%s [%i/%i] (%s%i%s/%i%s)",
				INFO[desc], g_Weapons[client][i], INFO[maxLevel],
				INFO[prefix], WEP * INFO[powerPerLevel], INFO[firstUnit],
				INFO[maxLevel] * INFO[powerPerLevel], INFO[secondUnit]);
		else
			Format(buffer, sizeof(buffer), "%s [%i/%i] (%s%i%s/%i%s) [$%i]",
				INFO[desc], g_Weapons[client][i], INFO[maxLevel],
				INFO[prefix], WEP * INFO[powerPerLevel], INFO[firstUnit],
				INFO[maxLevel] * INFO[powerPerLevel], INFO[secondUnit],
				INFO[initialCost] << (WEP));


		menu.AddItem(itemname, buffer, maxlvl ? ITEMDRAW_DISABLED : ITEMDRAW_DEFAULT);
	}

	menu.Display(client, MENU_TIME_FOREVER);
}

public int HandleWeaponsMenu(Menu menu, MenuAction action, int client, int param2) {

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
			int wep = StringToInt(info);
			BuyWeapon(client, wep);
		}
		//redisplay menu
		ShowWeaponsMenu(client);
	}
}

public bool BuyWeapon(client, weapon)
{
	int cost = g_WeaponsInfo[weapon][initialCost] << (g_Weapons[client][weapon]);

	if(cost > g_Players[client][Money])
	{
		PrintToChat(client, "%s You can't afford this weapon :( $\x07%i\x01 to go!",
			CHAT_PREFIX, cost - g_Players[client][Money]);
		return false;
	}

	if(g_Weapons[client][weapon] >= g_WeaponsInfo[weapon][maxLevel])
	{
		PrintToChat(client, "%s You have reached the max level of this weapon!", CHAT_PREFIX);
		return false;
	}

	g_Players[client][Money] -= cost;
	g_Weapons[client][weapon]++;

	PrintToChat(client, "%s\x07 %s\x01 upgraded to level\x07 %i\x01!",
		CHAT_PREFIX, g_WeaponsInfo[weapon][desc], g_Weapons[client][weapon]);

	return true;
}
