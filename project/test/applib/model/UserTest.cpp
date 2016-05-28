//
// Created by jonathan on 28/05/16.
//

#include <json/json.h>
#include <User.h>
#include "UserTest.h"


TEST_F(UserTest, buildInterests) {
    Json::Value int1;
    int1["category"] = "comida";
    int1["value"] = "pizza";
    Json::Value int2;
    int2["category"] = "comida";
    int2["value"] = "milanesas";
    Json::Value root;
    root.append(int1);
    root.append(int2);
    User user;
    list <Interest> interests = user.buildInterests(root);
    ASSERT_EQ(2, interests.size());
    bool firstFound = false;
    bool secondFound = false;
    for(list<Interest>::iterator it = interests.begin(); it != interests.end(); ++it) {
        firstFound = firstFound || ((*it).getCategory() == "comida" && (*it).getValue() =="pizza");
        secondFound = secondFound || ((*it).getCategory() == "comida" && (*it).getValue() == "milanesas");
    }

}


TEST_F(UserTest, toJson) {
    unordered_map<string, set<string>> interests;
    set<string> comida;
    comida.insert("pizza");
    interests["comida"] = comida;
    User user("id", "name", 1, "email", "sex", 2, "photo", interests, Location(3,4));
    const Json::Value values = user.toJson();
    ASSERT_EQ("id",values.get("id","").asString());
    ASSERT_EQ("name",values.get("name","").asString());
    ASSERT_EQ(1,values.get("externalId","").asInt());
    ASSERT_EQ("email",values.get("email","").asString());
    ASSERT_EQ("sex",values.get("sex","").asString());
    ASSERT_EQ("photo",values.get("photo_profile","").asString());
    Json::Value interestsJSON = values.get("interests", "");
    Json::Value::iterator iterator = interestsJSON.begin();
    for (; iterator != interestsJSON.end() ; ++iterator) {
        ASSERT_EQ((*iterator).get("category",""),"comida");
        ASSERT_EQ((*iterator).get("value",""),"pizza");

    }
    
}