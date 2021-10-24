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

#include <memory>

#include "JtCADImporter.h"
#include "JtCADExporter.h"
#include "JtAttrib.h"
#include "JtProperty.h"
#include "JtHierarchy.h"
#include "JtShape.h"
#include "JtTriStripSet.h"

/**
 * @brief A static factory class used to create all toolkit objects.
 * Client applications should use this class to create all 
 * JtEntity-derived objects instead of C++'s new command.
 */
class JT_TOOLKIT_EXPORT JtEntityFactory
{
public:
    /**
     * @brief Creates a new JtCADImporter object.
     */
    static std::shared_ptr<JtCADImporter> createCADImporter();
    /**
     * @brief Creates a new JtCADExporter object.
     */
    static std::shared_ptr<JtCADExporter> createCADExporter();

    static std::shared_ptr<JtAssembly>    createAssembly();
    static std::shared_ptr<JtPart>        createPart();
    static std::shared_ptr<JtInstance>    createInstance(std::shared_ptr<JtHierarchy> refOrig);

    static std::shared_ptr<JtMaterial>  createMaterial();
    static std::shared_ptr<JtTransform> createTransform();

    static std::shared_ptr<JtProperty>  createProperty(const std::wstring& keyString,
                                                       const std::wstring& value);
    static std::shared_ptr<JtProperty>  createProperty(const std::wstring& keyString,
                                                       const int value);
    static std::shared_ptr<JtProperty>  createProperty(const std::wstring& keyString,
                                                       const float value);
    static std::shared_ptr<JtProperty>  createProperty(const std::wstring& keyString,
        const short year, const short month, const short day, const short hour,
        const short minutes, const short seconds);

    static std::shared_ptr<JtShape>       createShape();
    static std::shared_ptr<JtTriStripSet> createTriStripSet();
};

#endif  // __JT_TOOLKIT_ENTITY_FACTORY_H_
