// Copyright 2026 Eric Hermosis
//
// This file is part of the Tannic Tensor Library.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// 
#ifndef EXCEPTIONS_HPP_0x45524943 
#define EXCEPTIONS_HPP_0x45524943 

#include <exception> 
#include <string> 
#include <format>
#include <string_view>
#include <source_location> 

namespace tannic {
    
class Exception : public std::exception {
public: 
    constexpr Exception(std::string message, std::source_location location = std::source_location::current()) 
    :   message_(std::move(message))
    ,   location_(std::move(location)) {}    
    
    [[nodiscard]] constexpr const char* what() const noexcept override { 
        return message_.c_str(); 
    }
  
    [[nodiscard]] constexpr auto where() const noexcept -> const std::source_location& {
        return location_;
    }
    
private:
    std::string message_; 
    std::source_location location_;
};
 
class Error : public std::runtime_error {
public: 
    explicit Error(std::string_view message, std::source_location location = std::source_location::current())
    :   std::runtime_error(
            std::format(
                "[{}:{}] {}: {}", 
                location.file_name(), 
                location.line(), 
                location.function_name(), 
                message
            )
        ) 
    {}
};
     
} 

#endif