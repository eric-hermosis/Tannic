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

#ifndef MEMORY_H_0x45524943
#define MEMORY_H_0x45524943 

#ifdef __cplusplus 
#include <cstddef>    
namespace tannic {
#else 
#include <stddef.h> 
#endif 
  
enum domain {
    HOST,
    DEVICE
};  
  
struct allocator_t { 
    const char* name;
    void* (*allocate)(size_t);
    void (*deallocate)(void*, size_t);
};    

struct buffer_t {
    size_t size;
    void* address;
};

struct memory_t {   
    enum domain domain; 
    struct allocator_t allocator;  
    struct buffer_t buffer; 
}; 

#ifdef __cplusplus  
}
#endif 
#endif