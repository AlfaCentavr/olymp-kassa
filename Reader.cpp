#include "Reader.h"

#include <QCryptographicHash>
#include <QFile>
#include <QRegularExpression>
#include <QTimer>

Reader::Reader(QString &pathHtml, QObject *parent)
    : QObject{parent}
    , pathHtml(pathHtml)
{

}

void Reader::start()
{
    checkFile();
}

/**
 * @brief Reader::checkFile
 * Если не получилось открыть файл/файл не существует, то hash = 0 и отправляется пустая строка для отображения
 * html формы. Иначе открываем и читаем файл, после чего сравниваем с хеш-суммой в памяти, если суммы сходятся,
 * то прочитайнный файл уже отображен. В противном случае устанавливаем стрингу для передачи в форму и сохраняем хеш-сумму
 */
void Reader::checkFile(){
    qDebug() << "path html: " + pathHtml;
    QFile htmlFile(pathHtml);
    QByteArray dataHtml;
    QString textHtml = "";
    if(htmlFile.exists()) {
        if(htmlFile.open(QIODevice::ReadOnly)){
           dataHtml = htmlFile.readAll();
           QByteArray hash = QCryptographicHash::hash(dataHtml, QCryptographicHash::Md5);
           if(hash != this->hash) {
               textHtml = QString(dataHtml);
               textHtml.replace(QRegularExpression("(<BODY STYLE).*(>)"), "<BODY STYLE=\"background-color: #edab71; margin: 0; font-family: Arial; font-size: 8pt; font-style: normal; \">");
               this->hash = hash;
               qDebug() << "html is open";
           } else {
               qDebug() << "html doesn't change";
               return;
           }
        } else {
            qDebug() << "html doesn't open";
            this->hash = 0;
        }
    } else {
        qDebug() << "html doesn't exist";
        this->hash = 0;
    }
    emit updateFile(textHtml);
}
