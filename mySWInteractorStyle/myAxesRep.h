#ifndef MYAXESREP_H
#define MYAXESREP_H

#include<vtkWidgetRepresentation.h>

class vtkActor;
class vtkPropPicker;
class myAxesRep : public vtkWidgetRepresentation
{
    vtkTypeMacro(myAxesRep, vtkWidgetRepresentation)
public:
    static myAxesRep *New();
    void PrintSelf(ostream &os, vtkIndent indent) override;

    //必须实现
    void BuildRepresentation() override;


    //推荐实现
    void Highlight(int h) override;
    void RegisterPickers() override;
    void UnRegisterPickers() override;
    void PlaceWidget(double *bounds) override;
    void WidgetInteraction(double *newEventPos) override;
    void StartWidgetInteraction(double *eventPos) override;
    void EndWidgetInteraction(double *newEventPos) override;
    int ComputeInteractionState(int X, int Y, int modify = 0) override;

    void setActor(vtkActor *actor);

    enum {
        OnArrowX,
        OnArrowY,
        OnArrowZ,
        OnRingX,
        OnRingY,
        OnRingZ,
        OutSide
    };

private:
    myAxesRep();
    ~myAxesRep();
    void createActors();                        //创建actors
    void clearUserTransfrom();         //清除actors的user变换,回到创建时状态

private:
#define ActorNum 6
    vtkActor *m_actors[ActorNum];
    vtkPropPicker *m_picker;
    vtkActor *m_opActor;

    int m_pressedState;
    double m_preEventPos[3];
    double m_preWorldPos[4];
};

#endif // MYAXESREP_H
