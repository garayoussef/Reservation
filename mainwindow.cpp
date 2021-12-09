#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Reservation.h"
#include "mainwindow.h"
#include <QMessageBox>
#include "exportexcelobjet.h"
#include <QFileDialog>
#include <QDebug>





MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     ui->tableView_Res->setModel(tmpres.afficher_Res());

     ui->le_code_2->setValidator( new QIntValidator(0, 999999999, this));
      ui->le_cin->setValidator( new QIntValidator(0, 99999999, this));
       ui->le_code->setValidator( new QIntValidator(0, 999999999, this));
}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_pushButton_4_clicked()
{
    QString id_res = ui->le_code->text();
    QString cin = ui->le_cin->text();
    QString heur = ui->le_heur->text();
     QDate date_res = ui->le_date->date();
      QString service = ui->comboBox->currentText();

      if(cin.size() == 8){

    Reservation r(id_res,service,date_res,cin,heur);
    bool test=r.ajouter_Res();

    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("Ajouter"),
                          QObject::tr("reservation ajouté.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);

    }
      }else{
          QMessageBox::critical(nullptr, QObject::tr("Ajouter"),
                            QObject::tr("Verifier Le CIN.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

      }

 ui->tableView_Res->setModel(tmpres.afficher_Res());
 foreach(QLineEdit* le, findChildren<QLineEdit*>()) {
              le->clear();}
         QFile file("C:/Users/waelk/OneDrive/Bureau/Projet_gara/historique.txt");
         if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
             return;
         QTextStream cout(&file);
         QString d_info = QDateTime::currentDateTime().toString();
         QString message2=d_info+" - Une reservation a été ajoutée avec la référence "+id_res+"\n";
         cout << message2;

}


void MainWindow::on_pushmod_2_clicked()
{
    QString id_res = ui->le_code_2->text();
    QString heur = ui->le_heur_2->text();
     QDate date_res = ui->date_2->date();
     QString service = ui->comboBox_2->currentText();
    Reservation r;
    bool test=r.modifier_Res(id_res,date_res,heur,service);

    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("modifie une Reservation"),
                          QObject::tr("Reservation modifie.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
        foreach(QLineEdit* le, findChildren<QLineEdit*>()) {
                     le->clear();}
                QFile file("C:/Users/waelk/OneDrive/Bureau/Projet_gara/historique.txt");
                if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
                    return;
                QTextStream cout(&file);
                QString d_info = QDateTime::currentDateTime().toString();
                QString message2=d_info+" - Une reservation a été modifiée avec la référence "+id_res+"\n";
                cout << message2;
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("non modifie"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

     ui->tableView_Res->setModel(tmpres.afficher_Res());


}

void MainWindow::on_supp_clicked()
{
    QString id =ui->tableView_Res->model()->index(ui->tableView_Res->currentIndex().row(),0).data().toString();
    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Supprimer", "Etes vous sur de supprimer cette Reservation ?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
          bool test=tmpres.supprimer_Res(id);
          if(test)
          {
              ui->tableView_Res->setModel(tmpres.afficher_Res());
              QMessageBox::information(nullptr,"Suppression","Reservatoin supprimé");
              foreach(QLineEdit* le, findChildren<QLineEdit*>()) {
                           le->clear();}
                      QFile file("C:/Users/waelk/OneDrive/Bureau/Projet_gara/historique.txt");
                      if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
                          return;
                      QTextStream cout(&file);
                      QString d_info = QDateTime::currentDateTime().toString();
                      QString message2=d_info+" - Une reservation a été supprimée avec la référence "+id+"\n";
                      cout << message2;
          }
      }

}

void MainWindow::on_xl_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Exportation en fichier Excel"), qApp->applicationDirPath (),
                                                                tr("Fichiers d'extension Excel (*.xls)"));
                if (fileName.isEmpty())
                    return;

                ExportExcelObject obj(fileName, "mydata", ui->tableView_Res);

                // you can change the column order and
                // choose which colum to export
                obj.addField(0, "ID_RES", "char(20)");
                obj.addField(1, "SERVICE", "char(20)");
                obj.addField(2, "DATE_RES", "char(20)");
                obj.addField(3, "CIN", "char(20)");
                obj.addField(4, "HEUR", "char(20)");


                int retVal = obj.export2Excel();

                if( retVal > 0)
                {
                    QMessageBox::information(this, tr("FAIS!"),
                                             QString(tr("%1 enregistrements exportés!")).arg(retVal)
                                             );
                    foreach(QLineEdit* le, findChildren<QLineEdit*>()) {
                                 le->clear();}
                            QFile file("C:/Users/waelk/OneDrive/Bureau/Projet_gara/historique.txt");
                            if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
                                return;
                            QTextStream cout(&file);
                            QString d_info = QDateTime::currentDateTime().toString();
                            QString message2=d_info+" - Une fichier exel a été génerée !\n";
                            cout << message2;

                }
}

void MainWindow::on_search_textEdited(const QString &arg1)
{
    ui->tableView_Res->setModel(tmpres.recherche(arg1));


}

void MainWindow::on_tri_clicked()
{
    ui->tableView_Res->setModel(tmpres.tri());

}

void MainWindow::readfile(){
    QString filename="C:/Users/waelk/OneDrive/Bureau/Projet_gara/historique.txt";
    QFile file(filename);
    if(!file.exists()){
        qDebug() << "NO existe el archivo "<<filename;
    }else{
        qDebug() << filename<<" encontrado...";
    }
    QString line;
    ui->Histo->clear();
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream stream(&file);
        while (!stream.atEnd()){
            line = stream.readLine();
            ui->Histo->setText(ui->Histo->toPlainText()+line+"\n");
            qDebug() << "linea: "<<line;
        }
    }
    file.close();
}

void MainWindow::on_tabWidget_2_currentChanged(int index)
{
    readfile();

}

void MainWindow::on_pdf_clicked()
{
    QString strStream;
            QTextStream out(&strStream);


    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }


    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);
    const int rowCount = ui->tableView_Res->model()->rowCount();
    const int columnCount = ui->tableView_Res->model()->columnCount();
    QString TT = QDate::currentDate().toString("yyyy/MM/dd");
    out <<"<html>\n"
          "<head>\n"
           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        << "<title>ERP - RESERVATIONS LIST<title>\n "
        << "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"
        "<h1 style=\"text-align: center;\"><strong> LISTE DES RESERVATIONS </strong></h1>"
        "<h5 style=\"text-align: center;\">Le : "+TT+"</h5>"
        "<br>\n"
        "<table style=\"text-align: center; font-size: 12;\" border=1>\n "
          "</br> </br>";
    // headers
    out << "<thead><tr bgcolor=#d6e5ff>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tableView_Res->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tableView_Res->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tableView_Res->isColumnHidden(column)) {
                QString data =ui->tableView_Res->model()->data(ui->tableView_Res->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table>\n"
        "</body>\n"
        "</html>\n";

    QTextDocument doc;
    doc.setHtml(strStream);
    doc.print(&printer);

    foreach(QLineEdit* le, findChildren<QLineEdit*>()) {
                 le->clear();}
            QFile file("C:/Users/waelk/OneDrive/Bureau/Projet_gara/historique.txt");
            if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
                return;
            QTextStream cout(&file);
            QString d_info = QDateTime::currentDateTime().toString();
            QString message2=d_info+" - Une fichier PDF a été génerée !\n";
            cout << message2;



}

