#ifndef MYAXESWIDGET_H
#define MYAXESWIDGET_H

#include<vtkAbstractWidget.h>

class vtkActor;
class myAxesWidget : public vtkAbstractWidget
{
    vtkTypeMacro(myAxesWidget, vtkAbstractWidget)
public:
    static myAxesWidget *New();
    void PrintSelf(ostream &os, vtkIndent indent) override;

    void SetEnabled(int enable) override;
    void CreateDefaultRepresentation() override;

    void setActor(vtkActor *actor);
private:
    myAxesWidget();
    ~myAxesWidget();

    static void mouseMove(vtkAbstractWidget *w);
    static void leftButtonPress(vtkAbstractWidget *w);
    static void leftButtonRelease(vtkAbstractWidget *w);

private:
    vtkActor *m_actor;
};

#endif // MYAXESWIDGET_H
