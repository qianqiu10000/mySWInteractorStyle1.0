
#include"myAxesRep.h"


#include<vtkPoints.h>
#include<vtkProperty.h>
#include<vtkRenderer.h>
#include<vtkCellArray.h>
#include<vtkAssembly.h>
#include<vtkTransform.h>
#include<vtkArcSource.h>
#include<vtkPropPicker.h>
#include<vtkPropPicker.h>
#include<vtkArrowSource.h>
#include<vtkTriangleStrip.h>
#include<vtkAssemblyPath.h>
#include<vtkLinearTransform.h>
#include<vtkPolyDataMapper.h>
#include<vtkInteractorObserver.h>

#define Create(type,name) \
    vtkNew<type> name

vtkStandardNewMacro(myAxesRep);

myAxesRep::myAxesRep()
{
    m_picker = nullptr;
    m_opActor = nullptr;
    m_pressedState = OutSide;
    InteractionState = OutSide;
    memset(m_actors, 0, sizeof (m_actors));
    memset(m_preEventPos, 0, sizeof (m_preEventPos));
    memset(m_preWorldPos, 0, sizeof (m_preWorldPos));


    createActors();
    clearUserTransfrom();
}

myAxesRep::~myAxesRep()
{

    for(int i = 0; i < ActorNum; i++)
        if(m_actors[i])
        {
            Renderer->RemoveActor(m_actors[i]);
            m_actors[i]->Delete();
            m_actors[i] = nullptr;
        }
}

void myAxesRep::createActors()
{
    //创造基础箭头
    Create(vtkArrowSource, aSource);
    Create(vtkPolyDataMapper, aMapper);
    aMapper->SetInputConnection(aSource->GetOutputPort());

    //X箭头
    {
        m_actors[0] = vtkActor::New();
        m_actors[0]->SetMapper(aMapper);
        m_actors[0]->GetProperty()->SetColor(1, 0, 0);
    }
    //Y箭头
    {
        m_actors[1] = vtkActor::New();
        m_actors[1]->RotateZ(90);
        m_actors[1]->SetMapper(aMapper);
        m_actors[1]->GetProperty()->SetColor(0, 1, 0);
    }
    //Z箭头
    {
        m_actors[2] = vtkActor::New();
        m_actors[2]->RotateY(-90);
        m_actors[2]->SetMapper(aMapper);
        m_actors[2]->GetProperty()->SetColor(0, 0, 1);
    }

    //创造基础形状

    Create(vtkPolyDataMapper, rMapper);
    {
        int resolution = 9;
        Create(vtkArcSource, arc1);
        arc1->SetResolution(resolution);
        arc1->SetCenter(0, 0, 0);
        arc1->SetPoint1(0, 0.7746, 0.2);
        arc1->SetPoint2(0, 0.2, 0.7746);
        arc1->Update();
        vtkPoints *points1 = arc1->GetOutput()->GetPoints();

        Create(vtkArcSource, arc2);
        arc2->SetResolution(resolution);
        arc2->SetCenter(0, 0, 0);
        arc2->SetPoint1(0, 0.9798, 0.2);
        arc2->SetPoint2(0, 0.2, 0.9798);
        arc2->Update();
        vtkPoints *points2 = arc2->GetOutput()->GetPoints();

        //添加点
        Create(vtkPoints, points);
        for(int i = 0; i < resolution + 1; i++) {
            points->InsertNextPoint(points1->GetPoint(i));
            points->InsertNextPoint(points2->GetPoint(i));
        }


        Create(vtkTriangleStrip, cell);
        for(int i = 2; i < points->GetNumberOfPoints(); i++) {
            if(i % 2 == 0)
            {
                cell->GetPointIds()->InsertNextId(i);
                cell->GetPointIds()->InsertNextId(i - 2);
                cell->GetPointIds()->InsertNextId(i - 1);
            }
            else
            {
                cell->GetPointIds()->InsertNextId(i);
                cell->GetPointIds()->InsertNextId(i - 1);
                cell->GetPointIds()->InsertNextId(i - 2);
            }
        }
        Create(vtkCellArray, cells);
        cells->InsertNextCell(cell);
        Create(vtkPolyData, area);
        area->SetPoints(points);
        area->SetStrips(cells);


        rMapper->SetInputData(area);
    }

    //绕X轴旋转
    {
        m_actors[3] = vtkActor::New();
        m_actors[3]->SetMapper(rMapper);
        m_actors[3]->GetProperty()->SetColor(1, 0, 0);
    }
    //绕Y轴旋转
    {
        m_actors[4] = vtkActor::New();
        m_actors[4]->RotateZ(-90);
        m_actors[4]->SetMapper(rMapper);
        m_actors[4]->GetProperty()->SetColor(0, 1, 0);
    }
    //绕Z轴旋转
    {
        m_actors[5] = vtkActor::New();
        m_actors[5]->RotateY(90);
        m_actors[5]->SetMapper(rMapper);
        m_actors[5]->GetProperty()->SetColor(0, 0, 1);
    }

}

void myAxesRep::Highlight(int h)
{

    double color[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };

    for(int i = 0; i < ActorNum; i++) {
        m_actors[i]->GetProperty()->SetColor(color[i % 3]);
    }
    if(!h) {
        return;
    }

    if(m_pressedState != OutSide) {
        m_actors[m_pressedState]->GetProperty()->SetColor(1, 1, 0);
    }
    else if(InteractionState != OutSide) {
        m_actors[InteractionState]->GetProperty()->SetColor(1, 1, 0);
    }
}

void myAxesRep::RegisterPickers()
{
    if(!m_picker)
    {
        m_picker = vtkPropPicker::New();
        for(int i = 0; i < ActorNum; i++) {
            m_picker->AddPickList(m_actors[i]);
        }
        m_picker->PickFromListOn();
    }
}

void myAxesRep::UnRegisterPickers()
{
    if(m_picker)
    {
        m_picker->Delete();
        m_picker = nullptr;
    }
}

void myAxesRep::clearUserTransfrom()
{
    Create(vtkTransform, transform);
    for(int i = 0; i < ActorNum; i++) {
        m_actors[i]->SetUserTransform(transform);
    }
}

void myAxesRep::BuildRepresentation()
{
    InteractionState = OutSide;

    if(m_opActor) {
        PlaceWidget(m_opActor->GetBounds());
    }
    for(int i = 0; i < ActorNum; i++) {
        Renderer->AddActor(m_actors[i]);
    }
}

void myAxesRep::setActor(vtkActor *actor)
{
    m_opActor = actor;
}

void myAxesRep::PlaceWidget(double *bounds)
{
    if(!m_opActor) {
        return;
    }

    //所有actor回到初始状态
    clearUserTransfrom();

    //计算边长
    double dx = std::abs(bounds[0] - bounds[1]);
    double dy = std::abs(bounds[2] - bounds[3]);
    double dz = std::abs(bounds[4] - bounds[5]);

    double max = std::max(dx, dy);
    max = std::max(max, dz);

    PlaceFactor = std::max(0.5, max);

    //获取actor的userTransform
    vtkTransform *actorTransform = (vtkTransform *)m_opActor->GetUserTransform();

    //平移和旋转变换，将坐标移动到actor位置
    Create(vtkTransform, transform);

    //如果actor本身有userFrom
    if(actorTransform) {
        transform->Concatenate(actorTransform);
    }
    //有些actor并不是从原点出发的
    transform->Translate(m_opActor->GetPosition());
    transform->Scale(PlaceFactor, PlaceFactor, PlaceFactor );

    //最终将actors移动到目标actor位置，并对齐
    for(int i = 0; i < ActorNum; i++)    {
        m_actors[i]->SetUserTransform(transform);
    }

}

void myAxesRep::WidgetInteraction(double *newEventPos)
{
    //如果没有选中，只处理鼠标划过高亮现实问题
    if(m_pressedState == OutSide) {
        int oldState = InteractionState;
        int newState = ComputeInteractionState(newEventPos[0], newEventPos[1]);

        if(oldState != newState)
        {
            if(newState != OutSide) {
                Highlight(true);
            }
            else  {
                Highlight(false);
            }

            NeedToRender = true;
        }
        return;
    }

    //主要计算焦平面
    double display[3] = {0};
    vtkInteractorObserver::ComputeWorldToDisplay(
        Renderer,
        m_preWorldPos[0],
        m_preWorldPos[1],
        m_preWorldPos[2],
        display);

    //使用焦平面重新计算上次事件世界点
    vtkInteractorObserver::ComputeDisplayToWorld(
        Renderer,
        m_preEventPos[0],
        m_preEventPos[1],
        display[2],
        m_preWorldPos);

    //使用焦平面重新计算当前事件世界点
    double curWorldPos[4] = {0};
    vtkInteractorObserver::ComputeDisplayToWorld(
        Renderer,
        newEventPos[0],
        newEventPos[1],
        display[2],
        curWorldPos);

    double dir[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    //根据装选择状态确定方向索引
    //比如状态是OnArrowX,说明选择了X箭头，方向是(1,0,0)
    //如果状态时OnRingX,说明选择了RingX，旋转轴方向也是(1,0,0)
    //这些方向是变换之前的，应用变换之后得到世界坐标系中的方向向量
    int index = m_pressedState % 3;

    //将方向向量转换
    //m_actors[0]的变换可以看作是所有actor的整体变换
    double direction[3] = {dir[index][0], dir[index][1], dir[index][2]};
    vtkTransform *selfTrans = (vtkTransform *)m_actors[0]->GetUserTransform();
    selfTrans->TransformVector(direction, direction);
    //转成单位向量
    vtkMath::Normalize(direction);

    //得到变换的原点的世界位置
    double origin[3] = {0};
    selfTrans->GetPosition(origin);

    //计算变换
    Create(vtkTransform, trans);
    trans->Translate(origin[0], origin[1], origin[2]);
    if(m_pressedState == OnArrowX ||
            m_pressedState == OnArrowY ||
            m_pressedState == OnArrowZ)
    {
        //两次世界点的向量
        double vec[3] = {0};
        vtkMath::Subtract(curWorldPos, m_preWorldPos, vec);
        //计算投影，计算世界点向量在世界方向的投影距离
        double length = vtkMath::Dot(vec, direction);

        trans->Translate(length * direction[0],
                         length * direction[1],
                         length * direction[2]);
    }
    else if(m_pressedState == OnRingX ||
            m_pressedState == OnRingY ||
            m_pressedState == OnRingZ)
    {
        //世界点到世界原点向量
        double vec1[3] = {
            m_preWorldPos[0] - origin[0],
            m_preWorldPos[1] - origin[1],
            m_preWorldPos[2] - origin[2]
        };
        //在转轴上的投影长度
        double length1 = vtkMath::Dot(vec1, direction);

        //在转轴上的投影向量
        double vecP1[3] = {length1 *direction[0], length1 *direction[1], length1 *direction[2]};
        //垂直于转轴的分量
        double vecT1[3] = {0};
        vtkMath::Subtract(vec1, vecP1, vecT1);

        //世界点到世界原点向量
        double vec2[3] = {
            curWorldPos[0] - origin[0],
            curWorldPos[1] - origin[1],
            curWorldPos[2] - origin[2]
        };
        //在转轴上的投影长度
        double length2 = vtkMath::Dot(vec2, direction);

        //在转轴上的投影向量
        double vecP2[3] = {length2 *direction[0], length2 *direction[1], length2 *direction[2]};
        //垂直于转轴的分量
        double vecT2[3] = {0};
        vtkMath::Subtract(vec2, vecP2, vecT2);

        //单位向量好计算
        vtkMath::Normalize(vecT1);
        vtkMath::Normalize(vecT2);

        //重新计算转轴，为了处理方向
        double axis[3] = {1, 0, 0};
        vtkMath::Cross(vecT1, vecT2, axis);

        double radians = vtkMath::Dot(vecT1, vecT2);
        double degree = vtkMath::DegreesFromRadians(std::acos(radians));

        trans->RotateWXYZ(degree, axis[0], axis[1], axis[2]);
    }
    trans->Translate(-origin[0], -origin[1], -origin[2]);

    //对每一个Actor应用坐标变换
    for(int i = 0; i < ActorNum; i++)
    {
        Create(vtkTransform, temp);
        temp->DeepCopy(trans);
        temp->Concatenate(m_actors[i]->GetUserTransform());
        m_actors[i]->SetUserTransform(temp);
    }

//actor移动
    if(m_opActor) {
        Create(vtkTransform, temp);
        temp->DeepCopy(trans);
        vtkLinearTransform *line = m_opActor->GetUserTransform();
        if(line) {
            temp->Concatenate(line);
        }
        m_opActor->SetUserTransform(temp);
    }

    m_preEventPos[0] = newEventPos[0];
    m_preEventPos[1] = newEventPos[1];
    m_preEventPos[2] = 0;
    NeedToRender = true;
}

void myAxesRep::StartWidgetInteraction(double *eventPos)
{
    m_pressedState = ComputeInteractionState(eventPos[0], eventPos[1]);
    if(m_pressedState != OutSide)
    {
        m_picker->GetPickPosition(m_preWorldPos);
        m_preEventPos[0] = eventPos[0];
        m_preEventPos[1] = eventPos[1];
        m_preEventPos[2] = 0;
    }
}

void myAxesRep::PrintSelf(std::ostream &os, vtkIndent indent)
{
    Superclass::PrintSelf(os, indent);
    os << indent << "Number of Actors:" << ActorNum << "\n";
    os << indent << "Pressed state:" << m_pressedState << "\n";
}

void myAxesRep::EndWidgetInteraction(double *vtkNotUsed(newEventPos))
{
    m_pressedState = OutSide;

}

int myAxesRep::ComputeInteractionState(int X, int Y, int vtkNotUsed(modify))
{
    InteractionState = OutSide;
    if(!Renderer || !Renderer->IsInViewport(X, Y)) {
        return InteractionState;
    }

    m_picker->Pick(X, Y, 0, Renderer);
    vtkActor *actor = m_picker->GetActor();

    for(int j = 0; j < ActorNum; j++)
    {
        if(actor == m_actors[j]) {
            InteractionState = j;
            break;
        }
    }

    return InteractionState;
}
