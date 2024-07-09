#include "myCubeViewWidget.h"
#include"myCubeViewRep.h"
#include"mySWInteractorStyle.h"

#include<vtkRenderer.h>
#include<vtkCommand.h>
#include<vtkWidgetEvent.h>
#include<vtkObjectFactory.h>
#include<vtkActorCollection.h>
#include<vtkCallbackCommand.h>
#include<vtkRenderWindowInteractor.h>
#include<vtkWidgetCallbackMapper.h>

vtkStandardNewMacro(myCubeViewWidget);

myCubeViewWidget::myCubeViewWidget()
{
    KeyPressActivationValue = 0;

    CallbackMapper->SetCallbackMethod(
        vtkCommand::LeftButtonPressEvent,
        vtkWidgetEvent::Select,
        this,
        leftButtonPress);

    CallbackMapper->SetCallbackMethod(
        vtkCommand::LeftButtonReleaseEvent,
        vtkWidgetEvent::EndSelect,
        this,
        leftButtonRelease);

    CallbackMapper->SetCallbackMethod(
        vtkCommand::MouseMoveEvent,
        vtkWidgetEvent::Move,
        this,
        mouseMove);



}

myCubeViewWidget::~myCubeViewWidget()
{
}

void myCubeViewWidget::SetEnabled(int enable)
{
    vtkRenderer *render = nullptr;
    if(enable)
    {
        vtkAbstractWidget::SetEnabled(enable);//创建currenRender,WidgetRep
        render = CurrentRenderer;
    }
    else {
        render = CurrentRenderer;
        vtkAbstractWidget::SetEnabled(enable);//清零CurrenRender，还要用到WidgeRep
        if(WidgetRep)
        {
            WidgetRep->Delete();
            WidgetRep = nullptr;
        }
    }

    if(render) {
        render->ResetCamera();
    }
    Interactor->Render();
}

void myCubeViewWidget::CreateDefaultRepresentation()
{
    if(WidgetRep) {
        return;
    }

    WidgetRep = myCubeViewRep::New();
}

void myCubeViewWidget::mouseMove(vtkAbstractWidget *widget)
{
    myCubeViewWidget *self = dynamic_cast<myCubeViewWidget *>(widget);
    int x = 0, y = 0;
    self->Interactor->GetEventPosition(x, y);
    double newPos[2] = {0};
    newPos[0] = x;
    newPos[1] = y;
    self->WidgetRep->WidgetInteraction(newPos);
    if(self->WidgetRep->GetNeedToRender()) {
        self->Interactor->Render();
    }
}

void myCubeViewWidget::PrintSelf(std::ostream &os, vtkIndent indent)
{
    Superclass::PrintSelf(os, indent);
}

void myCubeViewWidget::leftButtonPress(vtkAbstractWidget *widget)
{
    myCubeViewWidget *self = static_cast<myCubeViewWidget *>(widget);
    int x = 0, y = 0;
    self->Interactor->GetEventPosition(x, y);
    double pos[2] = {0};
    pos[0] = x;
    pos[1] = y;
    self->WidgetRep->StartWidgetInteraction(pos);
    if(self->WidgetRep->GetNeedToRender() ) {
        self->Interactor->Render();
        self->EventCallbackCommand->AbortFlagOn();
    }
}

void myCubeViewWidget::leftButtonRelease(vtkAbstractWidget *widget)
{
    myCubeViewWidget *self = dynamic_cast<myCubeViewWidget *>(widget);
    int x = 0, y = 0;
    self->Interactor->GetEventPosition(x, y);
    double pos[2] = {0};
    pos[0] = x;
    pos[1] = y;
    self->WidgetRep->EndWidgetInteraction(pos);
    if(self->WidgetRep->GetNeedToRender()) {
        self->EnabledOff();
    }
}

