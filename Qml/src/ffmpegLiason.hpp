#include <string>

// Just some sequence of characters unlikely to be in a filepath
// And also not meaningful to regex
#define REPLACEMENT_CHAR "XZX"

FILE* runFFmpeg(const std::string& args, bool ffprobe = false, bool forceQuiet = false);
