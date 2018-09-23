#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QFormLayout>
#include <QFileDialog>
#include <QGroupBox>
#include <QMenuBar>
#include <QScrollBar>

#include <string>
#include <fstream>
using namespace std;

class Window : public QMainWindow
{
   Q_OBJECT
   public:
       Window(QWidget* parent = 0);
   private slots:
       void getMaskLoc();
       void clearCryptBox();
       void clearLastMessage();
       void scrollChatHistoryDown();
       void encrypt();
       void decrypt();
       void encryptFile();
       void decryptFile();
   private:
       int getOffset();    
           
       QPushButton *openMask;
       QLabel *maskName;
       QSpinBox *baseOffset;
       QSpinBox *incrementalStep;
       QSpinBox *messageNumber;
       
       QPushButton *encryptButton;
       QPushButton *decryptButton;
      // QTextEdit *input;
      // QTextEdit *output;
       QTextEdit *cryptBox;
       QPushButton *clearButton;
       QPushButton *clearMessageButton;
       QTextEdit *chatHistory;
       
       QString maskLoc;
   
};

#endif
