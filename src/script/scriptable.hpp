#ifndef SCRIPTABLE_HPP
#define SCRIPTABLE_HPP

class Script;

class Scriptable
{
    protected:
        Script* script;
    public:
        Scriptable();

        virtual void registerScript() = 0;
};

#endif //SCRIPTABLE_HPP
