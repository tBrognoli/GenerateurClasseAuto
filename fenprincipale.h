#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#include <QtWidgets>


class FenPrincipale : public QWidget
{
    Q_OBJECT
public:
    FenPrincipale();

    QString getNom();

public slots:
    void genererCode();
    void ajouterAttribut();

private:
    int i;
    QLineEdit *nom;
    QLineEdit *classeMere;

    QCheckBox *protections;
    QCheckBox *genererConstructeur;
    QCheckBox *genererDestructeur;

    QCheckBox *ajtAttributCheck;
    QPushButton *validerAtt;
    QLineEdit *typeAttribut;
    QLineEdit *nomAttribut;
    QGroupBox *attributBox;
    QCheckBox *accesseur;
    QVector<QString> typeAttributTab;
    QVector<QString> nomAttributTab;
    QVector<bool> boolAttributTab;

    QGroupBox *commentBox;
    QLineEdit *auteur;
    QDateEdit *date;
    QTextEdit *role;
    QPushButton *generer;
    QPushButton *quitter;
};

#endif // FENPRINCIPALE_H
