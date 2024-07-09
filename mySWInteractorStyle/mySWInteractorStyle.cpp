
#include"myAxesWidget.h"
#include"myCubeViewWidget.h"
#include"mySWInteractorStyle.h"

#include<vtkProperty.h>
#include<vtkCamera.h>
#include<vtkRenderer.h>
#include<vtkCommand.h>
#include<vtkAssemblyPath.h>
#include<vtkObjectFactory.h>
#include<vtkRenderWindow.h>
#include<vtkAbstractPropPicker.h>
#include<vtkCallbackCommand.h>
#include<vtkRenderWindowInteractor.h>

#define TargetActor vtkActor
vtkStandardNewMacro(mySWInteractorStyle);

void mySWInteractorStyle::Pan()
{
    if (!CurrentRenderer)
    {
        return;
    }

    double viewFocus[3] = {0};
    vtkCamera *camera = CurrentRenderer->GetActiveCamera();
    camera->GetFocalPoint(viewFocus);
    //相机焦点在视口坐标系投影，主要获取视口深度
    ComputeWorldToDisplay(viewFocus[0], viewFocus[1], viewFocus[2],
                          viewFocus);
    //使用上面的视口深度，计算当前鼠标位置对应的世界坐标点
    double newPickPoint[4] = {0};
    ComputeDisplayToWorld(Interactor->GetEventPosition()[0],
                          Interactor->GetEventPosition()[1],
                          viewFocus[2],
                          newPickPoint);
    //使用上面的视口深度，计算最后一次鼠标位置对应的世界坐标点
    double oldPickPoint[4] = {0};
    ComputeDisplayToWorld(Interactor->GetLastEventPosition()[0],
                          Interactor->GetLastEventPosition()[1],
                          viewFocus[2],
                          oldPickPoint);

    //计算世界坐标系中移动向量，注意方向
    double motionVector[3] = {0};
    motionVector[0] = oldPickPoint[0] - newPickPoint[0];
    motionVector[1] = oldPickPoint[1] - newPickPoint[1];
    motionVector[2] = oldPickPoint[2] - newPickPoint[2];

    //相机焦点和位置平移
    double position[3] = {0};
    camera->GetFocalPoint(viewFocus);
    camera->GetPosition(position);
    camera->SetFocalPoint(motionVector[0] + viewFocus[0],
                          motionVector[1] + viewFocus[1],
                          motionVector[2] + viewFocus[2]);

    camera->SetPosition(motionVector[0] + position[0],
                        motionVector[1] + position[1],
                        motionVector[2] + position[2]);

    if (Interactor->GetLightFollowCamera())
    {
        CurrentRenderer->UpdateLightsGeometryToFollowCamera();
    }

    Interactor->Render();
}

void mySWInteractorStyle::Spin()
{
    if ( this->CurrentRenderer == nullptr )
    {
        return;
    }

    vtkRenderWindowInteractor *rwi = this->Interactor;

    double *center = this->CurrentRenderer->GetCenter();

    double newAngle =
        vtkMath::DegreesFromRadians( atan2( rwi->GetEventPosition()[1] - center[1],
                                            rwi->GetEventPosition()[0] - center[0] ) );

    double oldAngle =
        vtkMath::DegreesFromRadians( atan2( rwi->GetLastEventPosition()[1] - center[1],
                                            rwi->GetLastEventPosition()[0] - center[0] ) );

    vtkCamera *camera = this->CurrentRenderer->GetActiveCamera();
    camera->Roll( newAngle - oldAngle );
    camera->OrthogonalizeViewUp();

    rwi->Render();
}

void mySWInteractorStyle::Dolly()
{
    if (!CurrentRenderer)
    {
        return;
    }

    double *center = CurrentRenderer->GetCenter();
    int dy = Interactor->GetEventPosition()[1] - Interactor->GetLastEventPosition()[1];
    double dyf = m_MotionFactor * dy / center[1];
    Dolly(pow(1.1, dyf));
}

void mySWInteractorStyle::Rotate()
{
    if (this->CurrentRenderer == nullptr)
    {
        return;
    }

    vtkRenderWindowInteractor *rwi = this->Interactor;

    int dx = rwi->GetEventPosition()[0] - rwi->GetLastEventPosition()[0];
    int dy = rwi->GetEventPosition()[1] - rwi->GetLastEventPosition()[1];

    int *size = this->CurrentRenderer->GetRenderWindow()->GetSize();

    double delta_elevation = -20.0 / size[1];
    double delta_azimuth = -20.0 / size[0];

    double rxf = dx * delta_azimuth * this->m_MotionFactor;
    double ryf = dy * delta_elevation * this->m_MotionFactor;

    vtkCamera *camera = this->CurrentRenderer->GetActiveCamera();
    camera->Azimuth(rxf);
    camera->Elevation(ryf);
    camera->OrthogonalizeViewUp();

    if (this->AutoAdjustCameraClippingRange)
    {
        this->CurrentRenderer->ResetCameraClippingRange();
    }

    if (rwi->GetLightFollowCamera())
    {
        this->CurrentRenderer->UpdateLightsGeometryToFollowCamera();
    }

    rwi->Render();
}

void mySWInteractorStyle::OnChar()
{
    int x = 0, y = 0;
    Interactor->GetEventPosition(x, y);
    FindPokedRenderer(x, y);
    if(!CurrentRenderer) {
        return;
    }
    char key = Interactor->GetKeyCode();
    if(key == ' ') {
        onCubeView();
    }
}

void mySWInteractorStyle::endMove()
{
    if(m_axesWidget)
    {
        m_axesWidget->Delete();
        m_axesWidget = nullptr;
    }
}

void mySWInteractorStyle::startMove()
{
    if(m_axesWidget) {
        m_axesWidget->Delete();
    }
    TargetActor *actor = TargetActor::SafeDownCast(CurrentProp);

    if(actor)
    {
        m_axesWidget = myAxesWidget::New();
        m_axesWidget->SetInteractor(Interactor);
        m_axesWidget->setActor(actor);
        m_axesWidget->EnabledOn();
    }
}

void mySWInteractorStyle::onCubeView()
{
    if(m_cubeView)
    {
        if(m_cubeView->GetEnabled()) {
            m_cubeView->EnabledOff();
        }
        else {
            m_cubeView->EnabledOn();
        }
        Interactor->Render();
    }
    else
    {
        m_cubeView = myCubeViewWidget::New();
        m_cubeView->SetInteractor(Interactor);
        m_cubeView->EnabledOn();
    }
}

void mySWInteractorStyle::OnMouseMove()
{
    int x = this->Interactor->GetEventPosition()[0];
    int y = this->Interactor->GetEventPosition()[1];

    switch (this->State)
    {
        case VTKIS_ROTATE:
            this->FindPokedRenderer(x, y);
            this->Rotate();
            this->InvokeEvent(vtkCommand::InteractionEvent, nullptr);
            break;

        case VTKIS_PAN:
            this->FindPokedRenderer(x, y);
            this->Pan();
            this->InvokeEvent(vtkCommand::InteractionEvent, nullptr);
            break;

        case VTKIS_DOLLY:
            this->FindPokedRenderer(x, y);
            this->Dolly();
            this->InvokeEvent(vtkCommand::InteractionEvent, nullptr);
            break;

        case VTKIS_SPIN:
            this->FindPokedRenderer(x, y);
            this->Spin();
            this->InvokeEvent(vtkCommand::InteractionEvent, nullptr);
            break;
    }

}

void mySWInteractorStyle::OnLeftButtonUp()
{
}

void mySWInteractorStyle::OnRightButtonUp()
{

}

mySWInteractorStyle::mySWInteractorStyle()
{
    m_MotionFactor   = 10.0;
    m_axesWidget = nullptr;
    m_cubeView = nullptr;
    memset(m_preColor, 0, sizeof (m_preColor));
}

mySWInteractorStyle::~mySWInteractorStyle()
{
    if(m_cubeView)
    {
        m_cubeView->Delete();
        m_cubeView = nullptr;
    }

    if(m_axesWidget)
    {
        m_axesWidget->Delete();
        m_axesWidget = nullptr;
    }

}

void mySWInteractorStyle::OnLeftButtonDown()
{
    int x = 0, y = 0;
    Interactor->GetEventPosition(x, y);
    FindPokedRenderer(x, y);
    if(!CurrentRenderer) {
        return;
    }

    vtkAssemblyPath *path = nullptr;
    vtkAbstractPropPicker *picker = vtkAbstractPropPicker::SafeDownCast(Interactor->GetPicker());
    if ( picker != nullptr )
    {
        picker->Pick(x, y, 0, CurrentRenderer);
        path = picker->GetPath();
    }
    if ( path == nullptr )
    {
        endMove();                      //要在HighlightProp前面，因为要使用currentProp
        PropPicked = 0;
        HighlightProp(nullptr);
    }
    else
    {
        HighlightProp(path->GetLastNode()->GetViewProp());
        PropPicked = 1;
    }

    int count = Interactor->GetRepeatCount();
    if(count == 1 && TargetActor::SafeDownCast(CurrentProp)) {
        startMove();
    }
    Interactor->Render();
}

void mySWInteractorStyle::OnMiddleButtonUp()
{
    switch (State)
    {
        case VTKIS_PAN:
            EndPan();
            break;

        case VTKIS_ROTATE:
            EndRotate();
            break;
        case VTKIS_DOLLY:
            EndDolly();
            break;
        default:
            break;
    }

    if ( Interactor )    {
        ReleaseFocus();
    }
}

void mySWInteractorStyle::OnRightButtonDown()
{

}

void mySWInteractorStyle::OnMiddleButtonDown()
{

    //确定currentRender
    int x = 0, y = 0;
    Interactor->GetEventPosition(x, y);
    FindPokedRenderer(x, y);
    if (!CurrentRenderer)
    {
        return;
    }

    int count = Interactor->GetRepeatCount();
    if(count == 0)//单击
    {
        GrabFocus(EventCallbackCommand);

        //如果按住Ctrl键，开始平移，否则旋转
        if(Interactor->GetShiftKey())    {
            StartDolly();
        }
        else if (Interactor->GetControlKey())    {
            StartPan();
        }
        else    {
            StartRotate();
        }
    }
    else//双击
    {
        CurrentRenderer->ResetCamera();
        Interactor->Render();
    }

}

void mySWInteractorStyle::Dolly(double factor)
{
    if (!CurrentRenderer)    {
        return;
    }

    vtkCamera *camera = CurrentRenderer->GetActiveCamera();

    //获取当前焦点
    double focus[3] = {0};
    camera->GetFocalPoint(focus);
    //焦点转为视口坐标系，求视口深度
    double disPt[3] = {0};
    ComputeWorldToDisplay(focus[0], focus[1], focus[2], disPt);
    //计算当前鼠标位置
    int x = 0, y = 0;
    Interactor->GetEventPosition(x, y);
    //以上面的视口深度，鼠标位置，计算世界坐标点
    double preWorldPt[4] = {0};
    ComputeDisplayToWorld(x, y, disPt[2], preWorldPt);

    if (camera->GetParallelProjection())
    {
        camera->SetParallelScale(camera->GetParallelScale() / factor);
    }
    else
    {
        camera->Dolly(factor);
        if (AutoAdjustCameraClippingRange)
        {
            CurrentRenderer->ResetCameraClippingRange();
        }
    }

    //获取当前焦点
    camera->GetFocalPoint(focus);
    //焦点转为视口坐标系，求视口深度
    ComputeWorldToDisplay(focus[0], focus[1], focus[2], disPt);
    //以上面的视口深度，鼠标位置，计算世界坐标点
    double curWorldPt[4] = {0};
    ComputeDisplayToWorld(x, y, disPt[2], curWorldPt);


    //相机焦点到上面的世界坐标点向量
    double vec[3] = {
        preWorldPt[0] - curWorldPt[0],
        preWorldPt[1] - curWorldPt[1],
        preWorldPt[2] - curWorldPt[2],
    };

    double position[3] = {0};
    camera->GetPosition(position);

    vtkMath::Add(focus, vec, focus);
    vtkMath::Add(position, vec, position);
    camera->SetFocalPoint(focus);
    camera->SetPosition(position);

    if (Interactor->GetLightFollowCamera())
    {
        CurrentRenderer->UpdateLightsGeometryToFollowCamera();
    }

    Interactor->Render();
}

void mySWInteractorStyle::OnMouseWheelForward()
{
    //先确定currentRender
    int x = 0, y = 0;
    Interactor->GetEventPosition(x, y);
    FindPokedRenderer(x, y);
    if (!CurrentRenderer)    {
        return;
    }

    GrabFocus(EventCallbackCommand);

    StartDolly();
    double factor = m_MotionFactor * -0.2 * MouseWheelMotionFactor;
    Dolly(pow(1.1, factor));
    EndDolly();
    ReleaseFocus();
}

void mySWInteractorStyle::OnMouseWheelBackward()
{
    //先确定currentRender
    int x = 0, y = 0;
    Interactor->GetEventPosition(x, y);
    FindPokedRenderer(x, y);
    if (!CurrentRenderer)    {
        return;
    }

    GrabFocus(EventCallbackCommand);

    StartDolly();
    double factor = m_MotionFactor * 0.2 * MouseWheelMotionFactor;
    Dolly(pow(1.1, factor));
    EndDolly();
    ReleaseFocus();
}

void mySWInteractorStyle::HighlightProp(vtkProp *prop)
{
    if(prop == CurrentProp) {
        return;
    }

    vtkActor *actor = vtkActor::SafeDownCast(CurrentProp);
    if(actor) {
        actor->GetProperty()->SetColor(m_preColor);
    }
    CurrentProp = prop;
    actor = vtkActor::SafeDownCast(prop);
    if(actor) {

        memcpy(m_preColor, actor->GetProperty()->GetColor(), sizeof (m_preColor));
        actor->GetProperty()->SetColor(PickColor);
    }
}

void mySWInteractorStyle::PrintSelf(ostream &os, vtkIndent indent)
{
    Superclass::PrintSelf(os, indent);
    os << indent << "m_MotionFactor: " << m_MotionFactor << "\n";
}
