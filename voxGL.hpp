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
#define NAME "voxGL"
#define VERTEX_PATH "vertex.glsl"
#define FRAG_PATH "frag.glsl"

#endif
