#ifndef VTKGLOBLE_H
#define VTKGLOBLE_H


#include<vtkNew.h>
#include<vtkRenderer.h>
#include<vtkRenderWindow.h>
#include<vtkPolyDataMapper.h>
#include<vtkRenderWindowInteractor.h>

#define Create(type,name)    vtkNew<type> name


#include<QString>
QByteArray Chinese(const char *str);


#endif // VTKGLOBLE_H
