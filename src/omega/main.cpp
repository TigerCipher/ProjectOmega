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

#include <spdlog/spdlog.h>

int main(int argc, char** argv)
{
    std::cout << "Hello World!\n";
    fmt::print("Hello!\n");
    auto* game = new omega::game();
    if (!game->initialize())
    {
        std::cerr << "Something went wrong!\n";
        return -1;
    }
    game->run();

    game->shutdown();

    delete game;
    return 0;
}
