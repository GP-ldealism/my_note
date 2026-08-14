#include "mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QMenuBar>
#include <QMenu>
#include <QActionGroup>
#include <QAction>
#include <QToolBar>
#include <QStatusBar>
#include <QLabel>
#include <QTextEdit>
#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QMenuBar *menuBar = new QMenuBar();

    QMenu *file = new QMenu("文件");
    QMenu *edit = new QMenu("编辑");
    QMenu *about = new QMenu("关于");

    menuBar->addMenu(file);
    menuBar->addMenu(edit);
    menuBar->addMenu(about);

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


    QToolBar *toolBar = new QToolBar(this);
    toolBar->toolTip();
    toolBar->setFloatable(true);
    toolBar->setMovable(true);
    toolBar->resize(80, 200);
    // toolBar->setAcceptDrops(true);
    toolBar->actionGeometry(new QAction("toolBar"));


    QStatusBar *statusBar = new QStatusBar();
    QLabel *time = new QLabel("时间:2026-08-14");
    QLabel *encodeFormat = new QLabel("编码格式:UTF-8");
    QHBoxLayout *statusHBox = new QHBoxLayout();
    statusBar->addWidget(time);
    statusBar->addPermanentWidget(encodeFormat);



    // statusBar->addWidget(time, 600);
    // statusBar->addWidget(encodeFormat, 700);
    // statusBar->showMessage("I love China!");


    textEdit = new QTextEdit();
    textEdit->setPlainText("");

    // connect
    connect(create, &QAction::triggered, this, &MainWindow::newfile);
    connect(open, &QAction::triggered, this, &MainWindow::openfile);


    this->setCentralWidget(textEdit);
    this->setMenuBar(menuBar);
    this->setStatusBar(statusBar);
    this->resize(800, 600);
}

MainWindow::~MainWindow() = default;
void MainWindow::newfile() {

}
void MainWindow::openfile() {
    QString filename = QFileDialog::getOpenFileName(this, "打开文件", "", "*.*");
    if (filename.isEmpty()) {
        return;
    }
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "error", "无法打开文件");
        return;
    }
    QTextStream in(&file);
    textEdit->setText(in.readAll());
    file.close();
    this->setWindowTitle("-" + QFileInfo(filename).fileName());
}
void MainWindow::savefile() {

}
