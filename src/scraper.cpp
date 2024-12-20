#include "scraper.h"
#include <fstream>
#include <gumbo.h>
#include <iostream>
#include <stdexcept>
#include <curl/curl.h>


size_t WriteCallback(void* contents, const size_t size, size_t nmemb, std::string* userp) {
    userp->append(static_cast<char *>(contents), size * nmemb);
    return size * nmemb;
}


std::string Scraper::fetchHTML(const std::string& url) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        throw std::runtime_error("Failed to initialize cURL");
    }

    std::string response;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    if (const CURLcode res = curl_easy_perform(curl); res != CURLE_OK) {
        curl_easy_cleanup(curl);
        throw std::runtime_error("cURL request failed: " + std::string(curl_easy_strerror(res)));
    }

    curl_easy_cleanup(curl);
    return response;
}


void searchForLinks(const GumboNode *node, std::ofstream &outFile) {
    if (node->type != GUMBO_NODE_ELEMENT) return;

    if (node->v.element.tag == GUMBO_TAG_A) {
        if (const GumboAttribute* href = gumbo_get_attribute(&node->v.element.attributes, "href")) {
            outFile << href->value << std::endl;
        }
    }

    const GumboVector* children = &node->v.element.children;
    for (unsigned int i = 0; i < children->length; ++i) {
        searchForLinks(static_cast<GumboNode*>(children->data[i]), outFile);
    }
}


void Scraper::parseHTML(const std::string& html, const std::string& outputFile) {
    GumboOutput* output = gumbo_parse(html.c_str());

    std::ofstream outFile(outputFile);
    if (!outFile) {
        gumbo_destroy_output(&kGumboDefaultOptions, output);
        throw std::runtime_error("Unable to open file for writing");
    }

    searchForLinks(output->root, outFile);

    gumbo_destroy_output(&kGumboDefaultOptions, output);
    std::cout << "Data saved to " << outputFile << std::endl;
}
