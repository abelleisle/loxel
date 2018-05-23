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
                : filename(filename)
            {}

            virtual const char* what() const throw()
            {
                return "File not found!";
            }

        private:
           std::string filename;
    };
}

#endif // SCRIPT_EXCEPTION_HPP
