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
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    this->startupMenuBar();
    this->startupStatusBar();
    this->startupConnect();

    textEdit = new QTextEdit();
    textEdit->setPlainText("");

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
void MainWindow::exitApp() {
    //todo
    QApplication::exit();
}
void MainWindow::about1() {
    QDialog *dialog = new QDialog(this);
    dialog->setModal(true);
    dialog->setWindowTitle("about");
    dialog->setFixedSize(300, 200);
    QVBoxLayout *vlayout = new QVBoxLayout(dialog);
    QLabel *titleLabel = new QLabel("<h2>my note<h2>");
    titleLabel->setAlignment(Qt::AlignCenter);
    vlayout->addWidget(titleLabel);
    QLabel *versionLabel = new QLabel("Version: v2.3.6");
    versionLabel->setAlignment(Qt::AlignCenter);
    vlayout->addWidget(versionLabel);
    dialog->exec();
}
void MainWindow::startupMenuBar() {
    this->menuBar = new QMenuBar();

    fileMenu = new QMenu("文件");
    recentMenu = new QMenu("最近使用");
    editMenu = new QMenu("编辑");
    aboutMenu = new QMenu("关于");

    menuBar->addMenu(fileMenu);
    menuBar->addMenu(editMenu);
    menuBar->addMenu(aboutMenu);

    createAction = new QAction("新建");
    openAction = new QAction("打开");

    curr1Action = new QAction("最近123");
    curr2Action = new QAction("最近456");
    recentMenu->addAction(curr1Action);
    recentMenu->addAction(curr2Action);

    saveAction = new QAction("保存");
    saveAllAction = new QAction("全部保存");
    exitAction = new QAction("退出");

    fileMenu->addAction(createAction);
    fileMenu->addAction(openAction);
    fileMenu->addSeparator();
    fileMenu->addMenu(recentMenu);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAllAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    copyAction = new QAction("复制");
    pasteAction = new QAction("粘贴");
    deleteAction = new QAction("删除");
    findAction = new QAction("查找");

    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addAction(deleteAction);
    editMenu->addSeparator();
    editMenu->addAction(findAction);

    aboutAction = new QAction("关于");
    aboutMenu->addAction(aboutAction);
}
void MainWindow::startupStatusBar() {
    statusBar = new QStatusBar();
    timer = new QTimer(this);
    timer->start(1000);
    timeLabel = new QLabel();
    encodeFormat = new QLabel("编码格式:UTF-8");
    statusBar->addWidget(timeLabel);
    statusBar->addPermanentWidget(encodeFormat);
}
void MainWindow::startupConnect() {
    // connect
    connect(createAction, &QAction::triggered, this, &MainWindow::newfile);
    connect(openAction, &QAction::triggered, this, &MainWindow::openfile);
    connect(saveAction, &QAction::triggered, this, &MainWindow::savefile);
    connect(timer, &QTimer::timeout, this, [this]() {
        timeLabel->setText("时间：" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    });
    connect(exitAction, &QAction::triggered, this, &MainWindow::exitApp);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about1);
    connect(findAction, &QAction::triggered, this, &MainWindow::findText);
}
void MainWindow::findText() {
    // 如果对话框已存在，直接显示并聚焦
    // if (findDialog) {
    //     findDialog->show();
    //     findDialog->raise();
    //     findLineEdit->setFocus();
    //     findLineEdit->selectAll();
    //     return;
    // }

    findDialog = new QDialog(this);
    findDialog->setModal(true);
    findDialog->setFixedSize(380, 200);
    findDialog->setAttribute(Qt::WA_DeleteOnClose);  // 关闭时自动删除
    QVBoxLayout *vlayout = new QVBoxLayout(findDialog);
    findLineEdit = new QLineEdit();
    findButton = new QPushButton("查找");


    vlayout->addWidget(findLineEdit);
    vlayout->addSpacing(20);
    vlayout->addWidget(findButton);
    findDialog->exec();
}
