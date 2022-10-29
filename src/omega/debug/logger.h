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
// File Name: logger.h
// Date File Created: 10/28/2022
// Author: Matt
//
// ------------------------------------------------------------------------------

#pragma once

#include "omega/core/types.h"

#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace omega
{

class logger
{
public:
    static void init();

    static sptr<spdlog::logger>& get_logger() { return s_logger; }
private:
    static sptr<spdlog::logger> s_logger;
};

} // namespace omega


#define OTRACE(...) omega::logger::get_logger()->trace(__VA_ARGS__)
#define OINFO(...) omega::logger::get_logger()->info(__VA_ARGS__)
#define OWARN(...) omega::logger::get_logger()->warn(__VA_ARGS__)
#define OERROR(...) omega::logger::get_logger()->error(__VA_ARGS__)
#define OFATAL(...) omega::logger::get_logger()->critical(__VA_ARGS__)
