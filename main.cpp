#include "json.hpp"
using json = nlohmann::json;
#include <fstream>   // std::ifstream (read files)
#include <iostream>  // std::cout, std::cerr
#include <string>    // std::string
#include <unordered_set>  // std::unordered_set
#include <stdexcept>  // std::runtime_error


std::unordered_set<std::string> getFollowers(const std::string& path){

    std::unordered_set<std::string> followers;
    std::ifstream f(path);
    if(!f.is_open()){
        throw std::runtime_error("Could not find file path: " + path);
    }

    json data;
    f >> data;

    if(data.is_array()){
        for(const auto& entry : data){
            if(entry.contains("string_list_data") && entry["string_list_data"].is_array() && !entry["string_list_data"].empty()){
               
                const auto& user = entry["string_list_data"][0];
                std::string username;

                if(user.contains("value")){
                    const auto& v = user["value"];
                    if(v.is_string()){
                        username = v.get<std::string>();
                    } 
                    else{
                        username = v.dump();
                    }
                }
                
                if (!username.empty()) followers.insert(username);
            }
        }
    }

    return followers;

}


int main() {
    
    
}