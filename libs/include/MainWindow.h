#pragma once
// QT
#include <QMainWindow>
#include <QGridLayout>
#include <QTextEdit>
#include <QSplitter>
#include <QTreeView>
#include <QPointer>

class MainWindow : public QMainWindow {
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private:
    void setupLayout();
    void setupMenuBar();
    void setupToolBar();
    void setupFileViewer();
    void setupEditViewer();
    void setupSelectionViewer();
    void setupFindViewer();
    void setupHelpViewer();

public:
    //File Functions
    void onOpenFileTriggered();
    void onOpenJsonFileTriggered();
    void onCalculateMedianTriggered();
    double CalcMedian(std::vector<double> scores);
    void OnExitTriggered();
    //Edit Functions
    void onCopyTriggered();
    void onCutTriggered();
    void onpasteTriggered();

private:
    //File
    QAction* _openFile;
    QAction* _openJsonFile;
    QAction* CalculateMedian;
    QAction* _exit;
    //Edit
    QAction* _copyText;
    QAction* _PasteText;
    QAction* _cutText;
    //
    QToolBar* toolBar;

    
    

private:
    QTextEdit* _textWidget;
    QWidget* _centralWidget;
    QGridLayout* _gridLayout;
    QSplitter* _widgetsplitter;
    QTextEdit* _textWidgetCalculator;
   //
    //QStringList stringList;
    std::vector<double> OrderedValues;
    std::vector<double> OrderedValuesinJson;
    QString strFinal;
    //
   


};