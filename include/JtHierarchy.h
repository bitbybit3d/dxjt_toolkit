//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2019 by bitbybit3d, All rights reserved. 
// Author: bitbybit3d@163.com 
// 
// 
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, 
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
//////////////////////////////////////////////////////////////////////////////
#ifndef __JT_TOOLKIT_HIERARCHY_H_
#define __JT_TOOLKIT_HIERARCHY_H_

#include <string>

#include "JtEntity.h"
#include "JtAttrib.h"
#include "JtProperty.h"
#include "JtShape.h"

/**
 * @brief The base class for all product structure objects (
 * JtAssembly, JtPart, and JtInstance).
 */
class JT_TOOLKIT_EXPORT JtHierarchy : public JtEntity
{
protected:
    JtHierarchy();

public:
    virtual ~JtHierarchy() {}

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

    // Basic ID APIs
    virtual std::wstring name() const = 0;
    virtual void setName(const std::wstring& nm) = 0;
    virtual int version() const = 0;
    virtual void setId(int InstId) = 0;
    virtual int getId() const = 0;

    // graph-related APIs
    virtual std::shared_ptr<JtHierarchy> parent() const = 0;

    // properties
    /**
     * @brief Get the number of properties.
     */
    virtual int numProps() const = 0;

    virtual bool addProp(std::shared_ptr<JtProperty> prop) = 0;
    virtual std::shared_ptr<JtProperty> getProp(int index) const = 0;

    // attributes
    /**
     * @brief Set the JtAttribute to this node.
     */
    virtual int addAttrib(std::shared_ptr<JtAttrib> attrib) = 0;
    /**
     * @brief Get the number of attributes.
     */
    virtual int numAttribs() const = 0;
    /**
     * @brief Gets the JtAttribute by index.
     */
    virtual std::shared_ptr<JtAttrib> getAttrib(int index) const = 0;

    // JT file structure ("shattering") APIs
    virtual void setJtFilename(const std::wstring& JtFileName) = 0;
    virtual std::wstring getJtFilename() const = 0;
};

/**
 * @brief The intermediate class implementing units and PMI
 * for JtAssembly and JtPart.
 */
class JT_TOOLKIT_EXPORT JtUnitHierarchy : public JtHierarchy
{
protected:
    JtUnitHierarchy();

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

    enum JtkUnits
    {
        JtkUNKNOWN = 0,
        JtkMICROMETERS,
        JtkMILLIMETERS,
        JtkCENTIMETERS,
        JtkDECIMETERS,
        JtkMETERS,
        JtkKILOMETERS,
        JtkINCHES,
        JtkFEET,
        JtkYARDS,
        JtkMILES,
        JtkMILS
    };

    // Measurement units APIs
    virtual void setUnits(JtkUnits units) = 0;
    virtual JtkUnits getUnits() const = 0;

    // Instance APIs
    virtual int numInstances() const = 0;
};

/**
 * @brief The object for defining non-leaf nodes in a product
 * structure hierarchy. Any hierarchy object may be a child
 * of this object.
 *
 * Note: all hierarchies must be a cyclical (i.e. an assembly
 * object cannot be a descendant of itself).
 * Cycle detection if NOT performed, and cyclic graphs will
 * likely lead to undefined results.
 */
class JT_TOOLKIT_EXPORT JtAssembly : public JtUnitHierarchy
{
protected:
    JtAssembly();

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
     * @brief Adds any JtHierarchy-derived object as a child of this assembly.
     */
    virtual int addChild(std::shared_ptr<JtHierarchy> son) = 0;

    /**
     * @brief Get the number of children.
     */
    virtual int numChildren() const = 0;

    /**
     * @brief Gets a JtHierarchy child by index.
     */
    virtual std::shared_ptr<JtHierarchy> child(int index) const = 0;
};


/**
 * @brief The object for defining leaf nodes in a product
 * structure hierarchy.  These objects are the only ones that
 * can hold geometry.
 */
class JT_TOOLKIT_EXPORT JtPart : public JtUnitHierarchy
{
protected:
    JtPart();

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

    virtual int addPolyShape(std::shared_ptr<JtShape> shape, int LODNum = 0) = 0;

    /**
     * @brief Get the number of faceted shape geometry LODs.
     */
    virtual int numPolyLODs() = 0;

    /**
     * @brief Returns the number of JtShape in a specified LOD.
     */
    virtual int numPolyShapes(int LODNum) = 0;
    virtual std::shared_ptr<JtShape> getPolyShape(int LODNum, int index) = 0;
};

/**
 * @brief Reference object pointing to an either a JtkAssembly or
 * JtkPart object.  Used to avoid physical duplication of
 * replicated assembly objects.
 */
class JT_TOOLKIT_EXPORT JtInstance : public JtHierarchy
{
protected:
    JtInstance();

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
     * @brief A pointer to the node being instanced.
     */
    virtual std::shared_ptr<JtHierarchy> original() const = 0;
};

#endif  // __JT_TOOLKIT_HIERARCHY_H_
