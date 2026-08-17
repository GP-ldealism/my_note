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
#include <QTimer>

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
    QTimer *timer = new QTimer(this);
    timer->start(1000);
    QLabel *time = new QLabel();
    QLabel *encodeFormat = new QLabel("编码格式:UTF-8");
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
    connect(save, &QAction::triggered, this, &MainWindow::savefile);
    connect(timer, &QTimer::timeout, this, [time]() {
        time->setText("时间：" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    });


    this->setCentralWidget(textEdit);
    this->setMenuBar(menuBar);
    this->setStatusBar(statusBar);
    this->resize(800, 600);
}

MainWindow::~MainWindow() = default;
void MainWindow::newfile() {
    if (!textEdit->document()->isEmpty()) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "保存", "1");
        if (reply == QMessageBox::Yes) {
            savefile();
        } else if (reply == QMessageBox::Cancel) {
            return;
        }
    }
    textEdit->clear();
    this->setWindowTitle("新建文件");
}
void MainWindow::openfile() {
    currentFile = QFileDialog::getOpenFileName(this, "打开文件", "", "*.*");
    if (currentFile.isEmpty()) {
        return;
    }
    QFile file(currentFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "error", "无法打开文件");
        return;
    }
    QTextStream in(&file);
    textEdit->setText(in.readAll());
    file.close();
    this->setWindowTitle("-" + QFileInfo(currentFile).fileName());
}
void MainWindow::savefile() {
    if (!currentFile.isEmpty()) {
        QFile file(currentFile);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "save fail", "保存失败");
            return;
        }
        QTextStream out(&file);
        QString res = textEdit->toPlainText();
        out << res;
        file.close();
        this->setWindowTitle("-" + QFileInfo(currentFile).fileName());
        QMessageBox::information(this, "save successed", "保存成功");
        return;
    }
    QString filename = QFileDialog::getSaveFileName(this, "保存文件", "*.*");
    if (filename.isEmpty())
        return;
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "save fail", "保存失败");
        return;
    }
    QTextStream out(&file);
    QString res = textEdit->toPlainText();
    out << res;
    file.close();
    this->setWindowTitle("-" + QFileInfo(filename).fileName());
}
