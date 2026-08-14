#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    QTextEdit *textEdit;
private slots:
    void newfile();
    void openfile();
    void savefile();
};
#endif // MAINWINDOW_H
