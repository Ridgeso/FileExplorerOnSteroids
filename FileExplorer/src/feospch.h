#pragma once

#include <iostream>
#include <cstdio>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <filesystem>

#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <array>

#include "FileExplorer/Core/Base.h"
#include "FileExplorer/Core/Log.h"
#include "FileExplorer/Core/Assert.h"

#ifdef FILE_EXPLORER_WINDOWS_PLATFOMR
    #include <windows.h>
#endif