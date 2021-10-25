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

#include "JtCADImporter.h"
#include "JtTraverser.h"
#include "JtEntityFactory.h"

#define indent(i) {for(int l=0; l < i; l++) std::cout << "  ";}

static int want_details = 2;

void printXform(JtTransform *partXform, int Level)
{
    std::vector<double> elements;

    indent(Level);
    std::cout << "JtkTRANSFORM" << std::endl;

    partXform->getTElements(elements);
    if (!elements.empty())
    {
        indent(Level + 1);
        std::cout << elements[0] << ", " << elements[1] << ", "
            << elements[2] << ", " << elements[3] << std::endl;
        indent(Level + 1);
        std::cout << elements[4] << ", " << elements[5] << ", "
            << elements[6] << ", " << elements[7] << std::endl;
        indent(Level + 1);
        std::cout << elements[8] << ", " << elements[9] << ", "
            << elements[10] << ", " << elements[11] << std::endl;
        indent(Level + 1);
        std::cout << elements[12] << ", " << elements[13] << ", "
            << elements[14] << ", " << elements[15] << std::endl;
    }
}

void printMaterial(JtMaterial *partMaterial, int Level)
{
    std::vector<float> ambient, diffuse, specular, emission;
    float shininess = -999.0;

    indent(Level);
    std::cout << "JtkMATERIAL" << std::endl;

    partMaterial->getAmbientColor(ambient);
    if (!ambient.empty())
    {
        indent(Level + 1);
        std::cout << "ambient = ( " << ambient[0] << ", " << ambient[1] << ", "
            << ambient[2] << ", " << ambient[3] << " )" << std::endl;
    }

    partMaterial->getDiffuseColor(diffuse);
    if (!diffuse.empty())
    {
        indent(Level + 1);
        std::cout << "diffuse = ( " << diffuse[0] << ", " << diffuse[1] << ", "
            << diffuse[2] << ", " << diffuse[3] << " )" << std::endl;
    }

    partMaterial->getSpecularColor(specular);
    if (!specular.empty())
    {
        indent(Level + 1);
        std::cout << "specular = ( " << specular[0] << ", " << specular[1] << ", "
            << specular[2] << ", " << specular[3] << " )" << std::endl;
    }

    partMaterial->getEmissionColor(emission);
    if (!emission.empty())
    {
        indent(Level + 1);
        std::cout << "emission = ( " << emission[0] << ", " << emission[1] << ", "
            << emission[2] << ", " << emission[3] << " )" << std::endl;
    }

    shininess = partMaterial->getShininess();
    if (shininess != -999.0)
    {
        indent(Level + 1);
        std::cout << "shininess = " << shininess << std::endl;
    }
}

void printAttribs(JtEntity* ent, int Level)
{
    JtHierarchy* node = nullptr;
    JtShape* partShape = nullptr;

    if (ent->isOfSubType(JtHierarchy::classTypeID()))
        node = (JtHierarchy*)ent;
    else if (ent->isOfSubType(JtShape::classTypeID()))
        partShape = (JtShape*)ent;

    if (node == nullptr && partShape == nullptr)
        return;

    int numAttrs = ((node != nullptr) ? node->numAttribs() : partShape->numAttribs());
    for (int i = 0; i < numAttrs; i++)
    {
        std::shared_ptr<JtAttrib> attrib;

        if (node != nullptr)
            attrib = node->getAttrib(i);
        else
            attrib = partShape->getAttrib(i);

        if (attrib)
        {
            switch (attrib->typeID())
            {
            case JtEntity::JtkMATERIAL:
                printMaterial((JtMaterial*)attrib.get(), Level);
                break;
            case JtEntity::JtkTRANSFORM:
                printXform((JtTransform*)attrib.get(), Level);
                break;
            }
        }
    }
}

void printData(const char* name, const std::vector<float>& data, int Level)
{
    if (!data.empty())
    {
        indent(Level);
        std::cout << name << " = ( ";
        for (std::size_t i = 0; i < data.size(); i++)
        {
            if (i)
                std::cout << ", ";

            std::cout << data[i];
        }
        std::cout << " )" << std::endl;
    }
}

void printShape(std::shared_ptr<JtShape> partShape, int Level)
{
    indent(Level);
    std::wcout << partShape->typeIDName() << std::endl;

    for (int set = 0; set < partShape->numOfSets(); set++)
    {
        indent(Level + 1);

        std::cout << "geom set #" << set << ":" << std::endl;

        std::vector<float> vertices, normals;

        partShape->getInternal(vertices, normals, set);

        // output
        printData("vertices", vertices, Level + 2);
        printData("normals", normals, Level + 2);
    }
}

class DumpTraverser : public JtTraverser
{
public:
    DumpTraverser() {}

    virtual bool preActionCallback(std::shared_ptr<JtHierarchy> CurrNode, int Level);
};

bool DumpTraverser::preActionCallback(std::shared_ptr<JtHierarchy> CurrNode, int Level)
{
    indent(Level);

    // Common data for all JtkHierarchy nodes...
//     int nodeId = -1;
//     CurrNode->getId(nodeId);

    std::wstring szName = CurrNode->name();

    switch (CurrNode->typeID())
    {
    case JtEntity::JtkPART: {
        std::shared_ptr<JtPart> pPart = std::dynamic_pointer_cast<JtPart>(CurrNode);
        assert(pPart != nullptr);

        std::wcout << CurrNode->typeIDName() << ": " << szName << std::endl;

        if (want_details > 0)
            printAttribs(CurrNode.get(), Level + 1);

        if (want_details > 1)
        {
            int partNumShapeLODs = pPart->numPolyLODs();
            for (int lod = 0; lod < partNumShapeLODs; ++lod)
            {
                indent(Level + 1);
                std::cout << "LOD#" << lod << ":" << std::endl;

                int partNumShapes = pPart->numPolyShapes(lod);
                for (int shNum = 0; shNum < partNumShapes; ++shNum)
                {
                    indent(Level + 2);
                    std::cout << "Shape#" << shNum << ":" << std::endl;

                    std::shared_ptr<JtShape> partShape = pPart->getPolyShape(lod, shNum);
                    if (partShape)
                    {
                        printAttribs(partShape.get(), Level + 3);

                        printShape(partShape, Level + 3);
                    }
                }
            }
        }
        break;
    }

    case JtEntity::JtkASSEMBLY: {
        std::wcout << CurrNode->typeIDName() << ": " << szName << std::endl;

        if (want_details > 0)
            printAttribs(CurrNode.get(), Level + 1);
        break;
    }

    case JtEntity::JtkINSTANCE: {
        std::wcout << CurrNode->typeIDName() << ": " << szName << std::endl;

        if (want_details > 0)
            printAttribs(CurrNode.get(), Level + 1);
        break;
    }

    default:
        break;
    }

    return true;
}

int main(int argc, char* argv[])
{
    const char* fileName = NULL;

    if (argc < 2)
    {
        std::cout << "Usage: traverse file.jt" << std::endl;
        return -1;
    }
    fileName = argv[1];

    wchar_t buf_wstr[_MAX_PATH];
    size_t numConverted = 0;
    size_t flen = strlen(fileName);

    mbstowcs_s(&numConverted, buf_wstr, _MAX_PATH, fileName, flen);

    std::shared_ptr<JtCADImporter> importer = JtEntityFactory::createCADImporter();
    if (importer == nullptr)
        return -1;

    std::shared_ptr<JtHierarchy> root = importer->importJt(buf_wstr);
    if (root == nullptr)
        return -1;

    std::shared_ptr<JtTraverser> traverser = std::shared_ptr<JtTraverser>(new DumpTraverser);
    if (traverser)
    {
        traverser->traverseGraph(root);
    }

    std::shared_ptr<JtCADExporter> exporter = JtEntityFactory::createCADExporter();
    if (exporter == nullptr)
        return -1;
    else if (0)
        exporter->exportJt(root);
    return 0;
}
