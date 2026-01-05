# Changelog

All notable changes to ONScripter-jh for Nintendo Switch will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [2.3.0] - 2025-01-06

### Added - GLES Renderer (CAS Sharpening)

- **GLES renderer with CAS (Contrast Adaptive Sharpening)** from OnscripterYuri
  - GPU-accelerated image sharpening for better visual quality when upscaling
  - Based on AMD FidelityFX CAS algorithm
  - Configurable via `--sharpness <0.0-1.0>` command line option
  - Automatic fallback to standard SDL rendering when sharpness is not set
- New source files:
  - `source/renderer/gles_renderer.h` - GLES renderer class header
  - `source/renderer/gles_renderer.cpp` - GLES renderer implementation
  - `source/renderer/gles2funcs.h` - GLES2 function declarations for dynamic binding
  - `source/renderer/shader/post_cas.h` - CAS fragment shader (GLSL ES 3.0)
- `USE_GLES` compile flag for enabling GLES renderer
- `GlesRenderer` class with pause/resume support for lifecycle management
- `render_view_rect` member for proper scaling calculations

### Changed

- Updated Makefile to include `source/renderer` in SOURCES directories
- ONScripter.h now includes GLES renderer forward declaration when USE_GLES is defined
- `calcRenderRect()` now updates GLES renderer constants when render rect changes
- `flushDirect()` uses GLES CAS renderer when sharpness is enabled
- `sharpness` member variable now uses NAN as default (unset state)

### Technical

- GLES 2.0/3.0 compatible shader implementation
- Nintendo Switch uses OpenGL ES via mesa/nouveau drivers
- Vertex buffer objects for efficient fullscreen quad rendering
- Dynamic GL function binding for desktop platform compatibility

## [2.2.0] - 2025-01-15

### Added - OnscripterYuri Feature Merge

- **UTF-8 script encoding support** (`--enc:utf8`) - Major feature from OnscripterYuri
  - Allows running games with UTF-8 encoded scripts
  - Use `iconv -f gbk -t utf8 0.txt -o 0.txt` to convert existing scripts
- **Arbitrary resolution support** (`--width`, `--height`) - Force custom window dimensions
- **GLES sharpness rendering** (`--sharpness <value>`) - GPU-based image sharpening
- **Fullscreen stretch mode** (`--fullscreen2`) - Fullscreen with aspect ratio stretch
- **Video disable option** (`--no-video`) - Skip video decoding for compatibility
- `force_utf8` flag in Coding2UTF16 class for UTF-8 mode detection
- `UTF8_N_BYTE` macro for UTF-8 byte length detection
- `stretch_mode`, `video_off`, `force_window_width`, `force_window_height`, `sharpness` member variables
- Global logging paths (`g_stdoutpath`, `g_stderrpath`) for file-based logging
- `auto_cast` template utility class from OnscripterYuri
- ONS_YURI_VERSION definition to track upstream version
- Feature flag macros (ONS_FEATURE_UTF8_SCRIPT, etc.)

### Changed

- Upgraded ONS_JH_VERSION from 0.7.6 to 0.8.0 (synced with OnscripterYuri)
- Reorganized command-line help into categories (Load, Render, Other options)
- `setFullscreenMode()` now accepts mode parameter (0=normal, 1=fullscreen, 2=stretch)
- `setWindowMode()` now properly resets fullscreen_mode flag
- Static strings in coding2utf16.cpp now have proper UTF-8 initialization
- Improved UTF-8 to UTF-16 conversion with 4-byte sequence handling
- Updated copyright headers to include yurisizuku (OnscripterYuri author)
- Command-line parser now supports `--enc:gbk` explicitly

### Technical

- Based on OnscripterYuri v0.7.6beta2 (October 2025)
- Maintained backward compatibility with existing GBK/SJIS scripts
- All new features are optional and don't affect default behavior

## [2.1.0] - 2025-01-15

### Added

- Modern C++17 support with updated language features
- Enhanced logging system with multiple log levels (DEBUG, INFO, WARNING, ERROR)
- RAII wrappers for video player resources (KitSourceGuard, KitPlayerGuard, TextureGuard)
- Utility functions: `startsWith`, `endsWith`, `strcasecmp_safe`, `strncpy_safe`, `fileExists`, `getFileExtension`
- Template utility functions: `clamp`, `min`, `max`
- Platform-specific macros (ONS_PLATFORM_NAME, ONS_DEFAULT_SAVE_DIR, ONS_PATH_SEPARATOR)
- Safe memory management macros (SAFE_DELETE, SAFE_DELETE_ARRAY, SAFE_FREE)
- Keyboard skip support for video playback (Escape and Space keys)
- Version components for programmatic access (ONS_NX_VERSION_MAJOR, etc.)
- Comprehensive documentation in header files

### Changed

- Upgraded C++ standard from C++11 to C++17
- Updated compiler architecture flags to support ARMv8-A CRC + Crypto extensions
- Improved linker flags with garbage collection for unused sections
- Enhanced video player with better error handling and resource management
- Modernized main.cpp with structured initialization and cleanup
- Updated ONScripter.json with expanded syscall support and kernel compatibility
- Improved README.md with better formatting, tables, and build instructions
- Refactored Utils.h with timestamp-based logging output
- Better organized Makefile with improved readability

### Fixed

- Potential memory leaks in video player through RAII patterns
- Missing null checks in string utility functions
- Improved error messages with more context
- FFmpeg API compatibility (ch_layout, swr_alloc_set_opts2)
- Lua 5.1 header includes
- Library linking order for static builds
- SDL_kitchensink CMake minimum version

### Technical

- Added `-fdata-sections` and `-Wl,--gc-sections` for smaller binary size
- Added warning flags (`-Wall`, `-Wextra`) with appropriate suppressions
- Updated min_kernel_version to 0x0 for broader firmware compatibility
- Increased highest_cpu_id from 2 to 3 for better multi-core utilization

## [2.0.0] - 2021-07-05

### Added

- English game support with SJIS encoding option
- Language switching via Plus (+) button in settings

### Fixed

- Fixed crash on firmware 12.0 and above
- Fixed game exit not returning to GUI properly

## [1.1.0] - 2019-10-03

### Fixed

- Fixed launcher crash when fewer than 5 games are installed
- Fixed save data corruption for some games

## [1.0.0] - 2019-09-XX

### Added

- Initial release of ONScripter-jh for Nintendo Switch
- Based on ONScripter-jh version 0.7.6
- SDL2 rendering support
- Video playback via SDL_kitchensink/FFmpeg
- Chinese (GBK) and Japanese (SJIS) encoding support
- OGG Vorbis audio support
- Lua scripting support
- ARM NEON SIMD optimizations
- ONSBrowser GUI launcher

### Features

- Full ONScripter script compatibility
- Save/Load functionality
- Fullscreen and windowed modes
- Font outline rendering
- Touch screen support
- Joy-Con controller support

---

## Version History Summary

| Version | Date       | Highlights                                         |
| ------- | ---------- | -------------------------------------------------- |
| 2.3.0   | 2025-01-06 | GLES renderer with CAS sharpening                  |
| 2.2.0   | 2025-01-15 | OnscripterYuri merge: UTF-8, resolution, sharpness |
| 2.1.0   | 2025-01-15 | C++17, improved logging, modernized codebase       |
| 2.0.0   | 2021-07-05 | English support, FW 12.0+ compatibility            |
| 1.1.0   | 2019-10-03 | Bug fixes for launcher and save data               |
| 1.0.0   | 2019-09    | Initial release                                    |

---

## Upstream Projects

- **ONScripter** by Ogapee - https://github.com/ogapee/onscripter
- **ONScripter-jh** by jh10001 - Original enhanced fork
- **OnscripterYuri** by YuriSizuku - https://github.com/YuriSizuku/OnscripterYuri

## Contributors

- **Ogapee** (ogapee@aqua.dti2.ne.jp) - Original ONScripter author
- **jh10001** (jh10001@live.cn) - ONScripter-jh maintainer
- **YuriSizuku** (https://github.com/YuriSizuku) - OnscripterYuri author
- **wetor** (makisehoshimi@163.com) - Nintendo Switch port

## License

This project is licensed under the GNU General Public License v2.0.
See the [COPYING](COPYING) file for details.
