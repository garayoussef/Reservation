#ifndef RESERVATION_H
#define RESERVATION_H

#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDate>


class Reservation
{
private:
    QString id_res;
    QString cin;
    QDate date_res;
    QString heur;
    QString service;


public:
    Reservation();

    Reservation(QString, QString, QDate, QString, QString);

    bool ajouter_Res();

    QSqlQueryModel * afficher_Res();

    bool supprimer_Res(QString);

    bool modifier_Res(QString,QDate,QString,QString);

    QSqlQueryModel* recherche(QString);

    QSqlQueryModel* tri();


};
#endif //
