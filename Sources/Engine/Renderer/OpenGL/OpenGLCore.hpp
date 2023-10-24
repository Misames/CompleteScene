#pragma once

#include <cstdint>

enum BufferType
{
    VBO,
    IBO,
    MAX
};

uint32_t CreateBufferObject(BufferType type, const size_t size, const void *data);

void DeleteBufferObject(uint32_t &BO);

uint32_t CreateTextureRGBA(const uint32_t width, const uint32_t height, const void *data, bool enableMipmaps = false);