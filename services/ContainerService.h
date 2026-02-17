#ifndef CONTAINERSERVICE_H
#define CONTAINERSERVICE_H

#include <QString>

class ContainerService
{
public:
    static bool createContainer(const QString& name);
    static bool addToContainer(int containerId, int productId, int qty);
};

#endif
