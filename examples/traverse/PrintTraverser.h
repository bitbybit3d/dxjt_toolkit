#pragma once

#include "DxJtTraverser.h"

class PrintTraverser : public DxJtTraverser
{
public:
    PrintTraverser() {}

    virtual bool preActionCallback(std::shared_ptr<DxJtHierarchy> CurrNode, int Level);
};
