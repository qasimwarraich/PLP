#include <fstream>
#include <iostream>
#include <curl/curl.h>
#include <tinyxml2.h>



void xml_parse()
{
    using namespace tinyxml2;

    XMLDocument doc;
    doc.LoadFile("books.xml");
    XMLElement *pRoot = doc.FirstChildElement("bookstore");
    XMLElement *pBook = pRoot->FirstChildElement("book");
    XMLElement *pYear = pBook->FirstChildElement("price");
    std::cout << pYear->GetText() << '\n';

    int count = 0; 
    float totalprice = 0; 
    for (XMLElement* e = pRoot->FirstChildElement("book"); e != NULL; e = e->NextSiblingElement("book")) {
        XMLElement* pPrice = e->FirstChildElement("price");
        totalprice += atof(pPrice->GetText());
        count ++;
    }
    std::cout << "Number of books: " << count << '\n';
    std::cout << "Total Price: " << totalprice << '\n';
}

size_t curl_writing_callback(void *ptr, size_t size, size_t nmemb, void *vstring)
{
    std::string * pstring = (std::string*)vstring;
    pstring->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

std::string curl_url_to_file(const std::string & url)
{
    std::string output;
    std::ofstream outputfile;

    CURL *curl_handle;
    curl_global_init(CURL_GLOBAL_ALL);
    curl_handle = curl_easy_init();
    curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, curl_writing_callback);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &output);
    curl_easy_perform(curl_handle); 
    curl_easy_cleanup(curl_handle);


    outputfile.open("books.xml");
    outputfile << output;
    outputfile.close();

    return output;
}

int main()
{
    curl_url_to_file("https://www.w3schools.com/xml/books.xml");
    xml_parse();

    return 0;
}
