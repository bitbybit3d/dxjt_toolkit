//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2019 by bitbybit3d, All rights reserved. 
// Author: bitbybit3d@163.com 
// 
// 
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, 
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
//////////////////////////////////////////////////////////////////////////////
#ifndef __JT_TOOLKIT_SHAPE_BASE_H_
#define __JT_TOOLKIT_SHAPE_BASE_H_

#include "DxJtEntity.h"
#include "DxJtAttrib.h"


/**
 * @brief Geometric shape definition data (e.g. vertices, normals, etc).
 */
class JT_TOOLKIT_EXPORT DxJtShape : public DxJtEntity
{
protected:
    DxJtShape();

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

    /**
     * @brief Set the JtAttribute to this node.
     */
    virtual int addAttrib(std::shared_ptr<DxJtAttrib> attrib) = 0;
    /**
     * @brief Get the number of attributes.
     */
    virtual int numAttribs() const = 0;
    /**
     * @brief Gets the JtAttribute by index.
     */
    virtual std::shared_ptr<DxJtAttrib> getAttrib(int index) const = 0;

    /**
     * @brief Add or get data as Tri-Strip Set.
     */
    virtual void addPrim(const std::vector<float>& vertices, const std::vector<float>& normals) = 0;
    virtual void getInternal(std::vector<float>& vertices, std::vector<float>& normals, int setNum) const = 0;
    virtual int numOfSets() const = 0;

    /**
     * @brief Get the all triangles for display.
     *
     * @warning no correspond setTriangles() function.
     */
    virtual void getTriangles(std::vector<float>& vertices, std::vector<float>& normals, std::vector<int>& indices) const = 0;
};

#endif  // __JT_TOOLKIT_SHAPE_BASE_H_
