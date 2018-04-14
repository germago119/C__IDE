//
// Created by karina on 29/03/18.
//

#include <DataStructures/MemoryNode.h>
#include "LocalServer.h"
#include "Server/loguru.hpp"

LocalServer::LocalServer(QObject *parent) : QLocalServer(parent)
{
    clientSocket = nullptr;
    connect(this, &LocalServer::newConnection, [&](){
        clientSocket = nextPendingConnection();
        connect(clientSocket, &QLocalSocket::readyRead, [&](){
            read();
        });
        LOG_F(INFO, "Local server signal connected to socket");
    });
    list = new SimpleLinkedList<MemoryNode>();
}

void LocalServer::send(const QString &msg)
{
    if(clientSocket){
        QTextStream T(clientSocket);
        T << msg;
        clientSocket->flush();
        LOG_F(INFO, "Message sent to client");
    }
    else{
        LOG_F(INFO, "Send failed. No client connected");
    }
}

void LocalServer::send(const QJsonDocument &msg)
{
    if(clientSocket){
        //send a message to the server
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_7);
        // client writes a QString
        out << msg.toJson(QJsonDocument::Compact);
        out.device()->seek(0);
        clientSocket->write(block);
        clientSocket->flush();
        LOG_F(INFO, "Message sent to client");
    }
    else{
        LOG_F(INFO, "Send failed. No client connected");
    }
}

void LocalServer::read(){
    LOG_F(INFO, "Reading incoming message.");
    if(clientSocket->bytesAvailable() > 0){
        while (clientSocket->bytesAvailable() < (int)sizeof(quint32))
            clientSocket->waitForReadyRead();

        connect(clientSocket, SIGNAL(disconnected()),
                clientSocket, SLOT(deleteLater()));

        QDataStream in(clientSocket);
        in.setVersion(QDataStream::Qt_4_7);
        if (clientSocket->bytesAvailable() < (int)sizeof(quint16)) {
            return;
        }

        QByteArray buffer;
        auto length = (int)clientSocket->bytesAvailable();
        char temp [length];
        int test = in.readRawData (temp, length);
        buffer.append (temp, length);
        //Crea un json desde los datos recibidos y elimina los primero 4 bytes
        QJsonDocument receivedData = QJsonDocument::fromJson(buffer.remove(0,4));
        QString jsonString = receivedData.toJson(QJsonDocument::Compact);
        std::cout << "Read-LocalServer: Qstring from json: " << jsonString.toStdString() << std::endl;
        const char* logMsg = jsonString.toUtf8().constData();
        LOG_F(INFO, "%s", logMsg);


        QJsonObject json = receivedData.object();
        QJsonArray array = json["Contents"].toArray();
        if(json["Subject"] == "Total_Malloc")
            memoryAllocation(array[0].toObject().value("Value").toInt());
        else
            readMsg(json);
        //else if(json["Subject"] == "RAM_data")
            //send(getRAMdata());
    }
    else
        LOG_F(INFO, "No message to read.");
}

void LocalServer::memoryAllocation(int total) {
    memoryBlock = (char*)malloc(sizeof(char)*total);
    size_t size = malloc_usable_size(memoryBlock);;
    //Eliminar después
    const char* msg = (char)size + " bytes were allocated";
    LOG_F(INFO, msg);
    std::cout << "Malloc size: " << size << std::endl;
}

QJsonDocument LocalServer::getRAMdata() {
    QJsonDocument *json = new QJsonDocument();
    return *json;
}

void LocalServer::readMsg(QJsonObject &msg) {
    if(msg.contains("Variables")){
        QJsonArray array = msg["Variables"].toArray();
        for(int i = 0; i < array.size(); ++i){
            QJsonObject obj = array[i].toObject();

            MemoryNode memNode;

            std::string identifier = obj.value("Identifier").toString().toStdString();
            std::cout << "Identifier: " << identifier << std::endl;
            memNode.setIdentifier(identifier);

            std::string type = obj.value("Type").toString().toStdString();
            std::cout << "Type: " << type << std::endl;
            memNode.setType(type);

            std::string value = obj.value("Value").toString().toStdString();
            if(type == "int"){
                try {
                    //Posibles errores de punteros
                    int var = boost::lexical_cast<int>(value);

                    char* ptr_dir_var = &*(memoryBlock + getBytesToMove());
                    *ptr_dir_var = boost::lexical_cast<int>(value);

                    std::cout << "Value: " << var << std::endl;
                    memNode.setBegining(ptr_dir_var);

                } catch( boost::bad_lexical_cast const& ) {
                    std::cout << "Error: input string was not valid" << std::endl;
                }
            }else if (type == "float") {
                try {
                    //Posibles errores de punteros
                    float var = boost::lexical_cast<float>(value);

                    char *ptr_dir_var = &*(memoryBlock + getBytesToMove());
                    *ptr_dir_var = boost::lexical_cast<float>(value);

                    std::cout << "Value: " << var << std::endl;
                    memNode.setBegining(ptr_dir_var);

                } catch (boost::bad_lexical_cast const &) {
                    std::cout << "Error: input string was not valid" << std::endl;
                }

            } else if (type == "double") {
                try {
                    //Posibles errores de punteros
                    double var = boost::lexical_cast<double>(value);

                    char* ptr_dir_var = &*(memoryBlock + getBytesToMove());
                    *ptr_dir_var = boost::lexical_cast<double>(value);

                    std::cout << "Value: " << var << std::endl;
                    memNode.setBegining(ptr_dir_var);

                } catch( boost::bad_lexical_cast const& ) {
                    std::cout << "Error: input string was not valid" << std::endl;
                }

            } else if (type == "char") {
                try {
                    //Posibles errores de punteros
                    char var = boost::lexical_cast<char>(value);

                    char* ptr_dir_var = &*(memoryBlock + getBytesToMove());
                    *ptr_dir_var = boost::lexical_cast<char>(value);

                    std::cout << "Value: " << var << std::endl;
                    memNode.setBegining(ptr_dir_var);

                } catch( boost::bad_lexical_cast const& ) {
                    std::cout << "Error: input string was not valid" << std::endl;
                }

            } else if (type == "long") {
                try {
                    //Posibles errores de punteros
                    long var = boost::lexical_cast<long>(value);

                    char* ptr_dir_var = &*(memoryBlock + getBytesToMove());
                    *ptr_dir_var = boost::lexical_cast<long>(value);

                    std::cout << "Value: " << var << std::endl;
                    memNode.setBegining(ptr_dir_var);

                } catch( boost::bad_lexical_cast const& ) {
                    std::cout << "Error: input string was not valid" << std::endl;
                }

            } else if (type == "struct") {
                //Struct not ready
            }
        }

    } else if(msg.contains("Identifier")){
        MemoryNode memNode;

        std::string identifier = msg.value("Identifier").toString().toStdString();
        std::cout << "Identifier: " << identifier << std::endl;
        memNode.setIdentifier(identifier);

        std::string type = msg.value("Type").toString().toStdString();
        std::cout << "Type: " << type << std::endl;
        memNode.setType(type);

        std::string value = msg.value("Value").toString().toStdString();
        if(type == "int"){
            try {
                //Posibles errores de punteros
                int var = boost::lexical_cast<int>(value);

                char* ptr_dir_var = &*(memoryBlock + getBytesToMove());
                *ptr_dir_var = boost::lexical_cast<int>(value);

                std::cout << "Value: " << var << std::endl;
                memNode.setBegining(ptr_dir_var);

            } catch( boost::bad_lexical_cast const& ) {
                std::cout << "Error: input string was not valid" << std::endl;
            }
        }else if (type == "float") {
            try {
                //Posibles errores de punteros
                float var = boost::lexical_cast<float>(value);

                char *ptr_dir_var = &*(memoryBlock + getBytesToMove());
                *ptr_dir_var = boost::lexical_cast<float>(value);

                std::cout << "Value: " << var << std::endl;
                memNode.setBegining(ptr_dir_var);

            } catch (boost::bad_lexical_cast const &) {
                std::cout << "Error: input string was not valid" << std::endl;
            }

        } else if (type == "double") {
            try {
                //Posibles errores de punteros
                double var = boost::lexical_cast<double>(value);

                char* ptr_dir_var = &*(memoryBlock + getBytesToMove());
                *ptr_dir_var = boost::lexical_cast<double>(value);

                std::cout << "Value: " << var << std::endl;
                memNode.setBegining(ptr_dir_var);

            } catch( boost::bad_lexical_cast const& ) {
                std::cout << "Error: input string was not valid" << std::endl;
            }

        } else if (type == "char") {
            try {
                //Posibles errores de punteros
                char var = boost::lexical_cast<char>(value);

                char* ptr_dir_var = &*(memoryBlock + getBytesToMove());
                *ptr_dir_var = boost::lexical_cast<char>(value);

                std::cout << "Value: " << var << std::endl;
                memNode.setBegining(ptr_dir_var);

            } catch( boost::bad_lexical_cast const& ) {
                std::cout << "Error: input string was not valid" << std::endl;
            }

        } else if (type == "long") {
            try {
                //Posibles errores de punteros
                long var = boost::lexical_cast<long>(value);

                char* ptr_dir_var = &*(memoryBlock + getBytesToMove());
                *ptr_dir_var = boost::lexical_cast<long>(value);

                std::cout << "Value: " << var << std::endl;
                memNode.setBegining(ptr_dir_var);

            } catch( boost::bad_lexical_cast const& ) {
                std::cout << "Error: input string was not valid" << std::endl;
            }

        } else if (type == "struct") {
            //Struct not ready
        }
    }
}

size_t LocalServer::getBytesToMove() {
    size_t totalBytes = 0;
    if(list->getSize() != 0) {
        Node<MemoryNode> *temp = list->getHead();
        for (int i = 0; i < list->getSize(); ++i) {
            std::string type = temp->getData().getType();
            if (type == "int") {
                totalBytes += sizeof(int);
            } else if (type == "float") {
                totalBytes += sizeof(float);
            } else if (type == "double") {
                totalBytes += sizeof(double);
            } else if (type == "char") {
                totalBytes += sizeof(char);
            } else if (type == "long") {
                totalBytes += sizeof(long);
            } else if (type == "struct") {

            }
            temp = temp->getNext();
        }
    }
    return totalBytes;
}
/*{"Identifier":"a","Scope":0,"Type":"int","Value":"1*(2+7)"}
{"Variables":[{"Identifier":"b","Scope":0,"Type":"int","Value":"0"}]}*/


