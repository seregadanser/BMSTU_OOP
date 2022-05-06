#ifndef WIDGET_H
#define WIDGET_H

#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QLabel>

#include "main_task.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QPushButton
        *btnRotate,
        *btnSize,
        *btnMove,
        *btnLoad;
    QGridLayout *layout_buttons;
    QGridLayout *down_layout;
    QHBoxLayout *up_layout;
    QVBoxLayout *main_layout;
    QGraphicsScene *scene;
    QGraphicsView *sc;
    QLabel
        *label1,
        *label2,
        *label3,
        *label4,
        *label5,
        *label6,
        *label7;
    QDoubleSpinBox
        *textbox1,
        *textbox2,
        *textbox3,
        *textbox4,
        *textbox5,
        *textbox6,
        *textbox7,
        *textbox8,
        *textbox9,
        *textbox10,
        *textbox11,
        *textbox12;
    QLineEdit *path_box;

    void init_lable();
    void init_buttons();
    void init_layouts();
    void init_textbox();
    void drawing();
private slots:
    void rotate_fig();
    void move_fig();
    void scale_fig();
    void load_fig();
    
};
#endif // WIDGET_H