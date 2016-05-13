import unittest


class MyTestCase(unittest.TestCase):
    def test_login(self):
        loginData = {
            'user': {
                'email': "elpedro@gmail.com",
                'password': "pedrin"
            }
        }
        #hacer el pedido http
        self.assertEqual(True, True)


if __name__ == '__main__':
    unittest.main()
