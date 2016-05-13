import unittest
import requests
import json

class MyTestCase(unittest.TestCase):
    def test_status_POSTauth(self):
        loginData = {
            'user': "elpedro@gmail.com",
            'password': "pedrin"
        }
        cabeceras = {
            "Content-Type": "application/json"
        }

        url = "http://..../auth"
        response = requests.post(url, data=json.dumps(loginData), headers=cabeceras)
        results = response.json()
        self.assertEqual(results["status"], 101)

    def test_status_PUTauth(self):
        loginData = {
            'user': "elpedro@gmail.com",
            'password': "pedrin"
        }
        cabeceras = {
            "Content-Type": "application/json"
        }

        url = "http://..../auth"
        response = requests.put(url, data=json.dumps(loginData), headers=cabeceras)
        results = response.json()
        self.assertEqual(results["status"], 200)

    def test_GETuser(self):
        loginData = {
            'user': "elpedroo@gmail.com",
            'password': "pedriin"
        }
        cabeceras = {
            "Content-Type": "application/json"
        }

        urlAuth = "http://..../auth"
        requests.post(urlAuth, data=json.dumps(loginData), headers=cabeceras)

        urlUser = "http://..../user"
        response = requests.get(urlUser)
        results = response.json()

        self.assertEqual(results["user"], "elpedroo@gmail.com")
        self.assertEqual(results["password"], "pedriin")


if __name__ == '__main__':
    unittest.main()
