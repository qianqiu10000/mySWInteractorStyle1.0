#include"vtkGloble.h"
#include"vtkModelInit.h"
#include"mySWInteractorStyle.h"

#include<vtkConeSource.h>


int main(int argc, char *argv[])
{

    Create(vtkRenderer, render);
    Create(vtkRenderWindow, window);
    window->AddRenderer(render);
    Create(vtkRenderWindowInteractor, inter);
    inter->SetRenderWindow(window);
    Create(mySWInteractorStyle, style);
    inter->SetInteractorStyle(style);



    Create(vtkConeSource, source);
    Create(vtkPolyDataMapper, mapper);
    mapper->SetInputConnection(source->GetOutputPort());
    vtkNew<vtkActor> cones[5];
    for(int i = 0; i < 5; i++)
    {
        cones[i]->SetMapper(mapper);
        cones[i]->SetPosition(vtkMath::Random(-5, 5), vtkMath::Random(-5, 5), vtkMath::Random(-5, 5));
        render->AddActor(cones[i]);
    }


    inter->Initialize();
    inter->Start();
    return 0;
}
