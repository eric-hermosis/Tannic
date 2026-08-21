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
#ifndef LAYOUTS_HPP_0x45524943
#define LAYOUTS_HPP_0x45524943

#include <cstdint>
#include <cstddef> 
#include <tannic/exceptions.hpp>

namespace tannic {

template<typename Type>
concept Iterable = requires(Type type) { std::begin(type); std::end(type); };   

template <typename Type>
concept Iterator = std::input_iterator<Type>;  

template<typename Type>
concept Integral = std::integral<Type>; 

using rank_type  = std::uint8_t;  
using size_type  = std::int64_t;
using index_type = std::int64_t; 

struct range_type {
    index_type start = 0;
    index_type stop  = -1;
}; 

constexpr auto normalize(index_type index, size_type bound) -> index_type {
    if (index < 0) {
        index += bound;
    }

    if (index < 0 || index > bound) {
        throw Exception("Index out of bounds");
    }
    
    return index;
}   
 
constexpr auto normalize(range_type range, size_type bound) -> range_type {
    index_type start = range.start < 0 ? bound + range.start : range.start;
    index_type stop  = range.stop  < 0 ? bound + range.stop  : range.stop; 

    if (start < 0 || start > bound || stop < 0 || stop > bound) {
        throw Exception("Range out of bounds");
    }
    return {.start=start, .stop=stop};
}

class Shape {
public:  
    static constexpr uint8_t limit = 8;    
    
    constexpr Shape() noexcept = default;
 
    template<Integral... Sizes>
    constexpr Shape(Sizes... sizes)
    :   size_(sizeof...(Sizes)) {
        static_assert(sizeof...(Sizes) <= limit, "Shape rank exceeds limit."); 
        size_type dimension = 0;  
        template for (auto size : std::tuple{sizes...}) {
            if constexpr (std::is_signed_v<decltype(size)>) {
                if (size < -1) {
                    throw Exception(
                        "Invalid size for dimension " + std::to_string(dimension) +
                        ": " + std::to_string(size) +
                        ". Size must be >= -1."
                    );
                }
            } 
            sizes_[dimension++] = static_cast<size_type>(size);
        }
    }

    template<Integral Size>
    constexpr Shape(std::initializer_list<Size> shape) {
        const auto dimensions = shape.size();

        if (dimensions > limit) {
            throw Exception(
                "Shape rank " + std::to_string(dimensions) +
                " exceeds limit of " + std::to_string(limit)
            );
        }

        size_ = static_cast<rank_type>(dimensions);

        size_type dimension = 0;

        for (auto size : shape) {
            if constexpr (std::is_signed_v<Size>) {
                if (size < -1) {
                    throw Exception(
                        "Invalid size for dimension " + std::to_string(dimension) +
                        ": " + std::to_string(size) +
                        ". Size must be >= -1."
                    );
                }
            }

            sizes_[dimension++] = static_cast<size_type>(size);
        }
    } 
        
    template<Iterable Sizes>
    constexpr Shape(Sizes&& sizes) {
        size_type dimension = 0;

        for (auto size : sizes) {
            if (dimension >= limit) {
                throw Exception(
                    "Shape rank exceeds limit of " + std::to_string(limit)
                );
            }

            if constexpr (std::is_signed_v<std::decay_t<decltype(size)>>) {
                if (size < -1) {
                    throw Exception(
                        "Invalid size for dimension " + std::to_string(dimension) +
                        ": " + std::to_string(size) +
                        ". Size must be >= -1."
                    );
                }
            }

            sizes_[dimension++] = static_cast<size_type>(size);
        }

        size_ = dimension;
    }


    template<Iterator Iterator>
    constexpr Shape(Iterator begin, Iterator end) {
        size_type dimension = 0;

        for (Iterator iterator = begin; iterator != end; ++iterator) {
            if (dimension >= limit) {
                throw Exception(
                    "Shape rank exceeds limit of " + std::to_string(limit)
                );
            }

            auto size = *iterator;

            if constexpr (std::is_signed_v<std::decay_t<decltype(size)>>) {
                if (size < -1) {
                    throw Exception(
                        "Invalid size for dimension " + std::to_string(dimension) +
                        ": " + std::to_string(size) +
                        ". Size must be >= -1."
                    );
                }
            }

            sizes_[dimension++] = static_cast<size_type>(size);
        }

        size_ = dimension;
    }

    [[nodiscard]] constexpr auto address() noexcept -> size_type* {
        return sizes_.data();
    }

    [[nodiscard]] constexpr auto address() const noexcept ->  size_type const* {
        return sizes_.data();
    }
    
    [[nodiscard]] constexpr auto size() const noexcept -> rank_type { 
        return size_; 
    }
    
    [[nodiscard]] constexpr auto begin() { 
        return sizes_.begin(); 
    }
     
    [[nodiscard]] constexpr auto end() { 
        return std::next(sizes_.begin(), size_);
    }
 
    [[nodiscard]] constexpr auto begin() const { 
        return sizes_.begin(); 
    }  

    [[nodiscard]] constexpr auto end() const { 
        return std::next(sizes_.begin(), size_); 
    } 
 
    [[nodiscard]] constexpr auto cbegin() const { 
        return sizes_.cbegin(); 
    }
     
    [[nodiscard]] constexpr auto cend() const { 
        return std::next(sizes_.cbegin(), size_); 
    }
    
    [[nodiscard]] constexpr auto front() const { 
        if (size_ == 0) {
            throw Exception("Cannot call front() on an empty Shape");
        }
        return sizes_.front(); 
    }
    
    [[nodiscard]] constexpr auto back() const { 
        if (size_ == 0) {
            throw Exception("Cannot call back() on an empty Shape");  
        }
        return sizes_[size_-1];
    }       

    template<Integral Index>
    [[nodiscard]] constexpr auto operator[](Index index) const -> size_type const&{ 
        return sizes_[normalize(index, size())]; 
    }
    
    template<Integral Index>
    constexpr auto operator[](Index index) -> size_type& {
        return sizes_[normalize(index, size())]; 
    } 

    constexpr void append(size_type size) { 
        if (size_ + 1 > limit) {
            throw Exception(
                "Shape dimensions " + std::to_string(size_) + 
                " exceeds limit of " + std::to_string(limit)
            );
        }  

        if (size < -1) {
            throw Exception(
                "Invalid size for dimension " + std::to_string(size_) +
                ": " + std::to_string(size) +
                ". Size must be >= -1."
            );
        }

        sizes_[size_++] = size;
    }

    constexpr void resize(rank_type dimensions) {
        if (dimensions > limit) {
            throw Exception(
                "Shape dimensions limit exceeded: rank is " + std::to_string(size_) +
                ", but the maximum allowed is " + std::to_string(limit)
            );
        }

        if (dimensions > size_) {
            std::fill(sizes_.begin() + size_, sizes_.begin() + dimensions, 0);
        }
        size_ = dimensions; 
    } 
     
    constexpr auto operator==(Shape const& other) const -> bool {

        if (size() != other.size_) {
            return false;
        }

        for (auto dimension = 0; dimension < size_; ++dimension) {
            if (sizes_[dimension] != other.sizes_[dimension]) {
                return false;
            }
        }
    
        return true;
    }

private:
    rank_type size_{0};      
    std::array<size_type, limit> sizes_{}; 
}; 
 
class Strides {
public:  
    static constexpr uint8_t limit = 8;    

    constexpr Strides() noexcept = default;  

    template<Integral... Sizes>
    constexpr Strides(Sizes... sizes) 
    :   size_(sizeof...(Sizes)) 
    {
        static_assert(sizeof...(Sizes) <= limit, "Strides rank exceeds limit.");
        size_type dimension = 0;  
        template for (auto size : std::tuple{sizes...}) {
            if constexpr (std::is_signed_v<decltype(size)>) {
                if (size < -1) {
                    throw Exception(
                        "Invalid size for dimension " + std::to_string(dimension) +
                        ": " + std::to_string(size) +
                        ". Size must be >= -1."
                    );
                }
            } 
            sizes_[dimension++] = static_cast<size_type>(size);
        }
    }
    
    template<Integral Size>
    constexpr Strides(std::initializer_list<Size> shape)
    {
        const auto dimensions = shape.size();

        if (dimensions > limit) {
            throw Exception(
                "Strides rank " + std::to_string(dimensions) +
                " exceeds limit of " + std::to_string(limit)
            );
        }

        size_ = static_cast<rank_type>(dimensions);

        size_type dimension = 0;

        for (auto size : shape) {
            if constexpr (std::is_signed_v<Size>) {
                if (size < -1) {
                    throw Exception(
                        "Invalid size for dimension " + std::to_string(dimension) +
                        ": " + std::to_string(size) +
                        ". Size must be >= -1."
                    );
                }
            }

            sizes_[dimension++] = static_cast<size_type>(size);
        }
    }
 
    template<Iterator Iterator>
    constexpr Strides(Iterator begin, Iterator end)
    {
        size_type dimension = 0;

        for (Iterator iterator = begin; iterator != end; ++iterator) {
            if (dimension >= limit) {
                throw Exception(
                    "Shape rank exceeds limit of " + std::to_string(limit)
                );
            }

            auto size = *iterator;

            if constexpr (std::is_signed_v<std::decay_t<decltype(size)>>) {
                if (size < -1) {
                    throw Exception(
                        "Invalid size for dimension " + std::to_string(dimension) +
                        ": " + std::to_string(size) +
                        ". Size must be >= -1."
                    );
                }
            }
            sizes_[dimension++] = static_cast<size_type>(size);
        }
        size_ = dimension;
    }
    
    constexpr Strides(const Shape& shape) noexcept
    :   size_(shape.size()) 
    {  
        if (size_ == 0) {
            return;
        }

        sizes_[size_ - 1] = 1;
        for (int size = size_ - 2; size >= 0; --size) {
            sizes_[size] = sizes_[size + 1] * shape[size + 1];
        } 
    }
 
    [[nodiscard]] constexpr auto address() noexcept -> size_type* {
        return sizes_.data();
    }

    [[nodiscard]] constexpr auto address() const noexcept -> size_type const* {
        return sizes_.data();
    }

    [[nodiscard]] constexpr auto size() const noexcept { 
        return size_; 
    } 

    [[nodiscard]] constexpr auto begin() { 
        return sizes_.begin(); 
    }
    
    [[nodiscard]] constexpr auto end() {
        return std::next(sizes_.begin(), size_);
    }

    [[nodiscard]] constexpr auto begin() const { 
        return sizes_.begin(); 
    }
    
    [[nodiscard]] constexpr auto end() const { 
        return std::next(sizes_.begin(), size_);
    }
    
    [[nodiscard]] constexpr auto cbegin() const { 
        return sizes_.cbegin(); 
    }
    
    [[nodiscard]] constexpr auto cend() const { 
        return std::next(sizes_.cbegin(), size_);
    }

    [[nodiscard]] constexpr auto front() const { 
        if (size_ == 0) {
            throw Exception("Cannot call front() on an empty Strides");
        }
        return sizes_.front(); 
    }
    
    [[nodiscard]] constexpr auto back() const { 
        if (size_ == 0) {
            throw Exception("Cannot call back() on an empty Strides");  
        }
        return sizes_[size_-1];
    }       

    template<Integral Index>
    [[nodiscard]] constexpr auto operator[](Index index) const -> size_type const&{ 
        return sizes_[normalize(index, size())]; 
    }
    
    template<Integral Index>
    constexpr auto operator[](Index index) -> size_type& {
        return sizes_[normalize(index, size())]; 
    } 

    constexpr void append(size_type size) { 
        if (size_ + 1 > limit) {
            throw Exception(
                "Strides dimensions " + std::to_string(size_) + 
                " exceeds limit of " + std::to_string(limit)
            );
        }  

        if (size < -1) {
            throw Exception(
                "Invalid size for dimension " + std::to_string(size_) +
                ": " + std::to_string(size) +
                ". Size must be >= -1."
            );
        }

        sizes_[size_++] = size;
    }

    constexpr void resize(rank_type dimensions) {
        if (dimensions > limit) {
            throw Exception(
                "Strides dimensions limit exceeded: rank is " + std::to_string(size_) +
                ", but the maximum allowed is " + std::to_string(limit)
            );
        }

        if (dimensions > size_) {
            std::fill(sizes_.begin() + size_, sizes_.begin() + dimensions, 0);
        }
        size_ = dimensions; 
    }
    
    constexpr auto operator==(Strides const& other) const -> bool {

        if (size_ != other.size_) {
            return false;
        }

        for (auto dimension = 0; dimension < size_; ++dimension) {
            if (sizes_[dimension] != other.sizes_[dimension]) {
                return false;
            }
        }
    
        return true;
    }

private:
    rank_type size_{0};
    std::array<size_type, limit> sizes_{};
}; 

class Layout {  
public:

    constexpr Layout()
    :   size_(1)
    ,   offset_(0) {}

    constexpr Layout(Shape const& shape, index_type offset = 0) 
    :   size_(1)
    ,   offset_(offset)
    ,   shape_(shape) {
        auto rank = shape.size();
        if (rank > 0) {
            strides_.resize(rank);
            for (rank_type dimension = rank; dimension-- > 0; ) {
                strides_[dimension] = size_;
                size_ *= shape[dimension];
            } 
        } 
    }

    constexpr Layout(Shape const& shape, Strides const& strides, index_type offset = 0) 
    :   size_(1)
    ,   offset_(offset)
    ,   shape_(shape)
    ,   strides_(strides) {
        auto rank = shape.size();  
        if (rank > 0) {
            for (rank_type dimension = rank; dimension-- > 0; ) {
                size_ *= shape[dimension];
            } 
        } 
    }

    [[nodiscard]] constexpr auto rank() const -> rank_type {
        return shape_.size();
    }

    [[nodiscard]] constexpr auto size() const -> size_type {
        return size_;
    }

    [[nodiscard]] constexpr auto offset() const -> index_type {
        return offset_;
    }

    [[nodiscard]] constexpr auto shape() const -> Shape const& {
        return shape_;
    }

    [[nodiscard]] constexpr auto strides() const -> Strides const& {
        return strides_;
    }

    [[nodiscard]] constexpr auto size(rank_type dimension) const -> size_type {
        return shape_[dimension];
    }

    [[nodiscard]] constexpr auto stride(rank_type dimension) const -> size_type {
        return strides_[dimension];
    }

    template<typename Tag = void, class... Layouts>
    [[nodiscard]] static constexpr auto infer(Layouts const&... layouts) -> Layout {
        rank_type rank = 0;

        template for (auto const& layout : std::tuple{layouts...}) {
            rank = std::max(rank, layout.rank());
        }

        Shape shape; 
        for (rank_type dimension = 0; dimension < rank; ++dimension) {
            size_type extent = 1;
            template for (auto const& layout : std::tuple{layouts...}) {
                auto offset = rank - layout.rank();
                auto broadcasted = (dimension < offset) ? 1 : layout.size(dimension - offset);

                if (broadcasted != 1) {
                    if (extent != 1 && extent != broadcasted) {
                        throw Exception(
                            "Operands are not broadcast-compatible at dimension " +
                            std::to_string(dimension)
                        );
                    }

                    extent = broadcasted;
                }
            }
            shape.append(extent);
        }
        return Layout(shape);
    }

private:     
    size_type size_;
    index_type offset_;
    Shape shape_;
    Strides strides_;
};  

auto operator<<(std::ostream&, Shape const& shape) -> std::ostream&;
auto operator<<(std::ostream&, Strides const& strides) -> std::ostream&;   

}

#endif