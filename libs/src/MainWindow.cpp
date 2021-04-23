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
// Internal
#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent){
    setWindowTitle("QtApp");

    setupLayout();
    setupMenuBar();
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

   // _widgetsplitter = new QSplitter();
    //_settingsWidget = new QTreeView();
    _textWidget = new QTextEdit(_centralWidget);

    // _settingsWidget->setMinimumWidth(100);

    _textWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   // _settingsWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    _gridLayout->addWidget(_textWidget);
    //_widgetsplitter->addWidget(_settingsWidget);
    //_widgetsplitter->addWidget(_textWidget);
   // _widgetsplitter->setStretchFactor(1, 1);

    _centralWidget->setLayout(_gridLayout);
    setCentralWidget(_centralWidget);
}



void MainWindow::setupFileViewer() {
    auto FileMenu = menuBar()->addMenu("&File");

    _NewFile = FileMenu->addAction("New File", [this]() {onNewFileTriggered(); });
    _NewFile->setShortcut(QKeySequence::New);

    _openFile = FileMenu->addAction("Open File..", [this]() {onOpenFileTriggered(); });
    _openFile->setShortcut(QKeySequence::Open);

    _openFolder = FileMenu->addAction("Open Folder..", [this]() {onOpenFolderTriggered(); });

    _exit = FileMenu->addAction("Exit", [this]() {OnExitTriggered(); });
    
}

void MainWindow::onNewFileTriggered() {
    _textWidget->clear();
    _textWidget->setText(QString());
}
void MainWindow::onOpenFileTriggered() {
    QString filename = QFileDialog::getOpenFileName(this, "Open");
    QFile file(filename);
    auto currentFile = filename;
   /* if (!file.open(QIODevice::ReadOnly | QFile::Text)) {

        QMessageBox::warning(this, "Warning", "Cannot open File : " + file.errorString());
    }*/

    setWindowTitle(filename + " - Mint Text");
    QTextStream in(&file);
    QString text = in.readAll();
    _textWidget->setText(text);
    file.close();
}
void MainWindow::onOpenFolderTriggered() {


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