#include "fs.h"

#ifdef _MSC_VER
#include <direct.h>
#define mkdir _mkdir
#endif

#ifdef __linux__
#include <sys/stat.h>
#endif

void fs::makeDir(const std::string &path) {
#ifdef __linux__
	mkdir(path.c_str(), 0755);
#elif defined(WIN32)
	mkdir(path.c_str());
#endif
}
