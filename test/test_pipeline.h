#include "Pipeline.h"
#include <vector>

namespace XRender::Test
{
    class TestPipeline: public Pipeline
    {
    public:
        ~TestPipeline() override {}
        void PreRender(Camera* camera) override {}
        void Render(Camera* camera) override
        {
            std::vector<Renderer*> renderers = Cull::GlobalCull().CullRenderers(camera, scene.get());
            DrawRenderers(renderers, camera);
        }

        void PostRender(Camera* camera) override {

        }
    };
}
