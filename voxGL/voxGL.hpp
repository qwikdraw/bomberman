#ifndef VOXGL_HPP
#define VOXGL_HPP

#define GLFW_INCLUDE_GLCOREARB

#include <GLFW/glfw3.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <regex>
#include <algorithm>
#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>
#include <chrono>

#include "Time.class.hpp"
#include "Window.class.hpp"
#include "ShadingProgram.class.hpp"
#include "VoxelChunk.class.hpp"
#include "VoxObject.class.hpp"
#include "VoxRenderer.class.hpp"
#include "Camera.class.hpp"

#define X_DIM 800
#define Y_DIM 600
#define NAME "Window Name"
#define VOXEL_VERTEX_SHADER_PATH "../voxGL/vertex.glsl"
#define VOXEL_FRAGMENT_SHADER_PATH "../voxGL/frag.glsl"

#endif
