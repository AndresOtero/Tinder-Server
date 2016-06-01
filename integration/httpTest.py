import unittest
import requests
import json

from user import User

URLbase = "http://localhost:8000/"

class MyTestCase(unittest.TestCase):

    def setUp(self):
        self.user1 = User("elpedro@gmail.com",
                       "1234",
                       "Pedro",
                       32,
                       "M",
                       "pedrin",
                       "www.image.com",
                       {'latitude': 12, 'longitude': 21},
                       [{'category': "Comida", 'value': "Pizza"}])
        
        self.user2 = User("lajulia@gmail.com",
                  "12345",
                  "Julia",
                  32,
                  "F",
                  "juli",
                  "www.image2.com",
                  {'latitude': 12, 'longitude': 21},
                  [{'category': "Comida", 'value': "Milanesa"}])

        self.user1.registerAndLogin()
        self.user1.saveProfile()
        self.user2.registerAndLogin()

    def tearDown(self):
        self.user1.unregister()
        self.user2.unregister()

    def doLoginInexistentUser(self):
        inexistentUser = User("inexistentIntegration@gmail.com",
                  "12345",
                  "Julia",
                  32,
                  "F",
                  "juli",
                  "www.image2.com",
                  {'latitude': 12, 'longitude': 21},
                  [{'category': "Comida", 'value': "Milanesa"}])

        response = inexistentUser.login()
        self.assertEqual(response.status_code, 401)

    def doLogin(self):
        response = self.user2.login()
        self.assertEqual(response.status_code, 200)        

    def registerUserAlreadyExistent(self):
        response = self.user1.registerAndLogin()
        self.assertEqual(response.status_code, 400)        

    def updateUser(self):
        s

    def test_POSTuser(self):
        response = requests.post(URLbase + "user", data=json.dumps(self.anUser.profileData), headers=self.cabeceras[1])
        results = response.json()

        self.assertEqual(results["status"], 200)

    def test_CheckUserProfile(self):
        responseGET = requests.get(URLbase + "user", headers=self.cabeceras[1])
        results = responseGET.json()

        self.assertEqual(results["name"], "Pedro")
        self.assertEqual(results["age"], "32")
        self.assertEqual(results["sex"], "M")
        self.assertEqual(results["alias"], "pedrin")
        self.assertEqual(results["email"], "elpedro@gmail.com")
        self.assertEqual(results["photo_profile"], "")
        self.assertEqual(results["location"], {'latitude': 12, 'longitude': 21})
        self.assertEqual(results["interests"], [{'category': "music", 'value': "los redondos"}])
        self.assertEqual(results["status"], 200)

    def test_UpdateLocation(self):
        self.anUser.location = {'latitude': 45, 'longitude': 54} #update location
        response = requests.post(URLbase + "location", data=json.dumps(self.anUser.location), headers=self.cabeceras[1])
        results = response.json()

        self.assertEqual(results["status"], 200)

    def test_CheckLocationUpdated(self):
        responseGET = requests.get(URLbase + "user", headers=self.cabeceras)
        results = responseGET.json()
        self.assertEqual(results["location"], self.anUser.location)

    def test_UpdateInterests(self):
        self.anUser.addInterest({'category': "Comida", 'value': "Asado"})
        response = requests.post(URLbase + "interest", data=json.dumps({'interests': self.anUser.interests}), headers=self.cabeceras[1])
        results = response.json()

        self.assertEqual(results["status"], 200)

    def test_DeleteInterest(self):
        interestToRemove = {'category': "Comida", 'value': "Asado"}

        self.anUser.removeInterest(interestToRemove)
        response = requests.delete(URLbase + "interest", data=json.dumps(interestToRemove), headers=self.cabeceras[1])
        results = response.json()

        self.assertEqual(results["status"], 200)

    def test_CheckInterestsRemoved(self):
        responseGET = requests.get(URLbase + "interest", headers=self.cabeceras[1])
        results = responseGET.json()

        self.assertEqual(results["interests"], self.anUser.interests)

    def test_likeUser(self):
        userToLike = {
            'user': "luly_salazar@gmail.com",
        }
        requests.post(URLbase + "auth", data=json.dumps(userToLike), headers=self.cabeceras[1])

        response = requests.post(URLbase + "like", data=json.dumps({'likedUser': "luly_salazar@gmail.com"}), headers=self.cabeceras[1])
        results = response.json()

        self.assertEqual(results["status"], 200)

    def test_CheckUsersLiked(self):
        responseGET = requests.get(URLbase + "like", headers=self.cabeceras[1])
        results = responseGET.json()
        candidates = results["response"]["candidates"]

        self.assertEqual(candidates, [{"luly_salazar@gmail.com"}])
        self.assertEqual(results["status"], 200)

    def test_matching(self):
        response = requests.post(URLbase + "auth", data=json.dumps(self.user2.loginData), headers=self.cabeceras[0])
        results = response.json()

        securityToken = results["response"]["token"]
        self.user2.setToken(securityToken)
        self.updateCabeceras(securityToken)

        requests.post(URLbase + "like", data=json.dumps({'likedUser': "elpedro@gmail.com"}),headers=self.cabeceras[2])#Julia da like a Pedro

        requests.post(URLbase + "like", data=json.dumps({'likedUser': "lajulia@gmail.com"}),headers=self.cabeceras[1])#Pedro da like a Julia
        responseGET = requests.get(URLbase + "match", headers=self.cabeceras[1])
        results = responseGET.json()
        candidatesMatch = results["response"]["candidates"]

        self.assertEqual(candidatesMatch, [{"lajulia@gmail.com"}])
        self.assertEqual(results["status"], 200)



if __name__ == '__main__':
    unittest.main()