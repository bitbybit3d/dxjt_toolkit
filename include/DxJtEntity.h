//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2019 by bitbybit3d, All rights reserved. 
// Author: bitbybit3d@163.com 
// 
// 
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, 
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
//////////////////////////////////////////////////////////////////////////////
#ifndef __JT_TOOLKIT_ENTITY_H_
#define __JT_TOOLKIT_ENTITY_H_

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
protected:
    DxJtEntity();

private:
    DxJtEntity(const DxJtEntity&);              // copy constructor
    DxJtEntity& operator=(const DxJtEntity&);   // assignment operator

public:
    virtual ~DxJtEntity();

    enum TypeID {
        JtkNONE,
        JtkENTITY,
        JtkHIERARCHY,
        JtkUNITHIERARCHY,
        JtkASSEMBLY,
        JtkPART,
        JtkINSTANCE,
        JtkATTRIB,
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
    const wchar_t* typeIDName() const;

    bool isOfType(TypeID id) const;

    /**
     * @brief Return true if instance belong to the type id.
     */
    virtual bool isOfSubType(TypeID id) const;
};

#endif  // __JT_TOOLKIT_ENTITY_H_
