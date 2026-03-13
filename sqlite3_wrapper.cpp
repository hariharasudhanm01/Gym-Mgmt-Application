// SQLite3 wrapper - compiles sqlite3 as C code wrapped for C++
extern "C" {
#define SQLITE_AMALGAMATION 1
#define SQLITE_OS_WIN 0
#define SQLITE_ENABLE_STAT3 0
#define SQLITE_ENABLE_UNLOCK_NOTIFY 0
#undef _WIN32_WINNT
#include "libs/sqlite/sqlite3.c"
}

