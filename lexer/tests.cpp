#include "Scanner.h"
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>


void parseStream(std::istream& input, std::ostream& out) {
    MyScanner lexer;
    lexer.switch_streams(input, out);    // По-умолчанию чтение из std::cin
    while (lexer.yylex() != Tokens::T_EOF) {
    }
}


int getdir (std::string dir, std::vector<std::string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        std::cout << "Error(" << errno << ") opening " << dir << std::endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(std::string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

int main()
{
	std::filebuf fboutput;
	fboutput.open("test.txt", std::ios::out);
	std::ostream isout(&fboutput);
    std::string dir = std::string("Samples");
    std::vector<std::string> files = std::vector<std::string>();

    getdir(dir,files);

    for (unsigned int i = 0; i < files.size(); i++) {
		if (files[i] != "." && files[i] != "..") {
			std::cout << files[i] << std::endl;
			std::filebuf fb;
			std::ifstream out(files[i]);
			if (fb.open("Samples/"+files[i], std::ios::in))
			{
				std::istream is(&fb);
				parseStream(is, isout);
				fb.close();
			}
			out.close();
		}
		
    }
	fboutput.close();
	//parseStream(std::cin);
    return 0;
}
