/*
====================================================================

DOOM RETRO
The classic, refined DOOM source port. For Windows PC.

Copyright (C) 1993-1996 id Software LLC, a ZeniMax Media company.
Copyright (C) 2005-2014 Simon Howard.
Copyright (C) 2013-2014 Brad Harding.

This file is part of DOOM RETRO.

DOOM RETRO is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

DOOM RETRO is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with DOOM RETRO. If not, see http://www.gnu.org/licenses/.

====================================================================
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stdarg.h>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
void done_win32(void);
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "doomdef.h"
#include "doomstat.h"
#include "m_argv.h"
#include "m_config.h"
#include "m_misc.h"
#include "i_gamepad.h"
#include "i_timer.h"
#include "i_video.h"
#include "s_sound.h"

#include "d_net.h"
#include "g_game.h"

#include "i_system.h"

#include "SDL.h"

#include "w_wad.h"
#include "z_zone.h"

#define DEFAULT_RAM 32 // MiB
#define MIN_RAM     32 // MiB

// Zone memory auto-allocation function that allocates the zone size
// by trying progressively smaller zone sizes until one is found that
// works.

static byte *AutoAllocMemory(int *size, int default_ram, int min_ram)
{
    byte *zonemem;

    // Allocate the zone memory.  This loop tries progressively smaller
    // zone sizes until a size is found that can be allocated.
    // If we used the -mb command line parameter, only the parameter
    // provided is accepted.

    zonemem = NULL;

    while (zonemem == NULL)
    {
        // We need a reasonable minimum amount of RAM to start.

        if (default_ram < min_ram)
        {
            I_Error("Unable to allocate %i MiB of RAM for zone", default_ram);
        }

        // Try to allocate the zone memory.

        *size = default_ram * 1024 * 1024;

        zonemem = (byte *)malloc(*size);

        // Failed to allocate?  Reduce zone size until we reach a size
        // that is acceptable.

        if (zonemem == NULL)
        {
            default_ram -= 1;
        }
    }

    return zonemem;
}

byte *I_ZoneBase(int *size)
{
    byte *zonemem;
    int min_ram, default_ram;
    int p;

    //!
    // @arg <mb>
    //
    // Specify the heap size, in MiB (default 16).
    //

    p = M_CheckParmWithArgs("-mb", 1);

    if (p > 0)
    {
        default_ram = atoi(myargv[p + 1]);
        min_ram = default_ram;
    }
    else
    {
        default_ram = DEFAULT_RAM;
        min_ram = MIN_RAM;
    }

    zonemem = AutoAllocMemory(size, default_ram, min_ram);

    return zonemem;
}

//
// I_Init
//
void I_Init(void)
{
    I_InitTimer();
    I_InitGamepad();
}

//
// I_Quit
//
void I_Quit(boolean shutdown)
{
    if (shutdown)
    {
        S_Shutdown();

        I_SaveWindowPosition();

        if (returntowidescreen)
            widescreen = true;

        M_SaveDefaults();

        I_ShutdownGraphics();

        I_ShutdownGamepad();
    }

#ifdef _WIN32
    done_win32();
#endif

    SDL_Quit();

    exit(0);
}

void I_WaitVBL(int count)
{
    I_Sleep((count * 1000) / 70);
}

#if !defined(_WIN32) && !defined(__MACOSX__)

#define ZENITY_BINARY "/usr/bin/zenity"

// returns non-zero if zenity is available

static int ZenityAvailable(void)
{
    return system(ZENITY_BINARY " --help >/dev/null 2>&1") == 0;
}

// Escape special characters in the given string so that they can be
// safely enclosed in shell quotes.

static char *EscapeShellString(char *string)
{
    char *result;
    char *r, *s;

    // In the worst case, every character might be escaped.
    result = malloc(strlen(string) * 2 + 3);
    r = result;

    // Enclosing quotes.
    *r = '"';
    ++r;

    for (s = string; *s != '\0'; ++s)
    {
        // From the bash manual:
        //
        //  "Enclosing characters in double quotes preserves the literal
        //   value of all characters within the quotes, with the exception
        //   of $, `, \, and, when history expansion is enabled, !."
        //
        // Therefore, escape these characters by prefixing with a backslash.

        if (strchr("$`\\!", *s) != NULL)
        {
            *r = '\\';
            ++r;
        }

        *r = *s;
        ++r;
    }

    // Enclosing quotes.
    *r = '"';
    ++r;
    *r = '\0';

    return result;
}

// Open a native error box with a message using zenity

static int ZenityErrorBox(char *message)
{
    int result;
    char *escaped_message;
    char *errorboxpath;
    static size_t errorboxpath_size;

    if (!ZenityAvailable())
    {
        return 0;
    }

    escaped_message = EscapeShellString(message);

    errorboxpath_size = strlen(ZENITY_BINARY) + strlen(escaped_message) + 19;
    errorboxpath = malloc(errorboxpath_size);
    M_snprintf(errorboxpath, errorboxpath_size, "%s --error --text=%s",
        ZENITY_BINARY, escaped_message);

    result = system(errorboxpath);

    free(errorboxpath);
    free(escaped_message);

    return result;
}

#endif

//
// I_Error
//
static boolean already_quitting = false;

void I_Error(char *error, ...)
{
    va_list     argptr;
    char        msgbuf[512];
    wchar_t     wmsgbuf[512];

    if (already_quitting)
        exit(-1);
    else
        already_quitting = true;

    // Message first.
    va_start(argptr, error);
    vfprintf(stderr, error, argptr);
    fprintf(stderr, "\n\n");
    va_end(argptr);
    fflush(stderr);

    // Shutdown. Here might be other errors.
    S_Shutdown();

    I_SaveWindowPosition();

    if (returntowidescreen)
        widescreen = true;

    I_ShutdownGraphics();

    I_ShutdownGamepad();

    va_start(argptr, error);
    memset(msgbuf, 0, sizeof(msgbuf));
    M_vsnprintf(msgbuf, sizeof(msgbuf) - 1, error, argptr);
    va_end(argptr);

#ifdef _WIN32
    MultiByteToWideChar(CP_ACP, 0,
                        msgbuf, strlen(msgbuf) + 1,
                        wmsgbuf, sizeof(wmsgbuf));

    MessageBoxW(NULL, wmsgbuf, L"DOOM RETRO", MB_ICONERROR | MB_OK);

    done_win32();

    SDL_Quit();

#elif defined(__MACOSX__)
    {
        CFStringRef message;
        int i;

        // The CoreFoundation message box wraps text lines, so replace
        // newline characters with spaces so that multiline messages
        // are continuous.

        for (i = 0; msgbuf[i] != '\0'; ++i)
            if (msgbuf[i] == '\n')
                msgbuf[i] = ' ';

        message = CFStringCreateWithCString(NULL, msgbuf, kCFStringEncodingUTF8);

        CFUserNotificationDisplayNotice(0,
            kCFUserNotificationCautionAlertLevel,
            NULL,
            NULL,
            NULL,
            CFSTR(PACKAGE_STRING),
            message,
            NULL);
    }
#else
    {
        ZenityErrorBox(msgbuf);
    }
#endif
    exit(-1);
}
