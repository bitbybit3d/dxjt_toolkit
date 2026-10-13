# dxjt_toolkit

Author: bitbybit3d@163.com

dxjt_toolkit 以C++ API形式，提供以下能力：
- 读取 JT 8.0 - JT 10.5格式 (限于LSG Segment、RangeLOD、Properties、Attributes等)
- 以 JT8.1 个数输出至 JT 文件  (不带Instance的部件可以在Jt2Go正常打开)


# 简介
个人作品，底层实现 **libdxjt** 和 **dxjt_toolkit** 不开源，仅开源用法与演示案例。

**libdxjt.dll** 为贴近JT格式解析文件内容，而 **dxjt_toolkit** 则类比 JTOpen Toolkit 转换成类似的装配组织结构。

dxjt_toolkit 依赖 libdxjt.dll，而 libdxjt.dll 依赖 zlib.dll 和 liblzma.dll。

项目状态：核心功能可用。本库尚未经过大规模生产测试，在关键业务流程使用前，请务必自行充分验证。

## 示例

### examples/traverse
以控制台形式，打开JT文件，遍历查询它的内容

### examples/osgexamples
项目 **Plugins jt** 系为OSG定制的可以读取JT文件的插件，将产生 osgdb_jtd.dll，若编译成功，会自动拷贝至 OSG 目录，但前提是
OSG_DIR 变量有定义。

项目 osgviewer_jt 仅为方便加载 jt文件用于测试。

### JtMFCViewer
未提供源码，在发行版处可以找到，但其实只是 OpenSceneGraph 内的 MFC 范例，额外添加 osgdb_jt.dll 插件用于读取JT文件而已。


## 重要建议
在 DxJtShape 类，建议采用 getTriangles() 接口一次获取该shape所包含的所有网格数据


## Change Log
- 2026/09/04 在 libdximpjt 里改为静态链接 zlib 和 liblzma，从而不再依赖 zlib.dll and liblzma.dll
- 2023/06/15 将接口头文件各类，加前缀 Dx，目的是为了加大与 JtOpen 头文件的区分度
- 2023/06/15 解决 JT10 版本里边的 Move-to-Front 解码问题


### TODO
- 支持多线程加载
- 增加 Primitive Set 解析
- 了解 JT格式里 JT_PROP_NAME 的构件规则，确保带有Instance的装配可以正确写入(只影响JT格式写出)


# 参考资源
- JT-v8.1_File_Format_Reference.PDF
- JT-v95_File_Format_Reference_Rev-D.pdf
- ISO14306-2012 Industrial automation systems and integration - JT file format specification for 3D visualization
- ISO14306-2017 Industrial automation systems and integration - JT file format specification for 3D visualization
- JT-V10.5 Format Description and annexs 10292019_tcm27-58011.pdf
