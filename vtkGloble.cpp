#include "vtkGloble.h"

QByteArray Chinese(const char *str)
{
    return
        QString::fromLocal8Bit(str).toUtf8();
}
