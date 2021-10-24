# jt_toolkit

解析JT格式文件。

### 简介

在设计上分二层，其中 libdxjt.dll 贴近JT格式解码，而 jt_toolkit 则类比 JTOpen Toolkit 转换类似的组织形式。

个人作品，底层实现 **libdxjt** 和 **jt_toolkit** 不开源，仅演示基于它们的用法与案例。

jt_toolkit 依赖：
- zlib.dll
- liblzma.dll

代码层面，仅依赖标准库与boost。

### 功能特性
- 支持读取 JT 8.0 - JT 10.5格式，但仅限于 LSG Scene 与 RangeLOD显示
- 支持 JT 8.1 格式的写入，当前测试仅部件形式在 Jt2Go 里可以打开
- 不支持解析 JT BREP Segment，更没法解析 XT BREP Segment
- 暂时没有多线程读取能力，也并不应用延迟加载


### TODO
- 分析并修复 JT10版本里的 Move-to-Front 解码问题 (里边会出现-1，没法确定此时应对应哪一个值)
- 了解 JT格式里 JT_PROP_NAME 的构件规则，确保带有Instance的装配可以正确写入


### 参考资源
- JT-v8.1_File_Format_Reference.PDF
- JT-v95_File_Format_Reference_Rev-D.pdf
- ISO14306-2012 Industrial automation systems and integration - JT file format specification for 3D visualization
- ISO14306-2017 Industrial automation systems and integration - JT file format specification for 3D visualization
- JT-V10.5 Format Description and annexs 10292019_tcm27-58011.pdf
