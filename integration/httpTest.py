import unittest
import requests
import json

from user import User

URLbase = "http://..../"

class MyTestCase(unittest.TestCase):
    def __init__(self):
        self.anUser = User("elpedro@gmail.com",
                           "1234",
                           "Pedro",
                           32,
                           "M",
                           "pedrin",
                           "www.image.com",
                           {'latitude': 12, 'longitude': 21},
                           {'category': "music", 'value': "los redondos"})

    def test_status_POSTauth(self):
        cabeceras = {
            "Content-Type": "application/json"
        }

        response = requests.post(URLbase + "auth", data=json.dumps(self.anUser.loginData), headers=cabeceras)
        results = response.json()
        self.anUser.setToken(results["response"]["token"])

        self.assertEqual(results["status"], 101)

    def test_status_PUTauth(self):
        cabeceras = {
            "Content-Type": "application/json"
        }

        response = requests.put(URLbase + "auth", data=json.dumps(self.anUser.loginData), headers=cabeceras)
        results = response.json()

        self.assertEqual(results["response"]["token"], self.anUser.token)
        self.assertEqual(results["status"], 200)

    def test_GETuser(self):
        cabeceras = {
            "Content-Type": "application/json",
            "SECURITY-TOKEN": self.anUser.token
        }

        response = requests.get(URLbase + self.anUser.email, headers=cabeceras)
        results = response.json()

        self.assertEqual(results["user"], "elpedro@gmail.com")
        self.assertEqual(results["password"], "1234")

    def test_POSTuser(self):
        cabeceras = {
            "Content-Type": "application/json",
            "SECURITY-TOKEN": self.anUser.token
        }

        responsePOST = requests.post(URLbase + self.anUser.email, data=json.dumps(self.anUser.profileData), headers=cabeceras)

        responseGET = requests.get(URLbase + self.anUser.email, headers=cabeceras)

        results = responseGET.json()
        self.assertEqual(results["name"], "Pedro")
        self.assertEqual(results["age"], "32")
        self.assertEqual(results["sex"], "M")
        self.assertEqual(results["alias"], "pedrin")


if __name__ == '__main__':
    unittest.main()