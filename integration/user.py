import requests
import json

URLbase = "http://52.67.7.172:8000/"


class User:
    def __init__(self, email, password, n, age, s, alias, pp, l, i):
        self.cabeceras = {"Content-Type": "application/json"}
        self.loginData = {
            'user': email,
            'password': password
        }
        self.profileData = {
            'name': n,
            'age': age,
            'sex': s,
            'alias': alias,
            'photo_profile': pp,
            'email': email,
            'location': l,
            'interests': i
        }
        self.securityToken = ""

    def setToken(self, token):
        self.token = token

    def getSecureadHeaders(self):
        return {"Content-Type": "application/json", "SECURITY-TOKEN": self.securityToken}

    def register(self):
        response = requests.post(URLbase + "auth", data=json.dumps(self.loginData), headers=self.cabeceras)
        try:
            results = response.json()
            self.securityToken = results["response"]["token"]
        except (ValueError, TypeError):
            print ("Error with register user: ", response)

        return response

    def login(self):
        response = requests.put(URLbase + "auth", data=json.dumps(self.loginData), headers=self.cabeceras)
        try:
            results = response.json()
            self.securityToken = results["response"]["token"];
        except (ValueError, TypeError):
            print("Error with login response: ", response)
        return response

    def unregister(self):
        try:
            data = {'password': self.loginData['password']}
            response = requests.delete(URLbase + "auth", data=json.dumps(data), headers=self.getSecureadHeaders())
            results = response.json()
        except (ValueError, TypeError):
            print("Error with delete response: ", response)
        return response

    def saveProfile(self):
        response = requests.post(URLbase + "user", data=json.dumps(self.profileData), headers=self.getSecureadHeaders())
        try:
            results = response.json()
        except (ValueError, TypeError):
            print("Error with saveProfile response: ", response)
        return response

    def reloadProfile(self):
        try:
            responseGET = requests.get(URLbase + "user", headers=self.getSecureadHeaders())
            jsonResponse = responseGET.json()
            #self.profileData = jsonResponse
        except (ValueError, TypeError):
            print("Error with reloading profile response: ", responseGET)
        return responseGET

    def updateLocation(self, location):
        self.profileData["location"] = location
        response = requests.post(URLbase + "location", data=json.dumps(location), headers=self.getSecureadHeaders())
        try:
            results = response.json()
        except (ValueError, TypeError):
            print("Error with update location response: ", response)
        return response

    def addInterest(self, interest):
        self.profileData["interests"].append(interest)
        response = requests.post(URLbase + "interest", data=json.dumps({'interests': self.profileData["interests"]}),
                                 headers=self.getSecureadHeaders())
        try:
            results = response.json()
        except (ValueError, TypeError):
            print("Error with update interests response: ", response)
        return response

    def haveThisInterests(self, interests):
        if len(interests) != len(self.profileData["interests"]):
            return False
        else:
            haveThatInterests = True
            for interest in interests:
                if self.profileData["interests"].count(interest) == 0:
                    haveThatInterests = False
            return haveThatInterests

    def removeInterest(self, interestToRemove):
        self.profileData["interests"].remove(interestToRemove)
        response = requests.delete(URLbase + "interest", data=json.dumps(interestToRemove), headers=self.getSecureadHeaders())
        try:
            results = response.json()
        except (ValueError, TypeError):
            print("Error with delete interest response: ", response)
        return response

    def like(self, userToLike):
        response = requests.post(URLbase + "like", data=json.dumps({'likedUser': userToLike.profileData["email"]}),
                                 headers=self.getSecureadHeaders())
        try:
            results = response.json()
        except (ValueError, TypeError):
            print("Error with like user response: ", response)
        return response

    def getUsersLiked(self):
        responseGET = requests.get(URLbase + "like", headers=self.getSecureadHeaders())
        try:
            results = responseGET.json()
        except (ValueError, TypeError):
            print("Error with get users liked response: ", responseGET)
        return responseGET

    def getMatchs(self):
        responseGET = requests.get(URLbase + "match", headers=self.getSecureadHeaders())
        try:
            results = responseGET.json()
        except (ValueError, TypeError):
            print("Error with get matchs response: ", responseGET)
        return responseGET

    def getAvailableInterests(self):
        print("obteniendo lista de intereses")
