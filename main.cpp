#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
#include "json.hpp"
#include <iostream>
#include <map>
#include <string>

int main()
{
    httplib::Client ipCli("https://whatsmyip.dev");

    // httplib::Request req("/ip");
    // std::cout << "here\n";

    auto res = ipCli.Get("/api/ip");
    std::string ip;
    nlohmann::json j = nlohmann::json::parse(res->body);
    ip = j["addr"];
    ip = "/" + ip;
    httplib::Client geoCli("https://json.geoiplookup.io");

    res = geoCli.Get(ip.c_str());
    // std::cout << "here\n";

    j = nlohmann::json::parse(res->body);
    // std::cout << j;

    double temp;
    std::string latitude;
    temp = j["latitude"];
    latitude = std::to_string(temp);
    // std::cout << "here\n";
    std::string longitude;

    temp = j["longitude"];
    longitude = std::to_string(temp);
    // std::cout << "here\n";

    std::string city = j["city"];

    // std::cout << latitude << ' ' << longitude << std::endl;

    httplib::Client weatherCli("http://api.weatherapi.com");

    // std::string task = "/data/3.0/onecall?lat=" + latitude + "&lon=" +
    // longitude +
    // "&units=metrix&exclude=current&appid=bf10a33e451acf72727817b24caf5a11";
    std::string task =
        "/v1/current.json?key=9ec54f791e204282879130403223005&q=" + latitude +
        ',' + longitude;
    // std::cout << task << std::endl;
    res = weatherCli.Get((task).c_str());
    // std::cout << res << std::endl;

    j = nlohmann::json::parse(res->body);
    // std::cout << task << std::endl;

    std::cout << j["current"]["condition"]["text"] << std::endl;

    return 0;
}
