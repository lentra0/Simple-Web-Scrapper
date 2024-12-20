#ifndef SCRAPER_H
#define SCRAPER_H

#include <string>

class Scraper {
public:
    static std::string fetchHTML(const std::string& url);
    static void parseHTML(const std::string& html, const std::string& outputFile);
};

#endif
