//Qt
#include <QMenuBar>
#include <QTextEdit>
#include <QGridLayout>
#include <QSplitter>
#include <QTreeView>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QApplication>
#include <QToolBar>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
// Internal
#include "MainWindow.h"
//STL
#include <math.h>

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


    _openFile = FileMenu->addAction("Open Text File", [this]() {onOpenFileTriggered(); });
    _openFile->setShortcut(QKeySequence::Open);

    _openJsonFile = FileMenu->addAction("Open Json File", [this]() {onOpenJsonFileTriggered(); });

    CalculateMedian = FileMenu->addAction("Calculate Median", [this]() {onCalculateMedianTriggered(); });


    _exit = FileMenu->addAction("Exit", [this]() {OnExitTriggered(); });

    
}


void MainWindow::onOpenFileTriggered() {

    _textWidget->clear();
    _textWidgetCalculator->clear();
    OrderedValues.clear();
 
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
        QString line = in.readLine();
        if (line.isNull())
            break;
        else
            OrderedValues.push_back(line.toDouble());
            
    }
    std::sort(OrderedValues.begin(), OrderedValues.end());

    QString temp;
    for (int i = 0; i < OrderedValues.size(); ++i)
    {
        if (i > 0)
            temp += "\n";
        temp += QString::number(OrderedValues[i]);
    }

    _textWidget->setText(temp);

}

void MainWindow::onOpenJsonFileTriggered(){
    _textWidget->clear();
    _textWidgetCalculator->clear();
    OrderedValues.clear();

    QString filename = QFileDialog::getOpenFileName(this, "Open");
    QFile file(filename);
    auto currentFile = filename;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {

        QMessageBox::warning(this, "Warning", "Cannot open File : " + file.errorString());
    }

    setWindowTitle(filename + " - Qt App");
    QTextStream in(&file);
    QByteArray data = file.readAll();

    QJsonParseError errorPtr;
    QJsonDocument doc = QJsonDocument::fromJson(data, &errorPtr);
    if (doc.isNull()) {
        QMessageBox::warning(this, "Warning", "Cannot open File : " + file.errorString());
    }
    QJsonObject rootObj = doc.object();
    QVector<QPointF> listPoints;
    QJsonArray ptsArray = rootObj.value("Values").toArray();

    foreach(const QJsonValue & val, ptsArray) {
        double x = val.toObject().value("x").toDouble();
        double xx = val.toObject().value("y").toDouble();
        OrderedValues.emplace_back(x);
        OrderedValues.emplace_back(xx);
    }

    std::sort(OrderedValues.begin(), OrderedValues.end());

    QString temp;
    for (int i = 0; i < OrderedValues.size(); ++i)
    {
        if (i > 0)
            temp += "\n";
        temp += QString::number(OrderedValues[i]);
    }

    _textWidget->setText(temp);

  
}

double MainWindow::CalcMedian(std::vector<double> scores)
{
   
    size_t size = scores.size();

    if (size == 0)
    {
        return 0;  // Undefined
    }
    else
    {
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
    float rounded_down_median = floorf(median * 100) / 100;
    QString stringg = QString::number(rounded_down_median);
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
    toolBar->addAction(_openJsonFile);
    toolBar->addAction(CalculateMedian);
}