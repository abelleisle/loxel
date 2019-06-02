#include <script/script.hpp>

namespace Script
{
    std::string tabs(int amt) {
        std::string tmp;
        for (int i = 0; i < amt; i++)
            tmp += "    ";
        return tmp;
    }

    std::string printValue(std::string name, LuaRef value, int depth)
    {
        std::string output;

        if (value.isNil())
            return output;

        output += tabs(depth) + name + " = ";

        // TABLE //
        if (value.isTable()) {
            depth += 1;
            output += "{\n";
            for (auto &&p : pairs(value)) {
                output += printValue(p.first.cast<std::string>(), p.second, depth) + ",\n";
            }
            output += tabs(depth-1) + "}";
        // STRING //
        } else if (value.isString()) {
            output += "\"" + value.cast<std::string>() + "\"";
        // NUMBER //
        } else if (value.isNumber()) {
            output += value.cast<std::string>();
        // BOOLEAN //
        } else if (value.isBool()) {
            output += value.cast<bool>() ? 
                "true" :
                "false";
        }

        return output;
    }
}
