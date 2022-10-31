// ------------------------------------------------------------------------------
//
// ProjectOmega
//    Copyright 2022 Matthew Rogers
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
//
// File Name: main.cpp
// Date File Created: 10/21/2022
// Author: Matt
//
// ------------------------------------------------------------------------------

#include <iostream>

#include "omega/core/game.h"


int main(int argc, char** argv)
{
    omega::logger::init();
    std::cout << "Hello World!\n";
    OTRACE("This is a test trace message");
    OINFO("This is just a test message");
    OWARN("This is a test warning");
    OERROR("This is a test error");
    OFATAL("This is a test {} message", "fatal");
    OASSERT(1 > 2, "test {}. {:.5f}", "test2", 5.435435345f);
    auto* game = new omega::game();
    if (!game->initialize())
    {
        OFATAL("Game failed to initialize");
        return -1;
    }
    game->run();

    game->shutdown();

    delete game;
    return 0;
}
