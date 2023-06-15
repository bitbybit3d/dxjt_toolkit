//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2019 by bitbybit3d, All rights reserved. 
// Author: bitbybit3d@163.com 
// 
// 
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, 
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
//////////////////////////////////////////////////////////////////////////////
#ifndef __JT_TOOLKIT_ENTITY_FACTORY_H_
#define __JT_TOOLKIT_ENTITY_FACTORY_H_

#include "DxJtEntity.h"
#include "DxJtCADImporter.h"
#include "DxJtCADExporter.h"
#include "DxJtAttrib.h"
#include "DxJtProperty.h"
#include "DxJtHierarchy.h"
#include "DxJtShape.h"
#include "DxJtTriStripSet.h"

/**
 * @brief A static factory class used to create all toolkit objects.
 * Client applications should use this class to create all 
 * JtEntity-derived objects instead of C++'s new command.
 */
class JT_TOOLKIT_EXPORT DxJtEntityFactory
{
public:
    /**
     * @brief Creates a new JtCADImporter object.
     */
    static std::shared_ptr<DxJtCADImporter> createCADImporter();
    /**
     * @brief Creates a new JtCADExporter object.
     */
    static std::shared_ptr<DxJtCADExporter> createCADExporter();

    static std::shared_ptr<DxJtAssembly>    createAssembly();
    static std::shared_ptr<DxJtPart>        createPart();
    static std::shared_ptr<DxJtInstance>    createInstance(std::shared_ptr<DxJtHierarchy> refOrig);

    static std::shared_ptr<DxJtMaterial>  createMaterial();
    static std::shared_ptr<DxJtTransform> createTransform();

    static std::shared_ptr<DxJtProperty>  createProperty(const std::wstring& keyString,
                                                       const std::wstring& value);
    static std::shared_ptr<DxJtProperty>  createProperty(const std::wstring& keyString,
                                                       const int value);
    static std::shared_ptr<DxJtProperty>  createProperty(const std::wstring& keyString,
                                                       const float value);
    static std::shared_ptr<DxJtProperty>  createProperty(const std::wstring& keyString,
        const short year, const short month, const short day, const short hour,
        const short minutes, const short seconds);

    static std::shared_ptr<DxJtShape>       createShape();
    static std::shared_ptr<DxJtTriStripSet> createTriStripSet();
};

#endif  // __JT_TOOLKIT_ENTITY_FACTORY_H_
