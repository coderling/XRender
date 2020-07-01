#include "Pipeline.h"
#include <vector>

namespace XRender::Test
{
    class TestPipeline: public Pipeline
    {
    public:
        ~TestPipeline() override {}
        void PreRender() override {}
        void Render() override
        {
            std::vector<Renderer*> renderers = Cull::GlobalCull().CullRenderers(Camera::MainCamera(), scene.get());
            DrawRenderers(renderers);
        }

        void PostRender() override {}
    };
}
