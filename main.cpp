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
            else {
                throw std::runtime_error("Error parsing file. Unexpected JSON structure.");
            }

        }
    }
    else{
        throw std::runtime_error("Error parsing file. Unexpected JSON structure.");
    }

    return followers;

}

std::unordered_set<std::string> getFollowing(const std::string& path){

    std::unordered_set<std::string> following;
    std::ifstream f(path);
    if(!f.is_open()){
        throw std::runtime_error("Could not find file path: " + path);
    }

    json data;
    f >> data;

    if(data.is_object() && data.contains("relationships_following") && data["relationships_following"].is_array()){

        for(const auto& entry : data["relationships_following"]){

            if(entry.is_object() && entry.contains("title") && entry["title"].is_string()){
            
                std::string username = entry["title"].get<std::string>();

                if (!username.empty()) following.insert(username);

            }
        }
    }
    else{
        throw std::runtime_error("Error parsing file. Unexpected JSON structure.");
    }

    return following;

}

std::unordered_set<std::string> checkNotFollowingBack(const std::unordered_set<std::string> followers, const std::unordered_set<std::string> following){
    std::unordered_set<std::string> notFollowingBack;

    for (const auto& name : following) {
        if (followers.count(name) == 0) {
            notFollowingBack.insert(name);
        }
    }

    return notFollowingBack;
}

// run clang++ -std=c++17 -O2 -Wall -Wextra main.cpp -o followers 
// ./followers
// followers: /Users/samarth/Downloads/instagram-samarth212_-2025-12-26-jZEkw3FI/connections/followers_and_following/followers_1.json
// following: /Users/samarth/Downloads/instagram-samarth212_-2025-12-26-jZEkw3FI/connections/followers_and_following/following.json

int main() {

    std::string followersPath;
    std::string followingPath;
   
    std::cout << "File path of followers.json:";
    std::cin >> followersPath;
    std::cout << "File path of following.json:";
    std::cin >> followingPath;
    

    std::unordered_set<std::string> followers = getFollowers(followersPath);
    std::unordered_set<std::string> following = getFollowing(followingPath);


    std::unordered_set<std::string> usersNotFollowingBack = checkNotFollowingBack(followers, following);
    for(const std::string& user : usersNotFollowingBack){
        std::cout << user << "\n";
    }

    return 0; 
}