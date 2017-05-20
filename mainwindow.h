#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMessageBox>
#include <QString>
#include <QPrintDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <QPrinter>
//QT_BEGIN_NAMESPACE
//class QWidget ;
//QT_END_NAMESPACE


#include "TraiterImage.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();
protected:
       int meth; // метод для конструктора
    
private slots:

    void ouvrir();  //чтобы открыть изображение
    void enregistrer(); // чтобы сохранить изображение
    void about();

    void  hrgradient();
    void  vtgradient();
    void  gaussianfilter();
    void  rgbtolum();
    void  border_detect();

    void fenetragefilter();
    void seuillagefilter();
    void binarisationfilter();
    void moyenneurfilter();
    void medianefilter();
    void inversionfilter();
    void initialiser();
    void afficherParametre();
    void cacherParametre();
    void  updateA(int A);
    void  updateB(int A);


private:
    void print();
    void createConnection();
    void loadImage();

    int aa ;
    int bb;

    TraiterImage* im1; // class TraiterImage
    QImage image1;
    QImage image2;
    QString m_chemin;
    QString fileName;
    Ui::MainWindow *ui;

#ifndef QT_NO_PRINTER
    QPrinter printer;
#endif
};

#endif // MAINWINDOW_H
