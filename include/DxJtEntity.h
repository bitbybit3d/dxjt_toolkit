//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2019 by bitbybit3d, All rights reserved. 
// Author: bitbybit3d@163.com 
// 
// 
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, 
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
//////////////////////////////////////////////////////////////////////////////
#ifndef __DXJT_TOOLKIT_ENTITY_H_
#define __DXJT_TOOLKIT_ENTITY_H_

// Begin Microsoft Windows DLL support.
#if defined(DXJTTOOLKIT_EXPORTS)
    // For the DLL library.
#define JT_TOOLKIT_EXPORT __declspec(dllexport)
#pragma warning( disable : 4251 )
#pragma warning( disable : 4267 )
#elif defined(DXJT_TOOLKIT_STATIC_IMPORT)
    // For the static library and for Apple/Linux.
#define JT_TOOLKIT_EXPORT
#else
    // For a client of the DLL library.
#define JT_TOOLKIT_EXPORT __declspec(dllimport)
#endif
// End Microsoft Windows DLL support.


#include <memory>
#include <vector>
#include <string>

/**
 * @brief The root class.
 */
class JT_TOOLKIT_EXPORT DxJtEntity
{
    DxJtEntity(const DxJtEntity&) = delete;              // copy constructor
    DxJtEntity& operator=(const DxJtEntity&) = delete;   // assignment operator

protected:
    DxJtEntity();

public:
    virtual ~DxJtEntity();

    enum TypeID {
        JtkNONE,
        JtkENTITY,
        JtkHIERARCHY,
        JtkUNITHIERARCHY,
        JtkATTRIB,
        JtkPROPERTY,
        JtkASSEMBLY,
        JtkPART,
        JtkINSTANCE,
        JtkMATERIAL,
        JtkTRANSFORM,
        JtkSHAPE,
        JtkTRISTRIPSET,
        JtkCADIMPORTER,
        JtkCADEXPORTER,
    };

    // Type identification methods.
    /**
     * @brief Return the TypeID for class.
     */
    static TypeID classTypeID();
    /**
     * @brief Return the TypeID for instance.
     */
    virtual TypeID typeID() const;
    /**
     * @brief Return the typeId name for this instance.
     */
    virtual const wchar_t* const typeIDName() const;

    /**
     * @brief Return true if instance is the type id.
     */
    bool isOfType(TypeID id) const;

    /**
     * @brief Return true if instance belong to the type id.
     */
    virtual bool isOfSubType(TypeID id) const;
};


#define DXJT_ENTITY_TYPEID_HEADER(classname) \
public: \
    static TypeID classTypeID(); \
    virtual TypeID typeID() const; \
    virtual const wchar_t* const typeName() const; \
    virtual bool isOfSubType(TypeID id) const; \



#define DXJT_ENTITY_TYPEID_IMPLEMENT(classname, kTypeID, typeIDStr, baseclassname) \
    DxJtEntity::TypeID classname::classTypeID() { \
        return DxJtEntity::kTypeID; \
    } \
    DxJtEntity::TypeID classname::typeID() const {\
        return DxJtEntity::kTypeID; \
    } \
    const wchar_t* const classname::typeName() const {\
        return typeIDStr; \
    } \
    bool classname::isOfSubType(TypeID id) const {\
        if (id == classname::classTypeID()) \
            return true; \
        return baseclassname::isOfSubType(id); \
    } \


#endif  // __DXJT_TOOLKIT_ENTITY_H_
