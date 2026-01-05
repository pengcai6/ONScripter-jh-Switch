/* -*- C++ -*-
 *
 *  main.cpp - Main entry point for ONScripter-jh Nintendo Switch
 *
 *  Copyright (c) 2001-2018 Ogapee. All rights reserved.
 *            (C) 2014-2019 jh10001 <jh10001@live.cn>
 *            (C) 2019-2025 wetor <makisehoshimi@163.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <switch.h>

#ifdef DEBUG
#include <twili.h>
#endif

#include "main.h"
#include "Utils.h"
#include "Common.h"
#include "version.h"

// Global variables
void *mouse_png = nullptr;
int mouse_png_size = 0;
int english = 0;
char return_path[256] = {0};

// Constants
static constexpr const char* DEFAULT_RETURN_PATH = "sdmc:/onsemu/exefs/ONSBrowser.nro";
static constexpr const char* MOUSE_CURSOR_PATH = "romfs:/cursor/mouse.png";
static constexpr int MOUSE_PNG_EXPECTED_SIZE = 1699;

// Forward declarations
static bool initializeSystem();
static void cleanupSystem();
static bool loadMouseCursor();
static void parseCommandLineArgs(int argc, char* argv[], char* path, int* fullmode, int* outline);

/**
 * Parse command line arguments
 *
 * Args format:
 * 0 : self NRO program path
 * 1 : ONScripter game folder
 * 2 : mode: 0 default; mode&1 fullscreen stretch; mode&2 outline; mode&4 english
 * 3 : return nro path after game exit
 */
static void parseCommandLineArgs(int argc, char* argv[], char* path, int* fullmode, int* outline)
{
    if (!envHasArgv() || argc <= 1) {
        utils::printWarning("No command line arguments provided\n");
        return;
    }

    // Copy game path
    if (argv[1]) {
        utils::strncpy_safe(path, argv[1], 256);
        utils::printInfo("Game path: %s\n", path);
    }

    // Parse mode flags
    if (argc > 2 && argv[2]) {
        int setting = atoi(argv[2]);
        if (setting & 1) {
            *fullmode = 1;
            utils::printDebug("Fullscreen mode enabled\n");
        }
        if (setting & 2) {
            *outline = 1;
            utils::printDebug("Font outline enabled\n");
        }
        if (setting & 4) {
            english = 1;
            utils::printDebug("English mode enabled\n");
        }
    }

    // Parse return path
    if (argc > 3 && argv[3]) {
        utils::strncpy_safe(return_path, argv[3], sizeof(return_path));
        utils::printDebug("Return path: %s\n", return_path);
    }
}

/**
 * Initialize Switch system services
 */
static bool initializeSystem()
{
#ifdef DEBUG
    if (R_FAILED(twiliInitialize())) {
        // Debug init failed, but continue anyway
    }
    twiliBindStdio();
#endif

    // Initialize random seed
    srand(static_cast<unsigned int>(time(nullptr)));

    // Initialize romfs
    Result rc = romfsInit();
    if (R_FAILED(rc)) {
        utils::printError("Failed to initialize romfs: 0x%x\n", rc);
        return false;
    }

    return true;
}

/**
 * Clean up system resources
 */
static void cleanupSystem()
{
    // Free mouse cursor memory
    if (mouse_png) {
        free(mouse_png);
        mouse_png = nullptr;
        mouse_png_size = 0;
    }

    // Exit romfs
    romfsExit();

#ifdef DEBUG
    twiliExit();
#endif
}

/**
 * Load mouse cursor image from romfs
 */
static bool loadMouseCursor()
{
    mouse_png_size = MOUSE_PNG_EXPECTED_SIZE;
    mouse_png = malloc(mouse_png_size);

    if (!mouse_png) {
        utils::printError("Failed to allocate memory for mouse cursor\n");
        return false;
    }

    FILE* f = fopen(MOUSE_CURSOR_PATH, "rb");
    if (!f) {
        utils::printError("Failed to open mouse cursor: %s\n", MOUSE_CURSOR_PATH);
        free(mouse_png);
        mouse_png = nullptr;
        mouse_png_size = 0;
        return false;
    }

    size_t bytesRead = fread(mouse_png, 1, mouse_png_size, f);
    fclose(f);

    if (bytesRead != static_cast<size_t>(mouse_png_size)) {
        utils::printWarning("Mouse cursor file size mismatch: expected %d, got %zu\n",
                           mouse_png_size, bytesRead);
        // Continue anyway, might still work
    }

    utils::printDebug("Mouse cursor loaded successfully\n");
    return true;
}

/**
 * Exit handler - returns to launcher
 */
void ons_exit(int flag)
{
    cleanupSystem();

    // Prepare return arguments
    char args[256];
    snprintf(args, sizeof(args), "\"%s\"", return_path);

    // Set next load target
    envSetNextLoad(return_path, args);

    exit(EXIT_SUCCESS);
}

/**
 * Main entry point
 */
int main(int argc, char* argv[])
{
    // Initialize default return path
    utils::strncpy_safe(return_path, DEFAULT_RETURN_PATH, sizeof(return_path));

    // Initialize system
    if (!initializeSystem()) {
        utils::printError("System initialization failed\n");
        return 1;
    }

    // Print version info
    utils::printInfo("===========================================\n");
    utils::printInfo("ONScripter-jh for Nintendo Switch\n");
    utils::printInfo("Version: %s (JH: %s, ONS: %s)\n",
                     ONS_NX_VERSION, ONS_JH_VERSION, ONS_VERSION);
    utils::printInfo("NSC Version: %d.%02d\n", NSC_VERSION / 100, NSC_VERSION % 100);
    utils::printInfo("===========================================\n\n");

    // Parse arguments
    char path[256] = {0};
    int fullmode = 0;
    int outline = 0;

    parseCommandLineArgs(argc, argv, path, &fullmode, &outline);

    // Exit if no game path provided
    if (!envHasArgv() || argc <= 1) {
        utils::printInfo("No game specified, exiting to launcher\n");
        ons_exit(0);
        return 0;
    }

    // Build argument list for ONScripter
    // Maximum 16 arguments should be enough
    const int MAX_ARGS = 16;
    char* ons_argv[MAX_ARGS];
    int ons_argc = 0;

    // argv[0] is program name (unused but required)
    ons_argv[ons_argc++] = argv[0];

    // --root <path>
    ons_argv[ons_argc++] = const_cast<char*>("--root");
    ons_argv[ons_argc++] = path;

    // --compatible
    ons_argv[ons_argc++] = const_cast<char*>("--compatible");

    // --fontcache
    ons_argv[ons_argc++] = const_cast<char*>("--fontcache");

    // Window mode
    if (fullmode) {
        ons_argv[ons_argc++] = const_cast<char*>("--fullscreen");
    } else {
        ons_argv[ons_argc++] = const_cast<char*>("--window");
    }

    // Font outline
    if (outline) {
        ons_argv[ons_argc++] = const_cast<char*>("--render-font-outline");
    }

    // English mode (SJIS encoding)
    if (english) {
        ons_argv[ons_argc++] = const_cast<char*>("--enc:sjis");
    }

    // Debug mode (uncomment if needed)
    // ons_argv[ons_argc++] = const_cast<char*>("--debug:1");

    utils::printInfo("Starting ONScripter with %d arguments\n", ons_argc);
    for (int i = 0; i < ons_argc; i++) {
        utils::printDebug("  argv[%d] = %s\n", i, ons_argv[i]);
    }

    // Load mouse cursor
    if (!loadMouseCursor()) {
        utils::printWarning("Mouse cursor not loaded, using default\n");
    }

    // Run ONScripter main
    int result = OnsMain(ons_argc, ons_argv);

    if (result != 0) {
        utils::printError("ONScripter returned error: %d\n", result);
    }

    // Clean exit
    ons_exit(EXIT_SUCCESS);

    return 0;
}
