# 记录


## feature

* frustum culling

    * [1](https://www.gamedev.net/articles/programming/general-and-gameplay-programming/frustum-culling-r4613/)

    * [2](http://www.lighthouse3d.com/tutorials/view-frustum-culling/)

* back culling

* texture mapping

* multi Lighting

* shadow map

* animation

* windows生成vs工程，使用devenvbuild，并进行profile

* 要profile Rlease才会比较准确，关闭编译器优化，编译链接是生成pdb调试文件

* 考虑clang-cl编译，vscode分析调试

* Bresenham 优化

    * 减少计算量

    * 去浮点运算

* 模型格式： [wavefront obj file](https://en.wikipedia.org/wiki/Wavefront_.obj_file)

* 通过扫描三角形包围盒进行三角形绘制

    * 通过叉乘求某个点p得重心坐标, 投影后的重心坐标不是线性的了，但是倒数是线性的，可以反推出view空间下中重心坐标，定点属性插值需要使用View空间下的重心坐标
        * [1](https://www.scratchapixel.com/lessons/3d-basic-rendering/rasterization-practical-implementation/rasterization-stage)
        * [2](https://zhuanlan.zhihu.com/p/134912873)
        * [3](https://zhuanlan.zhihu.com/p/65495373)

* backface cull
    * https://www.khronos.org/registry/OpenGL/specs/es/2.0/es_full_spec_2.0.pdf 3.5.1
    * https://dev.gameres.com/Program/Abstract/Geometry.htm#%E7%9F%A2%E9%87%8F%E5%8F%89%E7%A7%AF

* CVV裁剪
    * https://www.zhihu.com/question/64675018
    * https://zhuanlan.zhihu.com/p/102758967
    * https://en.wikipedia.org/wiki/Sutherland%E2%80%93Hodgman_algorithm
    * https://www.gamasutra.com/view/news/168577/Indepth_Software_rasterizer_and_triangle_clipping.php
    * https://zhuanlan.zhihu.com/p/162190576

* ShadowMap
    * [1](https://learnopengl-cn.readthedocs.io/zh/latest/05%20Advanced%20Lighting/03%20Shadows/01%20Shadow%20Mapping/)
    * [2](http://www.opengl-tutorial.org/cn/intermediate-tutorials/tutorial-16-shadow-mapping/)