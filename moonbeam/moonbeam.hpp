#ifndef MOONBEAM_HPP
#define MOONBEAM_HPP

#include <moonbeam/dependencies.hpp>

#include <moonbeam/core/exception.hpp>

#include <moonbeam/core/memory/allocator.hpp>
#include <moonbeam/core/memory/linear-allocator.hpp>
#include <moonbeam/core/memory/stack-allocator.hpp>
#include <moonbeam/core/memory/block-list-allocator.hpp>
#include <moonbeam/core/memory/pool-allocator.hpp>
#include <moonbeam/core/memory/proxy-allocator.hpp>

#include <moonbeam/core/container/id-map.hpp>
#include <moonbeam/core/container/fixed-set.hpp>
#include <moonbeam/core/container/fixed-unordered-map.hpp>

#include <moonbeam/core/system.hpp>
#include <moonbeam/core/system-manager.hpp>
#include <moonbeam/core/entity.hpp>
#include <moonbeam/core/entity-manager.hpp>
#include <moonbeam/core/component.hpp>
#include <moonbeam/core/component-manager.hpp>

#include <moonbeam/transform.hpp>

#include <moonbeam/graphics/gl-object.hpp>
#include <moonbeam/graphics/window.hpp>
#include <moonbeam/graphics/buffer.hpp>
#include <moonbeam/graphics/uniform-buffer.hpp>
#include <moonbeam/graphics/shader.hpp>
#include <moonbeam/graphics/draw-shader.hpp>
#include <moonbeam/graphics/compute-shader.hpp>
#include <moonbeam/graphics/texture.hpp>
#include <moonbeam/graphics/texture2d.hpp>
#include <moonbeam/graphics/material.hpp>
#include <moonbeam/graphics/compute-material.hpp>
#include <moonbeam/graphics/vertex.hpp>
#include <moonbeam/graphics/mesh.hpp>
#include <moonbeam/graphics/model.hpp>
#include <moonbeam/graphics/camera.hpp>

#include <moonbeam/graphics/graphic-system.hpp>

#include <moonbeam/moonbeam-engine.hpp>

#endif