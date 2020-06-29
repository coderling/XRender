#include "Resources.h"

std::unordered_map<std::type_index, std::any> XRender::Res::Resources::loaders = std::unordered_map<std::type_index, std::any>();