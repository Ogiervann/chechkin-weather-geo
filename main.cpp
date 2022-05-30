#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
#include <iostream>
#include <string>
#include <map>


int main(){
  httplib::Client ipCli("https://whatsmyip.dev");

  //httplib::Request req("/ip");

  auto res = ipCli.Get("/api/ip");
  std::string ip;
  std::istringstream f(res->body);
  std::getline(f, ip, ',');
  ip.erase(0, 9);
  ip.erase(--ip.end());
  ip = '/' + ip;
  httplib::Client geoCli("https://json.geoiplookup.io");

  res = geoCli.Get(ip.c_str());

  //std::cout << res->body << "\n";

  std::istringstream g(res->body);
  std::string line;
  std::string latitude;
  std::string longitude;
  while(std::getline(g, line)){
    std::istringstream l(line);
    std::string result;

    if(std::getline(l, result, ':')){
      //std::cout << result << std::endl;
      if(result == "    \"latitude\""){
        std::getline(l, latitude, ' ');
        std::getline(l, latitude);
      }
      if(result == "    \"longitude\""){
        std::getline(l, longitude, ' ');
        std::getline(l, longitude);
      }
    }
  }

  latitude.erase(--(--(--latitude.end())), latitude.end());
  longitude.erase(--(--(--longitude.end())), longitude.end());

  std::cout << latitude << ' ' << longitude << std::endl;

  httplib::Client weatherCli("https://api.openweathermap.org");

  std::string task = "/data/3.0/onecall?lat=" + latitude + "&lon=" + longitude + "&units=metrix&exclude=current&appid=3c5d356723d2e5638a9938834df8734c";
  std::cout << task << std::endl;
  res = weatherCli.Get((task).c_str());
  std::cout << "here\n";
  std::cout << res->body << std::endl;

  return 0;
}
