        #include "Reservation.h"
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDialog>
#include <QDate>

Reservation::Reservation()
{
    this->id_res="";
    this->cin="";
    this->date_res =QDate(2000,01,01);
    this->heur="";
    this->service="";



}
Reservation::Reservation(QString id_res,QString service,QDate date_res,QString cin,QString heur)
{
    this->id_res=id_res;
     this->service=service;
     this->date_res=date_res;
     this->cin=cin;
    this->heur=heur;



}
bool Reservation::ajouter_Res()
{
    QSqlQuery query;
    query.prepare("INSERT INTO reservation (id_res,service,date_res,cin,heur) VALUES (:id_res,:service,:date_res,:cin,:heur)");
    query.bindValue(":id_res",id_res);
    query.bindValue(":service",service);
    query.bindValue(":date_res",date_res);
    query.bindValue(":cin",cin);
    query.bindValue(":heur",heur);

    return query.exec();
}
QSqlQueryModel * Reservation::afficher_Res()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from reservation");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_res"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("service"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("date_res"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("heur"));
        return model;
}


bool Reservation::modifier_Res(QString id_res,QDate date_res,QString heur,QString service)
{
    QSqlQuery query;
    query.prepare("UPDATE reservation SET id_res = :id_res,date_res = :date_res,heur = :heur,service = :service  WHERE id_res= :id_res ");
    query.bindValue(":id_res",id_res);
    query.bindValue(":date_res",date_res);
    query.bindValue(":heur",heur);
    query.bindValue(":service",service);
    return    query.exec();
}


bool Reservation::supprimer_Res(QString idd)
{
    QSqlQuery query;

    query.prepare("Delete from reservation where id_res = :id ");
    query.bindValue(":id", idd);
    return    query.exec();
}


QSqlQueryModel* Reservation::recherche(QString r)
{
    QSqlQueryModel* model=new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT* FROM reservation WHERE id_res like '"+r+"' ||'%' OR date_res like '"+r+"' ||'%' OR heur like '"+r+"' ||'%' OR service like '"+r+"' ||'%' OR id_res like '"+r+"' ||'%' OR cin like '"+r+"' ");
    query.bindValue(":id",r);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_res"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("service"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("date_res"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("heur"));

    return model;
}


QSqlQueryModel* Reservation::tri()
{
    QSqlQueryModel* model=new QSqlQueryModel();


    model->setQuery("SELECT* FROM reservation ORDER BY date_res");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_res"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("service"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("date_res"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("heur"));

    return model;
}

