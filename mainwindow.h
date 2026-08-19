#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    QTextEdit *textEdit;
    QString currentFile;
private:
    QMenuBar *menuBar;
    QMenu *fileMenu;
    QMenu *recentMenu;
    QMenu *editMenu;
    QMenu *aboutMenu;

    QAction *createAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *curr1Action;
    QAction *curr2Action;
    QAction *saveAllAction;
    QAction *exitAction;
    QAction *copyAction;
    QAction *pasteAction;
    QAction *deleteAction;
    QAction *findAction;
    QAction *aboutAction;

    QStatusBar * statusBar;

    QTimer *timer;
    QLabel *timeLabel;
    QLabel *encodeFormat;

    QToolBar *mainTool;
    //
    QDialog *findDialog;
    QLineEdit *findLineEdit;
    QPushButton *findButton;

    void startupMenuBar();
    void startupStatusBar();
    void startupConnect();

private slots:
    void newfile();
    void openfile();
    void savefile();
    void exitApp();
    void about1();
    void findText();
};
#endif // MAINWINDOW_H
