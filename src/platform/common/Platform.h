#pragma once
#include <string>
#include <memory>

#include "../../RenderTarget.h"

std::unique_ptr<XRender::RenderTarget> CreateRenderTarget(const std::string& name);