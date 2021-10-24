//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2019 by bitbybit3d, All rights reserved. 
// Author: bitbybit3d@163.com 
// 
// 
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, 
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
//////////////////////////////////////////////////////////////////////////////
#ifndef __JT_TOOLKIT_CAD_IMPORTER_H_
#define __JT_TOOLKIT_CAD_IMPORTER_H_

#include <memory>

#include "JtEntity.h"

class JtHierarchy;

/**
 * @brief Load JT format file to return a root node.
 */
class JT_TOOLKIT_EXPORT JtCADImporter : public JtEntity
{
protected:
    JtCADImporter();

public:

    /**
     * @brief Return the TypeID for class.
     */
    static TypeID classTypeID();
    /**
     * @brief Return the TypeID for instance.
     */
    virtual TypeID typeID() const;
    /**
     * @brief Return true if instance belong to the type id.
     */
    virtual bool isOfSubType(TypeID id) const;

    // Continue the export process normally.
    // Option to load tristrip/linestrip/polygon/point set data from the .jt file
    enum ShapeLoadOption
    {
        JtkALL_LODS = 0, // Retain all LODs from the input
        JtkHIGH_LOD
    };

    virtual void               setShapeLoadOption(ShapeLoadOption Option) = 0;
    virtual ShapeLoadOption    shapeLoadOption() const = 0;

    virtual std::shared_ptr<JtHierarchy> importJt(const wchar_t* filename) = 0;
};

#endif  // __JT_TOOLKIT_CAD_IMPORTER_H_
