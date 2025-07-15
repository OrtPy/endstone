// Copyright (c) 2024, The Endstone Project. (https://endstone.dev) All Rights Reserved.
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

#pragma once

#include <memory>
#include <optional>
#include <cmath>  // ★ 追加

#include "endstone/util/vector.h"

namespace endstone {

class Level;
class Dimension;

/**
 * @brief Represents a 3-dimensional position in a dimension within a level.
 */
class Position : public Vector<float> {
public:
    Position(Dimension *dimension, float x, float y, float z) : Vector(x, y, z), dimension_(dimension) {}

    /**
     * Gets the dimension that this position resides in
     *
     * @return Dimension that contains this position, or nullptr if the dimension is not set.
     */
    [[nodiscard]] Dimension *getDimension() const
    {
        return dimension_;
    }

    /**
     * Sets the dimension that this position resides in
     *
     * @param dimension New dimension that this position resides in
     */
    void setDimension(Dimension &dimension)
    {
        dimension_ = &dimension;
    }

    /**
     * @brief Gets the floored value of the X component, indicating the block that this location is contained with.
     *
     * @return block X
     */
    [[nodiscard]] int getBlockX() const
    {
        return static_cast<int>(std::floor(x_));  // ★ 修正
    }

    /**
     * @brief Gets the floored value of the Y component, indicating the block that this location is contained with.
     *
     * @return block Y
     */
    [[nodiscard]] int getBlockY() const
    {
        return static_cast<int>(std::floor(y_));  // ★ 修正
    }

    /**
     * @brief Gets the floored value of the Z component, indicating the block that this location is contained with.
     *
     * @return block Z
     */
    [[nodiscard]] int getBlockZ() const
    {
        return static_cast<int>(std::floor(z_));  // ★ 修正
    }

private:
    Dimension *dimension_;
};

}  // namespace endstone
