#include "Encrypt.h"
using namespace std;


//Encryprts string using characters between 32 - 126
string cryptTools::Encrypt(string str, char mask[]) 
{
    int i;
    unsigned int x, y;
    for (i = 0; i < str.length(); i++)    {
        x = str[i];
        y = (mask[i] + 950);
        if (x < 32 || x > 126)
            x = 0;
        else
            x -= 32;
        x = (x + y) % 95;
        str[i] = char(x + 32);
    }
    return str;
}

//Decrypts string using characters between 32 - 126
string cryptTools::Decrypt(string str, char mask[])
{
    int i;
    unsigned int x, y;
    for (i = 0; i < str.length(); i++)    {
        x = str[i];
        y = mask[i];
        if (x < 32 || x > 126)
            x = 0;
        else
            x -= 32;
        x = (x - y + 190) % 95;
        str[i] = char(x + 32);
    }
    return str;
}

string cryptTools::Encrypt(string str, string maskLoc, int offset, int messageNumber)
{
    char mask[str.length()];
    ifstream file;
    file.open(maskLoc.c_str(), ios::in | ios::binary);
    file.seekg(offset);
    file.read(mask, str.length());
    file.close();
    str = Encrypt(str, mask);
    
    string newStr;
    stringstream stream;
    stream << messageNumber;
   // while (stream.str().length() < 4)    {
  //      string temp = stream.str();
  //      temp.insert(0, "0");
  //      stream.clear();
 //       stream << temp;
 //   }
    newStr = stream.str();
    for (int n = newStr.length(); n < 4; n++)
        newStr.insert(0, "0");
    
    for (int i = 0; i < str.length(); i++)    {
        stringstream stream;
        stream << int(str[i] - 32);
        string temp = stream.str();
        if (temp.length() < 2)
            temp.insert(0, "0");
        newStr += temp;
    }
    return newStr;
    
}

//Encrypts string using characters between 32 - 126. Offset is in first two characters of string
string cryptTools::Decrypt(string str, string maskLoc, int baseOffset, int incrementalStep)
{
    stringstream stream;
    stream << str.substr(0, 4);
    int messageNumber;
    stream >> messageNumber;
    int offset = baseOffset + messageNumber*incrementalStep;
    str.erase(0, 4);
    char mask[str.length()/2];
    ifstream file;
    file.open(maskLoc.c_str(), ios::in | ios::binary);
    file.seekg(offset);
    file.read(mask, str.length()/2);
    file.close();
    
    string newStr;
    for (int i = 0; i < str.length(); i += 2)    {
        newStr +=  char((str[i] - '0')*10 + (str[i+1] - '0') + 32);
    } 
    str = Decrypt(newStr, mask);
    
    
    return str;
    
}




void cryptTools::Encrypt(char str[], int n, char mask[])
{
    int i;
    unsigned int x, y;
    for (i = 0; i < n; i++)    {
        x = (unsigned char)str[i];
        y = (unsigned char)mask[i];
        str[i] = (x + y) % 256;

    }
}

void cryptTools::Decrypt(char str[], int n, char mask[])
{
    int i;
    unsigned int x, y;
    for (i = 0; i < n; i++)    {
        x = (unsigned char)str[i];
        y = (unsigned char)mask[i];
        str[i] = (x - y + 256) % 256;
    }
}

int cryptTools::EncryptFile(string fileLoc, string maskLoc, int messageNumber, int offset, string outputFileLoc)
{   
    ifstream infile; 
    infile.open(fileLoc.c_str(), ios::in | ios::ate | ios::binary);
    int length = infile.tellg();
    infile.seekg(ios::beg);
    char str[length];
    char mask[length];
    infile.read(str, length);
    infile.close();
    ifstream file;
    file.open(maskLoc.c_str(), ios::in | ios::ate | ios::binary);

    file.seekg(offset);
    file.read(mask, length);
    file.close();
    Encrypt(str, length, mask);
    ofstream outfile;
    outfile.open(outputFileLoc.c_str(), ios::out | ios::binary);
    outfile.write((char*)&messageNumber, sizeof(int));
    outfile.write(str, length);
    outfile.close();
    
    
} 

int cryptTools::DecryptFile(string fileLoc, string maskLoc, int baseOffset, int incrementalStep, string outputFileLoc)
{
    fstream file;
    int messageNumber;
    file.open(fileLoc.c_str(), ios::in | ios::ate | ios::binary);
    int length = int(file.tellg()) - sizeof(int);
    file.seekg(ios::beg);
    file.read((char*)&messageNumber, sizeof(int));
    int offset = baseOffset + messageNumber*incrementalStep;
    char str[length];
    char mask[length];
    file.read(str, length);
    file.close();
    ifstream maskFile;
    maskFile.open(maskLoc.c_str(), ios::in | ios::ate | ios::binary);

    maskFile.seekg(offset);
    maskFile.read(mask, length);
    maskFile.close();
    Decrypt(str, length, mask);
    ofstream outFile;
    outFile.open(outputFileLoc.c_str(), ios::out | ios::binary);
    outFile.write(str, length);
    outFile.close();
    
} 
