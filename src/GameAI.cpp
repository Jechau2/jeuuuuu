#include "GameAI.h"

#include <array>
#include <cstdio>
#include <string>

namespace {
std::string escapeQuotes(const std::string &in) {
    std::string out;
    out.reserve(in.size());
    for (char c : in) {
        if (c == '"') out += '\\';
        out += c;
    }
    return out;
}
}

GameAI::GameAI(const std::string &script) : scriptPath(script) {}

std::string GameAI::generateObject(const std::string &prompt) {
    std::string cmd = "python3 \"" + scriptPath + "\" \"" + escapeQuotes(prompt) + "\"";

    std::array<char, 128> buffer{};
    std::string result;
    FILE *pipe = popen(cmd.c_str(), "r");
    if (!pipe)
        return "Error: cannot run Python script";
    while (fgets(buffer.data(), buffer.size(), pipe)) {
        result += buffer.data();
    }
    int rc = pclose(pipe);
    if (rc != 0)
        return "Error: Python script failed";
    if (!result.empty() && result.back() == '\n')
        result.pop_back();
    return result;
}
