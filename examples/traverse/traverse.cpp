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
    char buffer[_MAX_PATH];

    if (argc == 2)
        fileName = argv[1];
    else
    {
        const char* dir1 = "F:\\NutstoreSync\\3dmodel_files\\TypeDistinguish";

        if (_access(dir1, 0) != 0)
            dir1 = "D:\\NutstoreSync\\3dmodel_files\\TypeDistinguish";

        // jt8.0-8.1
        // fileName = "nx_files\\primitives_stp\\example_block_nx4.jt";  // pass
        // fileName = "nx_files\\primitives_stp\\example_block_jt8.1.jt";  // pass
        // fileName = "F:\\NutstoreSync\\3dmodel_files\\TypeDistinguish\\nx_files\\example_cylinder_nx4.jt";   // pass
        // fileName = "F:\\NutstoreSync\\3dmodel_files\\TypeDistinguish\\nx_files\\example_cone_nx4.jt";   // pass huffman codec
        // fileName = "F:\\NutstoreSync\\3dmodel_files\\TypeDistinguish\\nx_files\\example_sphere_nx4.jt"; // pass huffman codec
        // fileName = "F:\\NutstoreSync\\3dmodel_files\\TypeDistinguish\\nx_files\\angle1_nx4.jt";     // pass huffman codec
        // fileName = "nx_files\\opening_protection_plate1_nx4_monolithic.jt"; // pass huffman codec
        // fileName = "nx_files\\opening_protection_plate1_nx4_assembly.jt";

        // fileName = "jt_files\\butterflyvalve.jt";     // pass
        // fileName = "F:\\NutstoreSync\\3dmodel_files\\TypeDistinguish\\jt_files\\cam.jt";
        // fileName = "jt_files\\san2.jt";
        // fileName = "jt_files\\conrod.jt"; // huffman and arithmetic codec

        // JT9.0
        // fileName = "jt_files\\3067387_5b09.jt";
        fileName = "jt_files\\3417523_5b061.jt";

        // JT9.5
        // fileName = "F:\\NutstoreSync\\3dmodel_files\\TypeDistinguish\\jt_files\\CDPlayer_assm.jt";
        // fileName = "F:\\NutstoreSync\\3dmodel_files\\TypeDistinguish\\jt_files\\CoffeeMaker.jt"; // pass
        // fileName = "F:\\NutstoreSync\\3dmodel_files\\TypeDistinguish\\jt_files\\Control_Cabinet_assm.jt"; // pass
        // fileName = "jt_files\\ElectricRazor_assm.jt";
        // fileName = "F:\\NutstoreSync\\3dmodel_files\\TypeDistinguish\\jt_files\\floorjack_assm.jt"; // pass
        // fileName = "F:\\NutstoreSync\\3dmodel_files\\TypeDistinguish\\jt_files\\HandMixer.jt"; // pass
        // fileName = "jt_files\\MachineVice.jt"; // pass
        // fileName = "jt_files\\Radial_Engine_assm.jt"; // pass
        // fileName = "F:\\NutstoreSync\\3dmodel_files\\TypeDistinguish\\jt_files\\sextant.jt"; // pass

        // fileName = "nx_files\\primitives_stp\\example_block_nx8_5.jt";
        // fileName = "nx_files\\primitives_stp\\example_cylinder_nx6.jt";
        // fileName = "nx_files\\opening_protection_plate1_nx8_5_single.jt";
        // fileName = "nx_files\\primitives_stp\\example_cone2_diffcolor_nx8.jt";
        // fileName = "jt_files\\generated\\phone.jt";

        // JT10
        // fileName = "nx_files\\primitives_stp\\example_block_nx1872.jt";
        // fileName = "nx_files\\primitives_stp\\example_cylinder_nx1872.jt";
        // fileName = "nx_files\\primitives_stp\\example_sphere_nx1872.jt";
        // fileName = "nx_files\\opening_protection_plate1_nx1872.jt";
        // fileName = "nx_files\\primitives_stp\\example_cylinder_jt10.4.jt";

        sprintf_s(buffer, _MAX_PATH, "%s\\%s", dir1, fileName);
        fileName = buffer;
    }
    // fileName = "opening_protection_plate1_nx4_monolithic.jt";

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
