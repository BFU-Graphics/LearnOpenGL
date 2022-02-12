#include "world.h"
#include "shader.h"
#include "model.h"

#include <iostream>

int main()
{
    HelloModel::Shader shader("common_model.vert", "common_model.frag");
    HelloModel::Model model("sphere.obj");
    HelloModel::World world;

    model.shader_ = &shader;
    world.add_model(&model);
    world.render_loop();
    return 0;
}
