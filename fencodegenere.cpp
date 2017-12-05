#include "fencodegenere.h"

FenCodeGenere::FenCodeGenere(QString &codeH, QString &codeCpp, QString &nomClasse ,QWidget *parent = 0) : QDialog(parent), m_nomClasse(nomClasse)
{
    QTabWidget *onglets = new QTabWidget;

    QWidget *pageCpp = new QWidget;
    QWidget *pageH = new QWidget;

//Contenu PageCPP
    codeGenereCpp = new QTextEdit();
    codeGenereCpp->setPlainText(codeCpp);
    codeGenereCpp->setFont(QFont("Courrier"));
    codeGenereCpp->setReadOnly(true);
    codeGenereCpp->setLineWrapMode(QTextEdit::NoWrap);
    //place codeGenereCpp dans un Layout
    QVBoxLayout *pageCppLayout = new QVBoxLayout;
    pageCppLayout->addWidget(codeGenereCpp);
    //Place le layout contenant le code genere dans le premier onglet
    pageCpp->setLayout(pageCppLayout);

//Contenu PageH
    codeGenereH = new QTextEdit();
    codeGenereH-> setPlainText(codeH);
    codeGenereH->setFont(QFont("Courrier"));
    codeGenereH->setReadOnly(true);
    codeGenereH->setLineWrapMode(QTextEdit::NoWrap);
    //place codeGenereH dans un layout
    QVBoxLayout *pageHLayout = new QVBoxLayout;
    pageHLayout->addWidget(codeGenereH);
    //Place le layout contenant le code genere dans le deuxieme onglet
    pageH->setLayout(pageHLayout);

    //
    onglets->addTab(pageCpp, "Fichier source");
    onglets->addTab(pageH, "Fichier header");

    fermer = new QPushButton("Fermer");
    sauvegarder = new QPushButton("Sauvegarder");
    QVBoxLayout *layoutPrincip = new QVBoxLayout;
    layoutPrincip->addWidget(onglets);
    layoutPrincip->addWidget(sauvegarder);
    layoutPrincip->addWidget(fermer);

    setLayout(layoutPrincip);
    resize(350,450);

    connect(sauvegarder, SIGNAL(clicked()), this, SLOT(enregistrer()));
    connect(fermer, SIGNAL(clicked()), this, SLOT(accept()));
}

void FenCodeGenere::enregistrer()
{
//Choix du chemin d'enregistrement
    QString fichier = QFileDialog::getSaveFileName(this, "Enregistrer un fichier", m_nomClasse, "Tout");
//Enregistrement
    if(!fichier.isEmpty())
    {
    //Du .h
        QFile sauvegardeH(fichier + ".h");
        if(sauvegardeH.open(QFile::WriteOnly))
        {
            QTextStream out(&sauvegardeH);
            out << codeGenereH->toPlainText();
        }
        //du .cpp
        QFile sauvegardeCpp(fichier + ".cpp");
        if(sauvegardeCpp.open(QFile::WriteOnly))
        {
            QTextStream out(&sauvegardeCpp);
            out << codeGenereCpp->toPlainText();
        }
    }
}
