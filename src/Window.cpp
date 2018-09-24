#include "Window.h"
#include "Encrypt.h"
using namespace std;
using namespace cryptTools;

QString nameOfFile(QString loc)
{
     string str = loc.toStdString();
     int p;
     p = str.rfind("/");
     return QString(str.substr(p+1, str.length() - p -1).c_str());
}

Window::Window(QWidget *parent) : QMainWindow(parent)
{
    openMask = new QPushButton("Open Mask");
    connect(openMask, SIGNAL(clicked()), this, SLOT(getMaskLoc()));
    maskName = new QLabel("None");
    QHBoxLayout *maskLayout = new QHBoxLayout();
    maskLayout->addWidget(openMask);
    maskLayout->addWidget(maskName);
    QWidget *mask = new QWidget();
    mask->setLayout(maskLayout);
    
    baseOffset = new QSpinBox();
    baseOffset->setRange(0, 10000000);
    baseOffset->setValue(1000);
    incrementalStep = new QSpinBox();
    incrementalStep->setRange(0, 10000000);
    incrementalStep->setValue(50);
    messageNumber = new QSpinBox();
    messageNumber->setRange(0, 94*94);
    messageNumber->setValue(1);
    
    QFormLayout *periodicWidgetsLayout = new QFormLayout();
    periodicWidgetsLayout->addRow("Mask:", mask);
    periodicWidgetsLayout->addRow("Base Offset:", baseOffset);
    periodicWidgetsLayout->addRow("Incremental Step:", incrementalStep);
    periodicWidgetsLayout->addRow("Message Number:", messageNumber);
    QGroupBox *periodicWidgets = new QGroupBox();
    periodicWidgets->setLayout(periodicWidgetsLayout);
    
    chatHistory = new QTextEdit();
    chatHistory->setReadOnly(true);
    clearMessageButton = new QPushButton("Clear Last Message");
    connect(clearMessageButton, SIGNAL(clicked()), this, SLOT(clearLastMessage()));
    connect(chatHistory, SIGNAL(textChanged()), this, SLOT(scrollChatHistoryDown()));
    
    cryptBox = new QTextEdit();
    clearButton = new QPushButton("Clear");
    clearButton->setMaximumSize(100, 50);
    connect(clearButton, SIGNAL(clicked()), this, SLOT(clearCryptBox()));
    
    encryptButton = new QPushButton("Encrypt");
    connect(encryptButton, SIGNAL(clicked()), this, SLOT(encrypt()));
    decryptButton = new QPushButton("Decrypt");
    connect(decryptButton, SIGNAL(clicked()), this, SLOT(decrypt()));
    QHBoxLayout* cryptLayout = new QHBoxLayout();
    cryptLayout->addWidget(encryptButton);
    cryptLayout->addWidget(decryptButton);
    QWidget *crypt = new QWidget();
    crypt->setLayout(cryptLayout);
    
    QVBoxLayout *separatorLayout = new QVBoxLayout();
    separatorLayout->addSpacing(30);
    QWidget *separator = new QWidget();
    separator->setLayout(separatorLayout);
    
    QFormLayout* layout = new QFormLayout();
    layout->addRow("", periodicWidgets);
    layout->addRow("", separator);
    layout->addRow("Chat History:", chatHistory);
    layout->addRow("", clearMessageButton);
    layout->addRow("", separator);
    layout->addRow("Crypt Box:", cryptBox);
    layout->addRow("", clearButton);
    layout->addRow("", crypt);
   // layout->addRow("cryptBox:", cryptBox);
   
    QWidget *centralWidget = new QWidget();
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
    
    chatHistory->setEnabled(false);
    cryptBox->setEnabled(false);
    cryptBox->setEnabled(false);
    encryptButton->setEnabled(false);
    decryptButton->setEnabled(false);
    
    
    
    QMenuBar *menubar = new QMenuBar();
    
    QMenu *utilityMenu = menubar->addMenu("Utility");
    QAction *encryptAct = utilityMenu->addAction("Encrypt File");
    connect(encryptAct, SIGNAL(triggered()), this, SLOT(encryptFile()));
    QAction *decryptAct = utilityMenu->addAction("Decrypt File");
    connect(decryptAct, SIGNAL(triggered()), this, SLOT(decryptFile()));
    
    setMenuBar(menubar);
    
}

int Window::getOffset()
{
    return baseOffset->value() + messageNumber->value()*incrementalStep->value();
}

void Window::scrollChatHistoryDown()
{
    QScrollBar *scrollBar = chatHistory->verticalScrollBar();
    scrollBar->setSliderPosition(scrollBar->maximum());
}

void Window::getMaskLoc()
{
     QString fileName = QFileDialog::getOpenFileName(this, "Open Mask");
     if (fileName == NULL)
         return;
     maskName->setText(nameOfFile(fileName));
     maskLoc = fileName;
     
    chatHistory->setEnabled(true);
    cryptBox->setEnabled(true);
    cryptBox->setEnabled(true);
    encryptButton->setEnabled(true);
    decryptButton->setEnabled(true);
}

void Window::clearCryptBox()
{
    cryptBox->clear();
}

void Window::clearLastMessage()
{
    string str = chatHistory->toHtml().toStdString();
    int p = str.rfind('\n');
    p = str.rfind('\n', p);
    chatHistory->setHtml(QString(str.substr(0, p).c_str()));
}

void Window::encrypt()
{
    int offset = getOffset();
  //  chatHistory->setText(chatHistory->toPlainText() + "Us: " + cryptBox->toPlainText() + "\n");
    chatHistory->setHtml(chatHistory->toHtml() + "<font color='red'>Us: " + cryptBox->toPlainText() + "</font> \n");
    string str = Encrypt(cryptBox->toPlainText().toStdString(), maskLoc.toStdString(), offset, messageNumber->value());
    cryptBox->setText(QString(str.c_str()));
    messageNumber->setValue(messageNumber->value() + 1);
    
    scrollChatHistoryDown();
}

void Window::decrypt()
{
    string str = Decrypt(cryptBox->toPlainText().toStdString(), maskLoc.toStdString(), baseOffset->value(), incrementalStep->value());
    chatHistory->setHtml(chatHistory->toHtml() + "<font color='blue'>Them: " + QString(str.c_str()) + "</font>\n");
    
    scrollChatHistoryDown();
   // cryptBox->setText(QString(str.c_str()));
}

void Window::encryptFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File");
    if (fileName == NULL)
        return;
    string str = fileName.toStdString();
    EncryptFile(str, maskLoc.toStdString(), messageNumber->value(), getOffset(), str + ".enc");
    chatHistory->setHtml(chatHistory->toHtml() + "<font color='purple'>You sent " + nameOfFile(fileName) + " to them "  + "</font>\n");
    
    scrollChatHistoryDown();
    
}

void Window::decryptFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File");
    if (fileName == NULL)
        return;
    string str = fileName.toStdString();
    DecryptFile(str, maskLoc.toStdString(), baseOffset->value(), incrementalStep->value(), str.substr(0, str.length()-4));
    chatHistory->setHtml(chatHistory->toHtml() + "<font color='purple'>They sent " + nameOfFile(fileName) + " to you "  + "</font>\n");
    
    scrollChatHistoryDown();
}
