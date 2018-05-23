#ifndef CONFIG_HPP
#define CONFIG_HPP
#include <script/script.hpp>

#include <string>
#include <unordered_map>
#include <experimental/any>

class Configuration
{
    private:
        Script script;
        std::string configFile;
		std::unordered_map<std::string, std::experimental::any> configItems;
    public:
        Configuration();
        Configuration(std::string);
       ~Configuration();

        void loadfile(std::string);
		bool addItem(std::string, std::experimental::any);
        bool addItem(std::string);
        bool setItem(std::string, std::experimental::any);
		std::experimental::any getItem(std::string);

        void readConfig();
        void createfile(std::string);
};

#endif // CONFIG_HPP
