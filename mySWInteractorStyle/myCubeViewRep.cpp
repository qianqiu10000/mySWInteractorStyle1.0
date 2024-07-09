#include "myCubeViewRep.h"

#include<vtkNew.h>
#include<vtkActor.h>
#include<vtkPoints.h>
#include<vtkCamera.h>
#include<vtkProperty.h>
#include<vtkPolygon.h>
#include<vtkPolyData.h>
#include<vtkCellArray.h>
#include<vtkRenderer.h>
#include<vtkTransform.h>
#include<vtkPropPicker.h>
#include<vtkWeakPointer.h>
#include<vtkInteractorStyle.h>
#include<vtkPickingManager.h>
#include<vtkRenderWindow.h>
#include<vtkPolyDataMapper.h>
#include<vtkRenderWindowInteractor.h>

#define Create(type,name)\
    vtkNew<type> name;


class computeViewUp
{
public:
    //相机焦点
    void setFocalPoint(double t[3])    {
        for(int i = 0; i < 3; i++) {
            m_focal[i] = t[i];
        }
    }
    //相机焦点
    void setFocalPoint(double x, double y, double z)    {
        m_focal[0] = x;
        m_focal[1] = y;
        m_focal[2] = z;
    }
    //相机位置
    void setPosition(double p[3])    {
        for(int i = 0; i < 3; i++) {
            m_postion[i] = p[i];
        }
    }
    //相机位置
    void setPosition(double x, double y, double z)    {
        m_postion[0] = x;
        m_postion[1] = y;
        m_postion[2] = z;
    }

    //相机朝上方向
    double *viewUp()    {
        double xf = m_focal[0];
        double yf = m_focal[1];
        double zf = m_focal[2];
        double xp = m_postion[0];
        double yp = m_postion[1];
        double zp = m_postion[2];
        double dx = std::abs(xf - xp);
        double dy = std::abs(yf - yp);
        double dz = std::abs(zf - zp);

        //如果dy太小，说明视线几乎平行于XZ平面，认为（0，1，0）就是上
        if(dy < 0.1) {
            return m_viewUp;
        }

        //如果dx+dz太小，说明视线几乎平行于Y轴
        //此时默认Z轴是up方向，±需要根据yp和yf(俯视仰视)判断
        if(dx + dz < 0.1)        {
            m_viewUp[0] = 0;
            m_viewUp[1] = 0;
            m_viewUp[2] =  yp > yf ? -1 : 1;
            return m_viewUp;
        }

        //一般情况下，根据几何法求解。
        //过Y轴上一点T，做视线的垂线，相交于位置点P
        //焦点是F，此时PT垂直于PF
        //根据相似三角形 PT在Y轴投影距离y = (dx * dx + dz * dz) / dy，大于零
        //视线PF在XZ平面投影(xp-xf,zp-zf)
        //yp>yf说明是俯视，PT在XZ投影(xf - xp,zf - zp)
        //yp<yf说明是仰视，PT在XZ投影(xp - xf,zp - zf)
        double y =  (dx * dx + dz * dz) / dy;
        m_viewUp[0] = yp > yf ? xf - xp : xp - xf;
        m_viewUp[1] = y;
        m_viewUp[2] = yp > yf ? zf - zp : zp - zf;
        return m_viewUp;
    }

private:
    double m_focal[3] = {0};
    double m_postion[3] = {3};
    double m_viewUp[3] = {0, 1, 0};
};

vtkStandardNewMacro(myCubeViewRep);

myCubeViewRep::myCubeViewRep()
{
    InteractionState = OutSide;
    m_picker = nullptr;

    for(int i = 0; i < 6; i++) {
        m_actors[i] = createFace(i);
    }

    for(int i = 0; i < 12; i++) {
        m_actors[i + 6] = createEdge(i);
    }

    for(int i = 0; i < 8; i++) {
        m_actors[i + 6 + 12] = createCorner(i);
    }
}

myCubeViewRep::~myCubeViewRep()
{
    for(int i = 0; i < ActorNumber; i++)
        if(m_actors[i])
        {
            Renderer->RemoveActor(m_actors[i]);
            m_actors[i]->Delete();
            m_actors[i] = nullptr;
        }
}

void myCubeViewRep::RegisterPickers()
{
    if(!m_picker)
    {
        m_picker = vtkPropPicker::New();
        for(int i = 0; i < ActorNumber; i++) {
            m_picker->AddPickList(m_actors[i]);
        }
    }
}

void myCubeViewRep::UnRegisterPickers()
{
    if(m_picker)
    {
        m_picker->Delete();
        m_picker = nullptr;
    }
}

void myCubeViewRep::BuildRepresentation()
{
    PlaceWidget(Renderer->ComputeVisiblePropBounds());
    for(int i = 0; i < ActorNumber; i++) {
        Renderer->AddActor(m_actors[i]);
    }
}

void myCubeViewRep::Highlight(int highlightOn)
{
    for(int i = 0; i < ActorNumber; i++)
    {
        m_actors[i]->GetProperty()->SetLineWidth(1);
        m_actors[i]->GetProperty()->SetEdgeColor(0, 0, 0);
    }

    if(InteractionState == OutSide) {
        return;
    }

    if(highlightOn )
    {
        m_actors[InteractionState]->GetProperty()->SetLineWidth(5);
        m_actors[InteractionState]->GetProperty()->SetEdgeColor(1, 0, 0);
    }
}

vtkActor *myCubeViewRep::createFace(int num)
{
    Create(vtkPoints, points);
    points->InsertNextPoint(-0.29, 0.39, 0.5);
    points->InsertNextPoint(-0.39, 0.29, 0.5);
    points->InsertNextPoint(-0.39, -0.29, 0.5);
    points->InsertNextPoint(-0.29, -0.39, 0.5);
    points->InsertNextPoint(0.29, -0.39, 0.5);
    points->InsertNextPoint(0.39, -0.29, 0.5);
    points->InsertNextPoint(0.39, 0.29, 0.5);
    points->InsertNextPoint(0.29, 0.39, 0.5);
    Create(vtkPolygon, polygon);
    polygon->GetPointIds()->InsertNextId(0);
    polygon->GetPointIds()->InsertNextId(1);
    polygon->GetPointIds()->InsertNextId(2);
    polygon->GetPointIds()->InsertNextId(3);
    polygon->GetPointIds()->InsertNextId(4);
    polygon->GetPointIds()->InsertNextId(5);
    polygon->GetPointIds()->InsertNextId(6);
    polygon->GetPointIds()->InsertNextId(7);

    Create(vtkCellArray, cells);
    cells->InsertNextCell(polygon);

    Create(vtkPolyData, polydata);
    polydata->SetPoints(points);
    polydata->SetPolys(cells);

    Create(vtkPolyDataMapper, mapper);
    mapper->SetInputData(polydata);

    vtkActor *actor = vtkActor::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(1, 1, 1);
    actor->GetProperty()->SetOpacity(0.8);
    actor->GetProperty()->EdgeVisibilityOn();
    actor->GetProperty()->SetEdgeColor(0, 0, 0);

    Create(vtkTransform, tranform);
    tranform->Identity();

    switch (num) {
        case 1:
            tranform->RotateY(90);
            break;
        case 2:
            tranform->RotateY(180);
            break;
        case 3:
            tranform->RotateY(-90);
            break;
        case 4:
            tranform->RotateX(-90);
            break;
        case 5:
            tranform->RotateX(90);
            break;
    }

    actor->SetUserTransform(tranform);

    return actor;
}

vtkActor *myCubeViewRep::createEdge(int num)
{
    Create(vtkPoints, points);
    points->InsertNextPoint(-0.29, 0.5, 0.39);
    points->InsertNextPoint(-0.29, 0.39, 0.5);
    points->InsertNextPoint(0.29, 0.39, 0.5);
    points->InsertNextPoint(0.29, 0.5, 0.39);
    Create(vtkPolygon, polygon);
    polygon->GetPointIds()->InsertNextId(0);
    polygon->GetPointIds()->InsertNextId(1);
    polygon->GetPointIds()->InsertNextId(2);
    polygon->GetPointIds()->InsertNextId(3);


    Create(vtkCellArray, cells);
    cells->InsertNextCell(polygon);

    Create(vtkPolyData, polydata);
    polydata->SetPoints(points);
    polydata->SetPolys(cells);

    Create(vtkPolyDataMapper, mapper);
    mapper->SetInputData(polydata);


    vtkActor *actor = vtkActor::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(1, 1, 1);
    actor->GetProperty()->SetOpacity(0.8);
    actor->GetProperty()->EdgeVisibilityOn();
    actor->GetProperty()->SetEdgeColor(0, 0, 0);


    Create(vtkTransform, tranform);
    tranform->Identity();

    switch (num) {
        case 1:
            tranform->RotateY(90);
            break;
        case 2:
            tranform->RotateY(180);
            break;
        case 3:
            tranform->RotateY(-90);
            break;
        case 4:
            tranform->RotateX(90);
            break;
        case 5:
            tranform->RotateX(90);
            tranform->RotateZ(90);
            break;
        case 6:
            tranform->RotateX(90);
            tranform->RotateZ(180);
            break;
        case 7:
            tranform->RotateX(90);
            tranform->RotateZ(-90);
            break;
        case 8:
            tranform->RotateZ(90);
            break;
        case 9:
            tranform->RotateZ(90);
            tranform->RotateX(90);
            break;
        case 10:
            tranform->RotateZ(90);
            tranform->RotateX(180);
            break;
        case 11:
            tranform->RotateZ(90);
            tranform->RotateX(-90);
            break;
    }

    actor->SetUserTransform(tranform);

    return actor;

}

vtkActor *myCubeViewRep::createCorner(int num)
{
    Create(vtkPoints, points);
    points->InsertNextPoint(-0.39, 0.5, 0.29);
    points->InsertNextPoint(-0.5, 0.39, 0.29);
    points->InsertNextPoint(-0.5, 0.29, 0.39);
    points->InsertNextPoint(-0.39, 0.29, 0.5);
    points->InsertNextPoint(-0.29, 0.39, 0.5);
    points->InsertNextPoint(-0.29, 0.5, 0.39);
    Create(vtkPolygon, polygon);
    polygon->GetPointIds()->InsertNextId(0);
    polygon->GetPointIds()->InsertNextId(1);
    polygon->GetPointIds()->InsertNextId(2);
    polygon->GetPointIds()->InsertNextId(3);
    polygon->GetPointIds()->InsertNextId(4);
    polygon->GetPointIds()->InsertNextId(5);

    Create(vtkCellArray, cells);
    cells->InsertNextCell(polygon);

    Create(vtkPolyData, polydata);
    polydata->SetPoints(points);
    polydata->SetPolys(cells);

    Create(vtkPolyDataMapper, mapper);
    mapper->SetInputData(polydata);

    vtkActor *actor = vtkActor::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(1, 1, 1);
    actor->GetProperty()->SetOpacity(0.8);
    actor->GetProperty()->EdgeVisibilityOn();
    actor->GetProperty()->SetEdgeColor(0, 0, 0);


    Create(vtkTransform, tranform);
    tranform->Identity();

    switch (num) {
        case 1:
            tranform->RotateY(90);
            break;
        case 2:
            tranform->RotateY(180);
            break;
        case 3:
            tranform->RotateY(-90);
            break;
        case 4:
            tranform->RotateX(90);
            break;
        case 5:
            tranform->RotateX(90);
            tranform->RotateZ(90);
            break;
        case 6:
            tranform->RotateX(90);
            tranform->RotateZ(180);
            break;
        case 7:
            tranform->RotateX(90);
            tranform->RotateZ(-90);
            break;
    }

    actor->SetUserTransform(tranform);

    return actor;
}

void myCubeViewRep::PlaceWidget(double bounds[])
{
    for(int i = 0; i < 6; i++) {
        InitialBounds[i] = bounds[i];
    }

    double dx = std::abs(bounds[0] - bounds[1]);
    double dy = std::abs(bounds[2] - bounds[3]);
    double dz = std::abs(bounds[4] - bounds[5]);

    //用最长边计算比例因子
    double max = std::max(dx, dy);
    max = std::max(max, dz);
    PlaceFactor = std::max(max, 0.5) ;

    //计算bounds中心
    double center[3] = {0};
    center[0] = (bounds[0] + bounds[1]) / 2.0;
    center[1] = (bounds[2] + bounds[3]) / 2.0;
    center[2] = (bounds[4] + bounds[5]) / 2.0;

    //平移和缩放变换
    for(int i = 0; i < ActorNumber; i++)    {
        vtkTransform *transform =
            vtkTransform::SafeDownCast(m_actors[i]->GetUserTransform());
        //将这些操作插入到原来旋转的前面，先平移再旋转
        //因为旋转之后xyz坐标系也变了，此时平移的XYZ不对
        transform->PostMultiply();
        transform->Scale(PlaceFactor, PlaceFactor, PlaceFactor );
        transform->Translate(center);
    }
}

void myCubeViewRep::StartWidgetInteraction(double *eventPos)
{
    int newState = ComputeInteractionState(eventPos[0], eventPos[1]);
    if(newState != OutSide)
    {
        m_actors[newState]->GetProperty()->SetColor(0, 1, 0);
        NeedToRender = true;
    }
    else {
        NeedToRender = false;
    }

}

void myCubeViewRep::WidgetInteraction(double *newEventPos)
{
    int oldState = InteractionState;
    int newState = ComputeInteractionState(newEventPos[0], newEventPos[1]);
    if(oldState != newState)
    {
        if(newState == OutSide) {
            Highlight(false);
        }
        else {
            Highlight(true);
        }

        NeedToRender = true;
    }
    else {
        NeedToRender = false;
    }
}

void myCubeViewRep::PrintSelf(std::ostream &os, vtkIndent indent)
{
    Superclass::PrintSelf(os, indent);
    os << indent << "Number of Actors:" << ActorNumber << "\n";
}

void myCubeViewRep::EndWidgetInteraction(double *newEventPos)
{
    ComputeInteractionState(newEventPos[0], newEventPos[1]);
    if(InteractionState != OutSide)
    {
        vtkCamera *camera = Renderer->GetActiveCamera();

        double focal[3] = {0};
        computeCenter(InitialBounds, focal);
        camera->SetFocalPoint(focal);
        camera->SetPosition(m_actors[InteractionState]->GetCenter());

        computeViewUp viewup;
        viewup.setFocalPoint(camera->GetFocalPoint());
        viewup.setPosition(camera->GetPosition());
        camera->SetViewUp(viewup.viewUp());

        for(int i = 0; i < ActorNumber; i++) {
            Renderer->RemoveActor(m_actors[i]);
        }

        Renderer->ResetCamera();

        NeedToRender = true;
    }
    else {
        NeedToRender = false;
    }
}

void myCubeViewRep::computeCenter(double *bound, double *center)
{
    center[0] = (bound[0] + bound[1]) / 2.0;
    center[1] = (bound[2] + bound[3]) / 2.0;
    center[2] = (bound[4] + bound[5]) / 2.0;

}

int myCubeViewRep::ComputeInteractionState(int X, int Y, int vtkNotUsed(modify) )
{

    InteractionState = OutSide;
    if(!Renderer || !Renderer->IsInViewport(X, Y)) {
        return InteractionState;
    }

    m_picker->PickProp(X, Y, Renderer);
    vtkActor *actor = m_picker->GetActor();

    for(int i = 0; i < ActorNumber; i++)
    {
        if(actor == m_actors[i])
        {
            InteractionState = i;
            break;
        }
    }

    return InteractionState;
}


