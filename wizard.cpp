#include "dhramacon.h"
#include <iostream>


 int main(int argc, char* argv[])
 {
     if (argc < 2) {
         std::cerr << "Usage: " << argv[0] << " <PATH TO CSV>" << std::endl;
         return 1;
     }
     // Process folder
     std::string folderName = argv[1];
     // validate folder
     if(WIN32){
         if (folderName.find(":\\") == std::string::npos){
             std::string cwd = getCurrentWorkingDir();
             std::cout << "CWD: " << cwd << std::endl;
             folderName = cwd + "\\" + folderName;
         }
         if(!directoryExists(folderName)){
             std::cerr << "Folder " << folderName << " doesn't exists" << std::endl;
            return 1;
         }
     } else{
         if (not (folderName.rfind("/", 0) == 0)){
             std::string cwd = getCurrentWorkingDir();
             std::cout << "CWD: " << cwd << std::endl;
             folderName = cwd + "/" + folderName;
         }
         if(!directoryExists(folderName)){
             std::cerr << "Folder " << folderName << " doesn't exists" << std::endl;
             return 1;
         }
     }
     processFolder(folderName);
     return 0;
 }
