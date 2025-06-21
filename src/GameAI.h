#ifndef GAMEAI_H
#define GAMEAI_H

#include <string>

/**
 * @brief Wrapper class to request text generation from a Python script running
 * TinyLlama.
 */
class GameAI {
public:
    explicit GameAI(const std::string &script = "../scripts/ai_prompt.py");
    std::string generateObject(const std::string &prompt);

private:
    std::string scriptPath;
};

#endif // GAMEAI_H
