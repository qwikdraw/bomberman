#pragma once

#define GLFW_INCLUDE_GLCOREARB

#include <GLFW/glfw3.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>
#include <entt/entt.hpp>
//#include "../lib/irrlkang/include/irrKlang.h"
#include <irrKlang.h>

#define ASSET_PATH "assets/"

using namespace irrklang;

namespace scripts
{
	typedef std::function<void(entt::DefaultRegistry&, uint32_t)> script;
}
