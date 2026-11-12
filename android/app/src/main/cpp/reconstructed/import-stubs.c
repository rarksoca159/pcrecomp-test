/* Import bridge stubs - manual implementation needed */

#include "recomp_types.h"


/* ===== DDRAW.dll ===== */

/* 0x0041D000 */ void bridge_DirectDrawCreate(void) {
    /* TODO: implement DDRAW.dll::DirectDrawCreate */
    STUB("DDRAW.dll::DirectDrawCreate");
}


/* ===== GDI32.dll ===== */

/* 0x0041D008 */ void bridge_GetTextExtentPoint32A(void) {
    /* TODO: implement GDI32.dll::GetTextExtentPoint32A */
    STUB("GDI32.dll::GetTextExtentPoint32A");
}

/* 0x0041D00C */ void bridge_SetBkMode(void) {
    /* TODO: implement GDI32.dll::SetBkMode */
    STUB("GDI32.dll::SetBkMode");
}

/* 0x0041D010 */ void bridge_SetTextColor(void) {
    /* TODO: implement GDI32.dll::SetTextColor */
    STUB("GDI32.dll::SetTextColor");
}

/* 0x0041D014 */ void bridge_CreateFontA(void) {
    /* TODO: implement GDI32.dll::CreateFontA */
    STUB("GDI32.dll::CreateFontA");
}

/* 0x0041D018 */ void bridge_SelectObject(void) {
    /* TODO: implement GDI32.dll::SelectObject */
    STUB("GDI32.dll::SelectObject");
}

/* 0x0041D01C */ void bridge_TextOutA(void) {
    /* TODO: implement GDI32.dll::TextOutA */
    STUB("GDI32.dll::TextOutA");
}

/* 0x0041D020 */ void bridge_DeleteObject(void) {
    /* TODO: implement GDI32.dll::DeleteObject */
    STUB("GDI32.dll::DeleteObject");
}

/* 0x0041D024 */ void bridge_GetDeviceCaps(void) {
    /* TODO: implement GDI32.dll::GetDeviceCaps */
    STUB("GDI32.dll::GetDeviceCaps");
}

/* 0x0041D028 */ void bridge_GetStockObject(void) {
    /* TODO: implement GDI32.dll::GetStockObject */
    STUB("GDI32.dll::GetStockObject");
}


/* ===== KERNEL32.dll ===== */

/* 0x0041D030 */ void bridge_LoadLibraryA(void) {
    /* TODO: implement KERNEL32.dll::LoadLibraryA */
    STUB("KERNEL32.dll::LoadLibraryA");
}

/* 0x0041D034 */ void bridge_GetOEMCP(void) {
    /* TODO: implement KERNEL32.dll::GetOEMCP */
    STUB("KERNEL32.dll::GetOEMCP");
}

/* 0x0041D038 */ void bridge_GetACP(void) {
    /* TODO: implement KERNEL32.dll::GetACP */
    STUB("KERNEL32.dll::GetACP");
}

/* 0x0041D03C */ void bridge_GetCPInfo(void) {
    /* TODO: implement KERNEL32.dll::GetCPInfo */
    STUB("KERNEL32.dll::GetCPInfo");
}

/* 0x0041D040 */ void bridge_IsBadCodePtr(void) {
    /* TODO: implement KERNEL32.dll::IsBadCodePtr */
    STUB("KERNEL32.dll::IsBadCodePtr");
}

/* 0x0041D044 */ void bridge_IsBadReadPtr(void) {
    /* TODO: implement KERNEL32.dll::IsBadReadPtr */
    STUB("KERNEL32.dll::IsBadReadPtr");
}

/* 0x0041D048 */ void bridge_SetUnhandledExceptionFilter(void) {
    /* TODO: implement KERNEL32.dll::SetUnhandledExceptionFilter */
    STUB("KERNEL32.dll::SetUnhandledExceptionFilter");
}

/* 0x0041D04C */ void bridge_MultiByteToWideChar(void) {
    /* TODO: implement KERNEL32.dll::MultiByteToWideChar */
    STUB("KERNEL32.dll::MultiByteToWideChar");
}

/* 0x0041D050 */ void bridge_CreateFileA(void) {
    /* TODO: implement KERNEL32.dll::CreateFileA */
    STUB("KERNEL32.dll::CreateFileA");
}

/* 0x0041D054 */ void bridge_FlushFileBuffers(void) {
    /* TODO: implement KERNEL32.dll::FlushFileBuffers */
    STUB("KERNEL32.dll::FlushFileBuffers");
}

/* 0x0041D058 */ void bridge_SetStdHandle(void) {
    /* TODO: implement KERNEL32.dll::SetStdHandle */
    STUB("KERNEL32.dll::SetStdHandle");
}

/* 0x0041D05C */ void bridge_GetFileType(void) {
    /* TODO: implement KERNEL32.dll::GetFileType */
    STUB("KERNEL32.dll::GetFileType");
}

/* 0x0041D060 */ void bridge_GetStdHandle(void) {
    /* TODO: implement KERNEL32.dll::GetStdHandle */
    STUB("KERNEL32.dll::GetStdHandle");
}

/* 0x0041D064 */ void bridge_SetHandleCount(void) {
    /* TODO: implement KERNEL32.dll::SetHandleCount */
    STUB("KERNEL32.dll::SetHandleCount");
}

/* 0x0041D068 */ void bridge_GetEnvironmentStringsW(void) {
    /* TODO: implement KERNEL32.dll::GetEnvironmentStringsW */
    STUB("KERNEL32.dll::GetEnvironmentStringsW");
}

/* 0x0041D06C */ void bridge_GetEnvironmentStrings(void) {
    /* TODO: implement KERNEL32.dll::GetEnvironmentStrings */
    STUB("KERNEL32.dll::GetEnvironmentStrings");
}

/* 0x0041D070 */ void bridge_GetStringTypeA(void) {
    /* TODO: implement KERNEL32.dll::GetStringTypeA */
    STUB("KERNEL32.dll::GetStringTypeA");
}

/* 0x0041D074 */ void bridge_FreeEnvironmentStringsW(void) {
    /* TODO: implement KERNEL32.dll::FreeEnvironmentStringsW */
    STUB("KERNEL32.dll::FreeEnvironmentStringsW");
}

/* 0x0041D078 */ void bridge_FreeEnvironmentStringsA(void) {
    /* TODO: implement KERNEL32.dll::FreeEnvironmentStringsA */
    STUB("KERNEL32.dll::FreeEnvironmentStringsA");
}

/* 0x0041D07C */ void bridge_UnhandledExceptionFilter(void) {
    /* TODO: implement KERNEL32.dll::UnhandledExceptionFilter */
    STUB("KERNEL32.dll::UnhandledExceptionFilter");
}

/* 0x0041D080 */ void bridge_IsBadWritePtr(void) {
    /* TODO: implement KERNEL32.dll::IsBadWritePtr */
    STUB("KERNEL32.dll::IsBadWritePtr");
}

/* 0x0041D084 */ void bridge_VirtualAlloc(void) {
    /* TODO: implement KERNEL32.dll::VirtualAlloc */
    STUB("KERNEL32.dll::VirtualAlloc");
}

/* 0x0041D088 */ void bridge_VirtualFree(void) {
    /* TODO: implement KERNEL32.dll::VirtualFree */
    STUB("KERNEL32.dll::VirtualFree");
}

/* 0x0041D08C */ void bridge_HeapCreate(void) {
    /* TODO: implement KERNEL32.dll::HeapCreate */
    STUB("KERNEL32.dll::HeapCreate");
}

/* 0x0041D090 */ void bridge_HeapDestroy(void) {
    /* TODO: implement KERNEL32.dll::HeapDestroy */
    STUB("KERNEL32.dll::HeapDestroy");
}

/* 0x0041D094 */ void bridge_SetFilePointer(void) {
    /* TODO: implement KERNEL32.dll::SetFilePointer */
    STUB("KERNEL32.dll::SetFilePointer");
}

/* 0x0041D098 */ void bridge_WriteFile(void) {
    /* TODO: implement KERNEL32.dll::WriteFile */
    STUB("KERNEL32.dll::WriteFile");
}

/* 0x0041D09C */ void bridge_ReadFile(void) {
    /* TODO: implement KERNEL32.dll::ReadFile */
    STUB("KERNEL32.dll::ReadFile");
}

/* 0x0041D0A0 */ void bridge_RaiseException(void) {
    /* TODO: implement KERNEL32.dll::RaiseException */
    STUB("KERNEL32.dll::RaiseException");
}

/* 0x0041D0A4 */ void bridge_CloseHandle(void) {
    /* TODO: implement KERNEL32.dll::CloseHandle */
    STUB("KERNEL32.dll::CloseHandle");
}

/* 0x0041D0A8 */ void bridge_GetLastError(void) {
    /* TODO: implement KERNEL32.dll::GetLastError */
    STUB("KERNEL32.dll::GetLastError");
}

/* 0x0041D0AC */ void bridge_HeapSize(void) {
    /* TODO: implement KERNEL32.dll::HeapSize */
    STUB("KERNEL32.dll::HeapSize");
}

/* 0x0041D0B0 */ void bridge_GetCurrentProcess(void) {
    /* TODO: implement KERNEL32.dll::GetCurrentProcess */
    STUB("KERNEL32.dll::GetCurrentProcess");
}

/* 0x0041D0B4 */ void bridge_GetStringTypeW(void) {
    /* TODO: implement KERNEL32.dll::GetStringTypeW */
    STUB("KERNEL32.dll::GetStringTypeW");
}

/* 0x0041D0B8 */ void bridge_LCMapStringA(void) {
    /* TODO: implement KERNEL32.dll::LCMapStringA */
    STUB("KERNEL32.dll::LCMapStringA");
}

/* 0x0041D0BC */ void bridge_LCMapStringW(void) {
    /* TODO: implement KERNEL32.dll::LCMapStringW */
    STUB("KERNEL32.dll::LCMapStringW");
}

/* 0x0041D0C0 */ void bridge_SetEndOfFile(void) {
    /* TODO: implement KERNEL32.dll::SetEndOfFile */
    STUB("KERNEL32.dll::SetEndOfFile");
}

/* 0x0041D0C4 */ void bridge_Sleep(void) {
    /* TODO: implement KERNEL32.dll::Sleep */
    STUB("KERNEL32.dll::Sleep");
}

/* 0x0041D0C8 */ void bridge_FindNextFileA(void) {
    /* TODO: implement KERNEL32.dll::FindNextFileA */
    STUB("KERNEL32.dll::FindNextFileA");
}

/* 0x0041D0CC */ void bridge_FindFirstFileA(void) {
    /* TODO: implement KERNEL32.dll::FindFirstFileA */
    STUB("KERNEL32.dll::FindFirstFileA");
}

/* 0x0041D0D0 */ void bridge_WideCharToMultiByte(void) {
    /* TODO: implement KERNEL32.dll::WideCharToMultiByte */
    STUB("KERNEL32.dll::WideCharToMultiByte");
}

/* 0x0041D0D4 */ void bridge_QueryPerformanceCounter(void) {
    /* TODO: implement KERNEL32.dll::QueryPerformanceCounter */
    STUB("KERNEL32.dll::QueryPerformanceCounter");
}

/* 0x0041D0D8 */ void bridge_QueryPerformanceFrequency(void) {
    /* TODO: implement KERNEL32.dll::QueryPerformanceFrequency */
    STUB("KERNEL32.dll::QueryPerformanceFrequency");
}

/* 0x0041D0DC */ void bridge_TerminateProcess(void) {
    /* TODO: implement KERNEL32.dll::TerminateProcess */
    STUB("KERNEL32.dll::TerminateProcess");
}

/* 0x0041D0E0 */ void bridge_GetProcAddress(void) {
    /* TODO: implement KERNEL32.dll::GetProcAddress */
    STUB("KERNEL32.dll::GetProcAddress");
}

/* 0x0041D0E4 */ void bridge_ExitProcess(void) {
    /* TODO: implement KERNEL32.dll::ExitProcess */
    STUB("KERNEL32.dll::ExitProcess");
}

/* 0x0041D0E8 */ void bridge_GetVersion(void) {
    /* TODO: implement KERNEL32.dll::GetVersion */
    STUB("KERNEL32.dll::GetVersion");
}

/* 0x0041D0EC */ void bridge_GetModuleFileNameA(void) {
    /* TODO: implement KERNEL32.dll::GetModuleFileNameA */
    STUB("KERNEL32.dll::GetModuleFileNameA");
}

/* 0x0041D0F0 */ void bridge_MulDiv(void) {
    /* TODO: implement KERNEL32.dll::MulDiv */
    STUB("KERNEL32.dll::MulDiv");
}

/* 0x0041D0F4 */ void bridge_GetCommandLineA(void) {
    /* TODO: implement KERNEL32.dll::GetCommandLineA */
    STUB("KERNEL32.dll::GetCommandLineA");
}

/* 0x0041D0F8 */ void bridge_GetStartupInfoA(void) {
    /* TODO: implement KERNEL32.dll::GetStartupInfoA */
    STUB("KERNEL32.dll::GetStartupInfoA");
}

/* 0x0041D0FC */ void bridge_GetModuleHandleA(void) {
    /* TODO: implement KERNEL32.dll::GetModuleHandleA */
    STUB("KERNEL32.dll::GetModuleHandleA");
}

/* 0x0041D100 */ void bridge_HeapFree(void) {
    /* TODO: implement KERNEL32.dll::HeapFree */
    STUB("KERNEL32.dll::HeapFree");
}

/* 0x0041D104 */ void bridge_HeapReAlloc(void) {
    /* TODO: implement KERNEL32.dll::HeapReAlloc */
    STUB("KERNEL32.dll::HeapReAlloc");
}

/* 0x0041D108 */ void bridge_HeapAlloc(void) {
    /* TODO: implement KERNEL32.dll::HeapAlloc */
    STUB("KERNEL32.dll::HeapAlloc");
}

/* 0x0041D10C */ void bridge_RtlUnwind(void) {
    /* TODO: implement KERNEL32.dll::RtlUnwind */
    STUB("KERNEL32.dll::RtlUnwind");
}


/* ===== SHELL32.dll ===== */

/* 0x0041D114 */ void bridge_ShellExecuteA(void) {
    /* TODO: implement SHELL32.dll::ShellExecuteA */
    STUB("SHELL32.dll::ShellExecuteA");
}


/* ===== USER32.dll ===== */

/* 0x0041D11C */ void bridge_SystemParametersInfoA(void) {
    /* TODO: implement USER32.dll::SystemParametersInfoA */
    STUB("USER32.dll::SystemParametersInfoA");
}

/* 0x0041D120 */ void bridge_SetCapture(void) {
    /* TODO: implement USER32.dll::SetCapture */
    STUB("USER32.dll::SetCapture");
}

/* 0x0041D124 */ void bridge_ReleaseCapture(void) {
    /* TODO: implement USER32.dll::ReleaseCapture */
    STUB("USER32.dll::ReleaseCapture");
}

/* 0x0041D128 */ void bridge_SetWindowPos(void) {
    /* TODO: implement USER32.dll::SetWindowPos */
    STUB("USER32.dll::SetWindowPos");
}

/* 0x0041D12C */ void bridge_SetWindowLongA(void) {
    /* TODO: implement USER32.dll::SetWindowLongA */
    STUB("USER32.dll::SetWindowLongA");
}

/* 0x0041D130 */ void bridge_AdjustWindowRect(void) {
    /* TODO: implement USER32.dll::AdjustWindowRect */
    STUB("USER32.dll::AdjustWindowRect");
}

/* 0x0041D134 */ void bridge_ClientToScreen(void) {
    /* TODO: implement USER32.dll::ClientToScreen */
    STUB("USER32.dll::ClientToScreen");
}

/* 0x0041D138 */ void bridge_GetDC(void) {
    /* TODO: implement USER32.dll::GetDC */
    STUB("USER32.dll::GetDC");
}

/* 0x0041D13C */ void bridge_SetCursorPos(void) {
    /* TODO: implement USER32.dll::SetCursorPos */
    STUB("USER32.dll::SetCursorPos");
}

/* 0x0041D140 */ void bridge_GetCursorPos(void) {
    /* TODO: implement USER32.dll::GetCursorPos */
    STUB("USER32.dll::GetCursorPos");
}

/* 0x0041D144 */ void bridge_ShowCursor(void) {
    /* TODO: implement USER32.dll::ShowCursor */
    STUB("USER32.dll::ShowCursor");
}

/* 0x0041D148 */ void bridge_ScreenToClient(void) {
    /* TODO: implement USER32.dll::ScreenToClient */
    STUB("USER32.dll::ScreenToClient");
}

/* 0x0041D14C */ void bridge_ToAsciiEx(void) {
    /* TODO: implement USER32.dll::ToAsciiEx */
    STUB("USER32.dll::ToAsciiEx");
}

/* 0x0041D150 */ void bridge_GetKeyboardState(void) {
    /* TODO: implement USER32.dll::GetKeyboardState */
    STUB("USER32.dll::GetKeyboardState");
}

/* 0x0041D154 */ void bridge_GetKeyboardLayout(void) {
    /* TODO: implement USER32.dll::GetKeyboardLayout */
    STUB("USER32.dll::GetKeyboardLayout");
}

/* 0x0041D158 */ void bridge_GetClientRect(void) {
    /* TODO: implement USER32.dll::GetClientRect */
    STUB("USER32.dll::GetClientRect");
}

/* 0x0041D15C */ void bridge_GetDesktopWindow(void) {
    /* TODO: implement USER32.dll::GetDesktopWindow */
    STUB("USER32.dll::GetDesktopWindow");
}

/* 0x0041D160 */ void bridge_PeekMessageA(void) {
    /* TODO: implement USER32.dll::PeekMessageA */
    STUB("USER32.dll::PeekMessageA");
}

/* 0x0041D164 */ void bridge_TranslateMessage(void) {
    /* TODO: implement USER32.dll::TranslateMessage */
    STUB("USER32.dll::TranslateMessage");
}

/* 0x0041D168 */ void bridge_DispatchMessageA(void) {
    /* TODO: implement USER32.dll::DispatchMessageA */
    STUB("USER32.dll::DispatchMessageA");
}

/* 0x0041D16C */ void bridge_GetMessageA(void) {
    /* TODO: implement USER32.dll::GetMessageA */
    STUB("USER32.dll::GetMessageA");
}

/* 0x0041D170 */ void bridge_WaitMessage(void) {
    /* TODO: implement USER32.dll::WaitMessage */
    STUB("USER32.dll::WaitMessage");
}

/* 0x0041D174 */ void bridge_CloseWindow(void) {
    /* TODO: implement USER32.dll::CloseWindow */
    STUB("USER32.dll::CloseWindow");
}

/* 0x0041D178 */ void bridge_LoadIconA(void) {
    /* TODO: implement USER32.dll::LoadIconA */
    STUB("USER32.dll::LoadIconA");
}

/* 0x0041D17C */ void bridge_LoadCursorA(void) {
    /* TODO: implement USER32.dll::LoadCursorA */
    STUB("USER32.dll::LoadCursorA");
}

/* 0x0041D180 */ void bridge_RegisterClassA(void) {
    /* TODO: implement USER32.dll::RegisterClassA */
    STUB("USER32.dll::RegisterClassA");
}

/* 0x0041D184 */ void bridge_GetWindowRect(void) {
    /* TODO: implement USER32.dll::GetWindowRect */
    STUB("USER32.dll::GetWindowRect");
}

/* 0x0041D188 */ void bridge_CreateWindowExA(void) {
    /* TODO: implement USER32.dll::CreateWindowExA */
    STUB("USER32.dll::CreateWindowExA");
}

/* 0x0041D18C */ void bridge_ShowWindow(void) {
    /* TODO: implement USER32.dll::ShowWindow */
    STUB("USER32.dll::ShowWindow");
}

/* 0x0041D190 */ void bridge_UpdateWindow(void) {
    /* TODO: implement USER32.dll::UpdateWindow */
    STUB("USER32.dll::UpdateWindow");
}

/* 0x0041D194 */ void bridge_SetFocus(void) {
    /* TODO: implement USER32.dll::SetFocus */
    STUB("USER32.dll::SetFocus");
}

/* 0x0041D198 */ void bridge_BeginPaint(void) {
    /* TODO: implement USER32.dll::BeginPaint */
    STUB("USER32.dll::BeginPaint");
}

/* 0x0041D19C */ void bridge_EndPaint(void) {
    /* TODO: implement USER32.dll::EndPaint */
    STUB("USER32.dll::EndPaint");
}

/* 0x0041D1A0 */ void bridge_DefWindowProcA(void) {
    /* TODO: implement USER32.dll::DefWindowProcA */
    STUB("USER32.dll::DefWindowProcA");
}

/* 0x0041D1A4 */ void bridge_MessageBoxA(void) {
    /* TODO: implement USER32.dll::MessageBoxA */
    STUB("USER32.dll::MessageBoxA");
}

/* 0x0041D1A8 */ void bridge_PostQuitMessage(void) {
    /* TODO: implement USER32.dll::PostQuitMessage */
    STUB("USER32.dll::PostQuitMessage");
}

/* 0x0041D1AC */ void bridge_MapVirtualKeyExA(void) {
    /* TODO: implement USER32.dll::MapVirtualKeyExA */
    STUB("USER32.dll::MapVirtualKeyExA");
}


/* ===== WINMM.dll ===== */

/* 0x0041D1B4 */ void bridge_timeGetTime(void) {
    /* TODO: implement WINMM.dll::timeGetTime */
    STUB("WINMM.dll::timeGetTime");
}

/* 0x0041D1B8 */ void bridge_joyGetPos(void) {
    /* TODO: implement WINMM.dll::joyGetPos */
    STUB("WINMM.dll::joyGetPos");
}


/* ===== fmod.dll ===== */

/* 0x0041D1C0 */ void bridge__FSOUND_SetSFXMasterVolume@4(void) {
    /* TODO: implement fmod.dll::_FSOUND_SetSFXMasterVolume@4 */
    STUB("fmod.dll::_FSOUND_SetSFXMasterVolume@4");
}

/* 0x0041D1C4 */ void bridge__FSOUND_PlaySound@8(void) {
    /* TODO: implement fmod.dll::_FSOUND_PlaySound@8 */
    STUB("fmod.dll::_FSOUND_PlaySound@8");
}

/* 0x0041D1C8 */ void bridge__FSOUND_SetPaused@8(void) {
    /* TODO: implement fmod.dll::_FSOUND_SetPaused@8 */
    STUB("fmod.dll::_FSOUND_SetPaused@8");
}

/* 0x0041D1CC */ void bridge__FSOUND_SetPan@8(void) {
    /* TODO: implement fmod.dll::_FSOUND_SetPan@8 */
    STUB("fmod.dll::_FSOUND_SetPan@8");
}

/* 0x0041D1D0 */ void bridge__FSOUND_SetVolume@8(void) {
    /* TODO: implement fmod.dll::_FSOUND_SetVolume@8 */
    STUB("fmod.dll::_FSOUND_SetVolume@8");
}

/* 0x0041D1D4 */ void bridge__FSOUND_SetFrequency@8(void) {
    /* TODO: implement fmod.dll::_FSOUND_SetFrequency@8 */
    STUB("fmod.dll::_FSOUND_SetFrequency@8");
}

/* 0x0041D1D8 */ void bridge__FSOUND_PlaySoundEx@16(void) {
    /* TODO: implement fmod.dll::_FSOUND_PlaySoundEx@16 */
    STUB("fmod.dll::_FSOUND_PlaySoundEx@16");
}

/* 0x0041D1DC */ void bridge__FSOUND_Sample_Free@4(void) {
    /* TODO: implement fmod.dll::_FSOUND_Sample_Free@4 */
    STUB("fmod.dll::_FSOUND_Sample_Free@4");
}

/* 0x0041D1E0 */ void bridge__FSOUND_Close@0(void) {
    /* TODO: implement fmod.dll::_FSOUND_Close@0 */
    STUB("fmod.dll::_FSOUND_Close@0");
}

/* 0x0041D1E4 */ void bridge__FSOUND_GetVersion@0(void) {
    /* TODO: implement fmod.dll::_FSOUND_GetVersion@0 */
    STUB("fmod.dll::_FSOUND_GetVersion@0");
}

/* 0x0041D1E8 */ void bridge__FSOUND_SetMemorySystem@20(void) {
    /* TODO: implement fmod.dll::_FSOUND_SetMemorySystem@20 */
    STUB("fmod.dll::_FSOUND_SetMemorySystem@20");
}

/* 0x0041D1EC */ void bridge__FSOUND_Init@12(void) {
    /* TODO: implement fmod.dll::_FSOUND_Init@12 */
    STUB("fmod.dll::_FSOUND_Init@12");
}

/* 0x0041D1F0 */ void bridge__FSOUND_Sample_Load@20(void) {
    /* TODO: implement fmod.dll::_FSOUND_Sample_Load@20 */
    STUB("fmod.dll::_FSOUND_Sample_Load@20");
}

/* 0x0041D1F4 */ void bridge__FSOUND_StopSound@4(void) {
    /* TODO: implement fmod.dll::_FSOUND_StopSound@4 */
    STUB("fmod.dll::_FSOUND_StopSound@4");
}

