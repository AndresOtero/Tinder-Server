class User:
    def __init__(self, email, password, n, age, s, alias, pp, l, i):
        self.email = email
        self.password = password
        self.loginData = {
            'user': email,
            'password': password
        }

        self.name = n
        self.age = age
        self.sex = s
        self.alias = alias
        self.photo_profile = pp
        self.location = l
        self.interests = i
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


    def setToken(self, token):
        self.token = token

    def addInterest(self, interest):
        self.interests.append(interest)

    def removeInterest(self, interestToRemove):
        self.interests.remove(interestToRemove)