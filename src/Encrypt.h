#ifndef ENCRYPT_H
#define ENCRYPT_H

#include <fstream>
#include <sstream>

namespace cryptTools {

std::string Encrypt(std::string str, char mask[]);
std::string Decrypt(std::string str, char mask[]);
std::string Encrypt(std::string str, std::string maskLoc, int offset, int messageNumber);
std::string Decrypt(std::string str, std::string maskLoc, int baseOffset, int incrementalStep);
void Encrypt(char str[], int n, char mask[]);
void Decrypt(char str[], int n, char mask[]);
int EncryptFile(std::string fileLoc, std::string maskLoc, int messageNumber, int offset, std::string outputFileLoc);
int DecryptFile(std::string fileLoc, std::string maskLoc, int baseOffset, int incrementalStep, std::string outputFileLoc);

}


#endif


