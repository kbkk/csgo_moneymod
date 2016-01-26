public int Native_GetBootsTime(Handle plugin, int numParams)
{
   int client = GetNativeCell(1);

   return GetClientAbiPower(client, LONGERBOOTS);
}

public int Native_GetInvincibilityTime(Handle plugin, int numParams)
{
   int client = GetNativeCell(1);

   return GetClientAbiPower(client, LONGERINVINCIBILITY);
}

public int Native_GetStealthTime(Handle plugin, int numParams)
{
   int client = GetNativeCell(1);

   return GetClientAbiPower(client, LONGERSTEALTH);
}

public int Native_GetWeakerFreezePercent(Handle plugin, int numParams)
{
   int client = GetNativeCell(1);

   return GetClientAbiPower(client, WEAKERFREEZE);
}
