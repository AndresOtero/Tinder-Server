import requests
import json

URLbase = "http://localhost:8000/"

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

    def addInterest(self, interest):
        self.interests.append(interest)

    def removeInterest(self, interestToRemove):
        self.interests.remove(interestToRemove)

    def registerAndLogin(self):
        response = requests.post(URLbase + "auth", data=json.dumps(self.loginData), headers=self.cabeceras)
        try:
            results = response.json()
            self.securityToken = results["response"]["token"]
        except (ValueError, TypeError):
            print "Error with register user: ", response
        
        return response

    def login(self):
        response = requests.put(URLbase + "auth", data=json.dumps(self.loginData), headers=self.cabeceras)
        try:
            results = response.json()
            self.securityToken = results["response"]["token"];
        except (ValueError, TypeError):
            print "Error with login response: ", response
        return response

    def unregister(self):
        try:
            data = {'password': self.loginData['password']}
            response = requests.delete(URLbase + "auth", data=json.dumps(data), headers=self.getSecureadHeaders())
            results = response.json()
        except (ValueError, TypeError):
            print "Error with delete response: ", response
        return response

    def saveProfile(self):
        response = requests.post(URLbase + "user", data=json.dumps(self.profileData), headers=self.getSecureadHeaders())
        try:
            results = response.json()
        except (ValueError, TypeError):
            print "Error with saveProfle response: ", response
        return response

    def reloadProfile(self):
        print ("recargando")

    def updateLocation(self):
        print ("recalculando location")

    def doMatch(self):
        print("haciendo match")

    def getAvailableInterests(self):
        print ("obteniendo lista de intereses")

    def getSecureadHeaders(self):
        return {"Content-Type": "application/json", "SECURITY-TOKEN": self.securityToken}
