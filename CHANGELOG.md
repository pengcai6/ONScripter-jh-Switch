# Changelog

All notable changes to ONScripter-jh for Nintendo Switch will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

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

| Version | Date       | Highlights                                    |
|---------|------------|-----------------------------------------------|
| 2.1.0   | 2025-01-15 | C++17, improved logging, modernized codebase  |
| 2.0.0   | 2021-07-05 | English support, FW 12.0+ compatibility       |
| 1.1.0   | 2019-10-03 | Bug fixes for launcher and save data          |
| 1.0.0   | 2019-09    | Initial release                               |

---

## Contributors

- **Ogapee** (ogapee@aqua.dti2.ne.jp) - Original ONScripter author
- **jh10001** (jh10001@live.cn) - ONScripter-jh maintainer
- **wetor** (makisehoshimi@163.com) - Nintendo Switch port

## License

This project is licensed under the GNU General Public License v2.0.
See the [COPYING](COPYING) file for details.
