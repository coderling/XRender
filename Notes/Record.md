# 记录

## windows生成vs工程，使用devenvbuild，并进行profile

* 要profile Rlease才会比较准确，关闭编译器优化，编译链接是生成pdb调试文件

* 考虑clang-cl编译，vscode分析调试

* Bresenham 优化

    * 减少计算量

    * 去浮点运算

* 模型格式： [wavefront obj file](https://en.wikipedia.org/wiki/Wavefront_.obj_file)

* 通过扫描三角形包围盒进行三角形绘制

    * 通过叉乘求某个点p得重心坐标