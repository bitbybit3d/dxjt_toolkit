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
#include <cassert>
#include <io.h>

#include "DxJtCADImporter.h"
#include "DxJtEntityFactory.h"

#include "PrintTraverser.h"



int main(int argc, char* argv[])
{
    const char* fileName = NULL;

    if (argc == 2)
        fileName = argv[1];
    else
        fileName = "..\\..\\samples\\opening_protection_plate1_jt9.5.jt";

    wchar_t buf_wstr[_MAX_PATH];
    size_t numConverted = 0;
    size_t flen = strlen(fileName);

    mbstowcs_s(&numConverted, buf_wstr, _MAX_PATH, fileName, flen);

    std::shared_ptr<DxJtCADImporter> importer = DxJtEntityFactory::createCADImporter();
    if (importer == nullptr)
        return -1;

    std::shared_ptr<DxJtHierarchy> root = importer->importJt(buf_wstr);
    if (root == nullptr)
        return -1;

    std::shared_ptr<DxJtTraverser> traverser = std::shared_ptr<DxJtTraverser>(new PrintTraverser);
    if (traverser)
    {
        traverser->traverseGraph(root);
    }

    std::shared_ptr<DxJtCADExporter> exporter = DxJtEntityFactory::createCADExporter();
    if (exporter == nullptr)
        return -1;
    else if (0)
        exporter->exportJt(root);
    return 0;
}
