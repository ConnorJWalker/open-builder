#pragma once

#include <common/world/voxel_data.h>
#include <glad/glad.h>

struct ClientVoxel {
    int id;
    std::string name;
    GLuint topTexture = 0;
    GLuint sideTexture = 0;
    GLuint bottomTexture = 0;

    VoxelMeshStyle meshStyle = VoxelMeshStyle::Error;
    VoxelType type = VoxelType::Error;

    bool isCollidable = true;
};
