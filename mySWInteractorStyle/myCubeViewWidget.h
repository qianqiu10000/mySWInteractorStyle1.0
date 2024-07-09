#ifndef MYCUBEVIEWWIDGET_H
#define MYCUBEVIEWWIDGET_H

#include<vtkAbstractWidget.h>

class mySWInteractorStyle;
class myCubeViewWidget : public vtkAbstractWidget
{
public:
    static myCubeViewWidget *New();
    vtkTypeMacro(myCubeViewWidget, vtkAbstractWidget);
    void PrintSelf(ostream &os, vtkIndent indent) override;

protected:
    static void mouseMove(vtkAbstractWidget *widget);
    static void leftButtonPress(vtkAbstractWidget *widget);
    static void leftButtonRelease(vtkAbstractWidget *widget);

    void SetEnabled(int enable) override;
    void CreateDefaultRepresentation() override;

private:
    myCubeViewWidget();
    ~myCubeViewWidget();
};

#endif // MYCUBEVIEWWIDGET_H
