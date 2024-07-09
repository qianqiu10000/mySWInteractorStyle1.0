#ifndef MYSWINTERACTORSTYLE_H
#define MYSWINTERACTORSTYLE_H

#include<vtkInteractorStyle.h>

class myAxesWidget;
class myCubeViewWidget;
class mySWInteractorStyle : public vtkInteractorStyle
{
public:
    static mySWInteractorStyle *New();
    vtkTypeMacro(mySWInteractorStyle, vtkInteractorStyle);
    void PrintSelf(ostream &os, vtkIndent indent) override;

protected:
    mySWInteractorStyle();
    ~mySWInteractorStyle() override;

    void Rotate() override;
    void Spin() override;
    void Pan() override;
    void Dolly() override;

    void OnChar() override;
    void OnMouseMove() override;
    void OnLeftButtonDown() override;
    void OnLeftButtonUp() override;
    void OnMiddleButtonDown() override;
    void OnMiddleButtonUp() override;
    void OnRightButtonDown() override;
    void OnRightButtonUp() override;
    void OnMouseWheelForward() override;
    void OnMouseWheelBackward() override;

    void HighlightProp(vtkProp *prop) override;
private:
    void Dolly(double factor);
    void startMove();
    void endMove();
    void onCubeView();
    void operator=(const mySWInteractorStyle &) = delete;
    mySWInteractorStyle(const mySWInteractorStyle &) = delete;


private:
    double m_MotionFactor;  //鼠标灵敏度
    double  m_preColor[3];//拾取前actor的颜色
    myAxesWidget *m_axesWidget;
    myCubeViewWidget *m_cubeView;
};

#endif // MYSWINTERACTORSTYLE_H
