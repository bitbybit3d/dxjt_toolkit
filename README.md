# dxjt_toolkit

Author: bitbybit3d@163.com

dxjt_toolkit is a C++ API library, it provides applications with the capablity to:
- read a JT file (JT 8.0 - JT 10.5 format)
- write to a JT file (saved as JT 8.1 format)


# Overview
Personal works, the code for **libdxjt** and **dxjt_toolkit** is not free, only open source about usage and demonstration cases.

**libdxjt.dll** is used to parse JT format from file content, while **dxjt_toolkit** will create a similar assembly organization 
structure like JtOpen Toolkit do.

dxjt_toolkit relies on libdxjt.dll, while libdxjt.dll relies on zlib.dll and liblzma.dll


## 示例

### examples/traverse
A example for read JT file.


### examples/osgexamples
**Plugins jt** is a plugin for openscenegraph to read a JT file.


## Change Log
- Add prefix Dx to all types of interface Header file
- fix the Move-to-Front decodec problem in JT 10 version. 


### TODO
- support multi-threaded loading


# References
- JT-v8.1_File_Format_Reference.PDF
- JT-v95_File_Format_Reference_Rev-D.pdf
- ISO14306-2012 Industrial automation systems and integration - JT file format specification for 3D visualization
- ISO14306-2017 Industrial automation systems and integration - JT file format specification for 3D visualization
- JT-V10.5 Format Description and annexs 10292019_tcm27-58011.pdf
