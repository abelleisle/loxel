#ifndef SCRIPT_EXCEPTION_HPP
#define SCRIPT_EXCEPTION_HPP

#include <exception>
#include <stdexcept>
#include <string>

namespace ScriptException
{
    class FileNotFound : public std::exception
    {
        public:
            FileNotFound()
            {};
            
            FileNotFound(std::string filename)
            {
                message = std::string("File not found: " + filename);
            };

            const char* what() const throw()
            {
                return message.c_str();
            }

        private:
           std::string message;
    };
}

#endif // SCRIPT_EXCEPTION_HPP
