#include "fenprincipale.h"
#include "fencodegenere.h"

FenPrincipale::FenPrincipale()
{
//Definition de la classe
    i=0;
    nom = new QLineEdit;
    classeMere = new QLineEdit;
    //Layout definitionClasse
    QFormLayout *defLayout = new QFormLayout;
        defLayout->addRow("&Nom :", nom);
        defLayout->addRow("Classe mère :", classeMere);
    //Box comprenant le layout definition
    QGroupBox *defClassBox = new QGroupBox("Définition de la classe");
        defClassBox->setLayout(defLayout);

//Options
    protections = new QCheckBox("Protéger le &header contre les inclusions multiples");
    genererConstructeur = new QCheckBox("Générer un &constructeur par défaut");
    genererDestructeur = new QCheckBox("Générer un &destructeur par défaut");

    protections->setChecked(true);
    genererConstructeur->setChecked(true);
    //Layout Option
    QVBoxLayout *optionLayout = new QVBoxLayout;
        optionLayout->addWidget(protections);
        optionLayout->addWidget(genererConstructeur);
        optionLayout->addWidget(genererDestructeur);
    //Box comprenant le layout Option
    QGroupBox *optionBox = new QGroupBox("Options");
        optionBox->setLayout(optionLayout);
//Ajouter Attributs
    typeAttribut = new QLineEdit;
    nomAttribut = new QLineEdit;
    validerAtt = new QPushButton("Valider");
    //Layout FormAttribut
    QFormLayout *ajtAttributLayout = new QFormLayout;
        ajtAttributLayout->addRow("Type :", typeAttribut);
        ajtAttributLayout->addRow("Nom :", nomAttribut);
    accesseur = new QCheckBox("Générer l'accesseur");
    accesseur->setChecked(true);
    //Layout FormAttribut+Bouton valider
     QVBoxLayout *attributLayoutBouton = new QVBoxLayout;
        attributLayoutBouton->addLayout(ajtAttributLayout);
        attributLayoutBouton->addWidget(accesseur);
        attributLayoutBouton->addWidget(validerAtt);
    //Box Attribut
     attributBox = new QGroupBox("Ajouter des attributs");
        attributBox->setCheckable(true);
        attributBox->setChecked(false);
        attributBox->setLayout(attributLayoutBouton);

//Ajout commentaire
    auteur = new QLineEdit;
    date = new QDateEdit;
        date->setDate(QDate::currentDate());
    role = new QTextEdit;
    //Layout Commentaire
    QFormLayout *commentLayout = new QFormLayout;
        commentLayout->addRow("&Auteur :", auteur);
        commentLayout->addRow("Da&te de création :", date);
        commentLayout->addRow("Rôle de la classe :", role);
    //Box comprenant le layout commentaire
    commentBox = new QGroupBox("Ajouter des commentaires");
        commentBox->setCheckable(true);
        commentBox->setChecked(false);
        commentBox->setLayout(commentLayout);

//Ajout Bouton generer/Quitter
    generer = new QPushButton("Générer");
    quitter = new QPushButton("Quitter");
    //layout bouton
    QHBoxLayout *boutonLayout = new QHBoxLayout;
        boutonLayout->addWidget(generer);
        boutonLayout->addWidget(quitter);
    //Box comprenant le layout bouton
    QGroupBox *boutonBox = new QGroupBox;
        boutonBox->setLayout(boutonLayout);

    //Layout comprenant tout les Box
    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
        layoutPrincipal->addWidget(defClassBox);
        layoutPrincipal->addWidget(optionBox);
        layoutPrincipal->addWidget(attributBox);
        layoutPrincipal->addWidget(commentBox);
        layoutPrincipal->addWidget(boutonBox);

    setLayout(layoutPrincipal);

    //Connection
    connect(quitter, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(generer, SIGNAL(clicked()), this, SLOT(genererCode()));

    connect(validerAtt, SIGNAL(clicked()), this, SLOT( ajouterAttribut()));
}

void FenPrincipale::genererCode()
{
    if(nom->text().isEmpty())
    {
        QMessageBox::critical(this, "Erreur", "Veuillez au minimum entrer le nom de la classe");
        return;
    }
//Fichier H
    QString codeH;

    if(commentBox->isChecked())
    {
        codeH += "/*\nAuteur : " + auteur->text() + "\n";
        codeH += "Date de création : " + date->text() + "\n";
        codeH += "Role : \n" + role->toPlainText() + "\n*/ \n \n";
    }

    if(protections->isChecked())
    {
        codeH += "#ifndef HEADER_" + nom->text().toUpper() + "\n";
        codeH += "#define HEADER_" + nom->text().toUpper() + "\n \n";
    }

    codeH += "class " + nom->text();

    if(!classeMere->text().isEmpty())
    {
        codeH += " : public " + nom->text() + "\n";
    }
    else
    {
        codeH += "\n";
    }

    codeH += "{\npublic:\n";

    if(genererConstructeur->isChecked())
    {
        codeH+= "//Constructeur\n";
        codeH += "   " + nom->text() + "();\n";
    }
    else
    {
        codeH += "\n";
    }

    if (genererDestructeur->isChecked())
    {
        codeH += "//Destructeur";
        codeH += "\n   ~" + nom->text() + "();\n";
    }
    else
    {
        codeH += "\n";
    }

    if(attributBox->isChecked())
    {
        codeH += "//Accesseur";
        for(i=0; i < typeAttributTab.size(); i++)
        {
            if(boolAttributTab[i] == true)
            {
                codeH += "\n  " + typeAttributTab[i] + " get" + nomAttributTab[i] + "();\n";
            }
        }
    }

    codeH += "\nprotected:\n";
    if(attributBox->isChecked())
    {
        codeH += "//Attributs\n";
        int i(0);
        for(i=0; i < typeAttributTab.size(); i++)
        {
            codeH += "  " + typeAttributTab[i] + " " + nomAttributTab[i] + ";\n";
        }
    }

    codeH += "\nprivate:\n\n};\n";

    if(protections->isChecked())
    {
        codeH += "#endif";
    }
//Implemente fichier Cpp
    QString codeCpp;

    codeCpp += "#include \"" + nom->text() + ".h\"\n\n";
    codeCpp += nom->text() + "::" + nom->text() + "() \n";
    codeCpp += "{\n}";

    if(genererDestructeur->isChecked())
    {
        codeCpp += "\n\n" + nom->text() + "::~" + nom->text() + "()\n";
        codeCpp += "{\n}";
    }

    if(attributBox->isChecked())
    {
        codeCpp += "\n\n//Accesseur";
        for(i=0; i < typeAttributTab.size(); i++)
        {
            if(boolAttributTab[i] == true)
            {
                codeCpp += "\n" + typeAttributTab[i] + " " + nom->text() + "::" + "get" + nomAttributTab[i] + "()\n";
                codeCpp += "{\n";
                codeCpp += "    return " + nomAttributTab[i] + ";\n";
                codeCpp += "}\n";
            }
        }
    }
//
    QString nomClasse = nom->text();
    FenCodeGenere *fenetreCode = new FenCodeGenere(codeH, codeCpp, nomClasse, this);
    fenetreCode->exec();
}

void FenPrincipale::ajouterAttribut()
{
    if(!typeAttribut->text().isEmpty())
    {
        if(!nomAttribut->text().isEmpty())
        {
            typeAttributTab.push_back(typeAttribut->text());
            nomAttributTab.push_back(nomAttribut->text());
            boolAttributTab.push_back(accesseur->isChecked());
            nomAttribut->clear();
        }
        else
        {
            QMessageBox::critical(this, "Erreur", "Veuillez remplir le champ \"Nom\"");
            return;
        }

    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Veuillez remplir le champ \"Type\"");
        return;
    }

}
