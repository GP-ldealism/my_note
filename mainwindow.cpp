#include "mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QActionGroup>
#include <QAction>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QMenuBar *menuBar = new QMenuBar();

    QMenu *file = new QMenu("文件");
    QMenu *edit = new QMenu("编辑");

    menuBar->addMenu(file);
    menuBar->addMenu(edit);

    QAction *create = new QAction("新建");
    QAction *open = new QAction("打开");

    QMenu *currentUse = new QMenu("最近使用");
    QAction *curr1 = new QAction("最近123");
    QAction *curr2 = new QAction("最近456");
    currentUse->addAction(curr1);
    currentUse->addAction(curr2);

    QAction *save = new QAction("保存");
    QAction *allSave = new QAction("全部保存");
    QAction *exit = new QAction("退出");

    file->addAction(create);
    file->addAction(open);
    file->addSeparator();
    file->addMenu(currentUse);
    file->addAction(save);
    file->addAction(allSave);
    file->addSeparator();
    file->addAction(exit);

    QAction *copy = new QAction("复制");
    QAction *paste = new QAction("粘贴");
    QAction *del = new QAction("删除");
    QAction *find = new QAction("查找");

    edit->addAction(copy);
    edit->addAction(paste);
    edit->addAction(del);
    edit->addSeparator();
    edit->addAction(find);

    this->setMenuBar(menuBar);
    this->resize(800, 600);
}

MainWindow::~MainWindow() = default;
