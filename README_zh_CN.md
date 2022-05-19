# jt_toolkit

Author: bitbybit3d@163.com

jt_toolkit 以C++ API形式，提供以下能力：
- 读取 JT 8.0 - JT 10.5格式 (限于LSG Segment、RangeLOD、Properties、Attributes等)
- 以 JT8.1 个数输出至 JT 文件  (不带Instance的部件可以在Jt2Go正常打开)


# 简介
个人作品，底层实现 **libdxjt** 和 **jt_toolkit** 不开源，仅开源用法与演示案例。

**libdxjt.dll** 为贴近JT格式解析文件内容，而 **jt_toolkit** 则类比 JTOpen Toolkit 转换成类似的装配组织结构。

jt_toolkit 依赖 libdxjt.dll，而 libdxjt.dll 依赖 zlib.dll 和 liblzma.dll。


## 示例

### examples/traverse
以控制台形式，打开JT文件，遍历查询它的内容

### examples/osgexamples
项目 **Plugins jt** 系为OSG定制的可以读取JT文件的插件，将产生 osgdb_jtd.dll，若编译成功，会自动拷贝至 OSG 目录，但前提是
OSG_DIR 变量有定义。

项目 osgviewer_jt 仅为方便加载 jt文件用于测试。


## TODO
- 分析并修复 JT10版本里的 Move-to-Front 解码问题 (里边会出现-1，目前没有研究清楚此时取对应的哪一个值，会导致部分JT10的文件显示不正常)
- 支持多线程加载
- 增加 Primitive Set 解析
- 了解 JT格式里 JT_PROP_NAME 的构件规则，确保带有Instance的装配可以正确写入(只影响JT格式写出)


# 参考资源
- JT-v8.1_File_Format_Reference.PDF
- JT-v95_File_Format_Reference_Rev-D.pdf
- ISO14306-2012 Industrial automation systems and integration - JT file format specification for 3D visualization
- ISO14306-2017 Industrial automation systems and integration - JT file format specification for 3D visualization
- JT-V10.5 Format Description and annexs 10292019_tcm27-58011.pdf
