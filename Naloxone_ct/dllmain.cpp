/*

Author: Dawg


Pain is inevitable. Suffering is optional


*/
#include "Globals/includes.h"




typedef __int64(__fastcall* t_pcall)(lua_State* L, int nargs, int nresults, int errfunc,lua_KContext ctx, lua_KFunction k);
t_pcall LuaPcall = (t_pcall)((uintptr_t)(LI_MODULE("citizen-scripting-lua.dll").cached<HMODULE>()) + 0x2CEB0);



__int64 __fastcall HackPcall(lua_State* L, int nargs, int nresults, int errfunc, lua_KContext ctx, lua_KFunction k) {

    if (L) {
        //luaL_dostring(L, "print('test')");
        luaL_dofile(L, "D:\\test.lua");
		Sleep(1);
        return LuaPcall(L, nargs, nresults, errfunc, ctx, k);

    };
    

	
    return LuaPcall(L, nargs, nresults, errfunc, ctx, k);
};





BOOL APIENTRY DllMain(HMODULE hModule,DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:

        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourAttach(&(LPVOID&)LuaPcall, &HackPcall);
        DetourTransactionCommit();

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

