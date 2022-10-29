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
// File Name: logger.cpp
// Date File Created: 10/28/2022
// Author: Matt
//
// ------------------------------------------------------------------------------

#include "logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace omega
{
sptr<spdlog::logger> logger::s_logger;

void logger::init()
{
    spdlog::set_pattern("%^[%T] [%n] [%l] %v%$");
    s_logger = spdlog::stdout_color_mt("Project Omega");
    s_logger->set_level(spdlog::level::trace);
}

} // namespace omega