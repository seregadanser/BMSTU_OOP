#include "../include/widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    init_buttons();
    init_layouts();
    init_lable();
    init_textbox();
    layout_buttons->addWidget(btnSize, 0, 0);
    layout_buttons->addWidget(btnRotate, 1, 0);
    layout_buttons->addWidget(btnMove, 2, 0);
    layout_buttons->addWidget(btnLoad, 3, 0);
    layout_buttons->addWidget(path_box, 4, 0);

    scene = new QGraphicsScene(this);
    sc = new QGraphicsView(scene);
    scene->setBackgroundBrush(Qt::blue);

    up_layout->addWidget(sc);
    up_layout->addLayout(layout_buttons);

    down_layout->addWidget(label1, 1, 0);
    down_layout->addWidget(label2, 2, 0);
    down_layout->addWidget(label3, 3, 0);
    down_layout->addWidget(label4, 0, 1);
    down_layout->addWidget(label5, 0, 2);
    down_layout->addWidget(label6, 0, 3);
    down_layout->addWidget(label7, 0, 4);

    down_layout->addWidget(textbox1, 1, 1);
    down_layout->addWidget(textbox2, 2, 1);
    down_layout->addWidget(textbox3, 3, 1);
    down_layout->addWidget(textbox4, 1, 2);
    down_layout->addWidget(textbox5, 2, 2);
    down_layout->addWidget(textbox6, 3, 2);
    down_layout->addWidget(textbox7, 1, 3);
    down_layout->addWidget(textbox8, 2, 3);
    down_layout->addWidget(textbox9, 3, 3);
    down_layout->addWidget(textbox10, 1, 4);
    down_layout->addWidget(textbox11, 2, 4);
    down_layout->addWidget(textbox12, 3, 4);

    main_layout->addLayout(up_layout);
    main_layout->addLayout(down_layout);
    setLayout(main_layout);
}

void Widget::init_buttons()
{
    btnRotate = new QPushButton("Вращать");
    connect(btnRotate, SIGNAL(clicked()), this, SLOT(rotate_fig()));
    btnMove = new QPushButton("Переместить");
    connect(btnMove, SIGNAL(clicked()), this, SLOT(move_fig()));
    btnSize = new QPushButton("Изменить");
    connect(btnSize, SIGNAL(clicked()), this, SLOT(scale_fig()));
    btnLoad = new QPushButton("Загрузить");
    connect(btnLoad, SIGNAL(clicked()), this, SLOT(load_fig()));
}

void Widget::init_layouts()
{
    layout_buttons = new QGridLayout();
    up_layout = new QHBoxLayout();
    main_layout = new QVBoxLayout();
    down_layout = new QGridLayout();
}

void Widget::init_textbox()
{
    path_box = new QLineEdit();
    path_box->setText("D:\\Study\\OOP\\lab1_oop\\kub.txt");
    path_box->setMaximumWidth(120);
    textbox1 = new QDoubleSpinBox();
    textbox2 = new QDoubleSpinBox();
    textbox3 = new QDoubleSpinBox();
    textbox4 = new QDoubleSpinBox();
    textbox5 = new QDoubleSpinBox();
    textbox6 = new QDoubleSpinBox();
    textbox7 = new QDoubleSpinBox();
    textbox8 = new QDoubleSpinBox();
    textbox9 = new QDoubleSpinBox();
    textbox10 = new QDoubleSpinBox();
    textbox11 = new QDoubleSpinBox();
    textbox12 = new QDoubleSpinBox();
    textbox1->setMinimum(-10000.000000000000000);
    textbox1->setMaximum(10000.000000000000000);
    textbox2->setMinimum(-10000.000000000000000);
    textbox2->setMaximum(10000.000000000000000);
    textbox3->setMinimum(-10000.000000000000000);
    textbox3->setMaximum(10000.000000000000000);
    textbox4->setMinimum(-10000.000000000000000);
    textbox4->setMaximum(10000.000000000000000);
    textbox5->setMinimum(-10000.000000000000000);
    textbox5->setMaximum(10000.000000000000000);
    textbox6->setMinimum(-10000.000000000000000);
    textbox6->setMaximum(10000.000000000000000);
    textbox7->setMinimum(-10000.000000000000000);
    textbox7->setMaximum(10000.000000000000000);
    textbox8->setMinimum(-10000.000000000000000);
    textbox8->setMaximum(10000.000000000000000);
    textbox9->setMinimum(-10000.000000000000000);
    textbox9->setMaximum(10000.000000000000000);
    textbox10->setMinimum(-10000.000000000000000);
    textbox10->setMaximum(10000.000000000000000);
    textbox11->setMinimum(-10000.000000000000000);
    textbox11->setMaximum(10000.000000000000000);
    textbox12->setMinimum(-10000.000000000000000);
    textbox12->setMaximum(10000.000000000000000);
}

void Widget::init_lable()
{
    label1 = new QLabel();
    label2 = new QLabel();
    label3 = new QLabel();
    label4 = new QLabel();
    label5 = new QLabel();
    label6 = new QLabel();
    label7 = new QLabel();
    label1->setText("x:");
    label2->setText("y:");
    label3->setText("z:");
    label4->setText("Поворот");
    label5->setText("Перемещение");
    label6->setText("Маштаб");
    label7->setText("Центр");
}

Widget::~Widget()
{
    task new_task;
    new_task.action = CLEAN;
    main_task(new_task);
}

void Widget::drawing()
{
    task new_task;
    new_task.action = DRAW;
    canvas c;
    c.scene = scene;
    c.height = 0;
    c.width = 0;
    new_task.p = c;
    errors err = main_task(new_task);
    if (err != OK)
    {
        handle_error(err);
        return;
    }
}

void Widget::rotate_fig()
{
    task new_task;

    new_task.action = ROTATE;
    rotate r;
    r.center = new_point(textbox10->value(), textbox11->value(), textbox12->value());
    r.angleX = textbox1->value();
    r.angleY = textbox2->value();
    r.angleZ = textbox3->value();
    new_task.rot = r;
    errors err = main_task(new_task);
    if (err != OK)
    {
        handle_error(err);
        return;
    }
    drawing();
}

void Widget::move_fig()
{
    task new_task;

    new_task.action = MOVE;
    movet m;
    m.x = textbox4->value();
    m.y = textbox5->value();
    m.z = textbox6->value();
    new_task.mov = m;
    errors err = main_task(new_task);
    if (err != OK)
    {
        handle_error(err);
        return;
    }
    drawing();
}

void Widget::scale_fig()
{
    task new_task;

    new_task.action = SCALE;
    scale s;
    s.center = new_point(textbox10->value(), textbox11->value(), textbox12->value());
    s.x = textbox7->value();
    s.y = textbox8->value();
    s.z = textbox9->value();
    new_task.sca = s;
    errors err = main_task(new_task);
    if (err != OK)
    {
        handle_error(err);
        return;
    }
    drawing();
}

void Widget::load_fig()
{
    task new_task;
    new_task.action = LOAD;
    //new_task.fn = "C:\\Users\\user\\Downloads\\lab1_oop\\points.txt";
    new_task.fn = path_box->text().toStdString().c_str();
    errors err = main_task(new_task);
    if (err != OK)
    {
        handle_error(err);
        return;
    }
    drawing();
}
