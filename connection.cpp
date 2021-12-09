#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Projet_2A");
db.setUserName("gara");//inserer nom de l'utilisateur
db.setPassword("gara");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
