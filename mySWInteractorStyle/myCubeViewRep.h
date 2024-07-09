#ifndef MYCUBEVIEWREP_H
#define MYCUBEVIEWREP_H

#include<vtkWidgetRepresentation.h>



class vtkActor;
class vtkPropPicker;
class myCubeViewRep : public vtkWidgetRepresentation
{
public:
    static myCubeViewRep *New();
    vtkTypeMacro(myCubeViewRep, vtkWidgetRepresentation);
    void PrintSelf(ostream &os, vtkIndent indent) override;

    //必须实现
    void BuildRepresentation() override;                        //根据状态更新几何特征

    //建议实现
    void Highlight(int highlightOn)override;                        //高亮显示
    void PlaceWidget(double bounds[6]) override;            //确定大小范围
    void StartWidgetInteraction(double *eventPos) override;//鼠标点击变色
    void WidgetInteraction(double *newEventPos) override;//处理鼠标移动事件
    void EndWidgetInteraction(double *newEventPos) override;//处理结束事件
    int ComputeInteractionState(int X, int Y, int modify = 0)override;//计算当前状态

    void RegisterPickers() override;                                    //注册拾取器
    void UnRegisterPickers() override;                              //注销拾取器

    enum State {
        OnFace0,
        OnFace1,
        OnFace2,
        OnFace3,
        OnFace4,
        OnFace5,
        OnEdget0,
        OnEdget1,
        OnEdget2,
        OnEdget3,
        OnEdget4,
        OnEdget5,
        OnEdget6,
        OnEdget7,
        OnEdget8,
        OnEdget9,
        OnEdget10,
        OnEdget11,
        OnCorner0,
        OnCorner1,
        OnCorner2,
        OnCorner3,
        OnCorner4,
        OnCorner5,
        OnCorner6,
        OnCorner7,
        OutSide
    };

private:
    myCubeViewRep();
    ~myCubeViewRep();
    vtkActor *createEdge(int num);
    vtkActor *createCorner(int num);
    vtkActor *createFace(int num);
    void computeCenter(double *bound, double *center);

private:
    vtkPropPicker *m_picker;

#define ActorNumber 26
    vtkActor *m_actors[ActorNumber];
};

#endif // MYCUBEVIEWREP_H
