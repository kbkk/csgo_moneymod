stock ClearTimer(&Handle:timer)
{
    if (timer != INVALID_HANDLE)
        KillTimer(timer);

    timer = INVALID_HANDLE;
}

stock any:Math_Min(any:a, any:b) { return a < b ? a : b; }

stock any:Math_Max(any:a, any:b) { return a > b ? a : b; }

stock FindSendPropOffsEx(const String:serverClass[64], const String:propName[64])
{
	new offset = FindSendPropOffs(serverClass, propName);

	// Disable plugin if a networkable send property offset was not found
	if (offset <= 0)
	{
		SetFailState("Unable to find offset \"%s::%s\"!", serverClass, propName);
	}

	return offset;
}
