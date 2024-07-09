#include"myAxesRep.h"
#include"myAxesWidget.h"

#include<vtkProp.h>
#include<vtkWidgetEvent.h>
#include<vtkObjectFactory.h>
#include<vtkCallbackCommand.h>
#include<vtkWidgetCallbackMapper.h>
#include<vtkRenderWindowInteractor.h>

vtkStandardNewMacro(myAxesWidget);

myAxesWidget::myAxesWidget()
{
    m_actor = nullptr;
    KeyPressActivationValue = 0;

    CallbackMapper->SetCallbackMethod(vtkCommand::LeftButtonPressEvent,
                                      vtkWidgetEvent::Select, this, leftButtonPress);
    CallbackMapper->SetCallbackMethod(vtkCommand::LeftButtonReleaseEvent,
                                      vtkWidgetEvent::EndSelect, this, leftButtonRelease);
    CallbackMapper->SetCallbackMethod(vtkCommand::MouseMoveEvent,
                                      vtkWidgetEvent::Move, this, mouseMove);
}

myAxesWidget::~myAxesWidget()
{

}

void myAxesWidget::SetEnabled(int enable)
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

    Interactor->Render();
}

void myAxesWidget::setActor(vtkActor *actor)
{
    m_actor = actor;
}

void myAxesWidget::CreateDefaultRepresentation()
{
    if(!WidgetRep) {
        WidgetRep = myAxesRep::New();
        static_cast<myAxesRep *>(WidgetRep)->setActor(m_actor);
    }
}

void myAxesWidget::mouseMove(vtkAbstractWidget *w)
{
    myAxesWidget *self = static_cast<myAxesWidget *>(w);
    int x = 0, y = 0;
    self->Interactor->GetEventPosition(x, y);
    double pos[2] = {0};
    pos[0] = x;
    pos[1] = y;
    self->WidgetRep->WidgetInteraction(pos);
    if(self->WidgetRep->GetNeedToRender() ) {
        self->Interactor->Render();
    }
}

void myAxesWidget::leftButtonPress(vtkAbstractWidget *w)
{

    myAxesWidget *self = static_cast<myAxesWidget *>(w);
    int x = 0, y = 0;
    self->Interactor->GetEventPosition(x, y);
    double pos[2] = {0};
    pos[0] = x;
    pos[1] = y;
    self->WidgetRep->StartWidgetInteraction(pos);
    if(self->WidgetRep->GetInteractionState() != myAxesRep::OutSide) {
        self->EventCallbackCommand->AbortFlagOn();
    }
}

void myAxesWidget::leftButtonRelease(vtkAbstractWidget *w)
{
    myAxesWidget *self = static_cast<myAxesWidget *>(w);
    int x = 0, y = 0;
    self->Interactor->GetEventPosition(x, y);
    double pos[2] = {0};
    pos[0] = x;
    pos[1] = y;
    self->WidgetRep->EndWidgetInteraction(pos);

}

void myAxesWidget::PrintSelf(std::ostream &os, vtkIndent indent)
{
    Superclass::PrintSelf(os, indent);
    os << indent << "Current Actor:" << m_actor << "\n";
}
