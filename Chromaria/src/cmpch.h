#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>

#include "Chromaria/Core/Log.h"
#include "Chromaria/Debug/Instrumentor.h"

#ifdef CM_PLATFORM_WINDOWS
	#include <Windows.h>
#endif