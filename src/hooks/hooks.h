#include <MinHook.h>

#include "Smith/Smith.h"

namespace Hooks {
    void Install() { 
        MH_Initialize();

        Smith::Install();

        MH_EnableHook(MH_ALL_HOOKS);
        return;
    }
}