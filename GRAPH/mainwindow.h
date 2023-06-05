#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QQueue>
#include <QPainter>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void addVertex();
    void deleteVertex();
    void DFS(int vertex);
    void BFS(int vertex);

    QVector<int> getNeighbours(int vertex);
    void getMatrix();

    //coomi
    void commi();
    void rowReduction();
    void columnReduction();

    int findMinInRow(int i, int j);			//i, j - excepts
    int findMinInColumn(int i, int j);

    void setInfinity(int i = -1, int j = -1);
    void printPath();
    //endcommi
    
    QString Deixtra(int &, QString &);
    bool MainWindow::AllVisited(QVector<bool> &visitedVerts);
    void MainWindow::FillLabels(int &start);
    int MainWindow::GetWeight(int x, int y);
    
    virtual void paintEvent(QPaintEvent *event);
    void paintEllipse(QPainter &painter, int numberOfVerticies = 0);
    void bindEllipseWithDirection(QPainter &painter, int numberOfVerticies = 0);


private slots:
    void on_pushButtonAddVertex();
    void on_pushButtonDeleteVertex();
    void on_updateButtonClicked();
    void on_TSPButtonClicked();
    void on_DFSButtonClicked();
    void on_BFSButtonClicked();


private:
    Ui::MainWindow *ui;
    QVector<bool> isVisitedVertecies;
    QPainter paint;

    QVector<QVector<int>> matrix;
    QVector<int> path;
    QString solution;
    QQueue<int> tmpQueue;
    QVector<int> vertexList;
    QVector<int> labelList {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
};
#endif // MAINWINDOW_H
