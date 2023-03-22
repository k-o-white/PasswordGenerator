#include <vector>
#include <QClipboard>
#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setText("To generate password input number of symbols here:");
    ui->outputLabel->setText("");
    QObject::connect(ui->generateButton, &QPushButton::clicked, this, &MainWindow::generate);
    QObject::connect(ui->copyButton, &QPushButton::clicked, this, &MainWindow::copyToClipboard);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generate()
{
    QString text = ui->lineEdit->text();
    bool isConverted = false;
    int number = text.toInt(&isConverted, 10);
    if (!isConverted)
    {
        ui->outputLabel->setText("Invalid! Not a number!");
        ui->outputLabel->setStyleSheet("QLabel {color : red;}");
        ui->outputLineEdit->setText("");
        return;
    }
    if (number < 12)
    {
        ui->outputLabel->setText("Number is less than 12!");
        ui->outputLabel->setStyleSheet("QLabel {color : red;}");
        ui->outputLineEdit->setText("");
        return;
    }
    if (number > 50)
    {
        ui->outputLabel->setText("Number is too big!");
        ui->outputLabel->setStyleSheet("QLabel {color : red;}");
        ui->outputLineEdit->setText("");
        return;
    }
    QString password = createPassword(number);
    ui->outputLabel->setText("Your password is:");
    ui->outputLabel->setStyleSheet("QLabel {color : green;}");
    ui->outputLineEdit->setText(password);
}

void MainWindow::copyToClipboard()
{
    QClipboard* clipboard = QApplication::clipboard();
    if (!ui->outputLineEdit->text().isEmpty())
    {
        clipboard->setText(ui->outputLineEdit->text(), QClipboard::Clipboard);
        ui->outputLabel->setText("Your password is copied to clipboard.");
        ui->outputLabel->setStyleSheet("QLabel {color : green;}");
    }
}

QString MainWindow::createPassword(const int &length)
{
    std::string result;
    std::vector<std::string> symbols;
    symbols.emplace_back("abcdefghijklmnopqrstuvwxyz");
    symbols.emplace_back("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    symbols.emplace_back("0123456789");
    symbols.emplace_back("#$%&'()*+,-./:;<=>?@[\\]^_`{|}~)");

    std::srand(std::time(nullptr));

    for (auto &symbol : symbols)
    {
        result += symbol[std::rand() % symbol.length()];
    }

    while (result.length() < length)
    {
        int arrayIndex = std::rand() % symbols.size();
        int symbolIndex = std::rand() % symbols[arrayIndex].length();
        char nextSymbol = symbols[arrayIndex][symbolIndex];
        if (!checkRepeat(result, nextSymbol))
            result += nextSymbol;
    }
    return QString::fromStdString(result);
}

std::string MainWindow::shuffle(const std::string &password)
{
    std::string result;
    std::vector<int> usedPositions;
    for (int i = 0; i < password.length(); ++i)
    {
        int index = std::rand() % password.length();
        if (checkPositions(usedPositions, index) || (i > 0 && password[index] == result[i - 1]))
            i -= 1;
        else
        {
            result += password[index];
            usedPositions.push_back(index);
        }
    }
    return result;
}

bool MainWindow::checkRepeat(const std::string &password, const char &symbol)
{
    for (int i = 0; i < password.length(); ++i)
    {
        if (password[i] == symbol)
            return true;
    }
    return false;
}

bool MainWindow::checkPositions(const std::vector<int> &numbers, const int &num)
{
    if (numbers.empty())
        return false;
    for (int i = 0; i < numbers.size(); ++i)
    {
        if (num == numbers[i])
            return true;
    }
    return false;
}

