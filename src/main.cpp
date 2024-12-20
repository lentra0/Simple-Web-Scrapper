#include "scraper.h"
#include <iostream>

int main() {
    try {

        std::string url;

        std::cout << "Enter URL: ";
        std::cin >> url;

        const std::string outputFile = "scraper.txt";


        std::cout << "Downloading page: " << url << std::endl;
        const std::string html = Scraper::fetchHTML(url);


        std::cout << "Parsing HTML and saving links..." << std::endl;
        Scraper::parseHTML(html, outputFile);

        std::cout << "Done!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
