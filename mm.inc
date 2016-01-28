#if defined _moneymod_included
 #endinput
#endif
#define _moneymod_included

native int mm_GetBootsTime(int client);

native int mm_GetInvincibilityTime(int client);

native int mm_GetStealthTime(int client);

native int mm_GetWeakerFreezePercent(int client);

native int mm_AddMoney(int client, int money);
