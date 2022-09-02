#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void region(const QPoint &currentGlobalPoint);
    ~MainWindow();
protected:
    //Mouse press, move and release events
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
QPoint m_movePoint;  //Mouse position
    bool isLeftPressDown;  // Determine whether the left button is pressed
    Direction dir;   
#endif // MAINWINDOW_H
