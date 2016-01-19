stock ClearTimer(&Handle:timer)
{
    if (timer != INVALID_HANDLE)
    {
        KillTimer(timer);
    }
    timer = INVALID_HANDLE;
}

stock any:Math_Min(any:a, any:b) { return a < b ? a : b; }

stock any:Math_Max(any:a, any:b) { return a > b ? a : b; }
