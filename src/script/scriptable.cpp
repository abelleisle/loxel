#include <script/scriptable.hpp>
#include <game_class.hpp>

Scriptable::Scriptable()
{
    script = GameState::getGlobalScript();
}
