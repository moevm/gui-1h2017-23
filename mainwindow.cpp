#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createConnection();

}
MainWindow::~MainWindow()

{
    delete ui;
    delete [] im1;

}

void MainWindow::createConnection()
{

    connect(ui->ouvrirAct, SIGNAL(triggered()), this, SLOT(ouvrir()));

    connect(ui->enregistrerAct, SIGNAL(triggered()), this, SLOT(enregistrer()));

    connect(ui->fermerAct, SIGNAL(triggered()), this, SLOT(close()));

    connect(ui->rgbtolumAct, SIGNAL (clicked()), this, SLOT(rgbtolum()));


    connect(ui->gaussianfilterAct, SIGNAL(clicked()), this, SLOT(gaussianfilter()));

    connect(ui->fenetragefilterAct, SIGNAL(clicked()), this, SLOT(fenetragefilter()));

    connect(ui->seuillagefilterAct, SIGNAL(clicked()), this, SLOT(seuillagefilter()));

    connect(ui->binarisationfilterAct, SIGNAL(clicked()), this, SLOT(binarisationfilter()));

    connect(ui->seuilageIntervallefilterAct, SIGNAL(clicked()), this, SLOT(moyenneurfilter()));

    connect(ui->binaristionIntervallefilterAct, SIGNAL(clicked()), this, SLOT(medianefilter()));

    connect(ui->inversionfilterAct, SIGNAL(clicked()), this, SLOT(inversionfilter()));

    connect(ui->hrgradientAct, SIGNAL(clicked()), this, SLOT(hrgradient()));

    connect(ui->vtgradientAct, SIGNAL(clicked()), this, SLOT(vtgradient()));

    connect(ui->borderdetectAct, SIGNAL(clicked()), this, SLOT(border_detect()));

    connect(ui->aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    connect(ui->initialiserAct, SIGNAL(clicked()),this, SLOT(initialiser()));
    connect(ui->slideA, SIGNAL(valueChanged(int)), this, SLOT(updateA(int)));
    connect(ui->slideB, SIGNAL(valueChanged(int)), this, SLOT(updateB(int)));

}


void MainWindow::loadImage()
{

    QSize size(ui->imageLabel->width(), ui->imageLabel->height());
    QImage image2 = image1.scaled(size, Qt::KeepAspectRatio);

    ui->imageLabel->setPixmap(QPixmap::fromImage(image2));


}

void MainWindow::ouvrir()
{
    cacherParametre();
    fileName = QFileDialog::getOpenFileName(this, "Open file...", QString());

    if (!fileName.isEmpty()) {
        QImage image(fileName);
        image1=image;
        m_chemin=fileName;
        if (image1.isNull()) {
            QMessageBox::information(this, "MainWindow ",
                                     tr("Unable to open .").arg(fileName));
            return;
        }
        int fact=image1.depth()/8;
        im1=new TraiterImage(image1.height(),fact*image1.width());
        this->loadImage();
    }
}


void MainWindow::enregistrer()
{
    QString chemin = QFileDialog::getSaveFileName(this, "Save file", m_chemin,"Image (*.jpeg)");
    QFile file(chemin);
    if(!file.open(QIODevice::WriteOnly))
        return;
    QImage im1=this->image1;
    QString extension=  QFileInfo(chemin).suffix();


}

void MainWindow::print()

{
    Q_ASSERT(ui->imageLabel->pixmap());
#ifndef QT_NO_PRINTER
    QPrintDialog dialog(&printer, this);

    if (dialog.exec()) {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = ui->imageLabel->pixmap()->size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(ui->imageLabel->pixmap()->rect());
        painter.drawPixmap(0, 0, *ui->imageLabel->pixmap());
    }
#endif
}


void MainWindow::about()
{

    QMessageBox::about(this, "About application",
                       tr("<p>This application is designed to editing image."
                          " It written in the C++ programming language in Qt Creator (cross-platform application framework)   "
                          ));
}



void MainWindow::vtgradient()
{
    if (image1.isNull()) {
        QMessageBox::information(this, "MainWindow ",
                                 " Please, upload the picture."
                                 " To open image,  click File - > Open."
                                 );
        return;
    }
    cacherParametre();
    int fact=image1.depth()/8;
    if(im1->isNULL())
    {
        im1=new TraiterImage(image1.height(),fact*image1.width());
    }
    // MainWindow *w = new MainWindow();
    this->setWindowTitle(tr("Filtre Gradient vertical"));
    this->show();
    this->image1=this->image1.copy();
    im1->transfert_to_exim(&(this->image1));
    im1->normex(fact);
    im1->transfertx();
    im1->transfert_to_qim(&(this->image1));
    this->loadImage();
    this->repaint();
}

void MainWindow::hrgradient()
{
    if (image1.isNull()) {
        QMessageBox::information(this, "MainWindow ",
                                 "To edit the image, click File, then Open and select the image."
                                 );
        return;
    }
    cacherParametre();
    int fact=image1.depth()/8;
    if(im1->isNULL())
    {
        im1=new TraiterImage(image1.height(),fact*image1.width());
    }
    this->setWindowTitle(tr(" Горизонтальный градиент"));
    this->show();
    this->image1=this->image1.copy();
    im1->transfert_to_exim(&(this->image1));
    im1->normey(fact);
    im1->transferty();
    im1->transfert_to_qim(&(this->image1));
    this->loadImage();
    this->repaint();

}

void MainWindow::gaussianfilter()
{
    if (image1.isNull()) {
        QMessageBox::information(this, "MainWindow ",
                                 "To edit the image, click File, then Open and select the image.");
        return;
    }
    cacherParametre();
    meth=0;
    int fact=image1.depth()/8;
    if(im1->isNULL())
    {
        im1=new TraiterImage(image1.height(),fact*image1.width());
    }
    this->setWindowTitle(tr("Гауссово размытие"));
    this->show();
    this->image1=this->image1.copy();
    im1->transfert_to_exim(&(this->image1));
    im1->gaussian(fact);
    im1->transfert_to_qim(&(this->image1));
    this->loadImage();
    this->repaint();
}

void MainWindow::rgbtolum()
{
    if (image1.isNull()) {
        QMessageBox::information(this, "MainWindow ",
                                 "To edit the image, click File, then Open and select the image.");
        return;
    }
    meth=1;
    cacherParametre();
    int fact=image1.depth()/8;
    if(im1->isNULL())
    {
        im1=new TraiterImage(image1.height(),fact*image1.width());
    }
    this->setWindowTitle(tr("Яркость"));
    this->show();
    this->image1=this->image1.copy();
    im1->transfert_to_exim(&(this->image1));
    if(fact==4)
    { im1->rgb_to_lum(fact);}
    im1->transfert_to_qim(&(this->image1));
    this->loadImage();
    this->repaint();;
}

void MainWindow::border_detect()
{
    if (image1.isNull()) {
        QMessageBox::information(this, "MainWindow ",
                                  "To edit the image, click File, then Open and select the image.");
        return;
    }
    meth=2;
    cacherParametre();
    int fact=image1.depth()/8;
    if(im1->isNULL())
    {
        im1=new TraiterImage(image1.height(),fact*image1.width());
    }
    this->setWindowTitle(tr(" Обнаружение контуров"));
    this->show();
    this->image1=this->image1.copy();
    im1->transfert_to_exim(&(this->image1));
    im1->normex(fact);
    im1->normey(fact);
    im1->norme(fact);
    im1->transfert_to_qim(&(this->image1));
    this->loadImage();
    this->repaint();
}

void MainWindow::fenetragefilter()
{
    if (image1.isNull()) {
        QMessageBox::information(this, "MainWindow ",
                                  "To edit the image, click File, then Open and select the image.");
        return;
    }

    if ( aa>255 ||aa<0 )
    {
        aa=50;
    }
    if ( bb>255 ||bb<0)
    {
        bb=100;
    }

    meth=3;
    afficherParametre();
    int fact=image1.depth()/8;
    //      int a=50,b=100,L=255;
    //      double teta=1;

    if(im1->isNULL())
    {
        im1=new TraiterImage(image1.height(),fact*image1.width());
    }
    //MainWindow* w =new MainWindow();
    this->setWindowTitle(tr("Гамма"));
    //w->m_chemin=m_chemin;
    this->show();
    // w->image1=this->image1;
    this->image1=this->image1.copy();
    this->image2=this->image1;
    // fenetragefilter_load();
    im1->transfert_to_exim(&(this->image1));
    im1->fenetrage(fact,aa,bb,255,1);
    im1->transfert_to_qim(&(this->image1));
    this->loadImage();
    this->repaint();
}



void MainWindow::seuillagefilter()
{
    if (image1.isNull()) {
        QMessageBox::information(this, "MainWindow ",
                                 "To edit the image, click File, then Open and select the image.");
        return;
    }
    if ( aa>255 ||aa<0 )
    {
        aa=50;
    }
    if ( bb>255 ||bb<0)
    {
        bb=100;
    }
    meth=4;
    afficherParametre();
    int fact=image1.depth()/8;
    //    int a=50;
    //    double teta=1;
    if(im1->isNULL())
    {
        im1=new TraiterImage(image1.height(),fact*image1.width());
    }
    this->setWindowTitle(tr("Пороговый фильтр"));
    //w->m_chemin=m_chemin;
    this->show();
    //w->image1=this->image1;

    this->image1=this->image1.copy();
    this->image2=this->image1;
    //  seuillagefilter_load();

    im1->transfert_to_exim(&(this->image1));
    im1->seuillage(fact,aa,1);
    im1->transfert_to_qim(&(this->image1));
    this->loadImage();
    this->repaint();
}


void MainWindow::binarisationfilter()
{
    if (image1.isNull()) {
        QMessageBox::information(this, "MainWindow ",
                                  "To edit the image, click File, then Open and select the image.");
        return;
    }
    if (aa>255 ||aa<0 )
    {
        aa=50;
    }
    if ( bb>255 ||bb<0)
    {
        bb=100;
    }
    meth=5;
    afficherParametre();

    int fact=image1.depth()/8;
    //    int a=50, L=255;
    if(im1->isNULL())
    {
        im1=new TraiterImage(image1.height(),fact*image1.width());
    }
    //MainWindow* w =new MainWindow();
    this->setWindowTitle(tr("Бинаризация"));
    //w->m_chemin=m_chemin;
    this->show();
    //w->image1=this->image1;
    this->image1=this->image1.copy();
    this->image2=this->image1;
    // binarisationfilter_load();
    im1->transfert_to_exim(&(this->image1));
    im1->binarisation(fact,aa,255);;
    im1->transfert_to_qim(&(this->image1));
    this->loadImage();
    this->repaint();
}



void MainWindow::moyenneurfilter()
{
    if (image1.isNull()) {
        QMessageBox::information(this, "MainWindow ",
                                  "To edit the image, click File, then Open and select the image.");
        return;
    }
    if ( aa>255 ||aa<0 )
    {
        aa=50;
    }
    if ( bb>255 ||bb<0)
    {
        bb=100;
    }
    meth=6;
    cacherParametre();
    int fact=image1.depth()/8;
    //    int a=50,b=100,L=255;
    //    double teta=1;
    if(im1->isNULL())
    {
        im1=new TraiterImage(image1.height(),fact*image1.width());
    }
    //MainWindow* w =new MainWindow();
    this->setWindowTitle(tr("Усреднение"));
    // w->m_chemin=m_chemin;
    this->show();
    //w->image1=this->image1;
    this->image1=this->image1.copy();
    im1->transfert_to_exim(&(this->image1));
    //     im1->seuillage_par_intervalle(fact,aa,bb,255,1);
    im1->moyenneur(fact);
    im1->transfert_to_qim(&(this->image1));
    this->loadImage();
    this->repaint();
}




void MainWindow::medianefilter()
{
    if (image1.isNull()) {
        QMessageBox::information(this, "MainWindow ",
                                 "To edit the image, click File, then Open and select the image.");
        return;
    }
    if ( aa>255 ||aa<0 )
    {
        aa=50;
    }
    if (bb>255 ||bb<0)
    {
        bb=100;
    }
    meth=7;
    cacherParametre();


    int fact=image1.depth()/8;
    //    int a=50,b=100,L=255;
    if(im1->isNULL())
    {
        im1=new TraiterImage(image1.height(),fact*image1.width());
    }

    this->show();
    //w->image1=this->image1;
    this->image1=this->image1.copy();
    this->image2=this->image1;
    //    binaristionIntervallefilter_load();
    im1->transfert_to_exim(&(this->image1));
    //    im1->
    im1->mediane(fact,3);
    im1->transfert_to_qim(&(this->image1));
    this->loadImage();
    this->repaint();
}



void MainWindow::inversionfilter()
{
    if (image1.isNull()) {
        QMessageBox::information(this, "MainWindow ",
                                  "To edit the image, click File, then Open and select the image.");
        return;
    }
    meth=8;
    cacherParametre();
    int fact=image1.depth()/8;
    if( im1->isNULL())
    {
        im1=new TraiterImage(image1.height(),fact*image1.width());
    }
    // MainWindow* w =new MainWindow();
    this->setWindowTitle(tr("Инверсия"));
    //w->m_chemin=m_chemin;
    this->show();
    //w->image1=this->image1;
    this->image1=this->image1.copy();
    im1->transfert_to_exim(&(this->image1));
    im1->inversion(fact);
    im1->transfert_to_qim(&(this->image1));

    this->loadImage();
    this->repaint();
}

void MainWindow::initialiser()
{
    if (image1.isNull()) {
        QMessageBox::information(this, "MainWindow ",
                                  "To edit the image, click File, then Open and select the image.");
        return;
    }
    cacherParametre();
    QImage image(fileName);
    image1=image;
    m_chemin=fileName;

    this->loadImage();
}

void MainWindow::afficherParametre()
{
    ui->slideA->setVisible(true);
    ui->labelA->setVisible(true);
    ui->LcdA->setVisible(true);
    if (meth==3)
    {
        ui->slideB->setVisible(true);
        ui->labelB->setVisible(true);
        ui->LcdB->setVisible(true);
    }
    else
    {
        ui->slideB->setVisible(false);
        ui->labelB->setVisible(false);
        ui->LcdB->setVisible(false);
    }



}

void MainWindow::cacherParametre()
{
    ui->slideA->setVisible(false);
    ui->labelA->setVisible(false);
    ui->LcdA->setVisible(false);
    ui->slideB->setVisible(false);
    ui->labelB->setVisible(false);
    ui->LcdB->setVisible(false);
}


void MainWindow::updateA(int A)
{
    aa=A;


    if (meth==3)
    {
        if(ui->slideA->value()>ui->slideB->value())
        {
            QMessageBox::information(this, "MainWindow ",
                                     "The value of A must be less than B");
        }
        fenetragefilter();
    }
    if (meth==4)
        seuillagefilter();
    if (meth==5)
        binarisationfilter();


}





void MainWindow::updateB(int A)
{
    bb=A;
    if (meth==3)
        fenetragefilter();



}

