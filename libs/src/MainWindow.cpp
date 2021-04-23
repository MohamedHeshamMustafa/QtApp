//Qt
#include <QMenuBar>
#include <QTextEdit>
#include <qgridlayout.h>
#include <qsplitter.h>
#include <qtreeview.h>
#include<QFileDialog.h>
#include <QMessageBox>
#include <QTextStream>
#include <QApplication>
#include <QToolBar>
// Internal
#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent){
    setWindowTitle("QtApp");

    setupLayout();
    setupMenuBar();
    setupToolBar();
}

MainWindow::~MainWindow() = default;

void MainWindow::setupMenuBar() {
    setupFileViewer();
    setupEditViewer();
    //setupSelectionViewer();
    //setupFindViewer();
    //setupHelpViewer();

}

void MainWindow::setupLayout() {

    _centralWidget = new QWidget(this);
    _gridLayout = new QGridLayout();
    _widgetsplitter = new QSplitter();
    _textWidgetCalculator = new QTextEdit();
    _textWidget = new QTextEdit(_centralWidget);

    _textWidgetCalculator->setMinimumWidth(100);

    _textWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _textWidgetCalculator->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    _gridLayout->addWidget(_widgetsplitter);
    _widgetsplitter->addWidget(_textWidgetCalculator);
    _widgetsplitter->addWidget(_textWidget);
    _widgetsplitter->setStretchFactor(1, 1);

    _centralWidget->setLayout(_gridLayout);
    setCentralWidget(_centralWidget);
}



void MainWindow::setupFileViewer() {
    auto FileMenu = menuBar()->addMenu("&File");


    _openFile = FileMenu->addAction("Open File", [this]() {onOpenFileTriggered(); });
    _openFile->setShortcut(QKeySequence::Open);

    CalculateMedian = FileMenu->addAction("Calculate Median", [this]() {onCalculateMedianTriggered(); });


    _exit = FileMenu->addAction("Exit", [this]() {OnExitTriggered(); });

    
}


void MainWindow::onOpenFileTriggered() {
    QString filename = QFileDialog::getOpenFileName(this, "Open");
    QFile file(filename);
    auto currentFile = filename;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {

        QMessageBox::warning(this, "Warning", "Cannot open File : " + file.errorString());
    }

    setWindowTitle(filename + " - Qt App");
    QTextStream in(&file);
    
 
    while (true)
    {
        QString line = in.readAll();
        if (line.isNull())
            break;
        else
            int value = line.toInt();
            OrderedValues.push_back(value);
            stringList.append(line);
    }
    std::sort(OrderedValues.begin(), OrderedValues.end());
    foreach(QString str, stringList)
    {
        //int value = str.toInt();
        OrderedValues.push_back(value);
        _textWidget->setText(str);
    }
    /*for (int i = 0; i < OrderedValues.size(); i++) {

        QString str = QString::number(OrderedValues[i]);
        _textWidget->setText(str);

    }*/
    //file.close();
}

double MainWindow::CalcMedian(std::vector<int> scores)
{
    size_t size = scores.size();

    if (size == 0)
    {
        return 0;  // Undefined
    }
    else
    {
        sort(scores.begin(), scores.end());
        if (size % 2 == 0)
        {
            return (scores[size / 2 - 1] + scores[size / 2]) / 2;
        }
        else
        {
            return scores[size / 2];
        }
    }
}

void MainWindow::onCalculateMedianTriggered() {

    auto median = CalcMedian(OrderedValues);
    QString stringg = QString::number(median);
    _textWidgetCalculator->setText(stringg);

}

void MainWindow::OnExitTriggered() {
    QApplication::quit();
}

void MainWindow::setupEditViewer() {
    auto EditMenu = menuBar()->addMenu("&Edit");

    _copyText = EditMenu->addAction("Copy", [this]() {onCopyTriggered();});
    _copyText->setShortcut(QKeySequence::Copy);

    _cutText = EditMenu->addAction("Cut", [this]() {onCutTriggered();});
    _cutText->setShortcut(QKeySequence::Cut);

    _PasteText= EditMenu->addAction("Paste", [this]() {onpasteTriggered();});
    _PasteText->setShortcut(QKeySequence::Paste);
}

void MainWindow::onCopyTriggered() {
    _textWidget->copy();
}
void MainWindow::onCutTriggered() {
    _textWidget->cut();
}
void MainWindow::onpasteTriggered() {
    _textWidget->paste();
}

void MainWindow::setupToolBar() {
    toolBar = addToolBar("main toolbar");

    toolBar->addAction(_openFile);
    toolBar->addAction(CalculateMedian);
}