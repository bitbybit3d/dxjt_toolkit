//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2019 by bitbybit3d, All rights reserved. 
// Author: bitbybit3d@163.com 
// 
// 
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, 
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
//////////////////////////////////////////////////////////////////////////////
#include <iostream>

#if defined(_WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN64)
#include <windows.h>
#endif

#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/StateSetManipulator>

int to_viewer(const osg::Node* sceneNode)
{
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
    traits->x = 50;
    traits->y = 50;
    traits->width = 640;
    traits->height = 480;
    traits->windowName = "3D File Viewer";
    traits->windowDecoration = true;
    traits->doubleBuffer = true;

    osg::ref_ptr<osg::GraphicsContext> gc =
        osg::GraphicsContext::createGraphicsContext( traits.get() );

    osgViewer::Viewer viewer;

    osg::Camera* camera = viewer.getCamera();

    camera->setGraphicsContext(gc.get());
    camera->setViewport( new osg::Viewport(0, 0, traits->width, traits->height) );
    viewer.addEventHandler(new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet()));
    viewer.setSceneData( const_cast<osg::Node*>(sceneNode) );
    viewer.addEventHandler(new osgViewer::StatsHandler);
    return viewer.run();
}


int main(int argc, char* argv[])
{
    const char* fileName = NULL;
    if (argc < 2)
    {
        std::cout << "Usage: osgviewer_jt file.jt" << std::endl;
        return -1;
    }
    fileName = argv[1];

    osg::Node* sceneNode = osgDB::readNodeFile(fileName);

    if (sceneNode != nullptr)
        return to_viewer(sceneNode);
    else
        return -1;
}
