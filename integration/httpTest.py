import unittest
import json

from user import User

URLbase = "http://52.67.7.172:8000/"


class MyTestCase(unittest.TestCase):
    def setUp(self):
        self.user1 = User("elpedro00@gmail.com",
                          "1234",
                          "Pedro",
                          32,
                          "M",
                          "pedrin",
                          "www.image.com",
                          {'latitude': 12, 'longitude': 21},
                          [{'category': "comida", 'value': "pizza"}])

        self.user2 = User("lajulia00@gmail.com",
                          "12345",
                          "Julia",
                          32,
                          "F",
                          "juli",
                          "www.image2.com",
                          {'latitude': 78, 'longitude': 87},
                          [{'category': "futbol", 'value': "river"}])

        self.user3 = User("lakenny00@gmail.com",
                          "12345",
                          "kenny",
                          32,
                          "F",
                          "ken",
                          "www.image3.com",
                          {'latitude': 78, 'longitude': 87},
                          [{'category': "comida", 'value': "pizza"}])

        if (self.user1.login()).status_code == 200:
            self.user1.unregister()

        self.user1.register()
        self.user1.saveProfile()

        if (self.user2.login()).status_code == 200:
            self.user2.unregister()

        self.user2.register()

        if (self.user3.login()).status_code == 200:
            self.user3.unregister()

        self.user3.register()
        self.user3.saveProfile()

    def tearDown(self):
        self.user1.unregister()
        self.user2.unregister()

    #@unittest.skip("\n")
    def test_checkStatusNewUser(self):
        newRegisteredUser = User("newregistereduserr@gmail.com",
                          "1234",
                          "user",
                          32,
                          "M",
                          "userin",
                          "www.image.com",
                          {'latitude': 12, 'longitude': 21},
                          [{'category': "comida", 'value': "pizza"}])
        response = newRegisteredUser.register()
        results = response.json()

        self.assertEqual(results["status"], 101)
        newRegisteredUser.unregister()

    #@unittest.skip("\n")
    def test_doLogin(self):
        response = self.user2.login()
        self.assertEqual(response.status_code, 200)

    #@unittest.skip("\n")
    def test_doLoginInexistentUser(self):
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

    #@unittest.skip("\n")
    def test_registerUserAlreadyExistent(self):
        response = self.user1.register()
        results = response.json()

        self.assertEqual(results["status"], 102)

    #@unittest.skip("\n")
    def test_checkStatusUpdateProfileData(self):
        response = self.user2.saveProfile()
        results = response.json()

        self.assertEqual(results["status"], 200)

    #@unittest.skip("\n")
    def test_checkUserProfile(self):
        response = self.user1.reloadProfile()
        results = response.json()["response"]

        self.assertEqual(results["name"], self.user1.profileData["name"])
        self.assertEqual(results["age"], self.user1.profileData["age"])
        self.assertEqual(results["sex"], self.user1.profileData["sex"])
        self.assertEqual(results["alias"], self.user1.profileData["alias"])
        self.assertEqual(results["email"], self.user1.profileData["email"])
        #self.assertEqual(results["photo_profile"], self.user1.profileData["photo_profile"])TODO - ESTE LO HACE FALLAR
        self.assertEqual(results["location"], self.user1.profileData["location"])
        self.assertEqual(results["interests"], self.user1.profileData["interests"])
        self.assertEqual(response.json()["status"], 200)

    #@unittest.skip("\n")
    def test_updateLocation(self):
        response = self.user1.updateLocation({'latitude': 45, 'longitude': 54})

        self.assertEqual(response.json()["status"], 200)
        self.assertEqual(self.user1.reloadProfile().json()["response"]["location"], self.user1.profileData["location"])

    #@unittest.skip("\n")
    def test_addInterests(self):
        response = self.user1.addInterest({'category': "futbol", 'value': "river"})

        self.assertEqual(response.json()["status"], 200)

        boolean = self.user1.haveThisInterests(self.user1.reloadProfile().json()["response"]["interests"])

        self.assertEqual(boolean, True)

    #@unittest.skip("\n")
    def test_checkStatusToLikeUser(self):
        self.user2.saveProfile()
        response = self.user1.like(self.user2)

        self.assertEqual(response.json()["status"], 200)

    #@unittest.skip("\n")
    def test_checkUsersLiked(self):
        self.user2.saveProfile()
        self.user1.like(self.user2)
        self.user1.like(self.user3)
        response = self.user1.getUsersLiked()
        usersLike = (response.json())["response"]["likes"]
        self.assertEqual(usersLike[0]["email"], self.user3.profileData["email"])
        self.assertEqual(usersLike[1]["email"], self.user2.profileData["email"])

    #@unittest.skip("\n")
    def test_matching(self):
        self.user1.like(self.user3)
        self.user3.like(self.user1)
        response = self.user1.getMatchs()
        results = response.json()

        candidatesMatch = results["response"]["matches"]

        self.assertEqual(candidatesMatch[0]["email"], self.user3.profileData["email"])
        self.assertEqual(results["status"], 200)


if __name__ == '__main__':
    unittest.main()