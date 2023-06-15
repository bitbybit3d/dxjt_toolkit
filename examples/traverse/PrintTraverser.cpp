#include <iostream>
#include <cassert>

#ifdef OUTPUT_TO_OPENMESH
// -------------------- OpenMesh
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/DefaultTriMesh.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#endif  // OUTPUT_TO_OPENMESH

#include "PrintTraverser.h"


#define indent(i) {for(int l=0; l < i; l++) std::cout << "  ";}

static int want_details = 2;

void printXform(DxJtTransform* partXform, int Level)
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

void printMaterial(DxJtMaterial* partMaterial, int Level)
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

void printAttribs(DxJtEntity* ent, int Level)
{
    DxJtHierarchy* node = nullptr;
    DxJtShape* partShape = nullptr;

    if (ent->isOfSubType(DxJtHierarchy::classTypeID()))
        node = (DxJtHierarchy*)ent;
    else if (ent->isOfSubType(DxJtShape::classTypeID()))
        partShape = (DxJtShape*)ent;

    if (node == nullptr && partShape == nullptr)
        return;

    int numAttrs = ((node != nullptr) ? node->numAttribs() : partShape->numAttribs());
    for (int i = 0; i < numAttrs; i++)
    {
        std::shared_ptr<DxJtAttrib> attrib;

        if (node != nullptr)
            attrib = node->getAttrib(i);
        else
            attrib = partShape->getAttrib(i);

        if (attrib)
        {
            switch (attrib->typeID())
            {
            case DxJtEntity::JtkMATERIAL:
                printMaterial((DxJtMaterial*)attrib.get(), Level);
                break;
            case DxJtEntity::JtkTRANSFORM:
                printXform((DxJtTransform*)attrib.get(), Level);
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

std::string ws2s_crt(const wchar_t* pwszSrc)
{
    std::string locname = setlocale(LC_ALL, NULL);
    setlocale(LC_ALL, "chs");

    size_t nLen = wcslen(pwszSrc);
    size_t nSize = 4 * nLen + 1;

    char* pszDst = new char[nSize];
    assert(pszDst != NULL);
    if (pszDst == NULL)
        return std::string("");

    memset(pszDst, 0, nSize);
    size_t numConverted;
    errno_t err = wcstombs_s(&numConverted, pszDst, nSize, pwszSrc, nSize);
    if (err == STRUNCATE)
        std::cout << "truncation occurred!\n" << std::endl;
    else if (err == EILSEQ)
    {
        setlocale(LC_ALL, "ko_KR");
        err = wcstombs_s(&numConverted, pszDst, nSize, pwszSrc, nSize);
        if (err == EILSEQ)
            std::cout << "EILSEQ" << std::endl;
    }
    assert(err == 0);

    std::string strTemp(pszDst);
    delete[] pszDst;

    setlocale(LC_ALL, locname.c_str());
    return strTemp;
}

void printShape(std::shared_ptr<DxJtShape> partShape, const std::string& szName, int Level)
{
    indent(Level);
    std::wcout << partShape->typeIDName() << std::endl;

#ifdef OUTPUT_TO_OPENMESH
    if (1)
    {
        std::vector<float> vertices;
        std::vector<float> normals;
        std::vector<int> indices;

        typedef OpenMesh::TriMesh_ArrayKernelT<>  MyMesh;
        MyMesh mesh;

        // request vertex normals, so the mesh reader can use normal information if available
        mesh.request_vertex_normals();

        partShape->getTriangles(vertices, normals, indices);

        int vertexCount = static_cast<int>(vertices.size() / 3);
        std::unique_ptr<MyMesh::VertexHandle[]> vhandle(new MyMesh::VertexHandle[vertexCount]);

        for (int i = 0; i < vertexCount; ++i)
        {
            vhandle[i] = mesh.add_vertex(MyMesh::Point(vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2]));
            mesh.set_normal(vhandle[i], MyMesh::Normal(normals[i * 3], normals[i * 3 + 1], normals[i * 3 + 2]));
        }

        int triangleCount = static_cast<int>(indices.size() / 3);
        for (int i = 0; i < triangleCount; ++i)
        {
            std::vector<MyMesh::VertexHandle>  face_vhandles;
            int a = indices[i * 3];
            int b = indices[i * 3 + 1];
            int c = indices[i * 3 + 2];

            face_vhandles.clear();
            face_vhandles.push_back(vhandle[a]);
            face_vhandles.push_back(vhandle[b]);
            face_vhandles.push_back(vhandle[c]);
            mesh.add_face(face_vhandles);
        }

        // write mesh to output.obj
        try
        {
            char buffer[_MAX_PATH];

            sprintf_s(buffer, _MAX_PATH, "partshape_%s.obj", szName.c_str());
            if (!OpenMesh::IO::write_mesh(mesh, buffer, OpenMesh::IO::Options::VertexNormal))
            {
                std::cerr << "Cannot write mesh to file 'output.obj'" << std::endl;
            }
        }
        catch (std::exception& x)
        {
            std::cerr << x.what() << std::endl;
        }
    }
#endif  // OUTPUT_TO_OPENMESH

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

bool PrintTraverser::preActionCallback(std::shared_ptr<DxJtHierarchy> CurrNode, int Level)
{
    indent(Level);

    // Common data for all JtkHierarchy nodes...
//     int nodeId = -1;
//     CurrNode->getId(nodeId);

    std::wstring szName = CurrNode->name();

    switch (CurrNode->typeID())
    {
    case DxJtEntity::JtkPART: {
        std::shared_ptr<DxJtPart> pPart = std::dynamic_pointer_cast<DxJtPart>(CurrNode);
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

                    std::shared_ptr<DxJtShape> partShape = pPart->getPolyShape(lod, shNum);
                    if (partShape)
                    {
                        std::string locSzName = ws2s_crt(szName.c_str());
                        size_t pos = locSzName.find(':');
                        if (pos != locSzName.npos)
                        {
                            locSzName = locSzName.substr(0, pos);
                        }

                        printAttribs(partShape.get(), Level + 3);

                        printShape(partShape, locSzName, Level + 3);
                    }
                }
            }
        }
        break;
    }

    case DxJtEntity::JtkASSEMBLY: {
        std::wcout << CurrNode->typeIDName() << ": " << szName << std::endl;

        if (want_details > 0)
            printAttribs(CurrNode.get(), Level + 1);
        break;
    }

    case DxJtEntity::JtkINSTANCE: {
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
