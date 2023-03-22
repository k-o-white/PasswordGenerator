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
    ~MainWindow();
private slots:
    void generate();
    void copyToClipboard();
private:
    Ui::MainWindow *ui;
    std::string shuffle(const std::string &password);
    bool checkRepeat(const std::string &password, const char &symbol);
    bool checkPositions(const std::vector<int> &numbers, const int &num);
    QString createPassword(const int &length);
};
#endif // MAINWINDOW_H
