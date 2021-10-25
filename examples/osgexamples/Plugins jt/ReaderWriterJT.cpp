//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2019 by bitbybit3d, All rights reserved. 
// Author: bitbybit3d@163.com 
// 
// 
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, 
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
//////////////////////////////////////////////////////////////////////////////
#include <osg/Notify>
#include <osg/Geode>
#include <osg/Geometry>

#include <osgDB/FileNameUtils>
#include <osgDB/FileUtils>
#include <osgDB/fstream>
#include <osgDB/Registry>
#include <osgUtil/SmoothingVisitor>

#include <cassert>

// in load_jt.cpp file
extern osg::Node* load_jt (const wchar_t *filename, const osgDB::ReaderWriter::Options* options);

class ReaderWriterJT : public osgDB::ReaderWriter
{
public:
    ReaderWriterJT() {
        supportsExtension("jt", "jt file format");
    }

    virtual const char* className() {
        return "JT File Reader";
    }

    virtual ReadResult readNode(const std::string& filename, const osgDB::ReaderWriter::Options* options) const;
};

REGISTER_OSGPLUGIN(jt, ReaderWriterJT)

osgDB::ReaderWriter::ReadResult ReaderWriterJT::readNode(const std::string& fname, const osgDB::ReaderWriter::Options* options) const
{
    std::string ext = osgDB::getLowerCaseFileExtension(fname);
    if (!acceptsExtension(ext)) return ReadResult::FILE_NOT_HANDLED;

    std::string fileName = osgDB::findDataFile( fname, options );
    if (fileName.empty()) return ReadResult::FILE_NOT_FOUND;

    OSG_INFO << "ReaderWriterSTL::readNode(" << fileName.c_str() << ")" << std::endl;

    wchar_t buf_wstr[_MAX_PATH];
    size_t numConverted = 0;
    size_t flen = fileName.size();

    mbstowcs_s(&numConverted, buf_wstr, _MAX_PATH, fileName.c_str(), flen);
    return load_jt(buf_wstr, options);
}
