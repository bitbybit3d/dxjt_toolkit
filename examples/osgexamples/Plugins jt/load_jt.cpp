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
#include <fstream>
#include <cassert>
#include <unordered_map>

#include <osg/Node>
#include <osg/Geometry>
#include <osg/Geode>
#include <osg/MatrixTransform>
#include <osg/Material>
#include <osgDB/Registry>

#include "DxJtEntityFactory.h"
#include "DxJtCADImporter.h"
#include "DxJtTraverser.h"

static osg::ref_ptr<osg::Node> convertPartShape2Geode(std::shared_ptr<DxJtShape> partShape);
static osg::ref_ptr<osg::Geometry> triangles_to_osgGeometry(const std::vector<float>& vertices, const std::vector<float>& normals, const std::vector<int>& indices);
static osg::ref_ptr<osg::Geometry> triStripSet_to_osgGeometry(const std::vector<float>& vertices, const std::vector<float>& normals);

class ConvertJtLSGNode : public DxJtTraverser
{
public:
    ConvertJtLSGNode(std::unordered_map<std::shared_ptr<DxJtHierarchy>, osg::ref_ptr<osg::Group> >& mapJt2Group)
        : m_mapJt2Node(mapJt2Group)
    {}

    virtual bool preActionCallback(std::shared_ptr<DxJtHierarchy> CurrNode, int Level);

private:
    std::unordered_map<std::shared_ptr<DxJtHierarchy>, osg::ref_ptr<osg::Group> >& m_mapJt2Node;
};

bool ConvertJtLSGNode::preActionCallback(std::shared_ptr<DxJtHierarchy> CurrNode, int Level)
{
    std::wstring szName = CurrNode->name();

    std::shared_ptr<DxJtTransform> attribTransf;
    std::shared_ptr<DxJtMaterial>  attribMat;

    int count = CurrNode->numAttribs();
    for (int i = 0; i < count; ++i)
    {
        std::shared_ptr<DxJtAttrib> attrib = CurrNode->getAttrib(i);

        // 默认仅会有一个 AttributeGeometricTransform 的属性存在
        if (attribTransf == nullptr && attrib->typeID() == DxJtEntity::JtkTRANSFORM)
            attribTransf = std::dynamic_pointer_cast<DxJtTransform>(attrib);

        if (attribMat == nullptr && attrib->typeID() == DxJtEntity::JtkMATERIAL)
            attribMat = std::dynamic_pointer_cast<DxJtMaterial>(attrib);
    }

    osg::ref_ptr<osg::Group> transfGroup = nullptr;
    osg::ref_ptr<osg::Material> osgMat = nullptr;

    if (attribTransf != nullptr)
    {
        std::vector<double> trsfMtx;
        attribTransf->getTElements(trsfMtx);
        osg::ref_ptr<osg::MatrixTransform> triangleMT = new osg::MatrixTransform;
        triangleMT->setMatrix(osg::Matrix(trsfMtx.data()));
        transfGroup = triangleMT;
    }

    if (attribMat != nullptr)
    {
        std::vector<float> ambientColor, diffuseColor, specularColor, emissionColor;

        attribMat->getAmbientColor(ambientColor);
        attribMat->getDiffuseColor(diffuseColor);
        attribMat->getSpecularColor(specularColor);
        attribMat->getEmissionColor(emissionColor);

        osgMat = new osg::Material();
        osgMat->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4(ambientColor[0], ambientColor[1], ambientColor[2], ambientColor[3]));
        osgMat->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4(diffuseColor[0], diffuseColor[1], diffuseColor[2], diffuseColor[3]));
        osgMat->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4(specularColor[0], specularColor[1], specularColor[2], specularColor[3]));
        osgMat->setEmission(osg::Material::FRONT_AND_BACK, osg::Vec4(emissionColor[0], emissionColor[1], emissionColor[2], emissionColor[3]));
        osgMat->setShininess(osg::Material::FRONT_AND_BACK, attribMat->getShininess());
    }

    osg::ref_ptr<osg::Group> aGroup = new osg::Group;

    if (osgMat != nullptr)
    {
        osg::ref_ptr<osg::StateSet> stateSet = aGroup->getOrCreateStateSet();
        stateSet->setAttribute(osgMat);
    }
    m_mapJt2Node.insert(std::make_pair(CurrNode, aGroup));

    osg::ref_ptr<osg::Group> aParent = nullptr;
    std::shared_ptr<DxJtHierarchy> parJtNode = CurrNode->parent();
    if (parJtNode != nullptr)
    {
        auto it_find = m_mapJt2Node.find(parJtNode);
        assert(it_find != m_mapJt2Node.end());
        if (it_find == m_mapJt2Node.end())
            return false;

        aParent = it_find->second;
    }

    if (aParent != nullptr)
    {
        if (transfGroup != nullptr)
        {
            aParent->addChild(transfGroup);
            transfGroup->addChild(aGroup);
        }
        else
            aParent->addChild(aGroup);
    }

    switch (CurrNode->typeID())
    {
    case DxJtEntity::JtkPART: {
        std::shared_ptr<DxJtPart> pPart = std::dynamic_pointer_cast<DxJtPart>(CurrNode);
        assert(pPart != nullptr);

        int partNumShapeLODs = pPart->numPolyLODs();
        if (partNumShapeLODs >= 1)
        {
            int lod = 0;
            int partNumShapes = pPart->numPolyShapes(lod);

            for (int shNum = 0; shNum < partNumShapes; ++shNum)
            {
                std::shared_ptr<DxJtShape> partShape = pPart->getPolyShape(lod, shNum);
                if (partShape == nullptr)
                    continue;

                osg::ref_ptr<osg::Node> aNode = convertPartShape2Geode(partShape);
                if (aNode != nullptr)
                {
                    aGroup->addChild(aNode);
                }
            }
        }
        break;
    }

    case DxJtEntity::JtkASSEMBLY: {
        break;
    }

    case DxJtEntity::JtkINSTANCE: {
        std::shared_ptr<DxJtInstance> pInst = std::dynamic_pointer_cast<DxJtInstance>(CurrNode);
        assert(pInst != nullptr);

        std::shared_ptr<DxJtHierarchy> pJtOrig = pInst->original();
        assert(pJtOrig != nullptr);

        auto it_find = m_mapJt2Node.find(pJtOrig);
        assert(it_find != m_mapJt2Node.end());
        if (it_find == m_mapJt2Node.end())
            return false;

        assert(aGroup != nullptr);
        aGroup->addChild(it_find->second);
        break;
    }

    default:
        break;
    }

    return true;
}

osg::Node* load_jt(const wchar_t *filename, const osgDB::ReaderWriter::Options* options)
{
    if (!DxJtEntityFactory::registerLicense())
        return nullptr;

    std::shared_ptr<DxJtCADImporter> importer = DxJtEntityFactory::createCADImporter();
    if (importer == nullptr)
        return nullptr;

    std::shared_ptr<DxJtHierarchy> root = importer->importJt(filename);
    if (root == nullptr)
        return nullptr;

    std::unordered_map<std::shared_ptr<DxJtHierarchy>, osg::ref_ptr<osg::Group> > mapJt2Group;
    std::shared_ptr<DxJtTraverser> traverser = std::shared_ptr<DxJtTraverser>(new ConvertJtLSGNode(mapJt2Group));
    if (traverser)
    {
        traverser->traverseGraph(root);

        auto it_find = mapJt2Group.find(root);
        assert(it_find != mapJt2Group.end());
        if (it_find != mapJt2Group.end())
            return it_find->second.release();
        else
            return nullptr;
    }
    return nullptr;
}


osg::ref_ptr<osg::Node> convertPartShape2Geode(std::shared_ptr<DxJtShape> partShape)
{
    std::shared_ptr<DxJtTransform> attribTransf;
    std::shared_ptr<DxJtMaterial>  attribMat;

    int count = partShape->numAttribs();
    for (int i = 0; i < count; ++i)
    {
        std::shared_ptr<DxJtAttrib> attrib = partShape->getAttrib(i);

        // 默认仅会有一个 AttributeGeometricTransform 的属性存在
        if (attribTransf == nullptr && attrib->typeID() == DxJtEntity::JtkTRANSFORM)
            attribTransf = std::dynamic_pointer_cast<DxJtTransform>(attrib);

        if (attribMat == nullptr && attrib->typeID() == DxJtEntity::JtkMATERIAL)
            attribMat = std::dynamic_pointer_cast<DxJtMaterial>(attrib);
    }

    osg::ref_ptr<osg::Group> transfGroup = nullptr;
    osg::ref_ptr<osg::Material> osgMat = nullptr;

    if (attribTransf != nullptr)
    {
        std::vector<double> trsfMtx;
        attribTransf->getTElements(trsfMtx);
        osg::ref_ptr<osg::MatrixTransform> triangleMT = new osg::MatrixTransform;
        triangleMT->setMatrix(osg::Matrix(trsfMtx.data()));
        transfGroup = triangleMT;
    }

    if (attribMat != nullptr)
    {
        std::vector<float> ambientColor, diffuseColor, specularColor, emissionColor;

        attribMat->getAmbientColor(ambientColor);
        attribMat->getDiffuseColor(diffuseColor);
        attribMat->getSpecularColor(specularColor);
        attribMat->getEmissionColor(emissionColor);

        osgMat = new osg::Material();
        osgMat->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4(ambientColor[0], ambientColor[1], ambientColor[2], ambientColor[3]));
        osgMat->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4(diffuseColor[0], diffuseColor[1], diffuseColor[2], diffuseColor[3]));
        osgMat->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4(specularColor[0], specularColor[1], specularColor[2], specularColor[3]));
        osgMat->setEmission(osg::Material::FRONT_AND_BACK, osg::Vec4(emissionColor[0], emissionColor[1], emissionColor[2], emissionColor[3]));
        osgMat->setShininess(osg::Material::FRONT_AND_BACK, attribMat->getShininess());
    }

    osg::ref_ptr<osg::Geode> pGeode = new osg::Geode;

    if (osgMat != nullptr)
    {
        osg::ref_ptr<osg::StateSet> stateSet = pGeode->getOrCreateStateSet();
        stateSet->setAttribute(osgMat);
    }

    if (transfGroup != nullptr)
        transfGroup->addChild(pGeode);

    if (1)
    {
        std::vector<float> vertices;
        std::vector<float> normals;
        std::vector<int> indices;

        partShape->getTriangles(vertices, normals, indices);
        osg::ref_ptr<osg::Geometry> aGeometry = triangles_to_osgGeometry(vertices, normals, indices);
        if (aGeometry != nullptr)
            pGeode->addDrawable(aGeometry);
    }
    else
    {
        int numSets = partShape->numOfSets();
        for (int set = 0; set < numSets; set++)
        {
            std::vector<float> vertices, normals;

            partShape->getInternal(vertices, normals, set);

            osg::ref_ptr<osg::Geometry> aGeometry = triStripSet_to_osgGeometry(vertices, normals);
            if (aGeometry != nullptr)
                pGeode->addDrawable(aGeometry);
        }
    }

    if (transfGroup != nullptr)
        return transfGroup;
    else
        return pGeode;
}

static osg::ref_ptr<osg::Geometry> triangles_to_osgGeometry(const std::vector<float>& vertices, const std::vector<float>& normals, const std::vector<int>& indices)
{
    if (vertices.empty() || indices.empty() || vertices.size() != normals.size())
        return nullptr;

    osg::ref_ptr<osg::Geometry> aGeometry = new osg::Geometry();
    osg::ref_ptr<osg::Vec3Array> aVertices = new osg::Vec3Array();
    osg::ref_ptr<osg::Vec3Array> aNormals = new osg::Vec3Array();

    int numVertex = vertices.size() / 3;
    for (size_t idx = 0; idx < numVertex; ++idx)
    {
        aVertices->push_back(osg::Vec3(vertices[idx * 3 + 0],
            vertices[idx * 3 + 1], vertices[idx * 3 + 2]));
    }
    for (size_t idx = 0; idx < numVertex; ++idx)
    {
        osg::Vec3 v3(normals[idx * 3 + 0], normals[idx * 3 + 1], normals[idx * 3 + 2]);
        v3.normalize();
        aNormals->push_back(v3);
    }

    aGeometry->setVertexArray(aVertices);
    aGeometry->setNormalArray(aNormals, osg::Array::BIND_PER_VERTEX);

    osg::ref_ptr<osg::DrawElementsUInt> aTriElement = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES);
    for (size_t idx = 0; idx < indices.size(); ++idx)
        aTriElement->push_back(indices[idx]);
    aGeometry->addPrimitiveSet(aTriElement.get());
    return aGeometry;
}

static osg::ref_ptr<osg::Geometry> triStripSet_to_osgGeometry(const std::vector<float>& vertices, const std::vector<float>& normals)
{
    if (vertices.empty() || vertices.size() != normals.size())
        return nullptr;

    osg::ref_ptr<osg::Geometry> aGeometry = new osg::Geometry();
    osg::ref_ptr<osg::Vec3Array> aVertices = new osg::Vec3Array();
    osg::ref_ptr<osg::Vec3Array> aNormals = new osg::Vec3Array();

    int numVertex = vertices.size() / 3;
    for (size_t idx = 0; idx < numVertex; ++idx)
    {
        aVertices->push_back(osg::Vec3(vertices[idx * 3 + 0],
            vertices[idx * 3 + 1], vertices[idx * 3 + 2]));
    }
    for (size_t idx = 0; idx < numVertex; ++idx)
    {
        osg::Vec3 v3(normals[idx * 3 + 0], normals[idx * 3 + 1], normals[idx * 3 + 2]);
        v3.normalize();
        aNormals->push_back(v3);
    }

    aGeometry->setVertexArray(aVertices);
    aGeometry->setNormalArray(aNormals, osg::Array::BIND_PER_VERTEX);

    aGeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLE_STRIP, 0, numVertex));
    return aGeometry;
}
