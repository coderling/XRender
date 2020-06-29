#include "IO.h"

std::string XRender::Res::FileExtendName(const std::string &path)
{
    auto const pos_index = path.find_last_of(".");
    std::string ext;
    ext.clear();
    if (pos_index != std::string::npos)
    {
        ext = path.substr(pos_index + 1);
    }
    return ext;
}