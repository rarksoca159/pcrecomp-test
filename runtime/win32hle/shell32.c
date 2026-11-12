/*
 * shell32.c - minimal SHELL32 compatibility for the Android host.
 *
 * Spin & Win imports ShellExecuteA. Android does not expose a Win32 shell
 * execute operation, so report SE_ERR_NOASSOC (31) rather than pretending an
 * external process was launched. The in-game renderer and game assets do not
 * depend on this API.
 */
#include "win32hle.h"

static void s_ShellExecuteA(void) {
    RET(31u, 6); /* HINSTANCE <= 32: no association / launch unsupported */
}

const win32hle_shim win32hle_shell32[] = {
    { "ShellExecuteA", s_ShellExecuteA },
    { 0, 0 }
};
