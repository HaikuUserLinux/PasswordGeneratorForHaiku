#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdlib.h>
#include <iostream>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->size().width(), this->size().height());
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*void MainWindow::region(const QPoint &currentGlobalPoint)
{
    // Get the position area of ​​the form on the screen, topLeft is the upper corner point, rightButton is the lower right corner point
    QRect rect = this->rect();

    QPoint topLeft = this->mapToGlobal(rect.topLeft()); //Convert (0,0) in the upper left corner to global coordinates
    QPoint rightButton = this->mapToGlobal(rect.bottomRight());

    int x = currenGlobalPoint.x(); //The coordinates of the current mouse
    int y = currentGlobalPoint.y();

    if(((topLeft.x() + PADDING >= x) && (topLeft.x() <= x))
            && ((topLeft.y() + PADDING >= y) && (topLeft.y() <= y)))
    {
        // upper left corner
        dir = LEFTTOP;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));  // Set the cursor shape
    }else if(((x >= rightButton.x() - PADDING) && (x <= rightButton.x()))
              && ((y >= rightButton.y() - PADDING) && (y <= rightButton.y())))
    {
        // bottom right corner
        dir = RIGHTBOTTOM;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
    }else if(((x <= topLeft.x() + PADDING) && (x >= topLeft.x()))
              && ((y >= rightButton.y() - PADDING) && (y <= rightButton.y())))
    {
        //Lower left corner
        dir = LEFTBOTTOM;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    }else if(((x <= rightButton.x()) && (x >= rightButton.x() - PADDING))
              && ((y >= topLeft.y()) && (y <= topLeft.y() + PADDING)))
    {
        // upper right corner
        dir = RIGHTTOP;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    }else if((x <= topLeft.x() + PADDING) && (x >= topLeft.x()))
    {
        // left
        dir = LEFT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    }else if((x <= rightButton.x()) && (x >= rightButton.x() - PADDING))
    {
        // right
        dir = RIGHT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    }else if((y >= topLeft.y()) && (y <= topLeft.y() + PADDING))
    {
        // top
        dir = UP;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    }else if((y <= rightButton.y()) && (y >= rightButton.y() - PADDING))
    {
        // below
        dir = DOWN;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    }else
    {
        // default
        dir = NONE;
        this->setCursor(QCursor(Qt::ArrowCursor));
    }
}


//Rewrite of three mouse events
//Mouse press event
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    switch(event->button())
    {
        case Qt::LeftButton:
            isLeftPressDown = true;

            if(dir != NONE)
            {
                this->mouseGrabber(); //Return to the window where the mouse input is currently captured
            }
            else
            {
                m_movePoint = event->globalPos() - this->frameGeometry().topLeft();
                //globalPos() mouse position, topLeft() position of the upper left corner of the window
            }
            break;
        case Qt::RightButton:
            this->setWindowState(Qt::WindowMinimized);
            break;
        default:
            MainWindow::mousePressEvent(event);
    }
}

void MainWindow::on_pushButton_clicked()
{
    string symbols = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    int len = ui->textEdit->toPlainText().toInt();
    QString res = "";
    int ind;
    for (int i = 0; i < len; i++)
    {
        ind = 0 + rand() % (symbols.length() - 0);
        res += symbols[ind];
    }
    ui->textEdit_2->setText(res);
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    QPoint globalPoint = event->globalPos();   //Mouse global coordinates

    QRect rect = this->rect();  //rect == QRect(0,0 1280x720)
    QPoint topLeft = mapToGlobal(rect.topLeft());
    QPoint bottomRight = mapToGlobal(rect.bottomRight());

    if (this->windowState() != Qt::WindowMaximized)
    {
        if(!isLeftPressDown)  //When the left button is not pressed
        {
            this->region(globalPoint); //Change of window size-determine the mouse position and change the cursor shape
        }
        else
        {
            if(dir != NONE)
            {
                QRect newRect(topLeft, bottomRight); //Define a rectangle after dragging the maximum 1000*1618

                switch(dir)
                {
                    case LEFT:

                        if(bottomRight.x() - globalPoint.x() <= this->minimumWidth())
                        {
                            newRect.setLeft(topLeft.x());  //When it is less than the minimum width of the interface, set the upper left corner to the window x
                            //Only change the left margin
                        }
                        else
                        {
                            newRect.setLeft(globalPoint.x());
                        }
                        break;
                    case RIGHT:
                        newRect.setWidth(globalPoint.x() - topLeft.x());  //Only the right margin can be changed
                        break;
                    case UP:
                        if(bottomRight.y() - globalPoint.y() <= this->minimumHeight())
                        {
                            newRect.setY(topLeft.y());
                        }
                        else
                        {
                            newRect.setY(globalPoint.y());
                        }
                        break;
                    case DOWN:
                        newRect.setHeight(globalPoint.y() - topLeft.y());
                        break;
                    case LEFTTOP:
                        if(bottomRight.x() - globalPoint.x() <= this->minimumWidth())
                        {
                            newRect.setX(topLeft.x());
                        }
                        else
                        {
                            newRect.setX(globalPoint.x());
                        }

                        if(bottomRight.y() - globalPoint.y() <= this->minimumHeight())
                        {
                            newRect.setY(topLeft.y());
                        }
                        else
                        {
                            newRect.setY(globalPoint.y());
                        }
                        break;
                     case RIGHTTOP:
                          if (globalPoint.x() - topLeft.x() >= this->minimumWidth())
                          {
                              newRect.setWidth(globalPoint.x() - topLeft.x());
                          }
                          else
                          {
                              newRect.setWidth(bottomRight.x() - topLeft.x());
                          }
                          if (bottomRight.y() - globalPoint.y() >= this->minimumHeight())
                          {
                              newRect.setY(globalPoint.y());
                          }
                          else
                          {
                              newRect.setY(topLeft.y());
                          }
                          break;
                     case LEFTBOTTOM:
                          if (bottomRight.x() - globalPoint.x() >= this->minimumWidth())
                          {
                              newRect.setX(globalPoint.x());
                          }
                          else
                          {
                              newRect.setX(topLeft.x());
                          }
                          if (globalPoint.y() - topLeft.y() >= this->minimumHeight())
                          {
                              newRect.setHeight(globalPoint.y() - topLeft.y());
                          }
                          else
                          {
                              newRect.setHeight(bottomRight.y() - topLeft.y());
                          }
                          break;
                      case RIGHTBOTTOM:
                          newRect.setWidth(globalPoint.x() - topLeft.x());
                          newRect.setHeight(globalPoint.y() - topLeft.y());
                          break;
                      default:
                          break;
                }
                this->setGeometry(newRect);
            }
            else
            {
                move(event->globalPos() - m_movePoint); //Move the window
                event->accept();
            }
        }
    }
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        isLeftPressDown = false;
        if (dir != NONE)
        {
            this->releaseMouse(); //Release the mouse to grab
            this->setCursor(QCursor(Qt::ArrowCursor));
        }
    }
}*/

void MainWindow::on_pushButton_2_clicked()
{
    ui->textEdit->setText("");
    ui->textEdit_2->setText("");
}

