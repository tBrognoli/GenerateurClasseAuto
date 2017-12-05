#ifndef FENCODEGENERE_H
#define FENCODEGENERE_H
#include <QtWidgets>

class FenCodeGenere : public QDialog
{
    Q_OBJECT
public:
    FenCodeGenere(QString &codeH, QString &codeCpp, QString &nomClasse ,QWidget *parent);
public slots:
    void enregistrer();
private:
    QTextEdit *codeGenereCpp;
    QTextEdit *codeGenereH;
    QPushButton *fermer;
    QPushButton *sauvegarder;
    QString m_nomClasse;

};
#endif // FENCODEGENERE_H
