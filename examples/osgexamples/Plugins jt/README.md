# 插件：osgdb_jt

### 简介
链接 jt_toolkit.dll 解码JT格式，产生 osgdb_jt 插件，使得 osg 可以浏览 JT格式文件。

#### 用法
osg为OpenSceneGraph-3.6.5官方源码编译，只有osgdb_jt为新增编译文件。

当 osgDB::readNodeFile(fileName) 遇到后缀为jt格式的文件时，会自动以osgdb_jt的形式去寻找插件，所以在osg源码部分没有任何修改。

osgdb_jt 仅依赖 jt_toolkit.dll, libdxjt.dll, zlib.dll, liblzma.dll 四个DLL。

用法举例：比如 osgviewer Control_Cabinet_assm.jt
