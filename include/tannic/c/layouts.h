// Copyright 2026 Eric Hermosis
//
// This file is part of the Blazar Tensor Library.
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
#ifndef LAYOUTS_H_0x45524943
#define LAYOUTS_H_0x45524943 
#define DIMENSIONS_0x45524943 8  
#ifdef __cplusplus
#include <cstdint>
#include <cstddef> 
namespace tannic {
#else 
#include <stdint.h>
#include <stddef.h>
#endif 
   
struct shape_t { 
    union {
        int64_t sizes[DIMENSIONS_0x45524943];
        const int64_t* address;
    };
};

struct strides_t { 
    union {
        int64_t sizes[DIMENSIONS_0x45524943];
        const int64_t* address;
    };
};  

struct layout_t {
    uint8_t rank;
    int64_t size;
    shape_t shape;
    strides_t strides;
};
  
#ifdef __cplusplus 
}
#endif 
#endif // LAYOUT_H_0x45524943